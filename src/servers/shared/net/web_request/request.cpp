#include "request.hpp"

Request::Request(std::string endPoint)
{
	_endPoint = endPoint;
	_apiKey = sSettings->GetSetting("api_key");
	_headers.push_back("X-Api-Key: " + _apiKey);
}

Request::~Request()
{
}

Response Request::Post(std::map<std::string, std::string> fields)
{
	try {
		curlpp::Cleanup cleaner;
		curlpp::Easy request;

		std::string variables;

		request.setOpt(new curlpp::options::Url(_endPoint));
		request.setOpt(new curlpp::options::HttpHeader(_headers));

		curlpp::Forms formParts;
		for (auto field : fields)
		{
			formParts.push_back(new curlpp::FormParts::Content(field.first, field.second));
		}
		request.setOpt(new curlpp::options::HttpPost(formParts));

		std::ostringstream response;
		request.setOpt(new curlpp::options::WriteStream(&response));

		request.perform();


		return Response{ static_cast<uint16_t>(curlpp::infos::ResponseCode::get(request)), response.str() };
	}
	catch (curlpp::LogicError & e) {
		std::cout << e.what() << std::endl;
	}
	catch (curlpp::RuntimeError & e) {
		std::cout << e.what() << std::endl;
	}
	return Response{ 401, std::string() };
}
