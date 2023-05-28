#pragma once
#include "includes.h"
#include "product.h"
#include <cstdlib>
#include <filesystem>
#include <fstream>


namespace globals {
	inline std::string version = "0.11";

	inline char inputusername[128];
	inline char inputmail[128];
	inline char inputpassword[128];
	inline char inputkey[128];
	
	inline int userId = -1;
	inline std::string userToken = "";
	inline std::vector<Product> products;


	inline ImVec2 window_size{ 600, 600 };
	inline const float padding{ 10 };

	inline API api;
	inline std::string hwid = "";
	inline int gameIndex = 0;
	inline int menuTab = 3;
	inline bool loggedIn = false;
	inline bool active = true;

	inline bool saveUserToken(const std::string& userToken) {
		
		char* appDataDir = nullptr;
		size_t len;

		errno_t err = _dupenv_s(&appDataDir, &len, "APPDATA");
		if (err != 0 || appDataDir == nullptr) {
			return false;
		}

		std::string appDataPath = appDataDir;
		std::string filePath = appDataPath + "\\gokernel.txt";

		std::ofstream outputFile(filePath);
		if (outputFile.is_open()) {
			outputFile << userToken;
			outputFile.close();
			return true;
		}
		else {
			return false;
		}

		free(appDataDir);
	}
}