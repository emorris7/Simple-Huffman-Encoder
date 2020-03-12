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

//Test the mapping of char frequencies for a file using the file 'test.txt'
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

//test the buidling of the Huffman tree from the file 'test.txt'
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

    SECTION("Testing with a smaller real file"){
        MRREMI007::HuffmanTree tree;
        tree.buildFromFile("testSmall.txt");

        //check root frequency and check the left and right node characters
        REQUIRE((*(tree.root)).occurence == 3);
        REQUIRE((*((*(tree.root)).leftNode)).character == 'e');
        REQUIRE((*((*(tree.root)).rightNode)).character == 'p');
    }
}