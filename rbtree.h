#ifndef __RBTREE_H__
#define __RBTREE_H__
#include <iostream>
#include <iomanip>
using std::cout;
using std::cin;
using std::endl;

//宏定义
#define rb_parent(r)   ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r)   ((r)->color==RED)
#define rb_is_black(r)  ((r)->color==BLACK)
#define rb_set_black(r)  { (r)->color = BLACK; } 
#define rb_set_red(r)   { (r)->color = RED; }
#define rb_set_parent(r,p)   { (r)->parent = (p); } 
#define rb_set_color(r,c)   { (r)->color = (c); } 

enum RBTColor { RED, BLACK };

//红黑树的结点类
template<typename T>
class RBTNode
{
public:
	//构造函数
	RBTNode(T value, RBTColor c = RED, RBTNode *p = nullptr, RBTNode *l = nullptr, RBTNode *r = nullptr) :
		key(value), color(c), parent(), left(l), right(r) {}

public:
	RBTColor color;          //颜色
	T key;                   //关键字（键值）
	RBTNode *left;
	RBTNode *right;
	RBTNode *parent;
};

//红黑树
template<typename T>
class RBTree
{
public:
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
private:
	// 找结点(x)的后继结点。即，查找"红黑树中数据值大于该结点"的"最小结点"。
	RBTNode<T>* successor(RBTNode<T> *x);
	// 找结点(x)的前驱结点。即，查找"红黑树中数据值小于该结点"的"最大结点"。
	RBTNode<T>* predecessor(RBTNode<T> *x);
	// 前序遍历"红黑树"
	void preOrder(RBTNode<T>* tree) const;
	// 中序遍历"红黑树"
	void inOrder(RBTNode<T>* tree) const;
	// 后序遍历"红黑树"
	void postOrder(RBTNode<T>* tree) const;

	// (递归实现)查找"红黑树x"中键值为key的节点
	RBTNode<T>* search(RBTNode<T>* x, T key) const;
	// (非递归实现)查找"红黑树x"中键值为key的节点
	RBTNode<T>* iterativeSearch(RBTNode<T>* x, T key) const;

	// 查找最小结点：返回tree为根结点的红黑树的最小结点。
	RBTNode<T>* minimum(RBTNode<T>* tree);
	// 查找最大结点：返回tree为根结点的红黑树的最大结点。
	RBTNode<T>* maximum(RBTNode<T>* tree);

	// 左旋
	void leftRotate(RBTNode<T>* &root, RBTNode<T>* x);
	// 右旋
	void rightRotate(RBTNode<T>* &root, RBTNode<T>* y);
	// 插入函数
	void insert(RBTNode<T>* &root, RBTNode<T>* node);
	// 插入修正函数
	void insertFixUp(RBTNode<T>* &root, RBTNode<T>* node);
	// 删除函数
	void remove(RBTNode<T>* &root, RBTNode<T> *node);
	// 删除修正函数
	void removeFixUp(RBTNode<T>* &root, RBTNode<T> *node, RBTNode<T> *parent);
	// 销毁红黑树
	void destroy(RBTNode<T>* &tree);
	// 打印红黑树
	void print(RBTNode<T>* tree, T key, int direction);

private:
	RBTNode<T> *mRoot;    //根节点
};

template<typename T>
RBTree<T>::RBTree():mRoot(nullptr){}

template<typename T>
RBTree<T>::~RBTree()
{
	destroy();
}


template<typename T>
void RBTree<T>::preOrder()
{
	preOrder(mRoot);
}


template<typename T>
void RBTree<T>::preOrder(RBTNode<T>* tree) const
{
	if (tree != nullptr)
	{
		cout << tree->key << endl;
		preOrder(tree->left);
		preOrder(tree->right);
	}
}


template<typename T>
void RBTree<T>::inOrder()
{
	inOrder(mRoot);
}


template<typename T>
void RBTree<T>::inOrder(RBTNode<T>* tree) const
{
	if (tree != nullptr)
	{
		inOrder(tree->left);
		cout << tree->key << endl;
		inOrder(tree->right);
	}
}


template<typename T>
void RBTree<T>::postOrder()
{
	postOrder(mRoot);
}


template<typename T>
void RBTree<T>::postOrder(RBTNode<T>* tree) const
{
	if (tree != nullptr)
	{
		postOrder(tree->left);
		postOrder(tree->right);
		cout << tree->key << endl;
	}
}


