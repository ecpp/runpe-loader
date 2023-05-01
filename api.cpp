#include "api.h"
#include "json.hpp"



bool API::signup(std::string username, std::string password, std::string email, std::string hwid) {
    nlohmann::json j;
    j["username"] = username;
    j["password"] = password;
    j["hwid"] = hwid;
    j["email"] = email;
    auto response = client.Post("/signup/", j.dump(), "application/json");
    
    if (response->status == 201) {
        return true;
    }
    return false;

}

int API::login(std::string username, std::string password, std::string hwid) {
	nlohmann::json j;
	j["username"] = username;
	j["password"] = password;
	j["hwid"] = hwid;
	auto response = client.Post("/login/", j.dump(), "application/json");
    if (response->status == 400) {
        return 1;
	}
    else if (response->status == 401) {
		return 2;
	}
    return 0;
}

bool API::testApi()
{
   //test if api is alive
    auto response = client.Get("/test/");
    if (response->status == 200) {
        return true;
    }
    return false;
}
    