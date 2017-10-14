#ifndef __BST_H__
#define __BST_H__
#include <iostream>
#include <string>
using std::cout;
using std::cin;
/************************************************************************/
/*      说明：此类为二叉查找树的结点类                                     */
/*      扩展：可将类的数据成员 value 替换为自定义类，但是必须重载相关的操作符 */
/*      比如，小于<，等于==，大于>，输出<<等操作                            */
/************************************************************************/
class CBstNode
{
public:
	CBstNode() :value(0), left(nullptr), right(nullptr) {}
	int value;
	CBstNode *left;
	CBstNode *right;
};

//二叉查找树类
class CBst
{
public:
	CBst();
public:
	bool insert(CBstNode* new_node);                                 //插入一个结点
	bool insert(decltype(CBstNode::value) new_value);                //插入值为new_value的结点
	bool deleteNode(CBstNode* pNode);                                //删除结点
	bool deleteNode(decltype(CBstNode::value) delete_value);         //删除值为delete_value的结点
	CBstNode* serarchKey(decltype(CBstNode::value) value);           //查找值value的结点,失败返回 nullptr
	CBstNode* minValue();                                            //返回查找树中的最小值	
	CBstNode* maxValue();                                            //返回查找树中的最大值
	void printBySort();                                              //排序输出结点的值
		
private:
	void printNode(const CBstNode *cur_node);
	void do_printBySort(const CBstNode *cur_node);
	CBstNode * do_serarchKey(CBstNode *cur_node, decltype(CBstNode::value) value);
	CBstNode * successor(CBstNode * pnode);              //中序遍历的后继
	int getParent(CBstNode * &parent, CBstNode * pnode); //寻找pnode的父节点，存在PARENT中，左孩子返回1，右孩子返回2
	CBstNode* minValue(CBstNode* start_node);                       
	CBstNode* maxValue(CBstNode* start_node);                        
private:
	CBstNode *Root;
};



#endif // !__BST_H__