template<typename T>
RBTNode<T>* RBTree<T>::search(T key)
{
	search(mRoot, key);
}


template<typename T>
RBTNode<T>* RBTree<T>::search(RBTNode<T>* x, T key) const
{
	if (x == nullptr)
		return nullptr;
	if (x->key == key)
		return x;

	if (x->key > key)
		return search(x->left, key);
	else
		return search(x->right, key);
}


template<typename T>
RBTNode<T>* RBTree<T>::iterativeSearch(T key)
{
	iterativeSearch(mRoot, key);
}


template<typename T>
RBTNode<T>* RBTree<T>::iterativeSearch(RBTNode<T>* x, T key) const
{
	while (x != nullptr)
	{
		if (x->key == key)
			return x;
		else if (key < x->key)
		{
			x = x->left;
		}
		else
		{
			x = x->right;
		}
	}

	return x;
}


template<typename T>
RBTNode<T>* RBTree<T>::minimum()
{
	return minimum(mRoot);
}


template<typename T>
RBTNode<T>* RBTree<T>::minimum(RBTNode<T>* tree)
{
	while (tree->left != nullptr)
		tree = tree->left;
	return tree;
}


template<typename T>
RBTNode<T>* RBTree<T>::maximum()
{
	return maximum(mRoot);
}


template<typename T>
RBTNode<T>* RBTree<T>::maximum(RBTNode<T>* tree)
{
	while (tree->right != nullptr)
		tree = tree->right;
	return tree;
}


template<typename T>
RBTNode<T>* RBTree<T>::successor(RBTNode<T> *x)
{
	//如果x存在右孩子，则后继为以x的右孩子为根的树的最小值
	if (x != nullptr && x->right != nullptr)
		return minimum(x->right);

	//如果x不存在右孩子
	//1.x是一个左孩子， x的后继为x的父节点
	//2.x是一个右孩子，
	RBTNode<T>* y = x->parent;
	while ((y != nullptr) && (x == y->right))
	{
		x = y;
		y = y->parent;
	}

	return y;
}

template<typename T>
RBTNode<T>* RBTree<T>::predecessor(RBTNode<T> *x)
{
	if (x != nullptr && x->left != nullptr)
		return x->left;

	RBTNode *y = x->parent;
	if (y != nullptr && y->left == x)
	{
		x = y;
		y = y->parent;
	}

	return y;
}


template<typename T>
void RBTree<T>::insert(T key)
{
	RBTNode<T>* new_node = nullptr;
	if ((new_node = new RBTNode<T>(key)) == nullptr)
		return ;
	insert(mRoot, new_node);
}

/*
* 对红黑树的节点(x)进行左旋转
* 左旋示意图(对节点x进行左旋)：
*      px                              px
*     /                               /
*    x                               y
*   /  \      --(左旋)-->           / \                #
*  lx   y                          x  ry
*     /   \                       /  \
*    ly   ry                     lx  ly
*
*
*/
template<typename T>
void RBTree<T>::leftRotate(RBTNode<T>* &root, RBTNode<T>* x)
{
	auto y = x->right;
	if (y == nullptr)
		return;

	x->right = y->left;
	if (y->left != nullptr)
		y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == nullptr)
	{
		root = y;
		y->parent = nullptr;
	}
	else
	{
		if (x->parent->left == x)
			x->parent->left = y;
		else
			x->parent->right = y;
	}

	y->left = x;
	x->parent = y;
}

/*
* 对红黑树的节点(y)进行右旋转
*
* 右旋示意图(对节点y进行左旋)：
*            py                               py
*           /                                /
*          y                                x
*         /  \      --(右旋)-->            /  \                     #
*        x   ry                           lx   y
*       / \                                   / \                   #
*      lx  rx                                rx  ry
*
*/

template<typename T>
void RBTree<T>::rightRotate(RBTNode<T>* &root, RBTNode<T>* y)
{
	auto x = y->left;
	if (x == nullptr)
		return;

	y->left = x->right;
	if (x->right != nullptr)
		x->right->parent = y;

	x->parent = y->parent;
	if (y->parent == nullptr)
	{
		root = x;
		x->parent = nullptr;
	}
	else
	{
		if (y->parent->right == y)
			y->parent->right = x;
		else
			y->parent->left = x;
	}
	x->right = y;
	y->parent = x;
}


