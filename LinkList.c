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
};
typedef struct Node NODE;

struct List
{
    int Number_Of_Elements;
    NODE *head;
    NODE *tail;
};
typedef struct List List;

void init(List *l)
{
    if (NULL == l)
    {
        printf("erro\n");
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
    }
    return p;
}
bool Insert_First(List *l, int n)
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
            l->head = p;
            l->tail = p;
            l->Number_Of_Elements = 1;
        }
        else
        {
            p->next = l->head;
            l->head = p;
            l->Number_Of_Elements++;
        }
    }
    return true;
}
bool Insert_Last(List *l, int n)
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
            l->head = p;
            l->tail = p;
            l->Number_Of_Elements = 1;
        }
        else
        {   
            (l->tail)->next = p;
            l->tail = p;
            l->Number_Of_Elements++;
        }
    }
    return true;
}

bool Insert_After_Addr(List *l, int n, int addr)
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
        q = (NODE*)l;
        while(addr--)
        {
            q = q->next;
        }
        
        p->next = q->next;
        q->next = p;
        l -> Number_Of_Elements ++;
        
    }
    return true;
}
bool Delete_First(List *l)
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
bool Delete_Node_Addr(List *l, int addr )
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

bool Delete_Node_Data(List *l, int data )
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


bool Show_List(List l)
{
    if (NULL == &l)
    {
        return flase;
    }
    else
    {
        while(l.Number_Of_Elements--)
        {
            printf("%d\t",(l.head)->data);
            l.head = (l.head)->next;
        }
       
    }
}
bool Sort(List *l)
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
    List h;
    init(&h);
    Insert_First(&h,2);
    Insert_First(&h,5);
    Insert_First(&h,12);
    Insert_First(&h,7);
    Insert_First(&h,26);
    Insert_Last(&h,17);
    Insert_Last(&h,20);
    Insert_After_Addr(&h,99,2);
    Show_List(h);
    printf("\n");
    Sort(&h);
    Show_List(h);
    printf("\n");
    Delete_Node_Addr(&h,0);
    Delete_Node_Addr(&h,2);
    Delete_Node_Data(&h,5);
    //Delete_First(&h);
    Show_List(h);



    return 0;
}
