#ifndef HUFFMANNODE
#define HUFFMANNODE
#include <memory>

namespace MRREMI007
{
class HuffmanNode
{
private:
    std::shared_ptr<HuffmanNode> leftNode;
    std::shared_ptr<HuffmanNode> rightNode;
    int occurence;
    char character;

public:
    HuffmanNode(const int o, const char c);

    HuffmanNode();

    ~HuffmanNode();

    //copy constructor
    HuffmanNode(const HuffmanNode& other);

    //copy assignment
    HuffmanNode& operator=(const HuffmanNode& other);

    //move constructor
    HuffmanNode(HuffmanNode&& other);

    //move assignment 
    HuffmanNode& operator=(HuffmanNode&& other);

    void setLeftNode(const std::shared_ptr<HuffmanNode>& leftNode);

    void setRightNode(const std::shared_ptr<HuffmanNode>& RightNode);

    bool operator<(const HuffmanNode& other);
};

} // namespace MRREMI007

#endif