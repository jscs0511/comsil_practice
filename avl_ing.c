#include <stdio.h>
#include <stdlib.h>

/*
 * data structure of AVL tree
 */
typedef struct tree
{
	int key;
	int cnt;
	struct tree* left;
	struct tree* right;
	int height;
} tree;

/*
 * return height of a node
 */
int height(tree* node)
{
	if (node == NULL)
		return 0;
	return node->height;
}

/*
 * return the bigger value between a and b
 */
int maxi(int a, int b)
{
	return (a > b) ? a : b;
}

/*
 * create a new node and return its pointer
 */
tree* new_node(int key)
{
	tree* new_node = (tree*)calloc(1, sizeof(tree));

	new_node->key = key;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->height = 0;
	new_node->cnt = 1;
	return new_node;
}

/*
 * right rotate subtree rooted with y
 */
tree* right_rotate(tree* y)
{
	tree* x = y->left;
	tree* T2 = x->right;

	/* rotation */
	x->right = y;
	y->left = T2;

	y->height = maxi(height(y->left), height(y->right)) + 1;
	x->height = maxi(height(x->left), height(x->right)) + 1;

	/* return new root */
	return x;
}

/*
 * left rotate subtree rooted with x
 */
tree* left_rotate(tree* x)
{
	tree* y = x->right;
	tree* T2 = y->left;

	/* rotation */
	y->left = x;
	x->right = T2;

	x->height = maxi(height(x->left), height(x->right)) + 1;
	y->height = maxi(height(y->left), height(y->right)) + 1;

	/* return new root */
	return y;
}

/*
 * get the difference between height of left subtree and height of right subtree
 */
int get_balance(tree* node)
{
	if (node == NULL)
		return 0;
	return height(node->left) - height(node->right);
}

/*
 * insert a node, caculate the balance of the node and rotate a tree to make it balanced
 */
tree* node_insert(tree* node, int key)
{
	int balance;

	if (node == NULL)
		return (new_node(key));

	if (key < node->key)
		node->left = node_insert(node->left, key);
	else
		node->right = node_insert(node->right, key);

	node->height = maxi(height(node->left), height(node->right)) + 1;
	balance = get_balance(node);

	/* Left Left */
	if (balance > 1 && key < (node->left)->key)
		return right_rotate(node);
	/* Left Right */
	if (balance > 1 && key > (node->left)->key) {
		node->left = left_rotate(node->left);
		return right_rotate(node);
	}
	/* Right Right */
	if (balance < -1 && key >(node->right)->key)
		return left_rotate(node);
	/* Right Left */
	if (balance < -1 && key < (node->right)->key) {
		node->right = right_rotate(node->right);
		return left_rotate(node);
	}

	return node;
}


tree* find_minimum(tree* node)
{
	tree* min;

	min = node;
	while (min->left != NULL)
		min = min->left;

	return min;
}

tree* node_delete(tree* node, int key)
{
	int balance;
	tree* temp = NULL;

	if (node == NULL)
		return node;
	if (key < node->key)
		node->left = node_delete(node->left, key);
	else if (key > node->key)
		node->right = node_delete(node->right, key);
	else if (key == node->key) {
		/* no child */
		if (node->left == NULL && node->right == NULL) {
			temp = node;
			node = NULL;
			free(temp);
		}
		/* one child */
		else if (node->left == NULL || node->right == NULL) {
			temp = node->left ? node->left : node->right;
			*node = *temp;
			free(temp);
		}
		/* two children */
		else if (node->left && node->right) {
			temp = find_minimum(node->right);
			node->key = temp->key;
			node->right = node_delete(node->right, temp->key);
		}
	}

	if (node == NULL)
		return node;
	node->height = maxi(height(node->left), height(node->right)) + 1;
	balance = get_balance(node);

	/* Left Left */
	if (balance > 1 && get_balance(node->left) >= 0)
		return right_rotate(node);
	/* Left Right */
	if (balance > 1 && get_balance(node->left) < 0) {
		node->left = left_rotate(node->left);
		return right_rotate(node);
	}
	if (balance < -1 && get_balance(node->right) <= 0)
		return left_rotate(node);
	if (balance < -1 && get_balance(node->right) > 0) {
		node->right = right_rotate(node->right);
		return left_rotate(node);
	}

	return node;
}

/*
 * print items of a tree
 */
void print_tree(tree* node)
{
	if (node) {
		print_tree(node->left);
		printf(" %d ", node->key);
		print_tree(node->right);
	}
}


int main()
{
	tree* root = NULL;

	root = node_insert(root, 3);
	root = node_insert(root, 4);
	root = node_insert(root, 5);
	root = node_insert(root, 1);
	root = node_insert(root, 2);
	print_tree(root);
	printf("\n");

	root = node_delete(root, 7);
	root = node_delete(root, 1);
	print_tree(root);

	return 0;
}