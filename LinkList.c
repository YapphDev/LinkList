#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TRUE 1
#define FALSE 0
#define SWAP( a, b ) do{ int t = a; a = b; b = t; } while(0)
typedef char bool;
struct node 
{       
    int data;
    struct node *left;
    struct node *right;
}; typedef struct node node;

struct binary_tree
{
    int total_node;
    node *root;
}; typedef struct binary_tree binary_tree;

binary_tree *init_binary_tree()
{   
    binary_tree *tree;
    tree = (binary_tree*)calloc(1,sizeof(binary_tree));
    if(NULL == tree)
    {
        return NULL;
    }
    tree->root = NULL;
    tree->total_node = 0;
    return tree;
}
node *cre_node(int data)
{
    node *new_node;
    new_node = (node*)calloc(1,sizeof(node));
    if(NULL == new_node)
    {
        return NULL;
    }

    new_node->left = NULL;
    new_node->right = NULL;
    new_node->data = data;
    
    return new_node;
}

node *search_node(binary_tree *tree,int data)
{  
    node *data_node;
    if(NULL == tree || NULL == tree->root )
    {  
        return NULL;
    }

    /*
    Finding data_node->data == data
    */
    
    data_node = tree->root;
    while( NULL != data_node  && data_node->data != data)
    {   
        if (data_node->data > data)
        {
            data_node = data_node->left; 
        }
        else
        {
            data_node = data_node->right;
        }
    }
    return data_node;

}

node *insert_node(binary_tree *tree,int data)
{  
    node *new_node;
    if(NULL == tree)
    {
        return NULL;
    }
    
    new_node = cre_node(data);
    if (NULL == new_node)
    {
        return NULL;
    }
    
    if(NULL == tree->root)
    {  
        tree->root = new_node;
    }
    else
    {   
        /*
         Finding parent  node
         */
        node *parent,*child;
        child = tree->root;
        parent = NULL;
        
        while( NULL != child )
        {   

            parent = child;
            if (child->data > data)
            {
                child = child->left; 
            }
            
            else 
            {
                child = child->right;
            }
        }
        
        /* 
         Inserting node to parent 
         */
        if(parent->data > data)
        {
            parent->left = new_node;
        }
        else 
        {
            parent->right = new_node;
        }
    }
    tree->total_node++;
    return new_node;
}

bool lnr (node *root)
{   
    node *temp_node;
    if(NULL == root)
    {
        return FALSE;
    }
        
    temp_node = root;
    if( NULL != temp_node )
    {
        lnr(temp_node->left);
        printf ("%d\t", temp_node->data);
        lnr(temp_node->right);
    }
    return TRUE;
}
bool nlr (node *root)
{
    node *temp_node;
    if(NULL == root)
    {
        return FALSE;
    }
    temp_node = root;
    if( NULL != temp_node )
    {   
        printf ("%d\t", temp_node->data);
        nlr(temp_node->left);
        nlr(temp_node->right);
    }
    return TRUE;
}


bool delete_node(binary_tree *tree, int data)
{   
    node *data_node,*parent_data_node;
    if(NULL == tree || NULL == tree->root)
    {
        return FALSE;
    }

    data_node = tree->root;
    parent_data_node = NULL;
    /*
      Find data_node 
    */
    while( NULL != data_node  && data_node->data != data)
    {   
        parent_data_node = data_node;
        if (data_node->data > data)
        {
            data_node = data_node->left; 
        }
        
        else 
        {
            data_node = data_node->right;
        }
    }
    
    /*
        Delete Node
    */
    if (NULL == data_node)
    {
        return FALSE;
    }
    
    
    /*---------------------------------------------------------------------
    If Node is leaf
    */
    if (NULL == data_node->right && NULL == data_node->left)
    {
        if( parent_data_node->data > data_node->data)
        {
            parent_data_node->left = NULL;
        }
        else
        {
            parent_data_node->right = NULL;
        }
        free(data_node);
    }
    /*-------------------------------------------------------
    If Node is parent has one leaf
    */
    else if (NULL == data_node->right)
    {
        if (parent_data_node->data > data_node->data)
        {
            parent_data_node->left = data_node->left;
        }
        else
            parent_data_node->right = data_node->left;
        free(data_node);
    }
    else if (NULL == data_node->left)
    {
        if (parent_data_node->data > data_node->data)
        {
            parent_data_node->left = data_node->right;
        }
        else
            parent_data_node->right = data_node->right;
        free(data_node);
    }
    
    /*--------------------------------------------------------------
    If Node is parent
    */
    else
    {   
        /* 
        Finding  Replace_Node
        */
        node *replace_node,*parent_replace_node;
        parent_replace_node = data_node;
        replace_node = data_node->left;
        while(replace_node->right != NULL )
        {   
            parent_replace_node = replace_node;
            replace_node = replace_node->right;
        }
        data_node->data = replace_node->data;
        
        /*
        If Replace_Node is leaf
        */
        if ( NULL == replace_node->left)
        {
            parent_replace_node->right = NULL;
            free(replace_node);
        }
        /*
        If Replace_Node is parent have one leaf
        */
        else
        {
            parent_replace_node->right = replace_node->left;
            free(replace_node);
        }
    }    
    tree->total_node--;
    return TRUE;
}

int main()
{   
    binary_tree *tree;
    tree = init_binary_tree();
    insert_node(tree,50);
    insert_node(tree,75);
    insert_node(tree,65);
    insert_node(tree,90);
    insert_node(tree,20);
    lnr(tree->root);
     printf("\n");
    delete_node(tree,65);
    lnr(tree->root);
    printf("\n");
    return 0;
}
