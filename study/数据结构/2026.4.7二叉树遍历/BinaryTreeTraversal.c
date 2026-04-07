#include"BinaryTreeTraversal.h"


void BTIint(BTNode* pbt)
{
	pbt->data = -1;
	pbt->left = pbt->right = NULL;
}
void BTDestroy(BTNode* pbt)
{

}

BTNode* BTBuyNode(BTDataType x)
{
	BTNode* newNode = (BTNode*)malloc(sizeof(BTNode));
	if (newNode == NULL)
	{
		perror("BTBuyNode malloc fail!\n");
		exit(-1);
	}
	newNode->data = x;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;

}

// 二叉树前序遍历 
void PreOrder(BTNode* root)
{
	if (root == NULL)
	{
		//printf("NULL ");
		return;
	}

	printf("%d ", root->data);
	PreOrder(root->left);
	PreOrder(root->right);
}
// 二叉树中序遍历
void InOrder(BTNode* root)
{
	if (root == NULL)
	{
		//printf("NULL ");
		return;
	}

	InOrder(root->left);
	printf("%d ", root->data);
	InOrder(root->right);
}
// 二叉树后序遍历
void PostOrder(BTNode* root)
{
	if (root == NULL)
	{
		//printf("NULL ");
		return;
	}

	PostOrder(root->left);
	PostOrder(root->right);
	printf("%d ", root->data);
}

// 层序遍历
void LevelOrder(BTNode* root)
{

	// 利用队列先进后出特性层序遍历， 根进先，根出来后带入左右孩子。
	//								继续左孩子视为根，出队列带入左孩子的左右孩子
	//								继续右孩子视为根，出对了带入右孩子的左右孩子
	//								当队列为空，则结束
	//								如果根的左孩子不为空，则左孩子入队列，反之不入
	//								如果根的右孩子不为空，则右孩子入队列，反之不入
	assert(root);
	Queue q;
	QueueInit(&q);
	//先入根
	QueuePush(&q, root);
	//队列不为空则继续
	while (!QueueEmpty(&q))
	{
		//接收根，方便找到左右孩子
		BTNode* cur = QueueFront(&q);
		//打印根的值
		printf("%d ", cur->data);
		//根出队列
		QueuePop(&q);
		//带入左右孩子
		if (cur->left != NULL)
		{
			QueuePush(&q, cur->left);
		}
		if (cur->right != NULL)
		{
			QueuePush(&q, cur->right);
		}
	}
	QueueDestroy(&q);
}


int _BinaryTreeSize(BTNode* root, int* n)
{
	if (root == NULL)
	{
		return 0;
	}
	else
	{
		(*n)++;
	}
	_BinaryTreeSize(root->left, n);
	_BinaryTreeSize(root->right, n);
	return *n;	

}

// 二叉树结点个数
int BinaryTreeSize(BTNode* root)
{
	//static int n = 0;
	//return _BinaryTreeSize(root, &n);
	return root == NULL ? 0 : BinaryTreeSize(root->left) + BinaryTreeSize(root->right) + 1;
}

// 二叉树叶子结点个数
int BinaryTreeLeafSize(BTNode* root)
{
	if (root == NULL)
		return 0;

	if (root->left == NULL && root->right == NULL)
		return 1;

	return BinaryTreeLeafSize(root->left) + BinaryTreeLeafSize(root->right);
}
// 二叉树第k层结点个数
int BinaryTreeLevelKSize(BTNode* root, int k)
{
	if (root == NULL)
		return 0;
	if (k == 1)
		return 1;

	return BinaryTreeLevelKSize(root->left, k - 1) + BinaryTreeLevelKSize(root->right, k - 1);
}
// 二叉树查找值为x的结点
BTNode* BinaryTreeFind(BTNode* root, BTDataType x)
{	
	if (root == NULL)
		return NULL;
	if (root->data == x)
		return root;

	BTNode*left = BinaryTreeFind(root->left, x);
	if (left)
		return left;
	BTNode*right = BinaryTreeFind(root->right, x);
	if (right)
		return right;
	return NULL;
}