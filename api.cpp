#include "api.h"
#include "json.hpp"
#include "globals.h"
#include "product.h"
#include <future>
#include <winternl.h>
#include <TlHelp32.h>
#include "runpe.cpp"
#include <regex>

typedef NTSTATUS(NTAPI* NtUnmapViewOfSection_t)(HANDLE, PVOID);
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
    globals::saveUserToken(globals::userToken);
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
    //open console and print
    /*AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    ShowWindow(GetConsoleWindow(), SW_SHOW);*//*
    std::cout << response->body << std::endl;*/
    globals::products.clear();
    for (auto& element : j["filtered_products"]) {
        int hack_id = element["hack_id"];
        std::string expiration_date = element["expiration_date"];
        std::string status = element["hack"]["status"];
        Product product(hack_id, expiration_date, status);
        globals::products.push_back(product);
    }
    
    return true;
    
}

bool API::validateProduct(int id) {
    std::string url = "/validate/";
    httplib::Headers headers = { {"Authorization", "Token " + globals::userToken} };
    nlohmann::json j;
    j["hwid"] = globals::hwid;
    j["pid"] = id;
    auto response = client.Post(url.c_str(), headers, j.dump(), "application/json");
    if (response->status == 200) {
		return true;
	}
	return false;
}

bool API::checkLoaderVersion(std::string productName) {
    std::string url = "/check_version/";
    nlohmann::json j;
    j["version"] = globals::version;
    j["product"] = productName;
    httplib::Headers headers = { {"Authorization", "Token " + globals::userToken} };

    auto response = client.Post(url.c_str(), headers, j.dump(), "application/json");
   
    if (response->status == 200) {
		return true;
	}
    return false;
}

bool API::redeemKey(std::string key) {
    
    std::string url = "/kms/redeem/";
    nlohmann::json j;
    j["key"] = key;
    j["user_id"] = globals::userId;
    httplib::Headers headers = { {"Authorization", "Token " + globals::userToken} };
    auto response = client.Post(url.c_str(), headers, j.dump(), "application/json");
    if (response->status == 200 || response->status == 201) {
		return true;
	}
    return false;
}

bool API::downloadFile(int id, int type) {
    std::string url = "/download/";
    nlohmann::json j;
    j["hwid"] = globals::hwid;
    j["type"] = type;
    j["pid"] = id;
    httplib::Headers headers = { {"Authorization", "Token " + globals::userToken} };

    

    // Make the POST request with the progress callback
    auto response = client.Post(url.c_str(), headers, j.dump(), "application/json");
    if (response && response->status == 200) {
        // Extract the raw data string from the response
        std::string raw_data_str = response->body;
        // Remove leading and trailing whitespaces
        
        raw_data_str.erase(
            raw_data_str.begin(),
            std::find_if(raw_data_str.begin(), raw_data_str.end(), [](int ch) {
                return !std::isspace(ch);
                })
        );
        raw_data_str.erase(
            std::find_if(raw_data_str.rbegin(), raw_data_str.rend(), [](int ch) {
                return !std::isspace(ch);
                }).base(),
                    raw_data_str.end()
                    );

        //split string by comma
        std::vector<unsigned char> data;
        std::regex hex_pattern(R"(0x[0-9A-Fa-f]{2})");
        std::sregex_iterator it(raw_data_str.begin(), raw_data_str.end(), hex_pattern);
        std::sregex_iterator end;
        std::vector<unsigned char> raw_data;
        // Iterate through the matches and print the hexadecimal values
        while (it != end) {
            unsigned int value;
            std::stringstream ss;
            ss << std::hex << it->str(); // Remove the "0x" prefix
            ss >> value;
            raw_data.push_back(static_cast<unsigned char>(value));
            ++it;
        }
        std::cout << raw_data.size() << std::endl;

        // Print the rawData vector

        // Pass the raw data to the runPe function
        int result = runpe::runPe(raw_data.data());
        raw_data.clear();
        return result == 0;
    }

    return false;
}