template<typename T>
void RBTree<T>::insert(RBTNode<T>* &root, RBTNode<T>* node)
{
	RBTNode<T>* y = nullptr;
	RBTNode<T>* x = root;

	while (x != nullptr)
	{
		y = x;
		if (x->key < node->key)
		{
			x = x->right;
		}
		else
		{
			x = x->left;
		}
	}

	if (y != nullptr)
	{
		if (y->key < node->key)
		{
			y->right = node;
		}
		else
		{
			y->left = node;
		}
	}
	else
	{
		root = node;
		root->parent = nullptr;
		root->color = BLACK;
		return;
	}

	node->parent = y;
	node->color = RED;
	if (node->parent->color == RED)
		insertFixUp(root, node);
}


template<typename T>
void RBTree<T>::insertFixUp(RBTNode<T>* &root, RBTNode<T>* node)
{
	RBTNode<T> *parent, *gparent;
	while ((parent = rb_parent(node)) && (rb_is_red(parent)))
	{
		gparent = rb_parent(parent);
		//父节点是祖父节点左孩子
		if (parent == gparent->left)
		{
			auto uncle = gparent->right;

			//叔叔是红色节点
			if (uncle && rb_is_red(uncle))
			{
				rb_set_black(parent);
				rb_set_black(uncle);
				rb_set_red(gparent);
				node = gparent;
				continue;
			}

			//叔叔节点是黑色的，当前节点是右孩子
			if (parent->right == node)
			{
				RBTNode<T>* tmp;
				leftRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			//叔叔节点是黑色的，当前节点是左孩子
			rb_set_black(parent);
			rb_set_red(gparent);
			rightRotate(root, gparent);
		}
		//父节点是祖父节点右孩子
		else if(parent == gparent->right)
		{
			auto uncle = gparent->left;

			//叔叔是红色节点
			if (uncle && rb_is_red(uncle))
			{
				rb_set_black(parent);
				rb_set_black(uncle);
				rb_set_red(gparent);
				node = gparent;
				continue;
			}

			//叔叔节点是黑色的，当前节点是左孩子
			if (parent->left == node)
			{
				RBTNode<T>* tmp;
				rightRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			//叔叔节点是黑色的，当前节点是右孩子
			rb_set_black(parent);
			rb_set_red(gparent);
			leftRotate(root, gparent);
		}
	}
	root->color = BLACK;
}


template<typename T>
void RBTree<T>::print(RBTNode<T>* tree, T key, int direction)
{
	if (tree != NULL)
	{
		if (direction == 0)    // tree是根节点
			cout << setw(2) << tree->key << "(B) is root" << endl;
		else                // tree是分支节点
			cout << setw(2) << tree->key << (rb_is_red(tree) ? "(R)" : "(B)") << " is " << setw(2) << key << "'s " << setw(12) << (direction == 1 ? "right child" : "left child") << endl;

		print(tree->left, tree->key, -1);
		print(tree->right, tree->key, 1);
	}
}

template<typename T>
void RBTree<T>::print()
{
	if (mRoot != NULL)
		print(mRoot, mRoot->key, 0);
}


template<typename T>
void RBTree<T>::remove(RBTNode<T>* &root, RBTNode<T> *node)
{
	//RBTNode<T> *y, *x;
	//if (node->left == nullptr || node->right == nullptr)
	//{
	//	y = node; //y为替换节点
	//}
	//else
	//{
	//	y = successor(node);
	//}

	//if (y->left != nullptr)
	//{
	//	x = y->left;
	//}
	//else
	//{
	//	x = y->right
	//}
	//x->parent = y->parent;

	//if (y->parent == nullptr)
	//{
	//	root = x;
	//}
	//else
	//{
	//	if (y == y->parent->left)
	//	{
	//		y->parent->left = x;
	//	}
	//	else
	//	{
	//		y->parent->right = x;
	//	}
	//}

	//if (y != node)
	//	node->key = y->key;
	//
	//if (y->color == BLACK)
	//	removeFixUp(root, node, node->parent);

	//delete y;
	RBTNode<T> *child, *parent;
	RBTColor color;

	// 被删除节点的"左右孩子都不为空"的情况。
	if ((node->left != NULL) && (node->right != NULL))
	{
		// 被删节点的后继节点。(称为"取代节点")
		// 用它来取代"被删节点"的位置，然后再将"被删节点"去掉。
		RBTNode<T> *replace = node;

		// 获取后继节点
		replace = replace->right;
		while (replace->left != NULL)
			replace = replace->left;

		// "node节点"不是根节点(只有根节点不存在父节点)
		if (rb_parent(node))
		{
			if (rb_parent(node)->left == node)
				rb_parent(node)->left = replace;
			else
				rb_parent(node)->right = replace;
		}
		else
			// "node节点"是根节点，更新根节点。
			root = replace;

		// child是"取代节点"的右孩子，也是需要"调整的节点"。
		// "取代节点"肯定不存在左孩子！因为它是一个后继节点。
		child = replace->right;
		parent = rb_parent(replace);
		// 保存"取代节点"的颜色
		color = rb_color(replace);

		// "被删除节点"是"它的后继节点的父节点"
		if (parent == node)
		{
			parent = replace;
		}
		else
		{
			// child不为空
			if (child)
				rb_set_parent(child, parent);
			parent->left = child;

			replace->right = node->right;
			rb_set_parent(node->right, replace);
		}

		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;

		if (color == BLACK)
			removeFixUp(root, child, parent);

		delete node;
		return;
	}

	if (node->left != NULL)
		child = node->left;
	else
		child = node->right;

	parent = node->parent;
	// 保存"取代节点"的颜色
	color = node->color;

	if (child)
		child->parent = parent;

	// "node节点"不是根节点
	if (parent)
	{
		if (parent->left == node)
			parent->left = child;
		else
			parent->right = child;
	}
	else
		root = child;

	if (color == BLACK)
		removeFixUp(root, child, parent);
	delete node;

}


template<typename T>
void RBTree<T>::removeFixUp(RBTNode<T>* &root, RBTNode<T> *node, RBTNode<T> *parent)
{
	RBTNode<T> *other;

	while ((!node || rb_is_black(node)) && node != root)
	{
		if (parent->left == node)
		{
			other = parent->right;
			if (rb_is_red(other))
			{
				// Case 1: x的兄弟w是红色的  
				rb_set_black(other);
				rb_set_red(parent);
				leftRotate(root, parent);
				other = parent->right;
			}
			if ((!other->left || rb_is_black(other->left)) &&
				(!other->right || rb_is_black(other->right)))
			{
				// Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的  
				rb_set_red(other);
				node = parent;
				parent = rb_parent(node);
			}
			else
			{
				if (!other->right || rb_is_black(other->right))
				{
					// Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。  
					rb_set_black(other->left);
					rb_set_red(other);
					rightRotate(root, other);
					other = parent->right;
				}
				// Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
				rb_set_color(other, rb_color(parent));
				rb_set_black(parent);
				rb_set_black(other->right);
				leftRotate(root, parent);
				node = root;
				break;
			}
		}
		else
		{
			other = parent->left;
			if (rb_is_red(other))
			{
				// Case 1: x的兄弟w是红色的  
				rb_set_black(other);
				rb_set_red(parent);
				rightRotate(root, parent);
				other = parent->left;
			}
			if ((!other->left || rb_is_black(other->left)) &&
				(!other->right || rb_is_black(other->right)))
			{
				// Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的  
				rb_set_red(other);
				node = parent;
				parent = rb_parent(node);
			}
			else
			{
				if (!other->left || rb_is_black(other->left))
				{
					// Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。  
					rb_set_black(other->right);
					rb_set_red(other);
					leftRotate(root, other);
					other = parent->left;
				}
				// Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
				rb_set_color(other, rb_color(parent));
				rb_set_black(parent);
				rb_set_black(other->left);
				rightRotate(root, parent);
				node = root;
				break;
			}
		}
	}
	if (node)
		rb_set_black(node);
}
template <class T>
void RBTree<T>::remove(T key)
{
	RBTNode<T> *node;

	// 查找key对应的节点(node)，找到的话就删除该节点
	if ((node = search(mRoot, key)) != nullptr)
		remove(mRoot, node);
}


template<typename T>
void RBTree<T>::destroy(RBTNode<T>* &tree)
{
	if (tree == nullptr)
		return;

	if (tree->left != nullptr)
		destroy(tree->left);
	if (tree->right != nullptr)
		destroy(tree->right);

	delete tree;
	tree = nullptr;
}


template<typename T>
void RBTree<T>::destroy()
{
	destroy(mRoot);
}

#endif
