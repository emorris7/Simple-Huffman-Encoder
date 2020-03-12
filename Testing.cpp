#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "HuffmanTree.h"
#include "HuffmanNode.h"

//check that priority queue is ordering Huffman Nodes correctly
TEST_CASE("Testing Priority Queue", "[Priority Queue]")
{
    std::unordered_map<char, int> map;
    map.insert({'j', 2});
    map.insert({'h', 4});
    map.insert({'k', 5});
    map.insert({'l', 1});

    MRREMI007::HuffmanTree tree;
    std::priority_queue<MRREMI007::HuffmanNode, std::vector<MRREMI007::HuffmanNode>, MRREMI007::HuffmanTree::compare> prio = tree.prioritise(map);
    SECTION("Testing to see if priority queue creation worked and that it is a min heap")
    {
        REQUIRE(prio.top().character == 'l');
        prio.pop();
        REQUIRE(prio.top().character == 'j');
        prio.pop();
        REQUIRE(prio.top().character == 'h');
        prio.pop();
        REQUIRE(prio.top().character == 'k');
        prio.pop();
        REQUIRE(prio.empty());
    }

    SECTION("Testing to see that if two nodes have the same frequency, the one added last is second")
    {
        MRREMI007::HuffmanNode nodeOne{'e', 1};
        prio.push(nodeOne);
        REQUIRE(prio.top().character == 'l');
    }
}

//Test the mapping of char frequencies
TEST_CASE("Testing map frequency", "[Frequency Map]")
{

    SECTION("Testing with a file that does not exist")
    {
        MRREMI007::HuffmanTree tree;
        std::unordered_map<char, int> map = tree.mapFrequency("blahhh");
        REQUIRE(map.empty());
    }

    SECTION("Testing a real file")
    {
        MRREMI007::HuffmanTree tree;
        std::unordered_map<char, int> map = tree.mapFrequency("test.txt");

        REQUIRE(map['y'] == 2);
        REQUIRE(map['e'] == 4);
        REQUIRE(map['p'] == 3);
        REQUIRE(map[' '] == 1);
    }
}

//Test the buidling of the Huffman tree
TEST_CASE("Testing building a Huffman Tree", "[Huffman Tree]")
{

    SECTION("Testing with a file that does not exist")
    {
        MRREMI007::HuffmanTree tree;
        tree.buildFromFile("blahhh");
        REQUIRE(tree.root == nullptr);
    }

    SECTION("Testing a real file")
    {
        MRREMI007::HuffmanTree tree;
        tree.buildFromFile("test.txt");

        //check root frequency and check the left node character value (easiest to access)
        REQUIRE((*(tree.root)).occurence == 10);
        REQUIRE((*((*(tree.root)).leftNode)).character == 'e');
    }

    SECTION("Testing with a smaller real file")
    {
        MRREMI007::HuffmanTree tree;
        tree.buildFromFile("testSmall.txt");

        //check root frequency and check the left and right node characters
        REQUIRE((*(tree.root)).occurence == 3);
        REQUIRE((*((*(tree.root)).leftNode)).character == 'e');
        REQUIRE((*((*(tree.root)).rightNode)).character == 'p');
    }
}

//Test the code table creation method for the Huffman Tree
TEST_CASE("Testing the code table creation", "[Code Table]")
{

    SECTION("Testing with a file that does not exist")
    {
        MRREMI007::HuffmanTree tree;
        tree.makeCodeTable();
        REQUIRE(tree.codeTable.empty());
    }

    SECTION("Testing a real file")
    {
        MRREMI007::HuffmanTree tree;
        tree.buildFromFile("test.txt");
        tree.makeCodeTable();

        REQUIRE(tree.codeTable['y'] == "111"); //right most branch as added after node p with frequency 3, meaning combined 3 node comes out second
        REQUIRE(tree.codeTable['e'] == "0");
        REQUIRE(tree.codeTable['p'] == "10");
        REQUIRE(tree.codeTable[' '] == "110");
    }

    SECTION("Testing with a smaller real file")
    {
        MRREMI007::HuffmanTree tree;
        tree.buildFromFile("testSmall.txt");
        tree.makeCodeTable();

        REQUIRE(tree.codeTable['e'] == "0");
        REQUIRE(tree.codeTable['p'] == "1");
    }
}

