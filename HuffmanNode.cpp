#include "HuffmanNode.h"

MRREMI007::HuffmanNode::HuffmanNode(const char c, const int o)
{
    occurence = o;
    character = c;
    leftNode = nullptr;
    rightNode = nullptr;
}

MRREMI007::HuffmanNode::HuffmanNode()
{
    occurence = 0;
    character = 0;
    leftNode = nullptr;
    rightNode = nullptr;
}

MRREMI007::HuffmanNode::~HuffmanNode()
{
    //don't think anything has to happen?
}

//copy constructor
MRREMI007::HuffmanNode::HuffmanNode(const MRREMI007::HuffmanNode &other)
{
    occurence = other.occurence;
    character = other.character;
    leftNode = other.leftNode;
    rightNode = other.rightNode;
}

//copy assignment
MRREMI007::HuffmanNode &MRREMI007::HuffmanNode::operator=(const MRREMI007::HuffmanNode &other)
{
    occurence = other.occurence;
    character = other.character;
    leftNode = other.leftNode;
    rightNode = other.rightNode;
    return *this;
}

//move constructor
MRREMI007::HuffmanNode::HuffmanNode(MRREMI007::HuffmanNode &&other)
{
    occurence = other.occurence;
    character = other.character;
    leftNode = other.leftNode;
    rightNode = other.rightNode;
}

//move assignment
MRREMI007::HuffmanNode &MRREMI007::HuffmanNode::operator=(MRREMI007::HuffmanNode &&other)
{
    if (this != &other)
    {
        occurence = other.occurence;
        character = other.character;
        leftNode = other.leftNode;
        rightNode = other.rightNode;
    }
    return *this;
}

bool MRREMI007::operator>(const MRREMI007::HuffmanNode &lhs, const MRREMI007::HuffmanNode &rhs)
{
    return lhs.occurence > rhs.occurence;
}