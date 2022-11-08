#include <stdlib.h>
#include <stdio.h>

#include "tree.h"

int main(){
    Node node8 = {7, NULL, NULL};
    Node node7 = {7, &node8, NULL};
    Node node6 = {7, NULL, NULL};
    Node node5 = {4, NULL, NULL};
    Node node4 = {5, NULL, NULL};
    Node node3 = {7, &node6, &node7};
    Node node2 = {9, &node4, &node5};
    Node Root = {44, &node2, &node3};

    Node *root = &Root;

    bool b = CheckForSumTree(root);
    printf("Tree is sum tree: %s\n", b? "True": "False");

    int dis = FindDistance(root, &node7, &node2);
    printf("The distance is: %d\n", dis);

    int subtrees = CountSubtrees(root);
    printf("Number of subtrees in which all nodes have identical values: %d\n", subtrees);

    b = CheckSkewed(root);
    printf("Tree is skewed: %s\n", b? "True": "False");

    printf("Left view of tree: "); PrintLeftView(root); puts("\n");

    puts("Level traversal of tree before truncation:"); PrintLevelTraversal(root); //puts("\n\n\n");
    //PrintTree2d(root, 0); puts("\n\n\n");

    truncate(root, 60);
    
    //PrintTree2d(root, 0); puts("\n\n\n");
    puts("Level traversal of tree after truncation:"); PrintLevelTraversal(root); //puts("\n\n\n");
}
