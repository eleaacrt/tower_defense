#pragma once
#include <vector>
#include <utility>

typedef int NodeId;

class Node
{
public:
    Node();
    NodeId m_Id;
    std::pair<int, int> m_Position;
    std::vector<NodeId> m_ConnectedNodes;
};
