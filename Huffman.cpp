#include <iostream>
#include<queue>
#include<iomanip>
using namespace std;

int length = 0;
queue<pair<int,int>> codes_len;int sum_times = 0;

class HuffmanTreeNode
{
public:
    int char_id;
    int char_weight;
    int code_len;
    HuffmanTreeNode* leftchild, * rightchild;
};

class HuffmanTree
{
public:
    HuffmanTreeNode* root;
    HuffmanTree()
    {
        this->root = nullptr;
    }
    void compute(HuffmanTreeNode* root);
    void averange(int n);
};

bool operator > (const HuffmanTreeNode& node1, const HuffmanTreeNode& node2)
{
	return node1.char_weight > node2.char_weight;
}

void HuffmanTree::compute(HuffmanTreeNode* root)
{
    length++;
    if (root->leftchild == nullptr && root->rightchild == nullptr)
    {
        root->code_len = length-1;
        pair<int, int> tmp; 
        tmp.first = root->code_len;tmp.second = root->char_weight;
        codes_len.push(tmp);
        return;
    }

    compute(root->leftchild);
    length--;
    compute(root->rightchild);
    length--;

}

void HuffmanTree::averange(int n)
{
    float aver = 0;
    while (!codes_len.empty())
    {
        aver += float(codes_len.front().first * (codes_len.front().second/float(sum_times)));
        codes_len.pop();
    }
    cout<< fixed << setprecision(2) << aver;
}



int main()
{
    int n;
    cin >> n;
    priority_queue<HuffmanTreeNode,vector<HuffmanTreeNode>,greater<HuffmanTreeNode>> huffman_que;

    for (int i = 0; i < n; i++)
    {
        HuffmanTreeNode * receive_char = new HuffmanTreeNode();
        receive_char->char_id = i + 1;
        receive_char->code_len = 0;
        receive_char->leftchild = nullptr;
        receive_char->rightchild = nullptr;
        cin >> receive_char->char_weight;
        sum_times += receive_char->char_weight;
        huffman_que.push(*(receive_char));
    }



    HuffmanTree huffman_tree;

    while(!huffman_que.empty())
    {
        HuffmanTreeNode* combine_node = new HuffmanTreeNode();
        HuffmanTreeNode* que_first_node = new HuffmanTreeNode(), * que_second_node = new HuffmanTreeNode();
        *que_first_node = huffman_que.top();  huffman_que.pop();
        if (huffman_que.empty())
        {
            huffman_tree.root = &(*que_first_node);
            break;
        }
        *que_second_node = huffman_que.top(); huffman_que.pop();

        combine_node->leftchild = que_first_node;
        combine_node->rightchild = que_second_node;
        combine_node->char_weight = que_first_node->char_weight + que_second_node->char_weight;

        huffman_que.push(*combine_node);

    }

    huffman_tree.compute(huffman_tree.root);
    huffman_tree.averange(n);

    return 0;
}