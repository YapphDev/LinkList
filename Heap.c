#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define SWAP( a, b ) do{ int t = a; a = b; b = t; }while(0)
typedef char bool;
struct Node
{
    struct Node *next;
    int data;
};
typedef struct Node Node;

struct Heap
{   
    Node *last;
    int index;
};
typedef struct Heap Heap;

void init(Heap *heap)
{
    if (NULL == heap)
    {
        printf("error\n");
    }
    else
    {
        heap->index = 0;
        heap->last = NULL;
    }
}

Node *CreNode(int data)
{
    Node *p;
    p = (Node *)malloc(sizeof(Node));
    if (NULL == p)
    {
        return NULL;
    }

    p->data = data;
    p->next = NULL;

    return p;
}
Node *Insert(Heap *heap, int data)
{   
    /*---------------------------------------------------------------------------
        Inserting new Node in last Heap
    ----------------------------------------------------------------------------*/
    Node *node;
    node = CreNode(data);
    if (NULL == heap || NULL == node)
    {
        return NULL;
    }

    if (0 == heap->index)
    {
        heap->last = node;
        heap->index = 1;
    }
    else
    {   
        node->next = heap->last;
        heap->last = node;
        heap->index++;
        
        /*-----------------------------------------------------------------------------------
            After Inserting new Node 
            Appling heap algorithm
        -------------------------------------------------------------------------------------*/
        Node *child,*parent=NULL;
        child = heap->last;
        int index, check, count;
        check = heap->index;
        for (int index = (heap->index)/2; index>0 ; index=index/2)
        {   
            int count;
            if(check%2 == 0)
            {
                count = index;
            }
            else
                count = index +1;
            check=index;
            Node *temp = child;
            while (count--)
            {
                parent = temp->next;
                temp=temp->next;
            }
            
            
            if (parent->data > child->data)
            {
                SWAP(parent->data,child->data);
            }
            child = parent;
        }
    }

    return node;
}

void Show_Heap(Node *node)
{   
    
   if (NULL != node)
    {   
        Node *p ;
        p = node;
    
        Show_Heap(p->next);
        printf("%d\t",p->data);
       
    }
}
int main()
{
    Heap heap;
    init(&heap);
    Insert(&heap,6);
    Insert(&heap,5);
    Insert(&heap,7);
    Insert(&heap,4);
    Insert(&heap,3);
    Insert(&heap,9);
    Insert(&heap,2);
    Insert(&heap,2);
    Show_Heap(heap.last);
    return 0;
}
