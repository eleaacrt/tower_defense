#include "ConfigTarget.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <sstream>

#include "GLHelpers.hpp"

#include "Log.hpp"
#include "utils.hpp"


ItdTarget::ItdTarget() {}

ItdTarget::~ItdTarget() {}

bool ItdTarget::read_itd_target(std::string const &fileName)
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
        if (myString.substr(0, 8) != "targets ")
        {
            Log::Error("Invalid file format: " + fileName);
            return false;
        }
        int nbTargets = std::stoi(myString.substr(8));

        ItdTarget::allTargets.clear();

        for (int i = 0; i < nbTargets; i++)
        {

            // type
            myString = get_next_line(myFile);
            if (myString.substr(0, 5) != "type ")
            {
                Log::Error("Invalid file format: " + fileName);
                return false;
            }
            Target newTarget;
            newTarget.m_Type = myString.substr(5);

            // pv
            myString = get_next_line(myFile);
            if (myString.substr(0, 3) != "pv ")
            {
                Log::Error("Invalid file format: " + fileName);
                return false;
            }
            newTarget.m_PointsVie = std::stoi(myString.substr(3));

            // speed
            myString = get_next_line(myFile);
            if (myString.substr(0, 6) != "speed ")
            {
                Log::Error("Invalid file format: " + fileName);
                return false;
            }
            newTarget.m_Speed = std::stoi(myString.substr(6));

            // value
            myString = get_next_line(myFile);
            if (myString.substr(0, 6) != "value ")
            {
                Log::Error("Invalid file format: " + fileName);
                return false;
            }
            newTarget.m_Value = std::stoi(myString.substr(6));

            // texture
            myString = get_next_line(myFile);
            if (myString.substr(0, 8) != "texture ")
            {
                Log::Error("Invalid file format: " + fileName);
                return false;
            }
            myString = myString.substr(8);
            // img::Image texture{img::load(make_absolute_path("images/" + myString, true), 3, true)};
            // newTarget.m_texture_file = loadTexture(texture);

            allTargets.push_back(newTarget);
        }

        // debug
        // for (auto &target : Targets)
        // {
        //     Log::Debug(target.m_Type + ", PV : " + std::to_string(target.m_PointsVie) + ", Speed : " + std::to_string(target.m_Speed) + ", Value : " + std::to_string(target.m_Value) + ", Texture : " + target.m_texture_file);
        // }

        // myString = get_next_line(myFile);
        // if (myString.substr(0, 6) != "waves ")
        // {
        //     Log::Error("Invalid file format: " + fileName);
        //     return false;
        // }
        // int nbWaves = std::stoi(myString.substr(6));

        // // Log::Debug("nbWaves : " + std::to_string(nbWaves));

        // ItdTarget::Waves.clear();

        // for (int i = 0; i < nbWaves; i++)
        // {
        //     // type
        //     myString = get_next_line(myFile);
        //     // Log::Debug("myString : " + myString);
        //     if (myString.substr(0, 5) != "wave ")
        //     {
        //         Log::Error("Invalid file format: " + fileName);
        //         return false;
        //     }

        //     std::vector<Target> newWave;
        //     int nbTargets = std::stoi(myString.substr(5));

        //     myString = myString.substr(myString.find(" ") + 1);
        //     for (int j = 0; j < nbTargets; j++)
        //     {
        //         myString = myString.substr(myString.find(" ") + 1);
        //         newWave.push_back(Targets[std::stoi(myString)]);
        //     }
        //     Waves.push_back(newWave);
        // }

        // debug
        // for (auto &wave : Waves)
        // {
        //     Log::Debug("WAVE : ");
        //     for (auto &target : wave)
        //     {
        //         Log::Debug(target.m_Type + ", PV : " + std::to_string(target.m_PointsVie) + ", Speed : " + std::to_string(target.m_Speed) + ", Value : " + std::to_string(target.m_Value));
        //     }
        // }
    }
    else
    {
        Log::Error("Failed to open file: " + fileName);
        return false;
    }

    return true;
}

std::string ItdTarget::get_next_line(std::ifstream &myFile)
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
