#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool avl_flag = false;

typedef struct _node {
	struct _node *child[2];
	int load;
	int value;
	struct _node **array;
	int index;
	int *count;
} Node;

typedef struct _stack {
	Node **array;
	int count;
	int capacity;
} Stack;

static int
bitwise_log2(int num) {
	int j;
	
	j = 0;
	while (num >> 1) {
		num >>= 1;
		j++;
	}
	
	return j;
}

static Node *
create_root(void) {
	Node *root = malloc(sizeof(Node));
	root->child[0] = NULL;
	root->child[1] = NULL;
	root->load = 0;
	
	return root;
}

static Node *
create_node(int value, Node **array, int index, int *count) {
	Node *node;
	
	node = create_root();
	node->value = value;
	node->array = array;
	node->index = index;
	node->count = count;
	
	(*count)++;
	
	return node;
}

static Node *
create_tree(int num_nodes) {
	Node *root;
	
	root = create_root();
	
	root->value = 0;
	
	root->array = calloc(num_nodes, sizeof(Node *));
	root->array[0] = NULL;
	root->array[1] = root;
	
	root->index = 1;
	
	root->count = calloc(1, sizeof(int));
	*root->count = 1;
	
	return root;
}

static Stack *
create_stack(int node_count) {
	Stack *stack;
	
	stack = malloc(sizeof(Stack));
	
	stack->capacity = 2 * bitwise_log2(node_count);
	stack->array = calloc(stack->capacity, sizeof(Node *));
	stack->count = 0;
	
	return stack;
}

static int
push(Stack *stack, Node *node) {
	stack->array[stack->count++] = node;
	
	return 0;
}

static Node *
pop(Stack *stack) {
	return stack->array[--stack->count];
}

static int
rebalance(Stack *stack) {
	
	return 0;
}

static Node *
find_parent(int value, Node *root, Stack *stack) {
	Node *parent;
	int direction;
	
	parent = root;
	push(stack, parent);
	direction = value > parent->value;
	
	while (parent->child[direction] && parent->child[direction]->value != value) {
		parent = parent->child[direction];
		push(stack, parent);
		direction = value > parent->value;
	}
	
	return parent;
}

static int
delete_node(Node *node) {
	(*node->count)--;
	free(node);
	
	return 0;
}

static int
delete(int value, Node *root) {
	Stack *stack;
	Node *parent;
	int direction;
	Node *node_del; /* node to be deleted */
	
	stack = create_stack(*root->count);
	parent = find_parent(value, root, stack);
	if (parent->value == root->value)
		return -1;
	
	direction = value > parent->value;
	node_del = parent->child[direction];
	
	if (node_del->child[0] && node_del->child[1]) {
		/* node to be deleted has two children */
		
		/* strategy:
		 * 1. remove node of interest and replace with next-smallest node
		 * 2. when swapping out next-smallest node, reconnect its child
		 * 	  (by definition, it can only have one, and it will be to the left)
		 * 	  with its parent
		 * 3. rebalance this new connection, if necessary
		 * 4. reconnect the children of the node to be deleted with the
		 *    next-smallest node, which is being swapped up
		 * 5. rebalance upwards from deletion */
		
		Stack *stack2;
		Node *node_swap; /* node to be swapped with node to be deleted */
		Node *node_swap_parent; /* parent of node to be swapped */
		
		stack2 = create_stack(*root->count);
		node_swap = find_parent(node_del->value, parent, stack2);
		
		pop(stack2); /* remove node to be swapped from stack2 */
		node_swap_parent = pop(stack2);
		
		node_swap_parent->child[1] = node_swap->child[0];
		node_swap->child[0] = node_del->child[0];
		node_swap->child[1] = node_del->child[1];
		parent->child[direction] = node_swap;
		
		rebalance(stack2);
		
		free(stack2);
	} else
		/* node to be deleted has zero or one children */
		parent->child[direction] = node_del->child[0] ? node_del->child[0] : node_del->child[1];
			
	delete_node(node_del);
	rebalance(stack);
	
	free(stack);
	return 0;
}

static int
insert(int value, Node *root) {
	Stack *stack;
	Node **array;
	Node *parent;
	int index, direction;
	
	array = root->array;
	stack = create_stack(*root->count);
	parent = find_parent(value, root, stack);
	
	direction = value > parent->value;
	index = parent->index * 2 + direction;
	parent->child[direction] = create_node(value, array, index, root->count);
	
	array[index] = parent->child[direction];
	rebalance(stack);
	
	free(stack);
	return 0;
}

int
main(int argc, char **argv)
{
	avl_flag = true;
	
	Node *root = create_tree(128);
	root->value = 22;
	insert(24, root);
	insert(2, root);
	insert(44, root);
	insert(23, root);
	delete(44, root);
	
	return 0;
}
