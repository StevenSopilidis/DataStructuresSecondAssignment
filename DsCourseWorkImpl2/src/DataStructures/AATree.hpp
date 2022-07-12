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
				auto tmp4 = node->left->level;

				node->data = node->left->data;
				node->left = node->left->left;
				node->right = new struct AATreeNode<T>;
				node->right->level = tmp4;

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
				auto tmp6 = node->level;

				node->level += 1;

				node->data = node->right->data;
				node->parent = tmp1->parent;
				// fix left child
				node->left = new struct AATreeNode<T>;
				node->left->parent = node;
				node->left->left = tmp5;
				node->left->right = tmp3;
				node->left->data = tmp4;
				node->left->level = tmp6;
				// fix right child
				node->right = new struct AATreeNode<T>;
				node->right->parent = node;
				node->right->left = tmp2->left;
				node->right->right = tmp2->right;
				node->right->data = tmp2->data;
				node->right->level = tmp6;

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
			
			// remove element from tree
			auto p = root;
			AATreeNode<T>* pp = nullptr;
			while (p->data != data)
			{
				pp = p;
				if (data < p->data)
					p = p->left;
				else
					p = p->right;
			}
			if (p->left != nullptr && p->right != nullptr)
			{
				// find largest element in left subtree
				auto s = p->left;
				auto ps = p;
				while (s->right)
				{
					ps = s;
					s = s->right;
				}
				p->data = s->data;
				p = s;
				pp = ps;
			}
			AATreeNode<T>* c;
			if (p->left) c = p->left;
			else c = p->right;
			// delete p
			if (p == root) root = c;
			else {// is p left or right child of pp?
				if (p == pp->left)
					pp->left = c;
				else pp->right = c;
			}

			// rebalance tree
			auto rb = p->parent;

			while (rb != nullptr)
			{
				// check if we need to decrease level
				if (rb->left == nullptr && rb->level >= 2)
					rb->level--;
				else if(rb->right == nullptr && rb->level >= 2)
					rb->level--;
				else if ((rb->left != nullptr && rb->level - 1 > rb->left->level) || rb->right != nullptr && rb->level - 1 > rb->right->level)
					rb->level--;
				Skew(rb);
				Split(rb);
				rb = rb->parent;
			}
			delete p;
			return true;
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
		struct AATreeNode<T>* getRoot() const
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