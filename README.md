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

#### Tree Type
```c
enum tree_type
{
	BIN,		/* binary tree, unsorted */
	BST,		/* binary search tree */
	AVL,		/* AVL tree */
	HEAP,		/* heap tree */
	SPLAY		/* splay tree */
};
```
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
| Description | Create new tree. Memory is allocated for one node and one integer. Must be freed with `destroy_tree()`. |
| Argument    | none |
| Return      | pointer to root node of tree |

| | `int destroy_tree(Node *root)` |
| ---- | ---- |
| Description | Destroy tree, including all nodes within. |
| Argument    | `root`: root node of tree |
| Return      | 0 on success, 1 on failure |

| | `Stack * create_stack(int node_count)` |
| ---- | ---- |
| Description | Create new stack. Memory is allocated for stack struct and number of pointers. Must be freed with `destroy_stack()`. |
| Argument    | `node_count`: number of nodes to reserve space for, usually height of tree |
| Return      | pointer to new stack |

| | `void destroy_stack(Stack *stack)` |
| ---- | ---- |
| Description | Destroy stack and free memory. |
| Argument    | `stack`: stack to be destroyed |
| Return      | no return value |

#### Node Functions
| | `Node *  create_node(int value, Node *root)` |
| ---- | ---- |
| Description | Create new node. The node must be freed with `destroy()` after use. |
| Arguments   | `value`: value of node<br>`root`: pointer to root node of tree |
| Return      | pointer to a new node |

| | `int destroy_node(int value, Node *root)` |
| ---- | ---- |
| Description | Destroy node and free memory. |
| Arguments   | `value`: value of node to be found and deleted<br>`root`: root of node's tree |
| Return      | 0 on success, 1 on failure |

| | `int insert(int value, Node *root)` |
| ---- | ---- |
| Description | Add node to tree as leaf in sorted order. |
| Arguments   | `value`: value of node for ordering<br>`root`: root of tree |
| Return      | 0 on success, 1 on failure |

| | `Node * find_parent(int value, Node *root, Stack *stack)` |
| ---- | ---- |
| Description | Get parent of node. |
| Arguments   | `value`: value of node whose parent will be found<br>`root`: root of tree<br>`stack` (optional): stack to be grown during iterative search |
| Return      | parent node of node with value `value` |

#### Rotation Functions
| | `int balance(Stack *stack, int value)` |
| ---- | ---- |
| Description | Balance tree path following AVL rules. |
| Arguments   | `stack`: path of nodes to iteratively traverse upward toward root<br>`value`: value of latest node, used for calculating load factor |
| Return      | 0 on success, 1 on failure |

| | `int zig(Node **node)` |
| ---- | ---- |
| Description | Single rotation. |
| Argument    | `node`: address of node with load factor of |2| |
| Return      | 0 on success, 1 on failure |

| | `int zag(Node **node)` |
| ---- | ---- |
| Description | Double rotation. |
| Argument    | `node`: address of node with load factor of |2| |
| Return      | 0 on success, 1 on failure |

#### Stack Functions
| | `int push(Stack *stack, Node *node)` |
| ---- | ---- |
| Description | Add node to stack. |
| Arguments   | `stack`: stack to be grown<br>`node`: node to add to stack |
| Return      | 0 on success, 1 on failure |

| | `Node * pop(Stack *stack)` |
| ---- | ---- |
| Description | Remove most recent node from stack.<br>Note: This does not actually delete the node from memory. It decrements the head pointer. |
| Argument    | `stack`: stack to pull from |
| Return      | pointer to node |

| | `Node * peek(Stack *stack)` |
| ---- | ---- |
| Description | See the most recent node at the top of the stack. |
| Argument    | `stack`: stack to examine |
| Return      | pointer to node |

| | `static int grow_stack(Stack *stack` |
| ---- | ---- |
| Description | Double capacity of stack. |
| Argument    | `stack`: stack struct of array to grow |
| Return      | 0 on success, 1 on failure |

#### Traversal Functions
| | `int breadth_first_traversal(Node *root, Stack *stack)` |
| ---- | ---- |
| Description | Create stack of nodes by passing over tree breadth-first (level by level). |
| Arguments   | `root`: root of tree<br>`stack`: stack to grow with nodes |
| Return      | 0 on success, 1 on failure |

| | `int pre_order_traversal(Node *root, Stack *stack)` |
| ---- | ---- |
| Description | Create stack of nodes by passing over tree pre order (parent, left, right). |
| Arguments   | `root`: root of tree<br>`stack`: stack to grow with nodes |
| Return      | 0 on success, 1 on failure |

| | `int in_order_traversal(Node *root, Stack *stack)` |
| ---- | ---- |
| Description | Create stack of nodes by passing over tree in order (left, parent, right). |
| Arguments   | `root`: root of tree<br>`stack`: stack to grow with nodes |
| Return      | 0 on success, 1 on failure |

| | `int post_order_traversal(Node *root, Stack *stack)` |
| ---- | ---- |
| Description | Create stack of nodes by passing over tree post order (left, right, parent). |
| Arguments   | `root`: root of tree<br>`stack`: stack to grow with nodes |
| Return      | 0 on success, 1 on failure |

#### Helper Functions
| | `int bitwise_log2(int num)` |
| ---- | ---- |
| Description | Calculate ceiling of log base 2 of number. |
| Argument    | `num`: number for calculation |
| Return      | floor of log base 2 of number |

| | `int zip(Node **node, int direction)` |
| ---- | ---- |
| Description | Perform rotation(s) on node, used by `zig()` and `zag()` |
| Arguments   | `node`: node to rotate<br>`direction`: direction of imbalance |
| Return      | 0 on success, 1 on failure |

| | `int rebalance(Node **node)` |
| ---- | ---- |
| Description | Determine if single or double rotation is need to rebalance tree |
| Argument    | `node`: node to be rebalanced |
| Return      | 0 on success, 1 on failure |
