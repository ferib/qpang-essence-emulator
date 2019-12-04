#ifndef LOGIN_EVENT_HPP
#define LOGIN_EVENT_HPP

#include <boost/lexical_cast.hpp>
#include <cstdint>
#include "web_request/request.hpp"
#include "auth_manager.hpp"
#include "packet_event.hpp"
#include "packet_data.hpp"
#include "login_error_event.hpp"
#include "login_response_event.hpp"
#include "settings_manager.hpp"
#include "string_converter.hpp"

class LoginEvent : public PacketEvent {

	enum ErrorCode : uint16_t {
		VERSION = 503,
		PASSWORD = 1101,
		USERNAME = 1102,
	};

public:

	LoginEvent() : PacketEvent(sizeof(Packets::Auth::Login)) {};
	void Read(Connection::Ptr conn, ClientPacket& pack) override
	{
		
		auto login = pack.Read<Packets::Auth::Login>();
		auto authManager = AuthManager::Instance();

		std::string strVersion = sSettings->GetSetting("game_version");
		std::string strHost = sSettings->GetSetting("lobby_host");

		std::string username = StringConverter::WcharToString(login.loginId, 16);
		std::string password = StringConverter::WcharToString(login.password, 16);

		uint32_t gameVersion;

		if (strVersion.empty() || strHost.empty())
			return sLogger->Get()->critical("lobby host or game version not set in database");

		try 
		{
			gameVersion = boost::lexical_cast<uint32_t>(strVersion);
		}
		catch (boost::bad_lexical_cast e)
		{
			sLogger->Get()->critical("Illegal game version");
		}

		//Players should not be able to login from different game versions.
		if (login.gameVersion != gameVersion)
		{
			sLogger->Get()->info("LoginEvent: {0} tried logging in with an illegal game version", username);
			auto loginErrorEvent = LoginErrorEvent{ ErrorCode::VERSION }.Compose(conn);
			return conn->SendPacket(loginErrorEvent);
		}

		auto request = Request{ sSettings->GetSetting("endpoint") + "/user/verify" };
		auto response = request.Post({ { "name", username }, { "password", password } });
		
		//status == 200 = credentials OK.
		if (response.Status() == 200)
		{
			uint32_t lobbyHost = inet_addr(strHost.c_str());
			uint32_t userId = boost::lexical_cast<uint32_t>(response.Body());
			uint8_t* uuidPtr = authManager->AddLoginAttempt(userId);
			std::array<uint8_t, 16> uuid;
			memcpy(&uuid, uuidPtr, 16);
			sLogger->Get()->info("LoginEvent: {0} succesfully logged in", username);
			auto loginResponseEvent = LoginResponseEvent{ uuid, lobbyHost }.Compose(conn);
			conn->SendPacket(loginResponseEvent);
		}
		else
		{
			//Always give username error.. not password, safety reasons.
			sLogger->Get()->warn("LoginEvent: {0} failed to login", username);
			auto loginErrorEvent = LoginErrorEvent{ ErrorCode::USERNAME }.Compose(conn);
			conn->SendPacket(loginErrorEvent);
		}
	}

private:
};

#endif