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
| | `Node * create_tree(int tree_type)` |
| ---- | ---- |
| Description | Create new tree. Memory is allocated for one node and one integer. Must be freed with `free_tree()`.<br>Note: the initial value for the root node will be 0. |
| Argument    | `tree_type`: type from enum `tree_type` |
| Return      | pointer to root node of tree, or NULL on error |

| | `int free_tree(Node *root)` |
| ---- | ---- |
| Description | Destroy tree, freeing all nodes within. |
| Argument    | `root`: root node of tree |
| Return      | 0 on success, 1 on failure |

| | `Stack * create_stack(int node_count)` |
| ---- | ---- |
| Description | Create new stack. Memory is allocated for stack struct and number of pointers. Must be freed with `free_stack()`. |
| Argument    | `node_count`: number of nodes to reserve space for, usually height of tree |
| Return      | pointer to new stack, or NULL on error |

| | `void free_stack(Stack *stack)` |
| ---- | ---- |
| Description | Destroy stack and free memory. |
| Argument    | `stack`: stack to be destroyed |
| Return      | no return value |

#### Node Functions
| | `Node *  create_node(int value, Node *root)` |
| ---- | ---- |
| Description | Create new node. The node must be freed with `destroy()` after use. |
| Arguments   | `value`: value of node<br>`root`: pointer to root node of tree |
| Return      | pointer to a new node, or NULL on error |

| | `int destroy_node(int value, Node *root)` |
| ---- | ---- |
| Description | Destroy node and free memory. If tree is binary tree (type is BIN), then the node and all its subordinates are all freed. |
| Arguments   | `value`: value of node to be found and deleted<br>`root`: root of node's tree |
| Return      | 0 on success, 1 on failure |

| | `int insert(int value, Node *root)` |
| ---- | ---- |
| Description | Add node to tree as leaf in sorted order.<br>Automatically balances according to tree type. |
| Arguments   | `value`: value of node for ordering<br>`root`: root of tree |
| Return      | 0 on success, 1 on failure |

| | `Node * find_parent(int value, Node *root, Stack *stack)` |
| ---- | ---- |
| Description | Get parent of node. |
| Arguments   | `value`: value of node whose parent will be found<br>`root`: root of tree<br>`stack` (optional): stack to be grown during iterative search |
| Return      | parent node of node with value `value`, or NULL on failure |

#### Rotation Functions
| | `void balance(Stack *stack, int value)` |
| ---- | ---- |
| Description | Balance tree path following AVL rules. |
| Arguments   | `stack`: path of nodes to iteratively traverse upward toward root<br>`value`: value of latest node, used for calculating load factor |
| Return      | no return value |

| | `void zig(Node **node)` |
| ---- | ---- |
| Description | Single rotation. |
| Argument    | `node`: address of node with load factor of |2| |
| Return      | no return value |

| | `void zag(Node **node)` |
| ---- | ---- |
| Description | Double rotation. |
| Argument    | `node`: address of node with load factor of |2| |
| Return      | no return value |

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
| Return      | pointer to node, or NULL on failure |

| | `Node * peek(Stack *stack)` |
| ---- | ---- |
| Description | See the most recent node at the top of the stack. |
| Argument    | `stack`: stack to examine |
| Return      | pointer to node |

| | `static Stack * grow_stack(Stack *stack)` |
| ---- | ---- |
| Description | Double capacity of stack. |
| Argument    | `stack`: stack struct of array to grow |
| Return      | pointer to stack, or NULL on failure |

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

| | `int set_type(int flag)` |
| ---- | ---- |
| Description | Set tree type (from enum `tree_type`) of tree. |
| Argument    | `flag`: number from enum `tree_type` |

| | `int get_type(Node *node)` |
| ---- | ---- |
| Description | Get tree type of tree (as per enum `tree_type`). |
| Argument    | `node`: node to check |

| | `int check_type(Node *node, int flag)` |
| ---- | ---- |
| Description | Check whether or not node is a certain `tree_type`. |
| Arguments   | `node`: node to check<br>`flag`: number from enum `tree_type` |

| | `void zip(Node **node, int direction)` |
| ---- | ---- |
| Description | Perform rotation(s) on node, used by `zig()` and `zag()` |
| Arguments   | `node`: node to rotate<br>`direction`: direction of imbalance |
| Return      | no return value |

| | `void rebalance(Node **node)` |
| ---- | ---- |
| Description | Determine if single or double rotation is need to rebalance tree |
| Argument    | `node`: node to be rebalanced |
| Return      | no return value |

| | `void splay(Node *node, Stack *stack)` |
| ---- | ---- |
| Description | Iteratively rotate node up into root position. |
| Arguments    | `node`: node to rotate up<br>`stack`: path to iteratively traverse |
| Return      | no return value |
