#include "api.h"
#include "json.hpp"
#include "globals.h"
#include "product.h"



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
    //return Response({'token': token.key, 'user_id': user.id})
	j = nlohmann::json::parse(response->body);
	globals::userToken = j["token"];
    globals::userId = j["user_id"];
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

bool API::getUserInfo() {
    std::string url = "/user/" + std::to_string(globals::userId);
    //set token as header
    httplib::Headers headers = { {"Authorization", "Token " + globals::userToken} };
    auto response = client.Get(url.c_str(), headers);
    if (response->status != 200) {
        return false;
    }
    nlohmann::json j;
    j = nlohmann::json::parse(response->body);

    for (auto& element : j["products"]) {
        std::string name = element["name"];
        std::string expiration_date = element["expiration_date"];
        int id = element["id"];
        Product product(name, id, expiration_date);
        globals::products.push_back(product);
    }
    
    return true;
    
}

void API::validateProduct() {

}