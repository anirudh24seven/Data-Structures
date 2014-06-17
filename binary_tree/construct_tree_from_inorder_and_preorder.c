/*
 * Problem Statement:
 * Construct a tree, given its inorder and preorder traversals.
 *
 * Solution:
 * Algorithm buildTree()
 *   1. Pick an element from Preorder. Increment a Preorder Index variable to pick next element in next recursive call
 *   2. Create a new tree node treeNode with the data as picked element.
 *   3. Find the picked element's index in Inorder. Let the index be inIndex.
 *   4. Call buildTree for elements before inIndex and make the built tree as left subtree of treeNode.
 *   5. Call buildTree for elements after inIndex and make the built tree as right subtree of treeNode.
 *   6. return treeNode
 *
 * Explanation:
 *   I think the algorithm is rather self-explanatory. We try to identify the parent node and call buildTree on its children.
 *
 */

#include <stdio.h>
#include <stdlib.h>

struct node {
    char data;
    struct node* left;
    struct node* right;
};

// Prototypes for utility functions
int search(char array[], int start, int end, char value);
struct node* newNode(char data);

// Recursive function to construct binary tree of size len from Inorder traversal and Preorder traversal. Initial values of inorderStart and inorderEnd should be 0 and -1.
// The function doesn't do error checking for cases where inorder and preorder do not form a tree
struct node* buildTree(char inorder[], char preorder[], int inorderStart, int inorderEnd) {
    static int preorderIndex = 0;

    if (inorderStart > inorderEnd) {
        return NULL;
    }

    // Pick current node from Preorder traversal using preorderIndex and increment preorderIndex
    struct node *treeNode = newNode(preorder[preorderIndex++]);

    // If this node has no children, then return
    if(inorderStart == inorderEnd) {
        return treeNode;
    }

    // Else find the index of this node in the Inorder traversal
    int inorderIndex = search(inorder, inorderStart, inorderEnd, treeNode->data);

    // Using index in Inorder traversal, construct left and right subtrees
    treeNode->left = buildTree(inorder, preorder, inorderStart, inorderIndex-1);
    treeNode->right = buildTree(inorder, preorder, inorderIndex+1, inorderEnd);

    return treeNode;

}

// Utility functions
//
// Function to find index of value in array[start...end]. The function assumes that value is present in inorder[]
int search(char array[], int start, int end, char value) {
    int i;
    for (i = start; i <= end; i++ ) {
        if (array[i] == value) {
            return i;
        }
    }
}

// Helper function that allocates a new node with the given data and NULL left and right pointers
struct node* newNode(char data) {
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return(node);
}

// Function to test buildTree()
void printInorder(struct node* node) {
    if (node == NULL) {
        return;
    }

    printInorder(node->left);

    printf("%c", node->data);

    printInorder(node->right);
}

// Driver program to test the above functions
int main() {
    char inorder[] = {'D', 'B', 'E', 'A', 'F', 'C'};
    char preorder[] = {'A', 'B', 'D', 'E', 'C', 'F'};

    int length = sizeof(inorder)/sizeof(inorder[0]);

    struct node *root = buildTree(inorder, preorder, 0, length -1 );

    printf("Inorder traversal of the constructed tree is \n");
    printInorder(root);
    printf("\n");
}
