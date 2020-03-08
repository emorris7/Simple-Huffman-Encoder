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

//moke code table for the given Huffman tree
void MRREMI007::HuffmanTree::makeCodeTable()
{
    if (root != nullptr)
    {
        makeCodeTableRec(root, "");
    }
    else
    {
        std::cout << "Cannot make code table, Huffman Tree is empty" << std::endl;
    }
}

//based off https://www.techiedelight.com/huffman-coding/
void MRREMI007::HuffmanTree::makeCodeTableRec(std::shared_ptr<MRREMI007::HuffmanNode> node, std::string str)
{
    //base case
    if (node == nullptr)
    {
        return;
    }

    if (node->leftNode == nullptr && node->rightNode == nullptr)
    {
        codeTable.insert({node->character, str});
        return;
    }

    makeCodeTableRec(node->leftNode, str + "0");
    makeCodeTableRec(node->rightNode, str + "1");
}

//write code table to a file
void MRREMI007::HuffmanTree::writeCodeTable(std::string fileName)
{
    if (codeTable.size() == 0)
    {
        std::cout << "Code table is empty, cannot create code table" << std::endl;
        return;
    }
    std::ofstream outputFile(fileName + ".hdr");
    if (outputFile.is_open())
    {
        outputFile << codeTable.size() << "\n";
        for (auto &e : codeTable)
        {
            outputFile << e.first << " " << e.second << "\n";
        }
        outputFile.close();
    }
    else
    {
        std::cout << "Could not open header file" << std::endl;
    }
}

//compress the given file and write compressed data to the given output file;
void MRREMI007::HuffmanTree::compressFile(std::string inputFileName, std::string outputFileName)
{
    buildFromFile(inputFileName);
    makeCodeTable();
    if (codeTable.size() == 0)
    {
        return;
    }
    std::ifstream inputFile(inputFileName);
    std::ofstream outputFile(outputFileName);

    if (inputFile.is_open() && outputFile.is_open())
    {
        writeCodeTable(outputFileName);
        char readIn;
        std::string output{};
        while (inputFile.get(readIn))
        {
            std::string str = codeTable[readIn];
            output += str;
        }
        outputFile << output;

        inputFile.close();
        outputFile.close();
    }
    else
    {
        std::cout << "Could not open file for compression" << std::endl;
    }
}