//Test basic file compression, where it is a simple string
TEST_CASE("Testing basic compression", "[Basic Compression]")
{
    SECTION("Testing with a file that does not exist")
    {
        MRREMI007::HuffmanTree tree;
        tree.compressFile("blaahhh", "outputBlahh");
        std::ifstream output("outputBlahh");
        std::ifstream outputHeader("outputBlahh.hdr");

        REQUIRE(!output.is_open());
        REQUIRE(!outputHeader.is_open());
    }

    SECTION("Testing with a file that exist")
    {
        MRREMI007::HuffmanTree tree;
        tree.compressFile("test.txt", "outputBasic");
        std::ifstream output("outputBasic");

        REQUIRE(output.is_open());
        std::string encoding{};
        std::getline(output, encoding);
        REQUIRE(encoding == "1110101100001111010");
    }

    SECTION("Testing with small file")
    {
        MRREMI007::HuffmanTree tree;
        tree.compressFile("testSmall.txt", "outputBasicSmall");
        std::ifstream output("outputBasicSmall");

        REQUIRE(output.is_open());
        std::string encoding{};
        std::getline(output, encoding);
        REQUIRE(encoding == "011");
    }
}

//Test file compression to binary
TEST_CASE("Testing binary compression", "[Binary Compression]")
{
    SECTION("Testing with a file that does not exist")
    {
        MRREMI007::HuffmanTree tree;
        tree.compressFileBinary("blaahhh", "outputBlahh");
        std::ifstream output("outputBlahh");
        std::ifstream outputHeader("outputBlahh.hdr");

        REQUIRE(!output.is_open());
        REQUIRE(!outputHeader.is_open());
    }

    SECTION("Testing with a file that exist")
    {
        MRREMI007::HuffmanTree tree;
        tree.compressFileBinary("test.txt", "outputBinary");
        std::FILE *input = fopen("outputBinary", "r");

        REQUIRE(input != nullptr);

        unsigned char *c = new unsigned char[1];
        fread(c, 1, 1, input);
        REQUIRE(*c == 235);
        fread(c, 1, 1, input);
        REQUIRE(*c == 15);
        fread(c, 1, 1, input);
        REQUIRE(*c == 64);

        fclose(input);
        delete[] c;
    }

    SECTION("Testing with small file")
    {
        MRREMI007::HuffmanTree tree;
        tree.compressFileBinary("testSmall.txt", "outputBinarySmall");
        std::FILE *input = fopen("outputBinarySmall", "r");

        REQUIRE(input != nullptr);

        unsigned char *c = new unsigned char[1];
        fread(c, 1, 1, input);
        REQUIRE(*c == 96);

        fclose(input);
        delete[] c;
    }
}

//Test file decompression
TEST_CASE("Testing binary decompression", "[Binary Decompression]")
{
    SECTION("Testing with a file that does not exist")
    {
        MRREMI007::HuffmanTree tree;
        tree.decompressFileBinary("blaahhh", "outputBlahh");
        std::ifstream output("outputBlahh");
        std::ifstream outputHeader("outputBlahh.hdr");

        REQUIRE(!output.is_open());
        REQUIRE(!outputHeader.is_open());
    }

    SECTION("Testing with a file that exist")
    {
        MRREMI007::HuffmanTree tree;
        tree.decompressFileBinary("outputBinary", "outputDecompress");
         std::ifstream output("outputDecompress");

        REQUIRE(output.is_open());
        std::string encoding{};
        std::getline(output, encoding);
        REQUIRE(encoding == "111010110000111101000000");

    }

    SECTION("Testing with small file")
    {
        MRREMI007::HuffmanTree tree;
        tree.decompressFileBinary("outputBinarySmall", "outputDecompressSmall");
        std::ifstream output("outputDecompressSmall");

        REQUIRE(output.is_open());
        std::string encoding{};
        std::getline(output, encoding);
        REQUIRE(encoding == "01100000");
    }
}