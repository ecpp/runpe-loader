#pragma once
#include "includes.h"


namespace globals {
	inline const char* version = "0.1";

	inline char inputusername[128];
	inline char inputmail[128];
	inline char inputpassword[128];
	inline char inputkey[128];

	inline int userId = -1;
	inline std::string userToken = "";
	inline std::vector<std::string> products;


	inline ImVec2 window_size{ 600, 600 };
	inline const float padding{ 10 };


	inline API api;
	inline std::vector<std::string> games = {"CSGO"};
	inline std::string hwid = "";
	inline int gameIndex = 0;
	inline int menuTab = 3;
	inline bool loggedIn = false;
	inline bool active = true;
}