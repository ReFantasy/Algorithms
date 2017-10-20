#ifndef __RBTREE_H__
#define __RBTREE_H__
#include <iostream>
#include <iomanip>
using std::cout;
using std::cin;
using std::endl;

#define rb_parent(r)   ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r)   ((r)->color==RED)
#define rb_is_black(r)  ((r)->color==BLACK)
#define rb_set_black(r)  do { (r)->color = BLACK; } while (0)
#define rb_set_red(r)  do { (r)->color = RED; } while (0)
#define rb_set_parent(r,p)  do { (r)->parent = (p); } while (0)
#define rb_set_color(r,c)  do { (r)->color = (c); } while (0)

enum RBTColor { RED, BLACK };

//������Ľ����
template<typename T>
class RBTNode
{
public:
	//���캯��
	RBTNode(T value, RBTColor c = RED, RBTNode *p = nullptr, RBTNode *l = nullptr, RBTNode *r = nullptr) :
		key(value), color(c), parent(), left(l), right(r) {}

public:
	RBTColor color;          //��ɫ
	T key;                   //�ؼ��֣���ֵ��
	RBTNode *left;
	RBTNode *right;
	RBTNode *parent;
};

//�����
template<typename T>
class RBTree
{
public:
	RBTree();
	~RBTree();

	//ǰ�����
	void preOrder();
	//�������
	void inOrder();
	//�������
	void postOrder();

	//(�ݹ�)���Ҽ�ֵkey�Ľڵ�
	RBTNode<T>* search(T key);
	//(�ǵݹ�)���Ҽ�ֵkey�Ľڵ�
	RBTNode<T>* iterativeSearch(T key);

	//������С�ڵ㣺������С�ڵ�ļ�ֵ
	RBTNode<T>* minimum();
	//�������ڵ㣺�������ڵ�ļ�ֵ
	RBTNode<T>* maximum();
	// �����(keyΪ�ڵ��ֵ)���뵽�������
	void insert(T key);

	// ɾ�����(keyΪ�ڵ��ֵ)
	void remove(T key);

	// ���ٺ����
	void destroy();

	// ��ӡ�����
	void print();
private:
	// �ҽ��(x)�ĺ�̽�㡣��������"�����������ֵ���ڸý��"��"��С���"��
	RBTNode<T>* successor(RBTNode<T> *x);
	// �ҽ��(x)��ǰ����㡣��������"�����������ֵС�ڸý��"��"�����"��
	RBTNode<T>* predecessor(RBTNode<T> *x);
	// ǰ�����"�����"
	void preOrder(RBTNode<T>* tree) const;
	// �������"�����"
	void inOrder(RBTNode<T>* tree) const;
	// �������"�����"
	void postOrder(RBTNode<T>* tree) const;

	// (�ݹ�ʵ��)����"�����x"�м�ֵΪkey�Ľڵ�
	RBTNode<T>* search(RBTNode<T>* x, T key) const;
	// (�ǵݹ�ʵ��)����"�����x"�м�ֵΪkey�Ľڵ�
	RBTNode<T>* iterativeSearch(RBTNode<T>* x, T key) const;

	// ������С��㣺����treeΪ�����ĺ��������С��㡣
	RBTNode<T>* minimum(RBTNode<T>* tree);
	// ��������㣺����treeΪ�����ĺ����������㡣
	RBTNode<T>* maximum(RBTNode<T>* tree);

	// ����
	void leftRotate(RBTNode<T>* &root, RBTNode<T>* x);
	// ����
	void rightRotate(RBTNode<T>* &root, RBTNode<T>* y);
	// ���뺯��
	void insert(RBTNode<T>* &root, RBTNode<T>* node);
	// ������������
	void insertFixUp(RBTNode<T>* &root, RBTNode<T>* node);
	// ɾ������
	void remove(RBTNode<T>* &root, RBTNode<T> *node);
	// ɾ����������
	void removeFixUp(RBTNode<T>* &root, RBTNode<T> *node, RBTNode<T> *parent);
	// ���ٺ����
	void destroy(RBTNode<T>* &tree);
	// ��ӡ�����
	void print(RBTNode<T>* tree, T key, int direction);

private:
	RBTNode<T> *mRoot;    //���ڵ�
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
	//���x�����Һ��ӣ�����Ϊ��x���Һ���Ϊ����������Сֵ
	if (x != nullptr && x->right != nullptr)
		return minimum(x->right);

