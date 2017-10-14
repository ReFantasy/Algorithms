#ifndef __BST_H__
#define __BST_H__
#include <iostream>
#include <string>
using std::cout;
using std::cin;
/************************************************************************/
/*      ˵��������Ϊ����������Ľ����                                     */
/*      ��չ���ɽ�������ݳ�Ա value �滻Ϊ�Զ����࣬���Ǳ���������صĲ����� */
/*      ���磬С��<������==������>�����<<�Ȳ���                            */
/************************************************************************/
class CBstNode
{
public:
	CBstNode() :value(0), left(nullptr), right(nullptr) {}
	int value;
	CBstNode *left;
	CBstNode *right;
};

//�����������
class CBst
{
public:
	CBst();
public:
	bool insert(CBstNode* new_node);                                 //����һ�����
	bool insert(decltype(CBstNode::value) new_value);                //����ֵΪnew_value�Ľ��
	bool deleteNode(CBstNode* pNode);                                //ɾ�����
	bool deleteNode(decltype(CBstNode::value) delete_value);         //ɾ��ֵΪdelete_value�Ľ��
	CBstNode* serarchKey(decltype(CBstNode::value) value);           //����ֵvalue�Ľ��,ʧ�ܷ��� nullptr
	CBstNode* minValue();                                            //���ز������е���Сֵ	
	CBstNode* maxValue();                                            //���ز������е����ֵ
	void printBySort();                                              //�����������ֵ
		
private:
	void printNode(const CBstNode *cur_node);
	void do_printBySort(const CBstNode *cur_node);
	CBstNode * do_serarchKey(CBstNode *cur_node, decltype(CBstNode::value) value);
	CBstNode * successor(CBstNode * pnode);              //��������ĺ��
	int getParent(CBstNode * &parent, CBstNode * pnode); //Ѱ��pnode�ĸ��ڵ㣬����PARENT�У����ӷ���1���Һ��ӷ���2
	CBstNode* minValue(CBstNode* start_node);                       
	CBstNode* maxValue(CBstNode* start_node);                        
private:
	CBstNode *Root;
};



#endif // !__BST_H__

