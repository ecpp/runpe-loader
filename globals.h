#pragma once
#include "includes.h"


namespace globals {
	inline char inputusername[128];
	inline char inputmail[128];
	inline char inputpassword[128];
	inline char inputkey[128];

	inline ImVec2 window_size{ 600, 600 };
	inline const float padding{ 10 };


	inline API api;
	inline std::vector<std::string> games = {"CSGO"};
	inline std::string hwid = "";
	inline int gameIndex = 0;
	inline int menuTab = 0;
	inline bool loggedIn = false;
	inline bool active = true;
}