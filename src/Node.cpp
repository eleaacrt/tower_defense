#include "Node.hpp"

Node::Node()
{
    // constructeur par défaut
    m_Id = -1;
    m_Position = std::make_pair(0, 0);
    m_ConnectedNodes = {};
}