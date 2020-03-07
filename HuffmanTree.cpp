#include "HuffmanTree.h"

MRREMI007::HuffmanTree::HuffmanTree()
{
    root = nullptr;
};

MRREMI007::HuffmanTree::~HuffmanTree(){
    //dont think this has to do anything
}

// //copy constructor
// MRREMI007::HuffmanTree::HuffmanTree(const HuffmanTree &other){};

// //copy assignment
// MRREMI007::HuffmanTree::HuffmanTree &MRREMI007::HuffmanTree::operator=(const MRREMI007::HuffmanTree &other){};

// //move constructor
// MRREMI007::HuffmanTree::HuffmanTree(MRREMI007::HuffmanTree &&other){};

// //move assignment
// MRREMI007::HuffmanTree::HuffmanTree &MRREMI007::HuffmanTree::operator=(MRREMI007::HuffmanTree &&other) {}

// //insert node in tree, not const as want to can left and right pointers
// MRREMI007::HuffmanTree::HuffmanTree &MRREMI007::HuffmanTree::insert(MRREMI007::HuffmanTree &node) {}

// //build tree from the given unordered map
// void MRREMI007::HuffmanTree::build(std::unordered_map<char, int> charFrequency) {}

//create a priority queue for the given unordered map
std::priority_queue<MRREMI007::HuffmanNode, std::vector<MRREMI007::HuffmanNode>, MRREMI007::HuffmanTree::compare> MRREMI007::HuffmanTree::prioritise(std::unordered_map<char, int> &charFrequency)
{
    std::priority_queue<HuffmanNode, std::vector<HuffmanNode>, compare> pri;
    for (std::pair<char, int> element: charFrequency){
        HuffmanNode node(element.first, element.second);
        pri.push(node);
    }
    return pri;
}
