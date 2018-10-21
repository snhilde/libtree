# libtree
Library for creating binary tree objects.

Contents:
* [Data Structures](#data-structures)
	* [Tree Node](#tree-node)
	* [Stack](#stack)
* [Functions](#functions)
	* [Object Functions](#object-functions)
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
* [Object Functions](#object-functions)
* [Node Functions](#node-functions)
* [Rotation Functions](#rotation-functions)
* [Stack Functions](#stack-functions)
* [Traversal Functions](#traversal-functions)
* [Helper Functions](#helper-functions)

#### Object Functions
| | `Node * create_tree(void)` |
| ---- | ---- |
| Description | Create new tree. Memory is allocated for one node and one integer. Must be freed with destroy_tree() |
| Argument    | none |
| Return      | pointer to root node of tree |

| | `int destroy_tree(Node *root)` |
| ---- | ---- |
| Description | Destroy tree, including all nodes within. |
| Argument    | root: root node of tree |
| Return      | 0 on success, 1 on failure |

| | `Stack * create_stack(int node_count)` |
| ---- | ---- |
| Description | Create new stack. Memory is allocated for stack struct and number of pointers. Must be freed with destroy_stack() |
| Argument    | node_count: number of nodes to reserve space for, rec. height of tree |
| Return      | pointer to new stack |

| | `void destroy_stack(Stack *stack)` |
| ---- | ---- |
| Description | Destroy stack. |
| Argument    | stack: stack to be destroyed |
| Return      | no return value |

#### Node Functions
| | `Node *  create_node(int value, int *count)` |
| ---- | ---- |
| Description | Create new node. The node must be freed with `destroy()` after use. |
| Arguments   | value: value of node<br>count: pointer to node count for tree |
| Return      | pointer to a new node |

| | `int destroy(int value, Node *root)` |
| ---- | ---- |
| Description | description |
| Arguments   | args |
| Return      | return |

| | `int insert(int value, Node *root)` |
| ---- | ---- |
| Description | description |
| Arguments   | args |
| Return      | return |

| | `Node * find_parent(int value, Node *root, Stack *stack)` |
| ---- | ---- |
| Description | description |
| Arguments   | args |
| Return      | return |

#### Rotation Functions
| | `int balance(Stack *stack, int value)` |
| ---- | ---- |
| Description | description |
| Arguments   | args |
| Return      | return |

| | `int zig(Node **node, int direction)` |
| ---- | ---- |
| Description | description |
| Arguments   | args |
| Return      | return |

| | `int zag(Node **node, int direction)` |
| ---- | ---- |
| Description | description |
| Arguments   | args |
| Return      | return |

#### Stack Functions
| | `int push(Stack *stack, Node *node)` |
| ---- | ---- |
| Description | description |
| Arguments   | args |
| Return      | return |

| | `Node * pop(Stack *stack)` |
| ---- | ---- |
| Description | description |
| Argument    | args |
| Return      | return |

| | `Node * peek(Stack *stack)` |
| ---- | ---- |
| Description | description |
| Argument    | args |
| Return      | return |

#### Traversal Functions
| | `int breadth_first_traversal(Node *root, Stack *stack)` |
| ---- | ---- |
| Description | description |
| Arguments   | args |
| Return      | return |

| | `int pre_order_traversal(Node *root, Stack *stack)` |
| ---- | ---- |
| Description | description |
| Arguments   | args |
| Return      | return |

| | `int in_order_traversal(Node *root, Stack *stack)` |
| ---- | ---- |
| Description | description |
| Arguments   | args |
| Return      | return |

| | `int post_order_traversal(Node *root, Stack *stack)` |
| ---- | ---- |
| Description | description |
| Arguments   | args |
| Return      | return |

#### Helper Functions
| | `int bitwise_log2(int num)` |
| ---- | ---- |
| Description | description |
| Argument    | args |
| Return      | return |

| | `int zip(Node **node, int direction)` |
| ---- | ---- |
| Description | description |
| Arguments   | args |
| Return      | return |

| | `int rebalance(Node **node)` |
| ---- | ---- |
| Description | description |
| Argument    | args |
| Return      | return |

| | `int destroy_node(Node *node)` |
| ---- | ---- |
| Description | description |
| Argument    | args |
| Return      | return |
