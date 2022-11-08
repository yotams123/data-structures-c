#include <stdbool.h>
#include <math.h>
#include <stdio.h>

typedef struct s Node;
struct s
{
    int data;
    Node *left;
    Node *right;
};

static Node NULLNODE = {-1, NULL, NULL};

static bool CompNodes(Node *n1, Node *n2){
    return (n1->data == n2->data && n1->left == n2->left && n1->right == n2->right);
}

void PreorderTraversalPrint(Node *root){
    if (root == NULL) return;

    printf("%d ", root->data);
    PreorderTraversalPrint(root->left);
    PreorderTraversalPrint(root->right);
}

int SumTree(Node *root){
    int sum = root->data;
    if (root->left) sum += SumTree(root->left);
    if (root->right) sum += SumTree(root->right);
    return sum;
}

bool CheckForSumTree(Node *root){
    if (!(root->left) && !(root->right)){
        return true;
    }
    bool flag = true;
    if (root->left && !CheckForSumTree(root->left)) flag = false;
    if (root->right && !CheckForSumTree(root->right)) flag = false;
    if (root->data != (SumTree(root) - root->data)) flag = false;
    return flag;
}

int FindDepth(Node *root, Node *n){
    if (n==root) return 0;
    if (!(root->left) && !(root->right)) return -1;

    if (root->left && FindDepth(root->left, n) > -1) return FindDepth(root->left, n) + 1;
    if (root->right && FindDepth(root->right, n) > -1) return FindDepth(root->right, n) + 1;
    return -1;
}


int FindDistance(Node *root, Node *n1, Node *n2){
    Node *curr = root;
    Node *backcurr = NULL;
    int d1 = FindDepth(root, n1);
    int d2 = FindDepth(root, n2);

    if (d1 == 0 || d2 == 0){
        return abs(d1 - d2);
    }

    bool prev = false; // says if curr backtracked previous round
    while(true){
        if (FindDepth(curr, n1) != -1 && FindDepth(curr, n2) != -1){  // both nodes are still in currs path
            backcurr = curr;
            curr = curr->left;
            prev = false; 
        }
        else if (!prev){  // curr hash checked only left node of parent, can now check right
            if (backcurr == n1){
                return FindDepth(n1, n2);
            } else if (backcurr == n2) {
                return FindDepth(n2, n1);
            }
            curr = backcurr->right;
            prev = true;
        } else { // backcurr is last common ancestor of n1 and n2
            curr = backcurr;
            break;
        }
    }
    
    if (curr == NULL) return -1;
    int common_depth = FindDepth(root, curr);
    return ((d1+d2) - (2*common_depth));
}

bool IdenticalSubtree(Node *root){  //returns true if all nodes share the same value  
    if (root->left && root->left->data != root->data) return false;
    if (root->right && root->right->data != root->data) return false;
    
    if (root->left && !IdenticalSubtree(root->left)) return false;
    if (root->right && !IdenticalSubtree(root->right)) return false;

    return true;
}

int CountSubtrees(Node *root){
    return (root == NULL)? 0: IdenticalSubtree(root) + CountSubtrees(root->left) + CountSubtrees(root->right);
}

bool CheckSkewed(Node *root){
    if(root->left && root->right) return false;
    if (root->left) return CheckSkewed(root->left);
    if (root->right) return CheckSkewed(root->right);
    return true;
}


void PrintLeftView(Node *root){
    printf("%d", root->data);
    if (root->left || root->right){
        printf("-->");
    } else return;
    if (root->left) PrintLeftView(root->left);
    else PrintLeftView(root->right);
}


void truncate(Node *root, int target){
    target -= root->data;
    if (target <= 0) return; 

    if (root->left) truncate(root->left, target);
    if (root->right) truncate(root->right, target);

    if (root->left && CompNodes(root->left, &NULLNODE)) root->left = NULL;
    if (root->right && CompNodes(root->right, &NULLNODE)) root->right = NULL;

    if (!(root->left) && !(root->right)){
        *root = NULLNODE;
    }

    return;
}


void PrintTree2d(Node *root, const int tabs){  // prints tree in a 2d fashion as such
    /*          4 (root->right->right)
            2 (root->right)
                5 (root->right->left)
        1(root)
            3 (root->left)
                6 (root->left->left)
    */
    if (root == NULL) return;

    PrintTree2d(root->right, tabs + 1);
    char *t = malloc((tabs + 1) * sizeof(char));
    for (int i=0; i<tabs; i++){
        t[i] = '\t';
    }
    t[tabs] = 0;
    printf("%s%d\n", t, root->data);
    PrintTree2d(root->left, tabs + 1);
}


int FindMaxDepth(Node *root){
    if (!root) return 0;
    int ldepth = FindMaxDepth(root->left) + 1;
    int rdepth = FindMaxDepth(root->right) + 1;
    return (ldepth > rdepth)? ldepth: rdepth;
}

void PrintNodesatDepth(Node *root, int depth){ // will print nodes at a given depth
    if (!root) return;

    if (depth == 0){
        printf("%d\t", root->data);
        return;
    }
    PrintNodesatDepth(root->left, depth - 1);
    PrintNodesatDepth(root->right, depth - 1);
}

void PrintLevelTraversal(Node *root){
    int levels = FindMaxDepth(root);

    for (int i = 0; i <= levels; i++){
        PrintNodesatDepth(root, i);
        printf("\n");
    }
}