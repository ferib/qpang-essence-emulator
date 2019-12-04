#ifndef _SHARED_DATABASE_H
#define _SHARED_DATABASE_H

#define DB_HOST ""   
#define DB_USER "root"   
#define DB_PASS ""   
#define DB_PORT 3306   
#define DB_NAME "qpang_test" 

#include <iostream>
#include <mysql.h>

#include <map>
#include <mutex>
#include <vector>
#include <ostream>

#include "logger.hpp"


#include <boost/lexical_cast.hpp>
#include "boost/format.hpp"


class DBResult;
using DBResult_ptr = std::shared_ptr<DBResult>;

class Database
{

public:

	Database();
	~Database();

	bool Connect();
	void Close();

	bool executeQuery(const std::string& query);

	DBResult_ptr storeQuery(const std::string& query);

	std::string escapeString(const std::string& s) const;

	std::string escapeBlob(const char* s, uint32_t length) const;

	std::string validateValue(uint32_t number);

	uint64_t getLastInsertId() const {
		return static_cast<uint64_t>(mysql_insert_id(_mysqlClient));
	}

	static const char* getClientVersion() {
		return mysql_get_client_info();
	}

	uint64_t getMaxPacketSize() const {
		return maxPacketSize;
	}

private:
	MYSQL* _mysqlClient;
	std::recursive_mutex databaseLock;
	uint64_t maxPacketSize = 1048576;

	bool beginTransaction();
	bool rollback();
	bool commit();
};

class DBResult
{
public:
	explicit DBResult(MYSQL_RES* res);
	~DBResult();

	// non-copyable
	DBResult(const DBResult&) = delete;
	DBResult& operator=(const DBResult&) = delete;

	template<typename T>
	T getNumber(const std::string& s) const
	{
		auto it = listNames.find(s);
		if (it == listNames.end()) {
			sLogger->Get()->error("Column {0} does not exist in result set", s);
			return static_cast<T>(0);
		}

		if (row[it->second] == nullptr) {
			return static_cast<T>(0);
		}

		T data;
		try {
			data = boost::lexical_cast<T>(row[it->second]);
		}
		catch (boost::bad_lexical_cast&) {
			data = 0;
		}
		return data;
	}

	std::string getString(const std::string& s) const;
	const char* getStream(const std::string& s, unsigned long& size) const;

	bool hasNext() const;
	bool next();

private:
	MYSQL_RES* handle;
	MYSQL_ROW row;
	std::map<std::string, size_t> listNames;

	friend class Database;
};

class DBInsert
{
	friend class DBTransaction;

public:
	explicit DBInsert(std::string query);
	bool addRow(const std::string& row);
	bool addRow(std::ostringstream& row);
	bool execute();

private:
	std::string query;
	std::string values;
	size_t length;

};


class DBTransaction
{
public:
	constexpr DBTransaction() = default;

	~DBTransaction() {
		if (state == STATE_START) {
			// ....
		}
	}

	DBTransaction(const DBTransaction&) = delete;
	DBTransaction& operator=(const DBTransaction&) = delete;

	bool begin() {
		state = STATE_START;
	}

	bool commit() {
		if (state != STATE_START) {
			return false;
		}

		state = STATE_COMMIT;
	}

private:
	enum TransactionStates_t {
		STATE_NO_START,
		STATE_START,
		STATE_COMMIT,
	};

	TransactionStates_t state = STATE_NO_START;
};

#endif //_DATABASE_H