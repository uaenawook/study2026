#pragma once

template <class T>
class BinarySearchTreeNode
{
public:
	T val;
	BinarySearchTreeNode<T>* left;
	BinarySearchTreeNode<T>* right;


	BinarySearchTreeNode(const T& v)
		:val(v)
		,left(nullptr)
		,right(nullptr)
	{}
};

template <class T>
class BinarySearchTree
{
public:

	BinarySearchTree()
		:_root(nullptr)
	{}



	

	bool insert(const T& v)
	{
		if (_root == nullptr)
		{
			_root = new BinarySearchTreeNode<int>(v);
		}
		else
		{
			BinarySearchTreeNode<T>* cur = _root;
			BinarySearchTreeNode<T>* parent = cur;

			while (cur)
			{
				parent = cur;
				if (cur->val < v)
				{
					cur = cur->right;
				}
				else if (cur->val > v)
				{
					cur = cur->left;
				}
				else
				{
					return false;
				}
			}
			if(parent->val > v)
				parent->left = new BinarySearchTreeNode<int>(v);
			else
				parent->right = new BinarySearchTreeNode<int>(v);
		}
	}
	void InOrderTree()
	{
		_InOrderTree(_root);
	}

private:
	BinarySearchTreeNode<T>* _root;

	void _InOrderTree(const BinarySearchTreeNode<int>* root)
	{
		if (root == nullptr)
			return;
		_InOrderTree(root->left);
		cout << root->val << " ";
		_InOrderTree(root->right);
	}
};