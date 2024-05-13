#include "Config.hpp"
#include "Log.hpp"
#include "Graph.hpp"

ItdMap::ItdMap()
{
    // rien à faire pour l'instant
}

ItdMap::~ItdMap()
{
    // rien à faire pour l'instant
}

bool ItdMap::read_itd_map(std::string const &fileName)
{
    Log::Debug("Reading map file: " + fileName);
    std::ifstream myFile(fileName);

    if (myFile.is_open())
    {
        std::string myString;
        // while (myFile)
        // {
        //     std::getline(myFile, myString);
        //     // Log::Debug(mystring);
        // }
        // myString = get_next_line(myFile);
        // Log::Debug(myString);
        // myString = get_next_line(myFile);
        // Log::Debug(myString);

        // lire le tag ITD
        myString = get_next_line(myFile);
        if (myString != "ITD")
        {
            Log::Error("Invalid file format: " + fileName);
            return false;
        }

        // lecture du fichier map
        myString = get_next_line(myFile);
        if (myString.substr(0, 4) != "map ")
        {
            Log::Error("Invalid file format: " + fileName);
            return false;
        }
        map_filename = myString.substr(4);
        Log::Debug("Map filename: " + map_filename);

        // lecture couleur chemin
        myString = get_next_line(myFile);
        if (myString.substr(0, 5) != "path ")
        {
            Log::Error("Invalid file format: " + fileName);
            return false;
        }
        path_color = ColorRGB(myString.substr(5));
        Log::Debug("Path color: " + std::string(path_color));

        // lecture couleur entrée
        myString = get_next_line(myFile);
        if (myString.substr(0, 3) != "in ")
        {
            Log::Error("Invalid file format: " + fileName);
            return false;
        }
        path_color = ColorRGB(myString.substr(3));
        Log::Debug("Path color: " + std::string(path_color));

        // lecture couleur sortie
        myString = get_next_line(myFile);
        if (myString.substr(0, 4) != "out ")
        {
            Log::Error("Invalid file format: " + fileName);
            return false;
        }
        path_color = ColorRGB(myString.substr(4));
        Log::Debug("Path color: " + std::string(path_color));

        // lecture du nombre de noeuds
        // lecture des noeuds
        myString = get_next_line(myFile);
        if (myString.substr(0, 6) != "graph ")
        {
            Log::Error("Invalid file format: " + fileName);
            return false;
        }
        int nbNodes = std::stoi(myString.substr(6));
        Log::Debug("Number of nodes: " + std::to_string(nbNodes));

        ItdMap::nodes.clear();

        for (int i = 0; i < nbNodes; i++)
        {
            myString = get_next_line(myFile);
            if (myString.substr(0, 5) != "node ")
            {
                Log::Error("Invalid file format: " + fileName);
                return false;
            }
            else
            {
                // création du noeud
                Node node;
                NodeId nodeId = std::stoi(myString.substr(5, myString.find(" ")));
                node.m_Id = nodeId;

                // position x, y
                myString = myString.substr(myString.find(" ") + 1);
                myString = myString.substr(myString.find(" ") + 1);
                int x = std::stoi(myString.substr(0, myString.find(" ")));
                myString = myString.substr(myString.find(" ") + 1);
                int y = std::stoi(myString.substr(0, myString.find(" ")));
                node.m_Position = std::make_pair(x, y);

                // noeuds connectés
                myString = myString.substr(myString.find(" ") + 1);
                node.m_ConnectedNodes.push_back(std::stoi(myString));

                ItdMap::nodes.push_back(node);

                Log::Debug("Node: " + std::to_string(nodeId) + " (" + std::to_string(x) + ", " + std::to_string(y) + ")");
                for (auto const &node : node.m_ConnectedNodes)
                {
                    Log::Debug("Connected node: " + std::to_string(node));
                }
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

std::string ItdMap::get_next_line(std::ifstream &myFile)
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
