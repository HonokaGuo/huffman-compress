#include "huffmanCompress.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "huffTree.h"
//modi sort
bool cmp(treeNode<char>* a, treeNode<char>* b) {
    return a->weight > b->weight;
}

void huffmanCompress::read()
{
    std::ifstream inFile;
    std::cout << "please enter file name (file limit :4039MB)" << std::endl;
    std::cin >> fileName;
    inFile.open(fileName, std::ios::in);
    while (!inFile.is_open()) {
        std::cout << "file doesn't exit!" << std::endl;
        std::cout << "please enter file name" << std::endl;
        std::cin >> fileName;
        inFile.open(fileName, std::ios::in);
    }
    //file has opened
    std::cout << "success!" << std::endl;
    char buf;
    while (inFile.read(&buf, sizeof(buf))) {
        ++weight_map[buf];
    }
    inFile.close();
    for (auto i = weight_map.begin(); i != weight_map.end(); ++i) {
        weight_vec.push_back(tree.makeNode(*i));
    }
    weight_map.clear();
    std::sort(weight_vec.begin(), weight_vec.end(), cmp);
    showWeight();
}

void huffmanCompress::showWeight(void)
{
    for (auto i = weight_vec.begin(); i != weight_vec.end(); ++i) {
        std::cout << "char: " << (*i)->data << 
            "(" << (unsigned int)((*i)->data) << ")" <<
            " weight: " << (*i)->weight << std::endl;
    }
    std::cout << "------------------------" << std::endl;
}

void huffmanCompress::compress()
{
    read();
    makeTree();
    genCompressedFile();
}

void huffmanCompress::makeTree()
{
    int size = weight_vec.end() - weight_vec.begin();
    treeNode<char>* tmp = nullptr;
    while (size != 1) {
        tmp = tree.emergeTwo(*(weight_vec.end() - 2), *(weight_vec.end() - 1));
        weight_vec.pop_back();
        weight_vec.pop_back();
        weight_vec.emplace_back(tmp);
        --size;
        // might be faster than vec.end()
        std::sort(weight_vec.begin(), weight_vec.begin() + size, cmp);
        showWeight();
    }
    tree.root = *weight_vec.begin();
    weight_vec.clear();
    tree.showTree();
}

char strTo8bitChar(std::string &temp) {
    std::string material;
    material = temp.substr(0, 8);
    //std::cout << material << std::endl;
    temp = temp.substr(8);
    //std::cout << temp << std::endl;
    char buf = 0;
    for (int i = 0; i < 8; ++i) {
        buf *= 2;
        buf += material[i] - '0';
    }
    return buf;
}

void huffmanCompress::genCompressedFile(void)
{
    std::string str = "";
    makeDiction(str, tree.root);
    for (auto i = dic.begin(); i!= dic.end(); ++i) {
        std::cout << "char:" << (*i).first << (*i).second << std::endl;
    }
    std::cout << "-------------" << std::endl;

    std::ifstream inFile;
    std::ofstream outFile;
    inFile.open(fileName, std::ios::in);
    outFile.open(fileName + ".huf", std::ios::out);
    if (!inFile.is_open()) {
        std::cout << "file moved!" << std::endl;
    }
    if (!outFile.is_open()) {
        std::cout << "create file failed" << std::endl;
    }

    //////////////////////////
    char buf;
    unsigned long count = 0;
    while (inFile.read(&buf, sizeof(buf))) {
        count++;
    }
    outFile << count << "$";
    inFile.close();
    inFile.open(fileName, std::ios::in);
    if (!inFile.is_open()) {
        std::cout << "file moved!" << std::endl;
    }
    /////////////////////////

    int leaf = 0;
    for (auto i = dic.begin(); i != dic.end(); ++i) {
        leaf++;
    }
    outFile << leaf << "$";
    for (auto i = dic.begin(); i != dic.end(); ++i) {
        
         outFile << (*i).second << "$" << (*i).first;
        
    }                                          //114$8$001$A000$B(byte data)          
    
                                               
                                               // tree already in
    std::cout << "------------" << std::endl;
    std::string temp = "";
    while (inFile.read(&buf, sizeof(buf))) {
        temp += dic[buf];
        while (temp.size() >= 8) {
            outFile << strTo8bitChar(temp);
        }
    }
    
    if (temp != "") {
        while (temp.size() >= 8) {
            outFile << strTo8bitChar(temp);
        }
        if (temp != "") {
            
            while (temp.size() != 8) {
                temp += "0";
            }
            outFile << strTo8bitChar(temp);
        }
    }
    
    inFile.close();
    outFile.close();
    dic.clear();
    if (tree.destoryTree()) {
        std::cout << "done! new file is " << fileName + ".huf" << std::endl;
        std::cout << "c to compress another file, d to decompress, q to quit" << std::endl;
    }
} 

