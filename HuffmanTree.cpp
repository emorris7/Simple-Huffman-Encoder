#include "HuffmanTree.h"
#include <iostream>
#include <fstream>
#include <cstdio>

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

//write code table to a file, (numbers of fields is number of bytes in file?)
void MRREMI007::HuffmanTree::writeCodeTable(std::string fileName)
{
    //check if there is actually anything in the code table
    if (codeTable.size() == 0)
    {
        std::cout << "Code table is empty, cannot create code table" << std::endl;
        return;
    }
    std::ofstream outputFile(fileName + ".hdr");
    if (outputFile.is_open())
    {
        outputFile << codeTable.size() << "\n";
        int counter{1};
        for (auto &e : codeTable)
        {
            if (counter < codeTable.size())
            {
                outputFile << e.first << " " << e.second << "\n";
                counter++;
            }
            else
            {
                outputFile << e.first << " " << e.second;
            }
        }
        outputFile.close();
    }
    else
    {
        std::cout << "Could not open header file" << std::endl;
    }
}

//compress the given file and write compressed data to the given output file;
void MRREMI007::HuffmanTree::compressFile(const std::string inputFileName, const std::string outputFileName)
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
        char readIn;
        std::string output{};
        long byteCounter{};
        long bitCounter{};
        while (inputFile.get(readIn))
        {
            std::string str = codeTable[readIn];
            byteCounter++;
            bitCounter += str.length();
            output += str;
        }
        writeCodeTable(outputFileName);
        //calculate padding
        long offSet = (bitCounter / 8) + (bitCounter % 8 ? 1 : 0);
        //pad string with zero's for extra bytes
        for (int i = bitCounter; i < offSet * 8; i++)
        {
            output += "0";
        }
        outputFile << output;

        //calculate compression ratio and print
        int ratio = (byteCounter * 8) / bitCounter;
        std::cout << "Compression ratio is roughly 1:" << ratio << std::endl;

        inputFile.close();
        outputFile.close();
    }
    else
    {
        std::cout << "Could not open file for compression" << std::endl;
    }
}

void MRREMI007::HuffmanTree::compressFileBinary(const std::string inputFileName, const std::string outputFileName)
{
    buildFromFile(inputFileName);
    makeCodeTable();
    if (codeTable.size() == 0)
    {
        return;
    }
    std::ifstream inputFile(inputFileName);
    std::ofstream outputFile(outputFileName, std::ios::binary);

    if (inputFile.is_open() && outputFile.is_open())
    {
        char readIn;
        std::string output{};
        long byteCounter{};
        long bitCounter{};
        while (inputFile.get(readIn))
        {
            std::string str = codeTable[readIn];
            byteCounter++;
            bitCounter += str.length();
            output += str;
        }
        writeCodeTable(outputFileName);
        //calculate padding
        long offSet = (bitCounter / 8) + (bitCounter % 8 ? 1 : 0);
        //pad string with zero's for extra bytes
        for (int i = bitCounter; i < offSet * 8; i++)
        {
            output += "0";
        }
        //extract cstring
        std::cout << output << std::endl;
        const char *cstring = output.c_str();
        //convert to bits and write to file

        for (int i = 0; i < output.length(); i += 8)
        {
            // unsigned char val{0};
            unsigned char check{0};
            for (int j = 0; j < 8; j++)
            {
                // if (cstring[i + j] == '1')
                // {
                //     val |= 1;
                //     std::cout << "not shift " << std::to_string(val) << std::endl;
                // }
                // if (j < 7)
                // {
                //     val <<= 1;
                //     std::cout << std::to_string(val) << std::endl;
                // }

                // std::cout << "char " << j << " " << std::to_string(cstring[i + j]) << std::endl;
                check |= (((int)cstring[i + j] - 48) << (7 - j)); //minus 48 to get actual int value (1/0)
            }
            // outputFile << val;
            outputFile << check;
        }

        //calculate compression ratio and print
        int ratio = (byteCounter * 8) / bitCounter;
        std::cout << "Compression ratio is roughly 1:" << ratio << std::endl;

        inputFile.close();
        outputFile.close();
    }
    else
    {
        std::cout << "Could not open file for compression" << std::endl;
    }
}

//extract compressed data to its encoded string representation
void MRREMI007::HuffmanTree::decompressFileBinary(const std::string inputFileName)
{
    std::FILE *input = fopen(inputFileName.c_str(), "r");
    if (input != nullptr)
    {
        unsigned char *c = new unsigned char[1];
        std::string encoding{};
        while (fread(c, 1, 1, input))
        {
            for (int i = 7; i > -1; --i)
            {
                char check = *c >> i;
                int val = check & 1;
                encoding += std::to_string(val);
            }
        }
        fclose(input);
        delete[] c;
        std::cout << encoding << std::endl;
    }
    else
    {
        std::cout << "Unable to open binary file for decompression" << std::endl;
    }
}
