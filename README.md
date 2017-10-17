# Algorithms
算法导论C++实现

## 十二章 二叉查找树
[bst.h](./bst.h)

[bst.cpp](./bst.cpp)

使用示例：
```C++
#include <iostream>
#include "bst.h"  //引入头文件
using namespace std;

int main()
{
  //创建查找树的实例
  CBst btree;  
  
  //插入若干值
  btree.insert(4);
  btree.insert(3);
  btree.insert(2);
  btree.insert(5);
  btree.insert(10);
  btree.insert(8);
  btree.insert(12);
	
  //删除值为3的结点
  btree.deleteNode(3);
  
  btree.printBySort();
  return 0;
}

```
