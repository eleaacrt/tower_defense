#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include "Graph.hpp"

namespace Graph
{
    bool WeightedGraphEdge::operator==(WeightedGraphEdge const &other) const
    {
        return to == other.to && weight == other.weight;
    }
    bool WeightedGraphEdge::operator!=(WeightedGraphEdge const &other) const
    {
        return !(*this == other);
    }

    bool WeightedGraph::operator==(WeightedGraph const &other) const
    {
        return adjacency_list == other.adjacency_list;
    }

    bool WeightedGraph::operator!=(WeightedGraph const &other) const
    {
        return !(*this == other);
    }
}

void Graph::WeightedGraph::add_vertex(int id)
{
    if (adjacency_list.find(id) == adjacency_list.end())
    {
        adjacency_list[id] = {};
    }
}

void Graph::WeightedGraph::add_directed_edge(int from, int to, float weight)
{
    add_vertex(from);
    add_vertex(to);

    adjacency_list[from].push_back({to, weight});
}

void Graph::WeightedGraph::add_undirected_edge(int from, int to, float weight)
{
    add_directed_edge(from, to, weight);
    add_directed_edge(to, from, weight);
}

Graph::WeightedGraph Graph::build_from_adjacency_matrix(const std::vector<std::vector<float>> &adjacency_matrix)
{
    Graph::WeightedGraph graph;

    for (size_t i = 0; i < adjacency_matrix.size(); i++)
    {
        graph.add_vertex(i);
        for (size_t j = 0; j < adjacency_matrix[i].size(); j++)
        {
            if (adjacency_matrix[i][j] != 0)
            {
                graph.add_directed_edge(i, j, adjacency_matrix[i][j]);
            }
        }
    }

    return graph;
}

void Graph::WeightedGraph::print_DFS(int start) const
{
    std::stack<int> stack;
    std::vector<bool> visited(adjacency_list.size(), false);

    stack.push(start);
    visited[start] = true;

    while (!stack.empty())
    {
        int current = stack.top();
        stack.pop();

        std::cout << current << " ";

        for (auto const &edge : adjacency_list.at(current))
        {
            if (!visited[edge.to])
            {
                stack.push(edge.to);
                visited[edge.to] = true;
            }
        }
    }

    std::cout << std::endl;
}

void Graph::WeightedGraph::print_BFS(int start) const
{
    std::queue<int> queue;
    std::vector<bool> visited(adjacency_list.size(), false);

    queue.push(start);
    visited[start] = true;

    while (!queue.empty())
    {
        int current = queue.front();
        queue.pop();

        std::cout << current << " ";

        for (auto const &edge : adjacency_list.at(current))
        {
            if (!visited[edge.to])
            {
                queue.push(edge.to);
                visited[edge.to] = true;
            }
        }
    }
    std::cout << std::endl;
}

std::unordered_map<int, std::pair<float, int>> Graph::WeightedGraph::dijkstra(const Graph::WeightedGraph &graph, const int &start, int end)
{
    std::unordered_map<int, std::pair<float, int>> distances{};
    std::priority_queue<std::pair<float, int>, std::vector<std::pair<float, int>>, std::greater<std::pair<float, int>>> to_visit{};

    std::vector<int> visited;

    // 1. On ajoute le sommet de départ à la liste des sommets à visiter avec une distance de 0 (on est déjà sur le sommet de départ)
    to_visit.push({0.f, start});
    // Tant qu'il reste des sommets à visiter
    while (!to_visit.empty())
    {
        // 2. On récupère le sommet le plus proche du sommet de départ dans la liste de priorité to_visit
        int current_node{to_visit.top().second};
        float current_distanceToStart{to_visit.top().first};
        to_visit.pop();
        // 3.Si on atteind le point d'arrivé, on s'arrête
        if (current_node == end)
            return distances;
        // 3. On parcourt la liste des voisins (grâce à la liste d'adjacence) du noeud courant
        for (auto edge : graph.adjacency_list.at(current_node))
        {
            // 4. on regarde si le noeud existe dans le tableau associatif (si oui il a déjà été visité)
            int current_adj_node{edge.to};
            float current_adj_distanceToParent{edge.weight};
            if (std::find(visited.begin(), visited.end(), current_adj_node) == visited.end())
            {
                // 5. Si le noeud n'a pas été visité, on l'ajoute au tableau associatif en calculant la distance pour aller jusqu'à ce noeud
                // la distance actuelle + le point de l'arrête)
                float adj_distanceToStart = current_distanceToStart + current_adj_distanceToParent;
                if (distances.find(current_adj_node) == distances.end())
                    distances.insert({current_adj_node, {adj_distanceToStart, current_node}});
                else if (distances.at(current_adj_node).first > adj_distanceToStart)
                    distances[current_adj_node] = {adj_distanceToStart, current_node};

                // 6. On ajoute également le noeud de destination à la liste des noeud à visité (avec la distance également pour prioriser les noeuds les plus proches)
                to_visit.push({adj_distanceToStart, current_adj_node});
            }
        }
        visited.push_back(current_node);
    }
    return distances;
}
