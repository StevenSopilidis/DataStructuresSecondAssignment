#pragma once

namespace DataStructures 
{
	template <typename T>
	struct AATreeNode
	{
		T data;
		int level;
		struct AATreeNode* left;
		struct AATreeNode* right;
		struct AATreeNode* parent;
	};
}