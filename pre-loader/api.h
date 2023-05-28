#pragma once
#define WIN32_LEAN_AND_MEAN
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include "json.hpp"
#include <string>

class API {
private:
	httplib::SSLClient client;
public:
	API() : client("91.191.173.36", 8000) {
		client.enable_server_certificate_verification(false);
	}

	std::string get_system32_path() {
		char* system32dir = nullptr;
		size_t len;

		errno_t err = _dupenv_s(&system32dir, &len, "WINDIR");
		if (err != 0 || system32dir == nullptr) {
			return "";
		}
		return std::string(system32dir) + "\\System32\\";
	}

	std::string getTempPath() {
		char tmpname[L_tmpnam_s];
		if (tmpnam_s(tmpname, L_tmpnam_s) != 0) {
			return "";
		}
		return tmpname;
	}

	bool downloadDll(std::string dllName) {
		std::string url = "/download_dll/";
		nlohmann::json j;
		j["dll"] = dllName;
		auto response = client.Post(url.c_str(), j.dump(), "application/json");
		if (response->status == 200) {
			std::string filename;
			auto content_disposition = response->get_header_value("Content-Disposition");
			size_t pos = content_disposition.find("filename=");
			if (pos != std::string::npos) {
				filename = content_disposition.substr(pos + 10, content_disposition.size() - pos - 11);
			}
			else {
				return false;
			}
			std::string save_path = get_system32_path() + filename;
			std::ofstream file(save_path, std::ofstream::binary);
			file.write(response->body.c_str(), response->body.size());
			file.close();
			return true;
		}
		return false;
	}

	bool downloadLoader()
	{
		std::string url = "/download_dll/";
		nlohmann::json j;
		j["dll"] = "loader";
		auto response = client.Post(url.c_str(), j.dump(), "application/json");
		if (response->status == 200) {
			std::string filename;
			auto content_disposition = response->get_header_value("Content-Disposition");
			size_t pos = content_disposition.find("filename=");
			if (pos != std::string::npos) {
				filename = content_disposition.substr(pos + 10, content_disposition.size() - pos - 11);
			}
			else {
				return false;
			}
			std::string save_path = getTempPath() + filename;
			std::ofstream file(save_path, std::ofstream::binary);
			file.write(response->body.c_str(), response->body.size());
			file.close();
			std::system(save_path.c_str());
			remove(save_path.c_str());
			return true;
		}
		return false;
	}

	bool checkLoaderVersion(std::string version, std::string productName) {
		std::string url = "/check_version/";
		nlohmann::json j;
		j["version"] = version;
		j["product"] = productName;

		auto response = client.Post(url.c_str(), j.dump(), "application/json");

		if (response->status == 200) {
			return true;
		}
		return false;
	}
};