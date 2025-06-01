#pragma once
#ifndef GAMEINFO_H
#define GAMEINFO_H

#include <string>

// Structure to hold game information
struct GameInfo {
    std::string name;
    std::string releaseDate;
    std::string developer;
    std::string publisher;
    std::string genres;
};

#endif // GAMEINFO_H

namespace SteamInfoLib
{
	GameInfo getInfoByAppID(int id);
}
