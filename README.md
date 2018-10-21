# libtree
Library for creating binary tree objects.

Contents:
* [Data Structures](#data-structures)
	* [Tree Node](#tree-node)
	* [Stack](#stack)
* [Functions](#functions)
	* [Object Creation](#object-creation)
	* [Node Functions](#node-functions)
	* [Rotation Functions](#rotation-functions)
	* [Stack Functions](#stack-functions)
	* [Traversal Functions](#traversal-functions)
	* [Helper Functions](#helper-functions)

## Data Structures
* [Tree Node](#tree-node)
* [Stack](#stack)

#### Tree Node
```c
typedef struct _node
{
	void *data;		/* pointer to user-supplied data */
	struct _node *child[2];	/* pointers to left and right children */
	int load;		/* balance factor, only used by balanced trees */
	int value;		/* numerical value for sorting tree */
	int *count;		/* pointer to number of nodes in tree */
} Node;
```
#### Stack
```c
typedef struct _stack
{
	Node **array;	/* pointer to stack array */
	int count;	/* number of nodes in stack */
	int capacity;	/* maximum capacity of stack */
} Stack;
```

## Functions
* [Object Creation](#object-creation)
* [Node Functions](#node-functions)
* [Rotation Functions](#rotation-functions)
* [Stack Functions](#stack-functions)
* [Traversal Functions](#traversal-functions)
* [Helper Functions](#helper-functions)

#### Object Creation
* `Node *  create_node(int value, int index, int *count)`
* `Node *  create_tree(int num_nodes)`
* `Stack * create_stack(int node_count)`
#### Node Functions
`int     insert(int value, Node *root)`
`int     delete(int value, Node *root)`
`Node *  find_parent(int value, Node *root, Stack *stack)`
#### Rotation Functions
`int     balance(Stack *stack, int value)`
`int     zig(Node **node, int direction)`
`int     zag(Node **node, int direction)`
#### Stack Functions
`int     push(Stack *stack, Node *node)`
`Node *  pop(Stack *stack)`
`Node *  peek(Stack *stack)`
#### Traversal Functions
`int     breadth_first_traversal(Node *root, Stack *stack)`
`int     pre_order_traversal(Node *root, Stack *stack)`
`int     in_order_traversal(Node *root, Stack *stack)`
`int     post_order_traversal(Node *root, Stack *stack)`
#### Helper Functions
`int     bitwise_log2(int num)`
`int     zip(Node **node, int direction)`
`int     rebalance(Node **node)`
`int     delete_node(Node *node)`
