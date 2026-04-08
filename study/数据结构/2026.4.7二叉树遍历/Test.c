#include"BinaryTreeTraversal.h"


BTNode* CreatBinaryTree()
{
	BTNode* node1 = BTBuyNode(1);
	BTNode* node2 = BTBuyNode(2);
	BTNode* node3 = BTBuyNode(3);
	BTNode* node4 = BTBuyNode(4);
	BTNode* node5 = BTBuyNode(5);
	BTNode* node6 = BTBuyNode(6);
	BTNode* node7 = BTBuyNode(7);


	node1->left = node2;
	node1->right = node4;
	node2->left = node3;
	node4->left = node5;
	node4->right = node6;
	node2->right = node7;

	return node1;
}


int main()
{

	BTNode* root =  CreatBinaryTree();

	printf("前序遍历：");
	PreOrder(root);
	printf("\n");

	printf("中序遍历：");
	InOrder(root);
	printf("\n");

	printf("后序遍历：");
	PostOrder(root);
	printf("\n");

	printf("层序遍历：");
	LevelOrder(root);
	printf("\n");

	printf("节点个数：%d\n", BinaryTreeSize(root));
	printf("叶子节点个数：%d\n", BinaryTreeLeafSize(root));
	printf("第K层节点个数：%d\n", BinaryTreeLevelKSize(root,4));

	BTNode* find = BinaryTreeFind(root, 7);
	if (find == NULL)
	{
		printf("没找到！\n");
	}
	else {
		printf("找到了：%d\n", find->data);
	}


	char a[] = { "ABD##E#H##CF##G##" };
	int i = 0;
	BinaryTreeCreate(&a,&i);

	printf("判断是否是完全二叉树0为假，1为真：%d",BinaryTreeComplete(root));
	printf("\n");

	return 0;
}