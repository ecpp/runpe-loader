#pragma once
#include "includes.h"

struct Globals
{
	static Globals* Get()
	{
		static auto* instance = new Globals();
		return instance;
	}

	int MenuTab = 0;

	std::vector<std::string> Games = { "FiveM","Valorant","CSGO","Warzone" };
	int Game = 0;

	bool AutoInject = false;
	bool Blockreports = false;
	bool SafeInjection = true;
	bool loggedIn = false;
	std::string defaultUsername = "admin";
	std::string defaultPassword = "admin";
};

namespace globals {
	inline std::vector<std::string> games = {"CSGO"};
	inline int gameIndex = 0;

	inline int menuTab = 0;
	inline bool loggedIn = false;
	inline std::string defaultUsername = "admin";
	inline std::string defaultPassword = "admin";
	inline bool active = true;
}