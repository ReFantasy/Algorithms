# Algorithms
算法导论C++实现

## 十二章 二叉查找树
源文件：

[bst.h](./bst.h)

[bst.cpp](./bst.cpp)

类成员函数：：
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


使用示例：
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
