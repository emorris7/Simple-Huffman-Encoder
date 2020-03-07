#ifndef HUFFMANNODE
#define HUFFMANNODE
#include <memory>

namespace MRREMI007
{
class HuffmanNode
{

public:
    std::shared_ptr<HuffmanNode> leftNode;
    std::shared_ptr<HuffmanNode> rightNode;
    int occurence;
    char character;

    HuffmanNode(const char c, const int o);

    HuffmanNode();

    ~HuffmanNode();

    //copy constructor
    HuffmanNode(const HuffmanNode &other);

    //copy assignment
    HuffmanNode &operator=(const HuffmanNode &other);

    //move constructor
    HuffmanNode(HuffmanNode &&other);

    //move assignment
    HuffmanNode &operator=(HuffmanNode &&other);

    void setLeftNode(const std::shared_ptr<HuffmanNode> &leftNode);

    void setRightNode(const std::shared_ptr<HuffmanNode> &RightNode);

    friend bool operator>(const HuffmanNode &lhs, const HuffmanNode &rhs);
};

bool operator>(const HuffmanNode &lhs, const HuffmanNode &rhs);

} // namespace MRREMI007

#endif