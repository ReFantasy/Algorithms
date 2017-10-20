# Algorithms
算法导论C++实现

## 十二章 二叉查找树
**源文件：**

[bst.h](./bst.h)

[bst.cpp](./bst.cpp)

**类成员函数:**
```C++
bool insert(CBstNode* new_node);                               //插入一个结点
bool insert(decltype(CBstNode::value) new_value);                //插入值为new_value的结点
bool deleteNode(CBstNode* pNode);                                //删除结点
bool deleteNode(decltype(CBstNode::value) delete_value);         //删除值为delete_value的结点
CBstNode* serarchKey(decltype(CBstNode::value) value);           //查找值value的结点,失败返回 nullptr
CBstNode* minValue();                                            //返回查找树中的最小值	
CBstNode* maxValue();                                            //返回查找树中的最大值
void printBySort();                                              //排序输出结点的值
```


**使用示例：**
```C++
#include <iostream>
#include "bst.h"  //引入头文件
using namespace std;

int main()
{
  //创建查找树的实例
  CBst bstree;  
  
  //插入若干值
  bstree.insert(4);
  bstree.insert(3);
  bstree.insert(2);
  bstree.insert(5);
  bstree.insert(10);
  bstree.insert(8);
  bstree.insert(12);
	
  //删除值为3的结点
  bstree.deleteNode(3);
  
  //排序打印查找树
  bstree.printBySort();
  return 0;
}

```

## 十三章 红黑树
**源文件：**

[rbtree.h](./rbtree.h)

**类成员函数:**
```C++
        RBTree();
	~RBTree();

	//前序遍历
	void preOrder();
	//中序遍历
	void inOrder();
	//后序遍历
	void postOrder();

	//(递归)查找键值key的节点
	RBTNode<T>* search(T key);
	//(非递归)查找键值key的节点
	RBTNode<T>* iterativeSearch(T key);

	//查找最小节点：返回最小节点的键值
	RBTNode<T>* minimum();
	//查找最大节点：返回最大节点的键值
	RBTNode<T>* maximum();
	// 将结点(key为节点键值)插入到红黑树中
	void insert(T key);

	// 删除结点(key为节点键值)
	void remove(T key);

	// 销毁红黑树
	void destroy();

	// 打印红黑树
	void print();
```


**使用示例：**
```C++
#include <iostream>
#include "rbtree.h"
using namespace std;

//自定义数据类型
class MyDataType
{
public:
	MyDataType():value(0) {}
	MyDataType(int mvalue)
	{
		value = mvalue;
	}

	int value = 0;

//运算符重载
public:
	bool operator<(MyDataType rvalue)
	{
		if (value < rvalue.value)
			return true;
		else
			return false;
	}
	bool operator>(MyDataType rvalue)
	{
		if (value > rvalue.value)
			return true;
		else
			return false;
	}
	bool operator==(MyDataType rvalue)
	{
		if (*this<rvalue || *this>rvalue)
			return false;
		else
			return true;
	}
	
};
std::ostream& operator<<(std::ostream& out, const MyDataType& m)
{
	out << m.value;
	return out;
}
int main()
{
        //模板类，可以使用自定义数据类型
	RBTree<MyDataType> tr;
	tr.insert(MyDataType(4));
	tr.insert(MyDataType(3));
	tr.insert(MyDataType(2));
	tr.insert(MyDataType(5));
	tr.insert(MyDataType(10));
	tr.insert(MyDataType(8));
	tr.insert(MyDataType(12));

	//tr.destroy();
	tr.print();
	return 0;
} 
```

