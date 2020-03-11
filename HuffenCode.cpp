#include "HuffmanTree.h"
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cout << "Invalid run attempt, please supply input and output file names" << std::endl;
    }
    else if (argc == 3)
    {
        MRREMI007::HuffmanTree tree;
        tree.compressFile(argv[1], argv[2]);
    }
    //run with optional -b for bit packing
    else{
        MRREMI007::HuffmanTree tree;
        tree.compressFileBinary(argv[2], argv[3]);
    }
}