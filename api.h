#pragma once
#include <iostream>
#include <string>
#define WIN32_LEAN_AND_MEAN
#include "httplib.h"


class API {
	private:
		httplib::Client client;
public:
	API() : client("127.0.0.1", 8000) {}
	bool signup(std::string username, std::string password, std::string email, std::string hwid);
	void login(std::string username, std::string password, std::string hwid);
	bool testApi();
};