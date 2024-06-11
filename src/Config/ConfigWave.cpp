#include "ConfigWave.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <sstream>

#include "GLHelpers.hpp"

#include "Log.hpp"
#include "utils.hpp"

ItdWave::ItdWave() {}

ItdWave::~ItdWave() {}

bool ItdWave::read_itd_wave(std::string const &fileName)
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

        allTargets.clear();
        ItdTarget.read_itd_target("data/itd_target.itd");
        allTargets = ItdTarget.allTargets;

        myString = get_next_line(myFile);
        if (myString.substr(0, 6) != "waves ")
        {
            Log::Error("Invalid file format: " + fileName);
            return false;
        }

        int nbWaves = std::stoi(myString.substr(6));

        Log::Debug("nbWaves : " + std::to_string(nbWaves));

        Waves.clear();

        for (int i = 0; i < nbWaves; i++)
        {
            // type
            myString = get_next_line(myFile);
            // Log::Debug("myString : " + myString);
            if (myString.substr(0, 5) != "wave ")
            {
                Log::Error("Invalid file format: " + fileName);
                return false;
            }

            std::vector<Target> newWave;
            int nbTargets = std::stoi(myString.substr(5));
            myString = myString.substr(myString.find(" ") + 1);

            for (int j = 0; j < nbTargets; j++)
            {
                myString = myString.substr(myString.find(" ") + 1);
                newWave.push_back(allTargets[std::stoi(myString)]);
            }

            Waves.push_back(newWave);
        }

        // debug
        for (auto &wave : Waves)
        {
            Log::Debug("WAVE : ");
            for (auto &target : wave)
            {
                Log::Debug(target.m_Type + ", PV : " + std::to_string(target.m_PointsVie) + ", Speed : " + std::to_string(target.m_Speed) + ", Value : " + std::to_string(target.m_Value));
            }
        }
    }
    else
    {
        Log::Error("Failed to open file: " + fileName);
        return false;
    }

    return true;
}

std::string ItdWave::get_next_line(std::ifstream &myFile)
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