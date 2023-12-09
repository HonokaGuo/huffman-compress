#pragma once

template <typename t>
class treeNode {
public:
	t data;
	int weight;
	treeNode<t>* rightChild; 
	treeNode<t>* leftChild;
	treeNode<t>* parent;
	treeNode();
	treeNode(const t& data, treeNode<t>* leftChild = nullptr,
		 treeNode<t>* rightChild = nullptr, treeNode<t>* parent = nullptr);
};

template<typename t>
inline treeNode<t>::treeNode()
{
	rightChild = nullptr;
	leftChild = nullptr;
	parent = nullptr;
}

template<typename t>
inline treeNode<t>::treeNode(const t& data, treeNode<t>* leftChild, treeNode<t>* rightChild, treeNode<t>* parent)
{
	this->data = data;
	this->leftChild = leftChild;
	this->rightChild = rightChild;
	this->parent = parent;
}
