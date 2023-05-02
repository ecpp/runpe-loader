#pragma once
#include <string>

class Product {
private:
	std::string name;
	int id;
	std::string expirationDate;
public:
	Product(std::string name, int id, std::string expirationDate) {
		this->name = name;
		this->id = id;
		this->expirationDate = expirationDate;
	}
	std::string getName() {
		return this->name;
	}
	int getId() {
		return this->id;
	}
	std::string getExpirationDate() {
		return this->expirationDate;
	}
};