#include "huffTree.h"

void huffTree::destroyHelp(treeNode<char>* r)
{
	if (leftChild(r) != nullptr) {
		destroyHelp(leftChild(r));
	}
	if (rightChild(r) != nullptr) {
		destroyHelp(rightChild(r));
	}
	//r is leaf
	if (r != root) {
		deleteThis(r);
	}
}

void huffTree::deleteLeftChild(treeNode<char>* cur)
{
	if (cur->leftChild != nullptr) {
		delete cur->leftChild;
		cur->leftChild = nullptr;
	}
}

void huffTree::deleteRightChild(treeNode<char>* cur)
{
	if (cur->rightChild != nullptr) {
		delete cur->rightChild;
		cur->rightChild = nullptr;
	}
}

void huffTree::deleteThis(treeNode<char>* cur)
{
	if (cur->parent->leftChild == cur) {
		cur->parent->leftChild = nullptr;
	}
	else {
		cur->parent->rightChild = nullptr;
	}
	delete cur;
}

treeNode<char>* huffTree::leftChild(const treeNode<char>* cur) const
{
	return cur->leftChild;
}

treeNode<char>* huffTree::rightChild(const treeNode<char>* cur) const
{
	return cur->rightChild;
}

void huffTree::breadthFirstHelp(treeNode<char>* cur, void(*visit)(treeNode<char>*))
{
	std::queue<treeNode<char>*> wait;
	wait.push(cur);
	while (wait.size()) {
		cur = wait.front();
		if (cur->leftChild != nullptr) {
			wait.push(cur->leftChild);
		}
		if (cur->rightChild != nullptr) {
			wait.push(cur->rightChild);
		}
		(*visit)(cur);
		wait.pop();
	}
}

huffTree::huffTree()
{
	root = nullptr;
}

huffTree::~huffTree()
{
	destroyHelp(root);
	delete root;
	root = nullptr;
}

bool huffTree::destoryTree(void)
{
	if (!root) {
		std::cout << "tree empty" << std::endl;
		return false;
	}
	destroyHelp(root);
	delete root;
	root = nullptr;
	return true;
}

treeNode<char>* huffTree::makeNode(std::pair<const char, int>& a)
{
	treeNode<char>* p = new treeNode<char>;
	p->data = a.first;
	p->weight = a.second;
	return p;
}

treeNode<char>* huffTree::emergeTwo(treeNode<char>* a, treeNode<char>* b)
{
	treeNode<char>* p;
	p = new treeNode<char>;
	p->data = 0;
	p->leftChild = a;
	p->rightChild = b;
	p->weight = a->weight + b->weight;
	a->parent = p;
	b->parent = p;
	return p;
}

void printElem(treeNode<char>* i) {
	static int depth = 1;
	std::cout << "char: " << i->data <<
		"(" << (unsigned int)(i->data) << ")" <<
		" weight: " << i->weight << std::endl;
	if (depth %= 2) {
		std::cout << std::endl;
	}
	++depth;
}

void huffTree::showTree(void)
{
	breadthFirstHelp(root, &printElem);
}

void huffTree::turnLeft(treeNode<char>*& cur)
{
	if (cur->leftChild) {
		cur = cur->leftChild;
	}
	else {
		treeNode<char>* p = new treeNode<char>;
		p->parent = cur;
		cur->leftChild = p;
		cur = p;
	}
}

void huffTree::turnLeftS(treeNode<char>*& cur)
{
	cur = cur->leftChild;
}

void huffTree::turnRightS(treeNode<char>*& cur)
{
	cur = cur->rightChild;
}

void huffTree::turnRight(treeNode<char>*& cur)
{
	if (cur->rightChild) {
		cur = cur->rightChild;
	}
	else {
		treeNode<char>* p = new treeNode<char>;
		p->parent = cur;
		cur->rightChild = p;
		cur = p;
	}
}
