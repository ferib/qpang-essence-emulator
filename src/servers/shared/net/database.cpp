#include "database.hpp"
#include <errmsg.h>

Database::Database()
{
	//_logger = new Logger("Database");
	_mysqlClient = mysql_init(NULL);

	Connect();
}

Database::~Database()
{
	//
}

bool Database::Connect()
{
	bool result = mysql_real_connect(_mysqlClient, DB_HOST, DB_USER, DB_PASS, DB_NAME, DB_PORT, NULL, 0);
	if (!result)
	{
		//_logger->Exception("Could not connect");
		return false;
	}
	return true;
}

void Database::Close()
{
	mysql_close(_mysqlClient);
	this->~Database();
}

bool Database::beginTransaction()
{
	if (!executeQuery("BEGIN")) {
		return false;
	}

	databaseLock.lock();
	return true;
}

bool Database::rollback()
{
	if (mysql_rollback(_mysqlClient) != 0) {
		std::cout << "[Error - mysql_rollback] Message: " << mysql_error(_mysqlClient) << std::endl;
		databaseLock.unlock();
		return false;
	}

	databaseLock.unlock();
	return true;
}

bool Database::commit()
{
	if (mysql_commit(_mysqlClient) != 0) {
		std::cout << "[Error - mysql_commit] Message: " << mysql_error(_mysqlClient) << std::endl;
		databaseLock.unlock();
		return false;
	}

	databaseLock.unlock();
	return true;
}

bool Database::executeQuery(const std::string& query)
{
	bool success = true;

	// executes the query
	databaseLock.lock();

	while (mysql_real_query(_mysqlClient, query.c_str(), query.length()) != 0) {
		//_logger->Exception(mysql_error(_mysqlClient));
		auto error = mysql_errno(_mysqlClient);
		if (error != CR_SERVER_LOST && error != CR_SERVER_GONE_ERROR && error != CR_CONN_HOST_ERROR && error != 1053/*ER_SERVER_SHUTDOWN*/ && error != CR_CONNECTION_ERROR) {
			databaseLock.unlock();
			return false;
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	MYSQL_RES* m_res = mysql_store_result(_mysqlClient);
	databaseLock.unlock();

	if (m_res) {
		mysql_free_result(m_res);
	}

	return success;
}

DBResult_ptr Database::storeQuery(const std::string& query)
{
	databaseLock.lock();

retry:
	while (mysql_real_query(_mysqlClient, query.c_str(), query.length()) != 0) {
		//_logger->Exception(mysql_error(_mysqlClient));
		auto error = mysql_errno(_mysqlClient);
		if (error != CR_SERVER_LOST && error != CR_SERVER_GONE_ERROR && error != CR_CONN_HOST_ERROR && error != 1053/*ER_SERVER_SHUTDOWN*/ && error != CR_CONNECTION_ERROR) {
		
			break;
		}
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	// we should call that every time as someone would call executeQuery('SELECT...')
	// as it is described in MySQL manual: "it doesn't hurt" :P
	MYSQL_RES* res = mysql_store_result(_mysqlClient);
	if (res == nullptr) {
		//_logger->Exception(mysql_error(_mysqlClient));
		auto error = mysql_errno(_mysqlClient);
		if (error != CR_SERVER_LOST && error != CR_SERVER_GONE_ERROR && error != CR_CONN_HOST_ERROR && error != 1053/*ER_SERVER_SHUTDOWN*/ && error != CR_CONNECTION_ERROR) {
			databaseLock.unlock();
			return nullptr;
		}
		goto retry;
	}
	databaseLock.unlock();

	// retrieving results of query
	DBResult_ptr result = std::make_shared<DBResult>(res);
	if (!result->hasNext()) {
		return nullptr;
	}
	return result;
}

std::string Database::escapeString(const std::string& s) const
{
	return escapeBlob(s.c_str(), s.length());
}

std::string Database::escapeBlob(const char* s, uint32_t length) const
{
	// the worst case is 2n + 1
	size_t maxLength = (length * 2) + 1;

	std::string escaped;
	escaped.reserve(maxLength + 2);
	escaped.push_back('\'');

	if (length != 0) {
		char* output = new char[maxLength];
		mysql_real_escape_string(_mysqlClient, output, s, length);
		escaped.append(output);
		delete[] output;
	}

	escaped.push_back('\'');
	return escaped;
}

std::string Database::validateValue(uint32_t number)
{
	//For database key constraints.
	return number != 0 ? std::to_string(number) : "NULL";
}

DBResult::DBResult(MYSQL_RES* res)
{

	handle = res;

	size_t i = 0;

	MYSQL_FIELD* field = mysql_fetch_field(handle);
	while (field) {
		listNames[field->name] = i++;
		field = mysql_fetch_field(handle);
	}

	row = mysql_fetch_row(handle);
}

DBResult::~DBResult()
{
	mysql_free_result(handle);
}

std::string DBResult::getString(const std::string& s) const
{
	auto it = listNames.find(s);
	if (it == listNames.end()) {

		sLogger->Get()->error("Column {0} does not exist in result set", s);
		return std::string();
	}

	if (row[it->second] == nullptr) {
		return std::string();
	}

	return std::string(row[it->second]);
}

const char* DBResult::getStream(const std::string& s, unsigned long& size) const
{
	auto it = listNames.find(s);
	if (it == listNames.end()) {
		sLogger->Get()->error("Column {0} does not exist in result set", s);
		size = 0;
		return nullptr;
	}

	if (row[it->second] == nullptr) {
		size = 0;
		return nullptr;
	}

	size = mysql_fetch_lengths(handle)[it->second];
	return row[it->second];
}

bool DBResult::hasNext() const
{
	return row != nullptr;
}

bool DBResult::next()
{
	row = mysql_fetch_row(handle);
	return row != nullptr;
}

DBInsert::DBInsert(std::string query) : query(std::move(query))
{
	this->length = this->query.length();
}

bool DBInsert::addRow(const std::string& row)
{
	// adds new row to buffer
	const size_t rowLength = row.length();
	length += rowLength;
	Database database{};
	if (length > database.getMaxPacketSize() && !execute()) {
		return false;
	}
	database.Close();

	if (values.empty()) {
		values.reserve(rowLength + 2);
		values.push_back('(');
		values.append(row);
		values.push_back(')');
	}
	else {
		values.reserve(values.length() + rowLength + 3);
		values.push_back(',');
		values.push_back('(');
		values.append(row);
		values.push_back(')');
	}
	return true;
}

bool DBInsert::addRow(std::ostringstream& row)
{
	bool ret = addRow(row.str());
	row.str(std::string());
	return ret;
}

bool DBInsert::execute()
{
	if (values.empty()) {
		return true;
	}

	// executes buffer
	Database database{};
	bool res = database.executeQuery(query + values);
	database.Close();
	values.clear();
	length = query.length();
	return res;
}