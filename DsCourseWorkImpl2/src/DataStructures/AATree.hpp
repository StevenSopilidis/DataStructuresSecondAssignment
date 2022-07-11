#pragma once
#include "AATreeNode.h"
#include <iostream>

namespace DataStructures 
{
	template <typename T>
	class AATree 
	{
	//private:
		struct AATreeNode<T>* root = nullptr;
		void Skew(struct AATreeNode<T>*& node)
		{
			if (node->left == nullptr)
				return;
			else if (node->left->level == node->level)
			{
				// perform the skewing
				/* auto tmp = node;
				node = tmp->left;
				tmp->left = node->right;
				node->right = tmp;
				node->parent = tmp->parent;
				tmp->parent = node;*/
				auto tmp = node->data;
				auto tmp2 = node->left->right;
				auto tmp3 = node->right;
				node->data = node->left->data;
				node->left = node->left->left;
				node->right = new struct AATreeNode<T>;
				node->right->data = tmp;
				node->right->left = tmp2;
				node->right->right = tmp3;
				node->right->parent = node;
			}
		}
		bool Split(struct AATreeNode<T>*& node)
		{
			if (node->right == nullptr || node->right->right == nullptr)
				return false;
			else if (node->right->right->level == node->right->level)
			{
				auto tmp1 = node;
				auto tmp2 = node->right->right;
				auto tmp3 = node->right->left;
				auto tmp4 = node->data;
				auto tmp5 = node->left;

				node->data = node->right->data;
				node->parent = tmp1->parent;
				// fix left child
				node->left = new struct AATreeNode<T>;
				node->left->parent = node;
				node->left->left = tmp5;
				node->left->right = tmp3;
				node->left->data = tmp4;
				node->left->level = tmp1->level + 1;
				// fix right child
				node->right = new struct AATreeNode<T>;
				node->right->parent = node;
				node->right->left = tmp2->left;
				node->right->right = tmp2->right;
				node->right->data = tmp2->data;
				node->right->level = tmp1->level + 1;

				return true;
			}
		}

	public:
		/// <summary>
		/// method for deleting a node from tree
		/// </summary>
		/// <param name="data"> data to delete </param>
		/// <returns> boolean indicating wether element was removed successfully </returns>
		bool Delete(T data) {
			// first check if the element actually exists in the tree
			if (!Search(data))
				return false;
			auto p = root;
			struct AATreeNode<T>* pp = nullptr;
			while (p->data != data)
			{
				pp = p;
				if (data > p->data)
					p = p->right;
				else
					p = p->left;
			}
			auto deleted = p; // element that we deleted
			if (p->left != nullptr && p->right != nullptr)
			{
				// find the largest left child
				p = p->left;
				while (p->right != nullptr)
				{
					p = p->right;
				}
				deleted->data = p->data;
				p->parent->right = nullptr;
				delete p->right;
			}
			else if (p->left != nullptr )
			{
				p->data = p->left->data;
				p->left = nullptr;
				delete p->left;
			}
			else if (p->right != nullptr)
			{
				p->data = p->right->data;
				p->right = nullptr;
				delete p->right;
			}
			else {
				if (pp->left->data == p->data) {
					pp->left = nullptr;
					delete pp->left;
				}
				else {
					pp->right = nullptr;
					delete pp->right;
				}
			}
			// need to rebalance tree

		}
		/// <summary>
		/// method for inserting an element at the AATree
		/// </summary>
		/// <param name="data">data to be inserted at the tree</param>
		void Insert(T data)
		{
			struct AATreeNode<T>* p = root;
			struct AATreeNode<T>* pp = nullptr;
			while (p != nullptr)
			{
				pp = p;
				if (data > p->data)
					p = p->right;
				else if (data < p->data)
					p = p->left;
				else
					return;
			}
			struct AATreeNode<T>* el = new struct AATreeNode<T>;
			el->data = data;
			el->parent = pp;
			el->left = nullptr;
			el->right = nullptr;
			if (pp == nullptr)
				el->level = 1;
			else
				el->level = pp->level;

			if (root == nullptr)
				root = el;
			else
				if (pp->data < data)
					pp->right = el;
				else
					pp->left = el;
			// balance tree after inserting
			p = el->parent;
			while (p)
			{
				Skew(p);
				Split(p);
				p = p->parent;
			}
		}
		/// <summary>
		/// method for printing the AATree using preOrder
		/// </summary>
		/// <param name="root">root of the tree</param>
		void preOrderPrint(struct AATreeNode<T>* root) const
		{
			if (root == nullptr)
				return;
			preOrderPrint(root->left);
			std::cout << root->data << " Level: " << root->level << std::endl;
			preOrderPrint(root->right);
		}
		/// <summary>
		/// method for getting the currents Tree root
		/// </summary>
		/// <returns>returns the root of the tree</returns>
		struct AATreeNode<T>*  getRoot() const
		{
			return root;
		}
		/// <summary>
		/// method for searching if an elements exists in the tree
		/// </summary>
		/// <param name="el"> element to seach for</param>
		/// <returns> boolean  indicating wether the element exists or not </returns>
		bool Search(T el) const
		{
			auto p = root;
			while (p)
			{
				if (el > p->data)
					p = p->right;
				else if (el < p->data)
					p = p->left;
				else
					return true;
			}
			return false;
		}
	};
}
