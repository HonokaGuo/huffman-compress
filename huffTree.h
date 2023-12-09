#pragma once
#include "node.h"
#include <utility>
#include <iostream>
#include <queue>
class huffTree
{
private:
	void destroyHelp(treeNode<char>* r);
	void deleteLeftChild(treeNode<char>* cur);
	void deleteRightChild(treeNode<char>* cur);
	void deleteThis(treeNode<char>* cur);
	treeNode<char>* leftChild(const treeNode<char>* cur) const;
	treeNode<char>* rightChild(const treeNode<char>* cur) const;
	void breadthFirstHelp(treeNode<char>* cur, void(*visit)(treeNode<char>*));
public:
	treeNode<char>* root;
	huffTree();
	~huffTree();
	bool destoryTree(void);
	treeNode<char>* makeNode(std::pair<const char, int>&);
	treeNode<char>* emergeTwo(treeNode<char>* a, treeNode<char>* b);
	void showTree(void);
	void turnLeft(treeNode<char>*& cur);
	void turnLeftS(treeNode<char>*& cur);
	void turnRightS(treeNode<char>*& cur);
	void turnRight(treeNode<char>*& cur);
};

