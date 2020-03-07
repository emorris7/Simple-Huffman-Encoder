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
    HuffmanTree(const HuffmanTree &other);

    //copy assignment
    HuffmanTree &operator=(const HuffmanTree &other);

    //move constructor
    HuffmanTree(HuffmanTree &&other);

    //move assignment
    HuffmanTree &operator=(HuffmanTree &&other);

    //build tree from the given unordered map
    void build(std::unordered_map<char, int> charFrequency);

    struct compare
    {
        bool operator()(const HuffmanNode &lhs, const HuffmanNode &rhs)
        {
            return lhs > rhs;
        }
    };

    //create a priority queue for the given unordered map
    std::priority_queue<HuffmanNode, std::vector<HuffmanNode>, compare> prioritise(std::unordered_map<char, int> &charFrequency);

    //encode given char (create table)
};

} // namespace MRREMI007
#endif