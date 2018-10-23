#include <stdio.h>
#include <stdlib.h>

enum tree_type
{
	BIN, 
	BST,
	AVL,
	RB,
	HEAP,
	SPLAY
};

typedef struct _node
{
	void *data;
	struct _node *child[2];
	int load;
	int value;
	int *count;
} Node;

typedef struct _stack
{
	Node **array;
	int count;
	int capacity;
} Stack;

static int
bitwise_log2(int num)
{
	int j;
	
	j = 0;
	while (num >> 1) {
		num >>= 1;
		j++;
	}
	
	return j;
}

static Stack *
create_stack(int node_count)
{
	Stack *stack;
	
	stack = malloc(sizeof(Stack));
	
	stack->capacity = 2 * bitwise_log2(node_count);
	stack->array = calloc(stack->capacity, sizeof(Node *));
	stack->count = 0;
	
	return stack;
}

static Node *
create_node(int value, int *count)
{
	Node *node;
	
	node = malloc(sizeof(Node));
	node->data = NULL;
	node->child[0] = NULL;
	node->child[1] = NULL;
	node->load = 0;
	node->value = value;
	node->count = count;
	
	(*count)++;
	
	return node;
}

static Node *
create_tree(void)
{
	int *count;
	Node *root;
	
	count = calloc(1, sizeof(int));
	
	root = create_node(0, count);
	
	return root;
}

static int
push(Stack *stack, Node *node)
{
	stack->array[stack->count++] = node;
	
	return 0;
}

static Node *
pop(Stack *stack)
{
	return stack->array[--stack->count];
}

static Node *
peek(Stack *stack)
{
	return stack->array[stack->count - 1];
}

static int
zip(Node **node, int direction)
{
	Node *node_new;
	
	node_new = (*node)->child[direction];
	(*node)->child[direction] = node_new->child[!direction];
	node_new->child[!direction] = *node;
	
	*node = node_new;
	
	return 0;
}

static int
zig(Node **node)
{
	int direction;
	
	direction = !((*node)->load & 4); /* use 2's complement to determine sign of load */
	
	zip(node, direction);
	
	(*node)->load = 0;
	(*node)->child[!direction]->load = 0;
	
	return 0;
}

static int
zag(Node **node)
{
	int direction;
	
	direction = !((*node)->load & 4); /* use 2's complement to determine sign of load */
	
	zip(&(*node)->child[direction], !direction);
	zip(node, direction);
	
	if (!direction)
		direction = -1;
	
	if (direction == (*node)->load) {
		(*node)->child[!direction]->load = direction * -1;
		(*node)->child[direction]->load = 0;
	} else {
		(*node)->child[!direction]->load = 0;
		(*node)->child[direction]->load = direction * -1;
	}
	(*node)->load = 0;
	
	return 0;
}

static Node *
find_parent(int value, Node *root, Stack *stack)
{
	Node *parent;
	int direction;
	
	parent = root;
	direction = value > parent->value;
	if (stack)
		push(stack, parent);
	
	while (parent->child[direction] && parent->child[direction]->value != value) {
		parent = parent->child[direction];
		direction = value > parent->value;
		if (stack)
			push(stack, parent);
	}
	
	return parent;
}

static int
rebalance(Node **node)
{
	int direction;
	
	direction = !((*node)->load & 4); /* use 2's complement to determine sign of load */
	
	if ((*node)->load >> 2 == (*node)->child[direction]->load >> 2)
		zig(node);
	else
		zag(node);
	
	return 0;
}

static int
balance(Stack *stack, int value)
{
	int i;
	Node *node;
	
	for (i = stack->count; i; i--) {
		node = pop(stack);
		
		if (value > node->value)
			node->load++;
		else
			node->load--;
		
		switch (node->load) {
			case 2:
			case -2:
				rebalance(&node);
			case 0:
				return 0;
		}
	}
	
	return 0;
}

void
destroy_stack(Stack *stack)
{
	free(stack->array);
	free(stack);
}

static int
destroy_node(int value, Node *root)
{
	Stack *stack;
	Node *parent;
	int direction;
	Node *node; /* node to be deleted */
	
	stack = create_stack(*root->count);
	parent = find_parent(value, root, stack);
	if (parent->value == root->value)
		return -1;
	
	direction = value > parent->value;
	node = parent->child[direction];
	
	if (node->child[0] && node->child[1]) {
		/* node to be deleted has two children */
		
		/* strategy:
		 * 1. Remove node of interest and replace with next-smallest node.
		 * 2. When swapping out next-smallest node, connect its child
		 * 	  (by definition, it can only have one, and it will be to the left)
		 * 	  to its parent.
		 * 3. Rebalance this new connection, if necessary.
		 * 4. Set the swap node into place and connect the children,
		 *    completing the swap.
		 * 5. Rebalance upwards from deletion. */
		
		Stack *stack2;
		Node *node_swap; /* node to be swapped with node to be deleted */
		Node *node_swap_parent; /* parent of node to be swapped */
		
		stack2 = create_stack(*root->count);
		node_swap = find_parent(node->value, parent, stack2);
		
		pop(stack2); /* reverse stack by one, throw away node */
		node_swap_parent = pop(stack2);
		
		node_swap_parent->child[1] = node_swap->child[0];
		node_swap->child[0] = node->child[0];
		node_swap->child[1] = node->child[1];
		parent->child[direction] = node_swap;
		
		balance(stack2, value);
		
		destroy_stack(stack2);
	} else
		/* node to be deleted has zero or one children */
		parent->child[direction] = node->child[0] ? node->child[0] : node->child[1];
			
	balance(stack, value);
	
	(*node->count)--;
	free(node->data);
	free(node);
	
	destroy_stack(stack);
	
	return 0;
}

static int
destroy_tree(Node *root)
{
	return 0;
}

static int
insert(int value, Node *root)
{
	Stack *stack;
	Node *parent;
	int direction;
	
	stack = create_stack(*root->count);
	parent = find_parent(value, root, stack);
	
	direction = value > parent->value;
	parent->child[direction] = create_node(value, root->count);
	
	balance(stack, value);
	
	destroy_stack(stack);
	return 0;
}

static int
breadth_first_traversal(Node *root, Stack *stack)
{
	
	return 0;
}

static int
pre_order_traversal(Node *root, Stack *stack)
{
	
	return 0;
}

static int
in_order_traversal(Node *root, Stack *stack)
{
	
	return 0;
}

static int
post_order_traversal(Node *root, Stack *stack)
{
	
	return 0;
}
