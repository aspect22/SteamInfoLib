# SteamInfoLib
Grab game information with appID from Steam games.

# Usage
Make sure you have **curl.h** and **nlohmann/json.hpp** linked to your Project with VCPKG with CMake or whatever you want to use.
To install these please refer to these or search for them yourself.
[Tutorial: Install and use packages with CMake in Visual Studio](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started-vs)
[Tutorial: Install and use packages with CMake in Visual Studio Code](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started-vscode)

Include **SteamInfoLib.h** and **SteamInfoLib.cpp** into your project.
```CPP
#include "SteamInfoLib.h"
#include <iostream>

void main()
{
	//EXAMPLE USAGE
	GameInfo Dota2;

	Dota2 = SteamInfoLib::getInfoByAppID(570); // Get information for Dota 2 (AppID 570)
	
	// Display the game information
	std::cout << "Name: \t\t" << Dota2.name << std::endl;
	std::cout << "Release Date: \t" << Dota2.releaseDate << std::endl;
	std::cout << "Developer: \t" << Dota2.developer << std::endl;
	std::cout << "Publisher: \t" << Dota2.publisher << std::endl;
	std::cout << "Genres: \t" << Dota2.genres << std::endl;
}
```

Information you can get:
``` CPP
struct GameInfo {
    std::string name;
    std::string releaseDate;
    std::string developer;
    std::string publisher;
    std::string genres;
};
```