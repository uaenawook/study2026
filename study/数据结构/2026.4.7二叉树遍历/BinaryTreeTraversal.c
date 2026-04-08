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


// 通过前序遍历的数组"ABD##E#H##CF##G##"构建二叉树
BTNode* _BinaryTreeCreate(char* a, int* pi)
{
	if (a[*pi] == '#')
	{
		(*pi)++;
		return NULL;
	}
	BTNode* root = (BTNode*)malloc(sizeof(BTNode));
	root->data = a[(*pi)++];
	root->left = _BinaryTreeCreate(a, pi);
	root->right = _BinaryTreeCreate(a, pi);
	return root;


}
void charPreOrder(BTNode* root)
{
	if (root == NULL)
	{
		//printf("NULL ");
		return;
	}

	printf("%c ", root->data);
	charPreOrder(root->left);
	charPreOrder(root->right);
}
BTNode* BinaryTreeCreate(char* a, int* pi)
{

	*pi = 0;
	BTNode* root = _BinaryTreeCreate(a, pi);
	printf("a的前序遍历：");
	charPreOrder(root);
	printf("\n");
	return root;
	
}
// 二叉树销毁
void BinaryTreeDestory(BTNode* root)
{
	if (root == NULL)
		return;
	BinaryTreeDestory(root->left);
	BinaryTreeDestory(root->right);
	free(root);
}
// 判断二叉树是否是完全二叉树
int BinaryTreeComplete(BTNode* root)
{
	// 利用栈 入根节点 根节点出带入子节点，
	//				如果出到NULL，后面还有非空则不是完全二叉树
	//				遇到空，后面全是空，栈出空了，则是完全二叉树
	Queue q;
	QueueInit(&q);
	QueuePush(&q, root);
	while (!QueueEmpty(&q))
	{
		//出队列
		BTNode* cur = QueueFront(&q);
		QueuePop(&q);
		// 如果出到空，检查后面是否有非空，非空返回0 ，全空返回1
		if (cur == NULL)
		{
			while (!QueueEmpty(&q))
			{
				BTNode* cur = QueueFront(&q);
				QueuePop(&q);
				if (cur != NULL)
				{
					QueueDestroy(&q);
					return 0;

				}
			}
			QueueDestroy(&q);
			return 1;
		}

		//代入孩子
		QueuePush(&q, cur->left);
		QueuePush(&q, cur->right);
	}
	QueueDestroy(&q);
	return 1;
}