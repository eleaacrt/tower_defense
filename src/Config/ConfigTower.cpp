#include "ConfigTower.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

// #include "GLHelpers.hpp"
#include "Log.hpp"

ItdTower::ItdTower() {}

ItdTower::~ItdTower() {}

bool ItdTower::read_itd_tower(std::string const &fileName)
{
    std::ifstream myFile(fileName);

    if (myFile.is_open())
    {
        std::string myString;

        // lire le tag ITD
        myString = get_next_line(myFile);
        if (myString != "ITD")
        {
            Log::Error("Invalid file format: " + fileName);
            return false;
        }

        // recupérer le nombre de cibles
        myString = get_next_line(myFile);
        if (myString.substr(0, 7) != "towers ")
        {
            Log::Error("Invalid file format: " + fileName);
            return false;
        }

        int nbTowers = std::stoi(myString.substr(7));

        ItdTower::allTowers.clear();

        // Log::Debug("nbTowers : " + std::to_string(nbTowers));

        for (int i = 0; i < nbTowers; i++)
        {
            // type
            myString = get_next_line(myFile);
            if (myString.substr(0, 5) != "type ")
            {
                Log::Error("Invalid file format: " + fileName);
                return false;
            }
            Tower newTower;
            newTower.m_Type = myString.substr(5);

            // Log::Debug("newTower.m_Type : " + newTower.m_Type);

            // power
            myString = get_next_line(myFile);
            if (myString.substr(0, 6) != "power ")
            {
                Log::Error("Invalid file format: " + fileName);
                return false;
            }
            newTower.m_Power = std::stoi(myString.substr(6));

            // Log::Debug("newTower.m_Power : " + std::to_string(newTower.m_Power));

            // range
            myString = get_next_line(myFile);
            if (myString.substr(0, 6) != "range ")
            {
                Log::Error("Invalid file format: " + fileName);
                return false;
            }
            newTower.m_Range = std::stoi(myString.substr(6));

            // Log::Debug("newTower.m_Range : " + std::to_string(newTower.m_Range));

            // speed
            myString = get_next_line(myFile);
            if (myString.substr(0, 6) != "speed ")
            {
                Log::Error("Invalid file format: " + fileName);
                return false;
            }
            newTower.m_ShotSpeed = std::stoi(myString.substr(6));

            // Log::Debug("newTower.m_ShotSpeed : " + std::to_string(newTower.m_ShotSpeed));

            // cost
            myString = get_next_line(myFile);
            if (myString.substr(0, 5) != "cost ")
            {
                Log::Error("Invalid file format: " + fileName);
                return false;
            }
            newTower.m_Cost = std::stoi(myString.substr(5));

            // Log::Debug("newTower.m_Cost : " + std::to_string(newTower.m_Cost));

            // texture
            myString = get_next_line(myFile);
            if (myString.substr(0, 8) != "texture ")
            {
                Log::Error("Invalid file format: " + fileName);
                return false;
            }
            newTower.m_TextureFile = myString.substr(8);

            // Log::Debug("newTower.m_TextureFile : " + newTower.m_TextureFile);

            ItdTower::allTowers.push_back(newTower);
        }

        // debug
        for (auto &tower : ItdTower::allTowers)
        {
            Log::Debug("TOWER : ");
            Log::Debug("Type : " + tower.m_Type + ", Power : " + std::to_string(tower.m_Power) + ", Range : " + std::to_string(tower.m_Range) + ", Speed : " + std::to_string(tower.m_ShotSpeed) + ", Cost : " + std::to_string(tower.m_Cost) + ", Texture : " + tower.m_TextureFile);
        }
    }
    else
    {
        Log::Error("Failed to open file: " + fileName);
        return false;
    }
}

std::string ItdTower::get_next_line(std::ifstream &myFile)
{
    std::string returnValue = "";
    do
    {
        if (!myFile)
        {
            return "";
        }
        std::getline(myFile, returnValue);
    } while (returnValue == "" || (returnValue.size() > 0 && returnValue[0] == '#'));
    return returnValue;
}