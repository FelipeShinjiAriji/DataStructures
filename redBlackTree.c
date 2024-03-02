#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node *left;
    struct node *right;
    struct node *parent;
    char color;
}node;

typedef struct tree {
    node *root;
    node *nil;
}tree;

void leftRotation(tree *T, node *x){
    node *y = x->right;
    x->right = y->left;
    if(y->left != T->nil){
        y->left->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == T->nil){
        T->root = y;
    }else if(x == x->parent->left){
        x->parent->left = y;
    }else{
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void rightRotation(tree *T, node *x){
    node *y = x->left;
    x->left = y->right;
    if(y->right != T->nil){
        y->right->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == T->nil){
        T->root = y;
    }else if(x == x->parent->right){
        x->parent->right = y;
    }else{
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void insertFixup(tree *T, node *z){
    while(z->parent->color == 'R'){
        if(z->parent == z->parent->parent->left){
            node *y = z->parent->parent->right;
            if(y->color == 'R'){
                printf("Case 1 insert:\n");
                printf("    Recoloring parent to black\n");
                z->parent->color = 'B';
                printf("    Recoloring uncle to black\n");
                y->color = 'B';
                printf("    Recoloring grandparent to red\n\n");
                z->parent->parent->color = 'R';
                printf("    Node points to grandparent\n");
                z = z->parent->parent;
            }else{
                if(z == z->parent->right){
                    printf("Case 2 insert:\n");
                    printf("    Left rotation parent\n\n");
                    z = z->parent;
                    leftRotation(T,z);
                }
                printf("Case 3 insert:\n");
                printf("    Recoloring parent to black\n");
                z->parent->color = 'B';
                printf("    Recoloring grandparent to red\n");
                z->parent->parent->color = 'R';
                printf("    Right rotation grandparent\n\n");
                rightRotation(T,z->parent->parent);
            }
        }else{
            node *y = z->parent->parent->left;
            if(y->color == 'R'){
                printf("Case 1 insert:\n");
                printf("    Recoloring parent to black\n");
                z->parent->color = 'B';
                printf("    Recoloring uncle to black\n");
                y->color = 'B';
                printf("    Recoloring grandparent to red\n\n");
                z->parent->parent->color = 'R';
                printf("    Node points to grandparent\n");
                z = z->parent->parent;
            }else{
                if(z == z->parent->left){
                    printf("Case 2 insert\n");
                    printf("    Right rotation parent\n\n");
                    z = z->parent;
                    rightRotation(T,z);
                }
                printf("Case 3 insert:\n");
                printf("    Recoloring parent to black\n");
                z->parent->color = 'B';
                printf("    Recoloring grandparent to red\n");
                z->parent->parent->color = 'R';
                printf("    Left rotation grandparent\n\n");
                leftRotation(T,z->parent->parent);
            }
        }
    }
    printf("Correct root color to black\n\n");
    T->root->color = 'B';
}

void insert(tree *T, node *z){
    node *y = T->nil;
    node *x = T->root;
    while(x != T->nil){
        y = x;
        if(z->key < x->key){
            x = x->left;
        }else{
            x = x->right;
        }
    }
    z->parent = y;
    if(y == T->nil){
        T->root = z;
    }else if(z->key < y->key){
        y->left = z;
    }else{
        y->right = z;
    }
    z->left = T->nil;
    z->right = T->nil;
    z->color = 'R';
    insertFixup(T,z);
}

void transplant(tree *T, node *u, node *v){
    if(u->parent == T->nil){
        T->root = v;
    }else if(u == u->parent->left){
        u->parent->left = v;
    }else{
        u->parent->right = v;
    }
    v->parent = u->parent;
}

node *treeMinimum(tree *T, node *x){
    while(x->left != T->nil){
        x = x->left;
    }
    return x;
}

void deleteFixup(tree *T, node *x){
    while(x != T->root && x->color == 'B'){
        if(x == x->parent->left){
            node *w = x->parent->right;
            if(w->color == 'R'){
                printf("    Case 3.1 delete:\n");
                printf("        Recoloring sibling to black\n");
                w->color = 'B';
                printf("        Recoloring parent to red\n");
                x->parent->color = 'R';
                printf("        Left rotation parent\n");
                leftRotation(T,x->parent);
                printf("        New sibling\n\n");
                w = x->parent->right;
            }
            if(w->left->color == 'B' && w->right->color == 'B'){
                printf("    Case 3.2 delete:\n");
                printf("        Recoloring sibling to red\n\n");
                w->color = 'R';
                printf("        Node points to parent\n\n");
                x = x->parent;
            }else if(w->right->color == 'B'){
                printf("    Case 3.3 delete:\n");
                printf("        Recoloring sibling to black\n");
                w->left->color = 'B';
                printf("        Recoloring sibling to red\n");
                w->color = 'R';
                printf("        Right rotation sibling\n");
                rightRotation(T,w);
                printf("        New sibling\n\n");
                w = x->parent->right;
            }
            printf("    Case 3.4 delete:\n");
            printf("        Recoloring sibling to parent color\n");
            w->color = x->parent->color;
            printf("        Recoloring parent to black\n");
            x->parent->color = 'B';
            printf("        Recoloring sibling right to black\n");
            w->right->color = 'B';
            printf("        Left rotation parent\n\n");
            leftRotation(T,x->parent);
            printf("        Nodes points to root to recolor it to black\n\n");
            x = T->root;
        }else{
            node *w = x->parent->left;
            if(w->color == 'R'){
                printf("    Case 3.1 delete:\n");
                printf("        Recoloring sibling to black\n");
                w->color = 'B';
                printf("        Recoloring parent to red\n");
                x->parent->color = 'R';
                printf("        Right rotation parent\n");
                rightRotation(T,x->parent);
                printf("        New sibling\n\n");
                w = x->parent->left;
            }
            if(w->right->color == 'B' && w->left->color == 'B'){
                printf("    Case 3.2 delete:\n");
                printf("        Recoloring sibling to red\n\n");
                w->color = 'R';
                printf("        Node points to parent\n\n");
                x = x->parent;
            }else if(w->left->color == 'B'){
                printf("    Case 3.3 delete:\n");
                printf("        Recoloring sibling to black\n");
                w->right->color = 'B';
                printf("        Recoloring sibling to red\n");
                w->color = 'R';
                printf("        Left rotation sibling\n");
                leftRotation(T,w);
                printf("        New sibling\n\n");
                w = x->parent->left;
            }
            printf("    Case 3.4 delete:\n");
            w->color = x->parent->color;
            printf("        Recoloring parent to black\n");
            x->parent->color = 'B';
            printf("        Recoloring sibling left to black\n");
            w->left->color = 'B';
            printf("        Right rotation parent\n");
            rightRotation(T,x->parent);
            printf("        Nodes points to root to recolor it to black\n\n");
            x = T->root;
        }
    }
    x->color = 'B';
}

void delete(tree *T, node *z){
    printf("Case 1/2 Delete:\n");
    printf("    Deleting a red node or starting to delete a black node\n\n");
    node *y = z;
    char yOriginalColor = y->color;
    node *x;
    if(z->left == T->nil){
        x = z->right;
        transplant(T,z,z->right);
    }else if(z->right == T->nil){
        x = z->left;
        transplant(T,z,z->left);
    }else{
        y = treeMinimum(T,z->right);
        yOriginalColor = y->color;
        x = y->right;
        if(y->parent == z){
            x->parent = y;
        }else{
            transplant(T,y,y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(T,z,y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    if(yOriginalColor == 'B'){
        printf("Case 3 Delete:\n");
        deleteFixup(T,x);
    }
}

void printTree(tree *T, node *x){
    if(x != T->nil){
        printTree(T,x->left);
        printf("%d: %c\n",x->key, x->color);
        printTree(T,x->right);
    }
}

int getTreeHeight(tree *T, node *x){
    if(x == T->nil){
        return 0;
    }else{
        int leftHeight = getTreeHeight(T,x->left);
        int rightHeight = getTreeHeight(T,x->right);
        if(leftHeight > rightHeight){
            return leftHeight + 1;
        }else{
            return rightHeight + 1;
        }
    }
}

int getBlackHeight(tree *T, node *x){
    if(x == T->nil){
        return 1;
    }
    else{
        int leftHeight = getBlackHeight(T,x->left);
        int rightHeight = getBlackHeight(T,x->right);
        if(x->color == 'B'){
            return leftHeight + 1;
        }else{
            return leftHeight;
        }
    }
}

int countTotalNodes(tree *T, node *x){
    if(x == T->nil){
        return 0;
    }else{
        return countTotalNodes(T,x->left) + countTotalNodes(T,x->right) + 1;
    }
}

int countTotalRedNodes(tree *T, node *x){
    if(x == T->nil){
        return 0;
    }else{
        if(x->color == 'R'){
            return countTotalRedNodes(T,x->left) + countTotalRedNodes(T,x->right) + 1;
        }else{
            return countTotalRedNodes(T,x->left) + countTotalRedNodes(T,x->right);
        }
    }
}

int countTotalBlackNodes(tree *T, node *x){
    if(x == T->nil){
        return 0;
    }else{
        if(x->color == 'B'){
            return countTotalBlackNodes(T,x->left) + countTotalBlackNodes(T,x->right) + 1;
        }else{
            return countTotalBlackNodes(T,x->left) + countTotalBlackNodes(T,x->right);
        }
    }
}

float getBlackPercentual(tree *T, node *x){
    return (countTotalBlackNodes(T,x) * 100)/countTotalNodes(T,x);
}

float getRedPercentual(tree *T, node *x){
    return 100-getBlackPercentual(T,x);
}

int searchElement(tree *T, node *x, int key){
    if(x == T->nil){
        return 0;
    }else if(x->key == key){
        return 1;
    }else if(key < x->key){
        return searchElement(T,x->left,key);
    }else{
        return searchElement(T,x->right,key);
    }
}

void isElementInTree(tree *T, node *x, int key){
    if(searchElement(T,x,key)){
        printf("O valor %d existe na árvore\n",key);
    }else{
        printf("O valor %d não existe na árvore\n",key);
    }
}

void deleteElement(tree *T, node *x, int key){
    if(x == T->nil){
        return;
    }else if(x->key == key){
        delete(T,x);
    }else if(key < x->key){
        deleteElement(T,x->left,key);
    }else{
        deleteElement(T,x->right,key);
    }
}

float calculateAverageCost(tree *T, node *x, int level){
    if(x == T->nil){
        return 0;
    }else{
        return (level + calculateAverageCost(T,x->left,level+1) + calculateAverageCost(T,x->right,level+1));
    }
}

float getAverageCost(tree *T, node *x){
    return calculateAverageCost(T,x,0)/countTotalNodes(T,x);
}

int main(){
    tree *T = (tree*)malloc(sizeof(tree));
    T->nil = (node*)malloc(sizeof(node));
    T->nil->color = 'B';
    T->root = T->nil;
    node *z = (node*)malloc(sizeof(node));
    z->key = 1;
    insert(T,z);
    z = (node*)malloc(sizeof(node));
    z->key = 2;
    insert(T,z);
    z = (node*)malloc(sizeof(node));
    z->key = 3;
    insert(T,z);
    z = (node*)malloc(sizeof(node));
    z->key = 4;
    insert(T,z);
    z = (node*)malloc(sizeof(node));
    z->key = 5;
    insert(T,z);
    z = (node*)malloc(sizeof(node));
    z->key = 6;
    insert(T,z);
    z = (node*)malloc(sizeof(node));
    z->key = 7;
    insert(T,z);
    z = (node*)malloc(sizeof(node));
    z->key = 8;
    insert(T,z);
    z = (node*)malloc(sizeof(node));
    z->key = 9;
    insert(T,z);
    z = (node*)malloc(sizeof(node));
    z->key = 10;
    insert(T,z);
    z = (node*)malloc(sizeof(node));
    z->key = 11;
    insert(T,z);
    z = (node*)malloc(sizeof(node));
    z->key = 12;
    insert(T,z);
    z = (node*)malloc(sizeof(node));
    z->key = 13;
    insert(T,z);
    z = (node*)malloc(sizeof(node));
    z->key = 14;
    insert(T,z);
    z = (node*)malloc(sizeof(node));
    z->key = 15;
    insert(T,z);
    z = (node*)malloc(sizeof(node));
    z->key = 16;
    insert(T,z);
    z = (node*)malloc(sizeof(node));
    z->key = 17;
    insert(T,z);
    z = (node*)malloc(sizeof(node));
    z->key = 18;
    insert(T,z);
    z = (node*)malloc(sizeof(node));
    z->key = 19;
    insert(T,z);
    z = (node*)malloc(sizeof(node));
    z->key = 20;
    insert(T,z);
    z = (node*)malloc(sizeof(node));
    z->key = 21;
    insert(T,z);

    printTree(T,T->root);
    printf("Altura da árvore: %d\n",getTreeHeight(T,T->root));
    printf("Altura preta da árvore: %d\n",getBlackHeight(T,T->root));
    printf("Total de nós da árvore: %d\n",countTotalNodes(T,T->root));
    printf("Total de nós vermelhos da árvore: %d\n",countTotalRedNodes(T,T->root));
    printf("Total de nós pretos da árvore: %d\n",countTotalBlackNodes(T,T->root));
    printf("Pecentual de nós pretos na árvore: %.2f\n",getBlackPercentual(T,T->root));
    printf("Percentual de nós vermelhos na árvore: %.2f\n",getRedPercentual(T,T->root));
    printf("Custo médio de busca: %.2f\n",getAverageCost(T,T->root));
    
    isElementInTree(T,T->root,21);
    delete(T,T->root->right);
    isElementInTree(T,T->root,21);
    deleteElement(T,T->root,21);
    isElementInTree(T,T->root,21);

    printTree(T,T->root);
    printf("Altura da árvore: %d\n",getTreeHeight(T,T->root));
    printf("Altura preta da árvore: %d\n",getBlackHeight(T,T->root));
    printf("Total de nós da árvore: %d\n",countTotalNodes(T,T->root));
    printf("Total de nós vermelhos da árvore: %d\n",countTotalRedNodes(T,T->root));
    printf("Total de nós pretos da árvore: %d\n",countTotalBlackNodes(T,T->root));
    printf("Pecentual de nós pretos na árvore: %.2f\n",getBlackPercentual(T,T->root));
    printf("Percentual de nós vermelhos na árvore: %.2f\n",getRedPercentual(T,T->root));
    printf("Custo médio de busca: %.2f\n",getAverageCost(T,T->root));
    return 0;
}
