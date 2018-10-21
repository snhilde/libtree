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
| | `Node *  create_node(int value, int *count)` |
| ------------------- | ------------------- |
| Description | Create new node. |
| Arguments | value of node, pointer to node count for tree |
| Return Value | pointer to a new node |

| | `Node *  create_tree(int num_nodes)` |
| --- | --- |
| Description | description |
| Arguments | args |
| Return Value | return |

| | `Stack * create_stack(int node_count)` |
| --- | --- |
| Description | description |
| Arguments | args |
| Return Value | return |

#### Node Functions
| | `int insert(int value, Node *root)` |
| --- | --- |
| Description | description |
| Arguments | args |
| Return Value | return |

| | `int delete(int value, Node *root)` |
| --- | --- |
| Description | description |
| Arguments | args |
| Return Value | return |

| | `Node * find_parent(int value, Node *root, Stack *stack)` |
| --- | --- |
| Description | description |
| Arguments | args |
| Return Value | return |

#### Rotation Functions
| | `int balance(Stack *stack, int value)` |
| --- | --- |
| Description | description |
| Arguments | args |
| Return Value | return |

| | `int zig(Node **node, int direction)` |
| --- | --- |
| Description | description |
| Arguments | args |
| Return Value | return |

| | `int zag(Node **node, int direction)` |
| --- | --- |
| Description | description |
| Arguments | args |
| Return Value | return |

#### Stack Functions
| | `int push(Stack *stack, Node *node)` |
| --- | --- |
| Description | description |
| Arguments | args |
| Return Value | return |

| | `Node * pop(Stack *stack)` |
| --- | --- |
| Description | description |
| Arguments | args |
| Return Value | return |

| | `Node * peek(Stack *stack)` |
| --- | --- |
| Description | description |
| Arguments | args |
| Return Value | return |

#### Traversal Functions
| | `int breadth_first_traversal(Node *root, Stack *stack)` |
| --- | --- |
| Description | description |
| Arguments | args |
| Return Value | return |

| | `int pre_order_traversal(Node *root, Stack *stack)` |
| --- | --- |
| Description | description |
| Arguments | args |
| Return Value | return |

| | `int in_order_traversal(Node *root, Stack *stack)` |
| --- | --- |
| Description | description |
| Arguments | args |
| Return Value | return |

| | `int post_order_traversal(Node *root, Stack *stack)` |
| --- | --- |
| Description | description |
| Arguments | args |
| Return Value | return |

#### Helper Functions
| | `int bitwise_log2(int num)` |
| --- | --- |
| Description | description |
| Arguments | args |
| Return Value | return |

| | `int zip(Node **node, int direction)` |
| --- | --- |
| Description | description |
| Arguments | args |
| Return Value | return |

| | `int rebalance(Node **node)` |
| --- | --- |
| Description | description |
| Arguments | args |
| Return Value | return |

| | `int delete_node(Node *node)` |
| --- | --- |
| Description | description |
| Arguments | args |
| Return Value | return |
