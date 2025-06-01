#include "SteamInfoLib.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <iostream>

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output)
{
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

using json = nlohmann::json;

namespace SteamInfoLib {
    GameInfo getInfoByAppID(int appid)
    {
        CURL* curl = curl_easy_init();
        std::string readBuffer;
        GameInfo gameInfo;

        if (curl)
        {
            std::string url = "https://store.steampowered.com/api/appdetails?appids=" + std::to_string(appid);
            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

            CURLcode res = curl_easy_perform(curl);
            if (res != CURLE_OK)
            {
                std::cerr << "cURL Error: " << curl_easy_strerror(res) << std::endl;
            }

            curl_easy_cleanup(curl);
        }
        try
        {
            json parsed = json::parse(readBuffer);
            std::string appidStr = std::to_string(appid);
            if (parsed.contains(appidStr) && parsed[appidStr]["success"])
            {
                std::string appidStr = std::to_string(appid);
                json data = parsed[appidStr]["data"];
                std::string name = data["name"];
                std::string releaseDate = data["release_date"]["date"];
                std::string developer = data["developers"][0];
                std::string publisher = data["publishers"][0];

                // Genres
                std::vector<std::string> genreDescriptions;

                for (const auto& genre : data["genres"]) {
                    genreDescriptions.push_back(genre["description"]);
                }
                std::string genresString;
                for (size_t i = 0; i < genreDescriptions.size(); ++i) {
                    genresString += genreDescriptions[i];
                    if (i != genreDescriptions.size() - 1) {
                        genresString += ", "; 
                    }
                }

				// Fill the GameInfo structure
                gameInfo.name = name;
                gameInfo.releaseDate = releaseDate;
                gameInfo.developer = developer;
                gameInfo.publisher = publisher;
                gameInfo.genres = genresString;
            }
            else
            {
                std::cerr << "Failed to fetch game details." << std::endl;
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "JSON Parsing Error: " << e.what() << std::endl;
        }
        return gameInfo;
    }
}
