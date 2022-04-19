/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>

struct Node 
{
    int data;
    struct Node *left;
    struct Node *right;
}; typedef struct Node Node;

struct Tree
{
    int Total;
    Node *root;
}; typedef struct Tree Tree;

void init(Tree *Tr)
{   
    Tr->root = NULL;
    Tr->Total = 0;
}
Node *Cre_Node(int data)
{
    Node *p;
    p = (Node*)malloc(sizeof(Node));
    if(NULL == p)
    {
        return NULL;
    }
    else
    {
        p->left = NULL;
        p->right = NULL;
        p->data = data;
    }
    return p;
}

Node *Search_Node(Tree *Tr,int data)
{  
    if(NULL == Tr->root)
    {  
        return NULL;
    }
    else
    {
        /*
        Fine Node_Data
        */
        Node *Node_Data;
        Node_Data = Tr->root;
        while( NULL != Node_Data  && Node_Data->data != data)
        {   
            if (Node_Data->data > data)
            {
                Node_Data = Node_Data->left; 
            }
            else
            {
                Node_Data = Node_Data->right;
            }
        }
        return Node_Data;
    }
}

Node *Insert_Node(Tree *Tr,int data)
{  
    if(NULL == Tr->root)
    {  
        Node *p ;
        p = Cre_Node(data);
        if(NULL == p)
        {
            return NULL;
        }
        Tr->root = p;
        Tr->Total++;
        return p;
    }
    else
    {   
        /*
        Finding Farther of Node
        */
        Node *Farther,*Son_Of_Farther;
        Son_Of_Farther = Tr->root;
        Farther = NULL;
        
        while( NULL != Son_Of_Farther )
        {   

            Farther = Son_Of_Farther;
            if (Son_Of_Farther->data > data)
            {
                Son_Of_Farther = Son_Of_Farther->left; 
            }
            
            else 
            {
                Son_Of_Farther = Son_Of_Farther->right;
            }
        }
        
        /* 
            Inserting Node to Farther 
        */
        Node *p = Cre_Node(data);
        if( NULL == p)
        {
            return NULL;
        }
        if(Farther->data > data)
        {
            Farther->left = p;
        }
        else 
        {
            Farther->right = p;
        }
        Tr->Total++;
        return p;

    }
}

void lnr (Node *root)
{   

    if(NULL != root)
    {   
        Node *p;
        p = root;
        if( NULL != p )
        {
            lnr(p->left);
            printf ("%d\t", p->data);
            lnr(p->right);
        }
    }
}
void nlr (Node *root)
{
    if(NULL != root)
    {   
        Node *p;
        p = root;
        if( NULL != p )
        {   
            printf ("%d\t", p->data);
            nlr(p->left);
            nlr(p->right);
        }
    }
}

void Delete_Node(Tree *Tr, int data)
{   
    if(NULL != Tr)
    {
        Node *Node_Data,*preNode_Data;
        Node_Data = Tr->root;
        preNode_Data = NULL;
        /*
          Find Node 
        */
        while( NULL != Node_Data  && Node_Data->data != data)
        {   
            preNode_Data = Node_Data;
            if (Node_Data->data > data)
            {
                Node_Data = Node_Data->left; 
            }
            
            else 
            {
                Node_Data = Node_Data->right;
            }
        }
        
        
        /*
            Delete Node
        */
        if ( NULL != Node_Data)
        {   
            /*
            If Node is leaf
            */
            if (NULL == Node_Data->right && NULL == Node_Data->left)
            {
                if( preNode_Data->data > Node_Data->data)
                {
                    preNode_Data->left = NULL;
                }
                else
                {
                    preNode_Data->right = NULL;
                }
                free(Node_Data);
            }
            /*
            If Node is prarent have one leaf
            */
            else if (NULL == Node_Data->right)
            {
                if (preNode_Data->data > Node_Data->data)
                {
                    preNode_Data->left = Node_Data->left;
                }
                else
                    preNode_Data->right = Node_Data->left;
                free(Node_Data);
            }
            else if (NULL == Node_Data->left)
            {
                if (preNode_Data->data > Node_Data->data)
                {
                    preNode_Data->left = Node_Data->right;
                }
                else
                    preNode_Data->right = Node_Data->right;
                free(Node_Data);
            }
            
            /*
            If Node is prarent
            */
            else
            {
                Node *Replace_Node,*preReplace_Node;
                preReplace_Node = Node_Data;
                Replace_Node = Node_Data->left;
                while(Replace_Node->right != NULL )
                {   
                    preReplace_Node = Replace_Node;
                    Replace_Node = Replace_Node->right;
                }
                Node_Data->data = Replace_Node->data;
                
                /*
                If Replace_Node is leaf
                */
                if ( NULL == Replace_Node->left)
                {
                    preReplace_Node->right = NULL;
                    free(Replace_Node);
                }
                /*
                If Replace_Node is prarent have one leaf
                */
                else
                {
                    preReplace_Node->right = Replace_Node->left;
                    free(Replace_Node);
                }
            }    
            
        }
        
    }
}

int main()
{   
    Tree tree1;
    init(&tree1);
    Insert_Node(&tree1,50);
    Insert_Node(&tree1,30);
    Insert_Node(&tree1,75);
    Insert_Node(&tree1,20);
    Insert_Node(&tree1,45);
    Insert_Node(&tree1,10);
    Insert_Node(&tree1,65);
    Insert_Node(&tree1,60);
    Insert_Node(&tree1,30);
    Node *p=Search_Node(&tree1,1000);
    lnr(tree1.root);
    printf("\n");
    Delete_Node(&tree1,50);
    Delete_Node(&tree1,10);
    lnr(tree1.root);

    return 0;
}
