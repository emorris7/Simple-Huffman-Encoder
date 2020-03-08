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
public:
    //maybe should make private
    std::shared_ptr<HuffmanNode> root;
    std::unordered_map<char, std::string> codeTable;

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

    //make a frequency map for the given file
    std::unordered_map<char, int> mapFrequency(std::string fileName);

    //build a huff man tree from the given file
    void buildFromFile(std::string fileName);

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

    //moke code table for the given Huffman tree
    void makeCodeTable();

    //moke code table for the given Huffman tree
    void makeCodeTableRec(std::shared_ptr<HuffmanNode> node, std::string str);

    //write code table to a file
    void writeCodeTable(std::string fileName);

    //compress the given file and write compressed data to the given output file;
    void compressFile(std::string inputFileName, std::string outputFileName);
};

} // namespace MRREMI007
#endif