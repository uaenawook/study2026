#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include"Queue.h"

typedef int BTDataType;

typedef struct BinaryTreeNode
{
	BTDataType data;
	struct BinaryTreeNode* left;
	struct BinaryTreeNode* right;
}BTNode;


BTNode* BTBuyNode(int x);
// 二叉树前序遍历 
void PreOrder(BTNode* root);
// 二叉树中序遍历
void InOrder(BTNode* root);
// 二叉树后序遍历
void PostOrder(BTNode* root);
// 层序遍历
void LevelOrder(BTNode* root);


// 二叉树结点个数
int BinaryTreeSize(BTNode* root);
// 二叉树叶子结点个数
int BinaryTreeLeafSize(BTNode* root);
// 二叉树第k层结点个数
int BinaryTreeLevelKSize(BTNode* root, int k);
// 二叉树查找值为x的结点
BTNode* BinaryTreeFind(BTNode* root, BTDataType x);
