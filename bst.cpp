#include "bst.h"
CBst::CBst()
	:Root(nullptr)
{

}

void CBst::printNode(const CBstNode *cur_node)
{
	cout << cur_node->value << " ";
}

CBstNode * CBst::serarchKey(decltype(CBstNode::value) value)
{
	return do_serarchKey(Root, value);
}

CBstNode* CBst::minValue()
{
	CBstNode *cur_node = Root;
	if (cur_node == nullptr)
		return cur_node;

	while (cur_node->left != nullptr)
	{
		cur_node = cur_node->left;
	}

	return cur_node;
}

CBstNode* CBst::minValue(CBstNode* start_node)
{
	CBstNode *cur_node = start_node;
	if (cur_node == nullptr)
		return cur_node;

	while (cur_node->left != nullptr)
	{
		cur_node = cur_node->left;
	}

	return cur_node;
}

CBstNode* CBst::maxValue()
{
	CBstNode *cur_node = Root;
	if (cur_node == nullptr)
		return cur_node;

	while (cur_node->right != nullptr)
	{
		cur_node = cur_node->right;
	}

	return cur_node;
}

CBstNode* CBst::maxValue(CBstNode* start_node)
{
	CBstNode *cur_node = start_node;
	if (cur_node == nullptr)
		return cur_node;

	while (cur_node->right != nullptr)
	{
		cur_node = cur_node->right;
	}

	return cur_node;
}

bool CBst::insert(CBstNode* new_node)
{
	if (!Root)
	{
		Root = new_node;
		return true;
	}

	CBstNode *cur_node = Root;
	CBstNode *parent = nullptr;
	while (cur_node != nullptr)
	{
		parent = cur_node;
		if (new_node->value < cur_node->value)
		{
			cur_node = cur_node->left;
		}
		else
		{
			cur_node = cur_node->right;
		}
	}

	if (new_node->value < parent->value)
		parent->left = new_node;
	else
		parent->right = new_node;

	return true;
		
}

bool CBst::insert(decltype(CBstNode::value) new_value)
{
	CBstNode *new_node = new CBstNode;
	new_node->left = new_node->right = nullptr;
	new_node->value = new_value;
	return insert(new_node);
}

bool CBst::deleteNode(CBstNode* pNode)
{
	if (!serarchKey(pNode->value))
		return false;
	CBstNode *parent = nullptr;
	int pos = 0;

	//没有孩子结点
	if ((pNode->left == nullptr) && (pNode->right == nullptr))
	{
		pos = getParent(parent, pNode);
		if (pos == 1)
			parent->left = nullptr;
		else if (pos == 2)
			parent->right = nullptr;

		delete pNode;
		if (pos == 0)
			Root = nullptr;
		return true;
	}
	else if ((pNode->left != nullptr) && (pNode->right != nullptr))
	{
		CBstNode *tmpsuccessor = successor(pNode);
		auto tmpvalue = tmpsuccessor->value;
		deleteNode(tmpsuccessor);
		pNode->value = tmpvalue;

		return true;
	}
	else//只有一个孩子结点
	{
		pos = getParent(parent, pNode);
		if (pos == 1)
			parent->left = (pNode->left!=nullptr) ?(pNode->left):(pNode->right);
		else if (pos == 2)
			parent->right = (pNode->left != nullptr) ? (pNode->left) : (pNode->right);
		else if (pos == 0)
		{
			Root = (pNode->left != nullptr) ? (pNode->left) : (pNode->right);
		}
		delete pNode;
		return true;
	}

	return false;
}

bool CBst::deleteNode(decltype(CBstNode::value) delete_value)
{
	CBstNode* pdelete = serarchKey(delete_value);
	if (!pdelete)
		return false;
	else
	{
		return deleteNode(pdelete);	
	}

	return false;
}

void CBst::printBySort()
{
	do_printBySort(Root);
}

void CBst::do_printBySort(const CBstNode *cur_node)
{//中序遍历
	if (cur_node != nullptr)
	{
		do_printBySort(cur_node->left);
		printNode(cur_node);
		do_printBySort(cur_node->right);
	}
}

CBstNode * CBst::do_serarchKey(CBstNode *cur_node, decltype(CBstNode::value) value)
{
	////递归版本
	//if (cur_node == nullptr)
	//	return nullptr;
	//if (cur_node->value == value)
	//	return cur_node;

	//if (value < cur_node->value)
	//{
	//	do_serarchKey(cur_node->left, value);
	//}
	//else
	//{
	//	do_serarchKey(cur_node->right, value);
	//}

	//非递归版本
	while (cur_node != nullptr && cur_node->value != value)
	{
		if (value < cur_node->value)
			cur_node = cur_node->left;
		else
			cur_node = cur_node->right;
		
	}
	if (cur_node->value == value)
		return cur_node;
	else
		return nullptr;
}

CBstNode * CBst::successor(CBstNode * pnode)
{
	if (pnode == nullptr)
		return nullptr;
	if (pnode->right != nullptr)
	{
		return minValue(pnode->right);
	}
}

int CBst::getParent(CBstNode * &parent, CBstNode * pnode)
{
	parent = nullptr;
	int pos = 0;
	CBstNode *cur_node = Root;
	if (Root == nullptr || Root->value == pnode->value)
		return pos;

	while (cur_node != nullptr)
	{	
		if (cur_node->value>pnode->value)
		{
			parent = cur_node;
			cur_node = cur_node->left;
			pos = 1;
		}
		else if (cur_node->value < pnode->value)
		{
			parent = cur_node;
			cur_node = cur_node->right;
			pos = 2;
		}
		else
		{
			return pos;
		}
	}

	return pos;
}

