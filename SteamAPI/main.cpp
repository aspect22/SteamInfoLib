#include "SteamInfoLib.h"
#include <iostream>

void main()
{
	//EXAMPLE USAGE
	GameInfo Dota2;

	Dota2 = SteamInfoLib::getInfoByAppID(570); // Get information for Dota 2 (AppID 570)

	if (Dota2.name.empty()) // Check if the game information was retrieved successfully
	{
		return;
	}

	// Display the game information
	std::cout << "Name: \t\t" << Dota2.name << std::endl;
	std::cout << "Release Date: \t" << Dota2.releaseDate << std::endl;
	std::cout << "Developer: \t" << Dota2.developer << std::endl;
	std::cout << "Publisher: \t" << Dota2.publisher << std::endl;
	std::cout << "Genres: \t" << Dota2.genres << std::endl;
}