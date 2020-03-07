#include "HuffmanTree.h"
#include <iostream>
#include <fstream>

MRREMI007::HuffmanTree::HuffmanTree()
{
    root = nullptr;
};

MRREMI007::HuffmanTree::~HuffmanTree()
{
    //dont think this has to do anything
}

//copy constructor
MRREMI007::HuffmanTree::HuffmanTree(const HuffmanTree &other)
{
    root = other.root;
}

//copy assignment
MRREMI007::HuffmanTree &MRREMI007::HuffmanTree::operator=(const MRREMI007::HuffmanTree &other)
{
    root = other.root;
    return *this;
};

//move constructor
MRREMI007::HuffmanTree::HuffmanTree(MRREMI007::HuffmanTree &&other)
{
    root = other.root;
};

//move assignment
MRREMI007::HuffmanTree &MRREMI007::HuffmanTree::operator=(MRREMI007::HuffmanTree &&other)
{
    if (this != &other)
    {
        root = other.root;
    }
    return *this;
}

//make a frequency map for the given file
std::unordered_map<char, int> MRREMI007::HuffmanTree::mapFrequency(std::string fileName)
{
    std::unordered_map<char, int> charMap;
    std::ifstream inputFile(fileName);
    if (inputFile.is_open())
    {
        char readIn;
        while (inputFile.get(readIn))
        {
            std::unordered_map<char, int>::iterator it = charMap.find(readIn);
            if (it != charMap.end())
            {
                it->second++;
            }
            else
            {
                charMap.insert({readIn, 1});
            }
        }
        inputFile.close();
    }
    else
    {
        std::cout << "Could not open file " << fileName << std::endl;
    }
    return charMap;
}

//build a huff man tree from the given file
void MRREMI007::HuffmanTree::buildFromFile(std::string fileName)
{
    std::unordered_map<char, int> map = mapFrequency(fileName);
    if (map.size() == 0)
    {
        std::cout << "Empty character frequency map" << std::endl;
    }
    else
    {
        build(map);
    }
}

//build tree from the given unordered map
void MRREMI007::HuffmanTree::build(std::unordered_map<char, int> charFrequency)
{
    std::priority_queue<HuffmanNode, std::vector<HuffmanNode>, compare> prio = prioritise(charFrequency);
    while (prio.size() > 1)
    {
        HuffmanNode nodeOne = prio.top();
        prio.pop();
        HuffmanNode nodeTwo = prio.top();
        prio.pop();
        HuffmanNode combineNode;
        combineNode.occurence = nodeOne.occurence + nodeTwo.occurence;
        combineNode.leftNode = std::make_shared<HuffmanNode>(nodeOne);
        combineNode.rightNode = std::make_shared<HuffmanNode>(nodeTwo);
        prio.push(combineNode);
    }
    root = std::make_shared<HuffmanNode>(prio.top());
}

//moke code table for the given Huffman tree
void MRREMI007::HuffmanTree::makeCodeTable()
{
}

//create a priority queue for the given unordered map
std::priority_queue<MRREMI007::HuffmanNode, std::vector<MRREMI007::HuffmanNode>, MRREMI007::HuffmanTree::compare> MRREMI007::HuffmanTree::prioritise(std::unordered_map<char, int> &charFrequency)
{
    std::priority_queue<HuffmanNode, std::vector<HuffmanNode>, compare> pri;
    for (std::pair<char, int> element : charFrequency)
    {
        HuffmanNode node(element.first, element.second);
        pri.push(node);
    }
    return pri;
}
