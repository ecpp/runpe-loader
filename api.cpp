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

bool API::testApi()
{
   //test if api is alive
    auto response = client.Get("/test/");
    if (response->status == 200) {
        return true;
    }
    return false;
}
    