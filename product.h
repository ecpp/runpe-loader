#pragma once
#include <string>

class Product {
private:
	std::string name;
	int id;
	std::string expirationDate;
	std::string status;
	std::string statusText;
public:
	Product(int id, std::string expirationDate, std::string status) {
		this->id = id;
		this->expirationDate = expirationDate;
		this->status = status;
		//name is CSGO if id is 1
		if (id == 1) {
			this->name = "CSGO";
		}
		if (status == "u") {
			this->statusText = "Undetected";
		}
		else {
			this->statusText = "Updating";
		}
	}
	std::string getName() {
		return this->name;
	}
	std::string getStatus() {
		return this->statusText;
	}
	int getId() {
		return this->id;
	}
	std::string getExpirationDate() {
		return this->expirationDate;
	}
};