#ifndef HUFFMANTREE
#define HUFFMANTREE
#include <memory>
#include <queue>
#include <unordered_map>
#include "HuffmanNode.h"

namespace MRREMI007
{

class HuffmanTree
{
private:
    std::shared_ptr<HuffmanNode> root;

public:

    HuffmanTree();

    ~HuffmanTree();

    //copy constructor
    HuffmanTree(const HuffmanTree& other);

    //copy assignment
    HuffmanTree& operator=(const HuffmanTree& other);

    //move constructor
    HuffmanTree(HuffmanTree&& other);

    //move assignment 
    HuffmanTree& operator=(HuffmanTree&& other);

    //insert node in tree, not const as want to can left and right pointers
    HuffmanTree& insert(HuffmanTree& node);

    //build tree from the given unordered map
    void build(std::unordered_map<char,int> charFrequency);

    //create a priority queue for the given unordered map
    std::priority_queue<HuffmanNode> prioritise(std::unordered_map<char,int> charFrequency);
//encode given char (create table)
};

bool compare(HuffmanNode& a, const HuffmanNode& b){
    return (a<b);
}
} // namespace MRREMI007
#endif