#include<iostream>
using namespace std;
#include"BinarySearchTree.h"

// 实现二叉搜索树 和  key/value 结构


int main()
{

	BinarySearchTree<int> bst;
	bst.insert(8);
	bst.insert(5);
	bst.insert(2);
	bst.insert(9);
	bst.insert(3);
	bst.insert(6);

	bst.InOrderTree();
	return 0;
}