	//���x�������Һ���
	//1.x��һ�����ӣ� x�ĺ��Ϊx�ĸ��ڵ�
	//2.x��һ���Һ��ӣ�
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
* �Ժ�����Ľڵ�(x)��������ת
* ����ʾ��ͼ(�Խڵ�x��������)��
*      px                              px
*     /                               /
*    x                               y
*   /  \      --(����)-->           / \                #
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
* �Ժ�����Ľڵ�(y)��������ת
*
* ����ʾ��ͼ(�Խڵ�y��������)��
*            py                               py
*           /                                /
*          y                                x
*         /  \      --(����)-->            /  \                     #
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
		//���ڵ����游�ڵ�����
		if (parent == gparent->left)
		{
			auto uncle = gparent->right;

			//�����Ǻ�ɫ�ڵ�
			if (uncle && rb_is_red(uncle))
			{
				rb_set_black(parent);
				rb_set_black(uncle);
				rb_set_red(gparent);
				node = gparent;
				continue;
			}

			//����ڵ��Ǻ�ɫ�ģ���ǰ�ڵ����Һ���
			if (parent->right == node)
			{
				RBTNode<T>* tmp;
				leftRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			//����ڵ��Ǻ�ɫ�ģ���ǰ�ڵ�������
			rb_set_black(parent);
			rb_set_red(gparent);
			rightRotate(root, gparent);
		}
		//���ڵ����游�ڵ��Һ���
		else if(parent == gparent->right)
		{
			auto uncle = gparent->left;

			//�����Ǻ�ɫ�ڵ�
			if (uncle && rb_is_red(uncle))
			{
				rb_set_black(parent);
				rb_set_black(uncle);
				rb_set_red(gparent);
				node = gparent;
				continue;
			}

			//����ڵ��Ǻ�ɫ�ģ���ǰ�ڵ�������
			if (parent->left == node)
			{
				RBTNode<T>* tmp;
				rightRotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}

			//����ڵ��Ǻ�ɫ�ģ���ǰ�ڵ����Һ���
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
		if (direction == 0)    // tree�Ǹ��ڵ�
			cout << setw(2) << tree->key << "(B) is root" << endl;
		else                // tree�Ƿ�֧�ڵ�
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
	//	y = node; //yΪ�滻�ڵ�
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

	// ��ɾ���ڵ��"���Һ��Ӷ���Ϊ��"�������
	if ((node->left != NULL) && (node->right != NULL))
	{
		// ��ɾ�ڵ�ĺ�̽ڵ㡣(��Ϊ"ȡ���ڵ�")
		// ������ȡ��"��ɾ�ڵ�"��λ�ã�Ȼ���ٽ�"��ɾ�ڵ�"ȥ����
		RBTNode<T> *replace = node;

		// ��ȡ��̽ڵ�
		replace = replace->right;
		while (replace->left != NULL)
			replace = replace->left;

		// "node�ڵ�"���Ǹ��ڵ�(ֻ�и��ڵ㲻���ڸ��ڵ�)
		if (rb_parent(node))
		{
			if (rb_parent(node)->left == node)
				rb_parent(node)->left = replace;
			else
				rb_parent(node)->right = replace;
		}
		else
			// "node�ڵ�"�Ǹ��ڵ㣬���¸��ڵ㡣
			root = replace;

		// child��"ȡ���ڵ�"���Һ��ӣ�Ҳ����Ҫ"�����Ľڵ�"��
		// "ȡ���ڵ�"�϶����������ӣ���Ϊ����һ����̽ڵ㡣
		child = replace->right;
		parent = rb_parent(replace);
		// ����"ȡ���ڵ�"����ɫ
		color = rb_color(replace);

		// "��ɾ���ڵ�"��"���ĺ�̽ڵ�ĸ��ڵ�"
		if (parent == node)
		{
			parent = replace;
		}
		else
		{
			// child��Ϊ��
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
	// ����"ȡ���ڵ�"����ɫ
	color = node->color;

	if (child)
		child->parent = parent;

	// "node�ڵ�"���Ǹ��ڵ�
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
				// Case 1: x���ֵ�w�Ǻ�ɫ��  
				rb_set_black(other);
				rb_set_red(parent);
				leftRotate(root, parent);
				other = parent->right;
			}
			if ((!other->left || rb_is_black(other->left)) &&
				(!other->right || rb_is_black(other->right)))
			{
				// Case 2: x���ֵ�w�Ǻ�ɫ����w����������Ҳ���Ǻ�ɫ��  
				rb_set_red(other);
				node = parent;
				parent = rb_parent(node);
			}
			else
			{
				if (!other->right || rb_is_black(other->right))
				{
					// Case 3: x���ֵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ���Һ���Ϊ��ɫ��  
					rb_set_black(other->left);
					rb_set_red(other);
					rightRotate(root, other);
					other = parent->right;
				}
				// Case 4: x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ�ģ�����������ɫ��
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
				// Case 1: x���ֵ�w�Ǻ�ɫ��  
				rb_set_black(other);
				rb_set_red(parent);
				rightRotate(root, parent);
				other = parent->left;
			}
			if ((!other->left || rb_is_black(other->left)) &&
				(!other->right || rb_is_black(other->right)))
			{
				// Case 2: x���ֵ�w�Ǻ�ɫ����w����������Ҳ���Ǻ�ɫ��  
				rb_set_red(other);
				node = parent;
				parent = rb_parent(node);
			}
			else
			{
				if (!other->left || rb_is_black(other->left))
				{
					// Case 3: x���ֵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ���Һ���Ϊ��ɫ��  
					rb_set_black(other->right);
					rb_set_red(other);
					leftRotate(root, other);
					other = parent->left;
				}
				// Case 4: x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ�ģ�����������ɫ��
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

	// ����key��Ӧ�Ľڵ�(node)���ҵ��Ļ���ɾ���ýڵ�
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
