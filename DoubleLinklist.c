#include <stdio.h>
#include <stdlib.h>
#define true 1
#define flase 0
#define Swap( a, b ) do{ int t = a; a = b; b = t; }while(0)
typedef char bool;
struct Node
{
    int data;
    struct Node *next;
    struct Node *previous;
};
typedef struct Node NODE;
struct doubleList
{
    int Number_Of_Elements; 
    NODE *head;
    NODE *tail;
};
typedef struct doubleList doubleList;

void init(doubleList *l)
{
    if (NULL == l)
    {
        printf("error\n");
    }
    else
    {
        l->Number_Of_Elements = 0;
        l->head = NULL;
        l->tail = NULL;
    }
}

NODE *CreNode(int n)
{
    NODE *p;
    p = (NODE *)malloc(sizeof(NODE));
    if (NULL == p)
    {
        return flase;
    }
    else
    {
        p->data = n;
        p->next = NULL;
        p->previous = NULL;
    }
    return p;
}
bool Insert_First(doubleList *l, int n)
{
    NODE *p;
    p = CreNode(n);
    if (NULL == l || NULL == p)
    {
        return flase;
    }
    else
    {
        if (0 == l->Number_Of_Elements)
        {
            l->head = l->tail = p;
        }
        else
        {
            p->next = l->head;
            (l->head)->previous = p;
            l->head = p;
        }
        l->Number_Of_Elements++;
    }
    return true;
}
bool Insert_Last(doubleList *l, int n)
{
    NODE *p;
    p = CreNode(n);
    if (NULL == l || NULL == p)
    {
        return flase;
    }
    else
    {
        if (0 == l->Number_Of_Elements)
        {
            l->head = l->tail = p;
        }
        else
        {   
            (l->tail)->next = p;
            p->previous = l->tail;
            l->tail = p;
            
        }
        l->Number_Of_Elements++;
    }
    return true;
}

bool Insert_After_Addr(doubleList *l, int n, int addr)
{
    NODE *p;
    p = CreNode(n);
    if (NULL == l || NULL == p || addr < 0 || addr > l ->Number_Of_Elements)
    {
        return flase;
    }
    else
    {   
        NODE *q;
        q = l->head;
        while(addr--)
        {
            q = q->next;
        }
        p->next = q->next;
        q->next->previous = p;
        q->next = p;
        p->previous = q;
        l -> Number_Of_Elements ++;
        
    }
    return true;
}
bool Delete_First(doubleList *l)
{
    if (NULL == l )
    {
        return flase;
    }
    else
    {   
        
        NODE *q;
        q = l->head;
        l->head = q->next;
        free(q);
    }
    l->Number_Of_Elements--;
    return true;
}
bool Delete_Node_Addr(doubleList *l, int addr )
{
    if (NULL == l || addr < 0 || addr > l ->Number_Of_Elements)
    {
        return flase;
    }
    else if (0 == addr)
    {
        NODE *q;
        q = l->head;
        l->head = q->next;
        free(q);
    }
    else
    {   
        
        NODE *q , *preq = NULL;
        q = l->head;
        while(addr--)
        {   
            preq = q;
            q = q->next; 
        }
            preq->next = q->next;
            q->next = NULL;
            free(q);
    }
    l->Number_Of_Elements--;
    return true;
}

bool Delete_Node_Data(doubleList *l, int data )
{
    if (NULL == l )
    {
        return flase;
    }
    else
    {   
        
        NODE *q , *preq = NULL;
        q = (NODE*)l;
        while(q->data!=data)
        {   
            preq = q;
            q = q->next; 
        }
        if (NULL != q)
        {
            if(NULL == preq)
        {
            Delete_First(l);
        }
        else
        {
            preq->next = q->next;
            q->next = NULL;
            free(q);
        }
        }
    }
    l->Number_Of_Elements--;
    return true;
}


bool Show_List(doubleList *l)
{
    if (NULL == &l)
    {
        return flase;
    }
    else
    {   NODE *p = l->head;
        while(p != NULL)
        {
            printf("%d\t",p->data);
            p = p->next;
        }
       
    }
    return true;
}
bool Show_List_Invert(doubleList *l)
{
    if (NULL == &l)
    {
        return flase;
    }
    else
    {   NODE *p = l->tail;
        while(p != NULL)
        {
            printf("%d\t",p->data);
            p = p->previous;
        }
       
    }
    return true;
}
bool Sort(doubleList *l)
{
    if(NULL == l)
    {
        return flase;
    }
    else
    {
        NODE *p,*q;
        for(p = l->head; p->next ; p = p->next)
            for(q = p ->next; q ; q = q->next)
                if(p->data > q->data)
                    Swap(p->data,q->data);
    }
    return true;
}

int main()
{
    doubleList h;
    init(&h);
    Insert_First(&h,2);
    Insert_First(&h,5);
    Insert_First(&h,12);
    Insert_First(&h,7);
    Insert_First(&h,26);
    Insert_Last(&h,17);
    Insert_Last(&h,20);
    Insert_After_Addr(&h,99,2);
    Show_List(&h);
    printf("\n");
    Sort(&h);
    Show_List(&h);
    printf("\n");
    Show_List_Invert(&h);
    printf("\n");
    // Delete_Node_Addr(&h,0);
    // Delete_Node_Addr(&h,1);
    // Delete_Node_Data(&h,20);
    //Delete_First(&h);
    // Show_List(&h);



    return 0;
}