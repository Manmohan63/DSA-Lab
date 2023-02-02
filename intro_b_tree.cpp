/*Introduction of B - Tree
                        Difficulty Level : Hard
                                               Last Updated : 01 Sep,
    2022 Read
            Discuss

                B -
        Tree is a self - balancing search tree.In most of the other self - balancing search trees(like AVL and Red - Black Trees),
    it is assumed that everything is in the main memory.

        To understand the use of B
        - Trees,
    we must think of the huge amount of data that cannot fit in the main memory.When the number of keys is high, the data is read from the disk in the form of blocks.Disk access time is very high compared to the main memory access time.The main idea of using B - Trees is to reduce the number of disk accesses.Most of the tree operations(search, insert, delete, max, min, ..etc) require O(h) disk accesses where h is the height of the tree. B-tree is a fat tree. The height of B-Trees is kept low by putting the maximum possible keys in a B-Tree node. Generally, the B-Tree node size is kept equal to the disk block size. Since the height of the B-tree is low so total disk accesses for most of the operations are reduced significantly compared to balanced Binary Search Trees like AVL Tree, Red-Black Tree, etc.

Time Complexity of B-Tree: 
 
Sr. No.	Algorithm	Time Complexity
1.	Search	O(log n)
2.	Insert	O(log n)
3.	Delete	O(log n)
Note: “n” is the total number of elements in the B-tree

Properties of B-Tree: 
All leaves are at the same level.
B-Tree is defined by the term minimum degree ‘t‘. The value of ‘t‘ depends upon disk block size.
Every node except the root must contain at least t-1 keys. The root may contain a minimum of 1 key.
All nodes (including root) may contain at most (2*t – 1) keys.
Number of children of a node is equal to the number of keys in it plus 1.
All keys of a node are sorted in increasing order. The child between two keys k1 and k2 contains all keys in the range from k1 and k2.
B-Tree grows and shrinks from the root which is unlike Binary Search Tree. Binary Search Trees grow downward and also shrink from downward.
Like other balanced Binary Search Trees, the time complexity to search, insert and delete is O(log n).
Insertion of a Node in B-Tree happens only at Leaf Node.
Following is an example of a B-Tree of minimum order 5 
Note: that in practical B-Trees, the value of the minimum order is much more than 5. 
 



We can see in the above diagram that all the leaf nodes are at the same level and all non-leafs have no empty sub-tree and have keys one less than the number of their children.

Interesting Facts about B-Trees: 
The minimum height of the B-Tree that can exist with n number of nodes and m is the maximum number of children of a node can have is:  h_{min} =\lceil\log_m (n + 1)\rceil - 1    
The maximum height of the B-Tree that can exist with n number of nodes and t is the minimum number of children that a non-root node can have is:  h_{max} =\lfloor\log_t\frac {n + 1}
{
    2
}
\rfloor and t = \lceil\frac{m} { 2 }\rceil
Traversal in B-Tree: 
Traversal is also similar to Inorder traversal of Binary Tree. We start from the leftmost child, recursively print the leftmost child, then repeat the same process for the remaining children and keys. In the end, recursively print the rightmost child. 

Search Operation in B-Tree: 
Search is similar to the search in Binary Search Tree. Let the key to be searched is k. 

Start from the root and recursively traverse down. 
For every visited non-leaf node, 
If the node has the key, we simply return the node. 
Otherwise, we recur down to the appropriate child (The child which is just before the first greater key) of the node. 
If we reach a leaf node and don’t find k in the leaf node, then return NULL.
Searching a B-Tree is similar to searching a binary tree. The algorithm is similar and goes with recursion. At each level, the search is optimized as if the key value is not present in the range of the parent then the key is present in another branch. As these values limit the search they are also known as limiting values or separation values. If we reach a leaf node and don’t find the desired key then it will display NULL.

Algorithm for Searching an Element in a B-Tree:-
BtreeSearch(x, k)
    i = 1
      
    // n[x] means number of keys in x node
    while i ≤ n[x] and k ≥ keyi[x]
        do i = i + 1
    if i  n[x] and k = keyi[x]
        then return (x, i)   
    if leaf [x]
        then return NIL
    else
        return BtreeSearch(ci[x], k)
Examples: 

Input: Search 120 in the given B-Tree. 
 



 
Solution: 
 



 



 



In this example, we can see that our search was reduced by just limiting the chances where the key containing the value could be present. Similarly if within the above example we’ve to look for 180, then the control will stop at step 2 because the program will find that the key 180 is present within the current node. And similarly, if it’s to seek out 90 then as 90 < 100 so it’ll go to the left subtree automatically, and therefore the control flow will go similarly as shown within the above example.

Below is the implementation of the above approach:
*/

// C++ implementation of search() and traverse() methods
#include <iostream>
using namespace std;

// A BTree node
class BTreeNode
{
    int *keys;     // An array of keys
    int t;         // Minimum degree (defines the range for number
                   // of keys)
    BTreeNode **C; // An array of child pointers
    int n;         // Current number of keys
    bool leaf;     // Is true when node is leaf. Otherwise false
public:
    BTreeNode(int _t, bool _leaf); // Constructor

    // A function to traverse all nodes in a subtree rooted
    // with this node
    void traverse();

    // A function to search a key in the subtree rooted with
    // this node.
    BTreeNode *
    search(int k); // returns NULL if k is not present.

    // Make the BTree friend of this so that we can access
    // private members of this class in BTree functions
    friend class BTree;
};

// A BTree
class BTree
{
    BTreeNode *root; // Pointer to root node
    int t;           // Minimum degree
public:
    // Constructor (Initializes tree as empty)
    BTree(int _t)
    {
        root = NULL;
        t = _t;
    }

    // function to traverse the tree
    void traverse()
    {
        if (root != NULL)
            root->traverse();
    }

    // function to search a key in this tree
    BTreeNode *search(int k)
    {
        return (root == NULL) ? NULL : root->search(k);
    }
};

// Constructor for BTreeNode class
BTreeNode::BTreeNode(int _t, bool _leaf)
{
    // Copy the given minimum degree and leaf property
    t = _t;
    leaf = _leaf;

    // Allocate memory for maximum number of possible keys
    // and child pointers
    keys = new int[2 * t - 1];
    C = new BTreeNode *[2 * t];

    // Initialize the number of keys as 0
    n = 0;
}

// Function to traverse all nodes in a subtree rooted with
// this node
void BTreeNode::traverse()
{
    // There are n keys and n+1 children, traverse through n
    // keys and first n children
    int i;
    for (i = 0; i < n; i++)
    {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (leaf == false)
            C[i]->traverse();
        cout << " " << keys[i];
    }

    // Print the subtree rooted with last child
    if (leaf == false)
        C[i]->traverse();
}

// Function to search key k in subtree rooted with this node
BTreeNode *BTreeNode::search(int k)
{
    // Find the first key greater than or equal to k
    int i = 0;
    while (i < n && k > keys[i])
        i++;

    // If the found key is equal to k, return this node
    if (keys[i] == k)
        return this;

    // If the key is not found here and this is a leaf node
    if (leaf == true)
        return NULL;

    // Go to the appropriate child
    return C[i]->search(k);
}