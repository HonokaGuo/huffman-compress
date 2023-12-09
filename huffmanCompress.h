#pragma once
#include <map>
#include <vector>
#include "huffTree.h"
#include <string>
class huffmanCompress
{
private:
	std::string fileName;
	std::string newName;
	std::map<char, int> weight_map;
	std::map<char, std::string> dic;		  //dictionary
	std::vector<treeNode<char>*> weight_vec; //store node pointers
	huffTree tree;
	void read(void);   //genelize weight
	void showWeight(void);
	void makeTree(void);
	void makeDiction(std::string str, treeNode<char>* cur);
	void genCompressedFile(void);
	//below de
	void readHuf(void);
	void genDecompressedFile(std::string& str, unsigned long& totalCount, treeNode<char>*& cur);
public:
	void compress();
	void decompress();
};

