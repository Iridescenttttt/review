#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 24

typedef struct TreeNode{
    int val;
    struct TreeNode *left, *right;
}TreeNode;

TreeNode* Insert(TreeNode *root, int val)                  //递归(不用**root，最后返回新树根节点)
{
    if(!root){
        root = (TreeNode*)malloc(sizeof(TreeNode));
        root->val = val;
        root->left = root->right = NULL;
        return root;
    }
    if(root->val == val)return root;
    else if(root->val > val){
        root->left = Insert(root->left, val);
    }
    else{
        root->right = Insert(root->right, val);
    }
    return root;
}

// TreeNode* Insert(TreeNode *root, int val)                       //非递归
// {
//     TreeNode *p = root, *q;
//     while(p){
//         if(p->val == val)return;
//         else if(p->val > val){
//             q = p;
//             p = p->left;
//         }
//         else{
//             q = p;
//             p = p->right;
//         }
//     }
//     p = (TreeNode*)malloc(sizeof(TreeNode));
//     p->val = val;
//     p->left = p->right = NULL;
//     if(!root)return p;
//     if(q->val > val)q->left = p;
//     else q->right = p;
//     return root;
// }

TreeNode* Creat(int n)
{
    TreeNode *root = NULL;
    int a;
    for(int i = 0; i < n; i++){
        scanf("%d", &a);
        root = Insert(root, a);
    }
    return root;
}

TreeNode* Search(TreeNode *root, int key)                       //递归
{
    if(!root)return NULL;
    else if(root->val == key)return root;
    else if(root->val > key)return Search(root->left, key);
    else return Search(root->right, key);
}

// TreeNode* Search(TreeNode *root, int key)                  //非递归
// {
//     TreeNode *p = root;
//     while(p){
//         if(p->val == key)return p;
//         else if(p->val > key)p = p->left;
//         else p = p->right;
//     }
// }

TreeNode* Delete(TreeNode *root, int val)
{
    TreeNode *p = root, *q;
    while(p){
        if(p->val == val)break;
        else if(p->val > val){
            q = p;
            p = p->left;
        }
        else{
            q = p;
            p = p->right;
        }
    }
    if(!p)return root;
    if(!p->left && !p->right){                           //p为叶子节点
        if(!q){                                          //p为根节点
            free(p);
            return NULL;
        }
        if(q->left == p)q->left = NULL;
        else q->right = NULL;
        free(p);
    }
    else if(p->left && !p->right){                       //左子树不为空
        if(!q){
            root = p->left;
            free(p);
            return root;
        }
        if(q->left == p)q->left = p->left;
        else q->right = p->left;
        free(p);
    }
    else if(!p->left && p->right){                       //右子树不为空
        if(!q){
            root = p->right;
            free(p);
            return root;
        }
        if(q->left == p)q->left = p->right;
        else q->right = p->right;
        free(p);
    }
    else{                                                //左右子树均不为空
        TreeNode *r = p->left;
        while(r->right){
            q = r;
            r = r->right;
        }
        p->val = r->val;
        q->right = r->left;
        free(r);
    }
    return root;
}

void InOrderTraverse(TreeNode *root)
{
    if(!root)return;
    InOrderTraverse(root->left);
    printf("%d ", root->val);
    InOrderTraverse(root->right);
}

int main()
{
    int n;
    scanf("%d", &n);
    TreeNode *root = Creat(n);
    InOrderTraverse(root);
    return 0;
}