void huffmanCompress::makeDiction(std::string str, treeNode<char>* cur)
{
    if (cur->leftChild == nullptr) {
        dic[cur->data] = str;
    }
    else {
        makeDiction(str + "0", cur->leftChild);
        makeDiction(str + "1", cur->rightChild);
    }
}

std::string charTo8bits(char cha) {
    std::string str= "";
    char buf[8]{'0'};
    int i = 0;
    unsigned int ch = cha;
    while (i < 8) {
        buf[i] = '0' + ch % 2;
        ch /= 2;
        ++i;
    }
    for (i = 7; i != -1; --i) {
        str += buf[i];
        //std::cout << buf[i];
    }
    //std::cout << std::endl;
    return str;
}

void huffmanCompress::readHuf(void)
{
    std::ifstream inFile;
    std::cout << "please enter file name (.huf)" << std::endl;
    std::cin >> fileName;
    inFile.open(fileName, std::ios::in|std::ios::binary);
    while (!inFile.is_open()) {
        std::cout << "file doesn't exit!" << std::endl;
        std::cout << "please enter file name" << std::endl;
        std::cin >> fileName;
        inFile.open(fileName, std::ios::in|std::ios::binary);
    }
    //file has opened
    std::cout << "success!" << std::endl;
    //114$8$001$A000$B(byte data)
    //total count/type num/
    unsigned long totalCount = 0;
    int typeNum = 0;
    char buf;
    while (inFile.read(&buf, sizeof(buf))) {
        if (buf != '$') {
            totalCount *= 10;
            totalCount += buf - '0';
        }
        else {
            break;
        }
    }
    std::cout << totalCount << std::endl;

    while (inFile.read(&buf, sizeof(buf))) {
        if (buf != '$') {
            typeNum *= 10;
            typeNum += buf - '0';
        }
        else {
            break;
        }
    }
    std::cout << typeNum << std::endl;

    //bulid a tree
    if (tree.root) {
        std::cout << "memory leakage!" << std::endl;
        exit(0);
    }
    treeNode<char>* cur = new treeNode<char>;
    tree.root = cur;
    while (typeNum) {
        inFile.read(&buf, sizeof(buf));
        if (buf != '$') {
            if (buf == '0') {
                tree.turnLeft(cur);
            }
            else {
                tree.turnRight(cur);
            }

        } else {
            inFile.read(&buf, sizeof(buf));
            if (buf != 0x0D) {
                cur->data = buf;
            }
            else {
                inFile.read(&buf, sizeof(buf));
                cur->data = buf;
            }
            cur = tree.root;
            --typeNum;
        }
    }
    tree.showTree();
    std::cout << "tree has reconstructed" << std::endl;
    std::ofstream outFile;
    newName = fileName.substr(0, fileName.size() - 4);
    newName = "new_" + newName;
    outFile.open(newName, std::ios::out);
    outFile.close();

    cur = tree.root;
    std::string stream = "";
    while (totalCount && inFile.read(&buf, sizeof(buf))) {
        stream += charTo8bits(buf);
        genDecompressedFile(stream, totalCount, cur);
    }
    while (totalCount) {
        genDecompressedFile(stream, totalCount, cur);
    }
    inFile.close();
    std::cout << "done! File is " << newName << std::endl;
}

void huffmanCompress::genDecompressedFile(std::string& str, unsigned long&totalCount, treeNode<char>*& cur) {
    std::ofstream outFile;
    outFile.open(newName, std::ios::app);
    int pos = 0;
    int size = str.size();

    while (pos < size && totalCount) {
        if (str[pos] == '0') {
            tree.turnLeftS(cur);
            if (!(cur->leftChild)) {
                outFile << cur->data;
                //std::cout << cur->data;
                cur = tree.root;
                --totalCount;
            }
        }
        else {
            tree.turnRightS(cur);
            if (!(cur->leftChild) ) {
                outFile << cur->data;
                //std::cout << cur->data;
                cur = tree.root;
                --totalCount;
            }
        }
        ++pos;
    }
    str = "";
    outFile.close();
}

void huffmanCompress::decompress()
{
    readHuf();
    tree.destoryTree();
}


