#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
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
        return NULL;
    }
    else
    {
        p->data = n;
        p->next = NULL;
        p->previous = NULL;
    }
    return p;
}
NODE *Insert_First(doubleList *l, int n)
{

    if (NULL == l )
    {
        return NULL;
    }
    else
    {   
        NODE *p;
        p = CreNode(n);
        if (NULL == p)
        {
            return NULL;
        }
        else
        {
            if (0 == l->Number_Of_Elements)
            {
                l->head = p;
                l->tail = p;
            }
            else
            {
                p->next = l->head;
                (l->head)->previous = p;
                l->head = p;
            }
            l->Number_Of_Elements++;
        }
        return p;
    }
    
}
NODE *Insert_Last(doubleList *l, int n)
{

    if (NULL == l)
    {
        return NULL;
    }
    else
    {  
        NODE *p;
        p = CreNode(n);
        if(NULL == p)
        {
            return NULL;
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
            return p;
        }
        
    }
    
}

NODE *Insert_After_Addr(doubleList *l, int n, int addr)
{

    if (NULL == l || addr < 0 || addr > l ->Number_Of_Elements)
    {
        return NULL;
    }
    else
    {   
        NODE *NODE_Addr;
        NODE_Addr = l->head;
        while(addr--)
        {
            NODE_Addr = NODE_Addr->next;
        }
        
        if(NODE_Addr == l->tail)
        {
            Insert_Last(l,n);
        }
        else
        {   
            NODE *p;
            p = CreNode(n);
            if (NULL == p)
            {
                return NULL;
            }
            else
            {
                p->next = NODE_Addr->next;
                NODE_Addr->next->previous = p;
                NODE_Addr->next = p;
                p->previous = NODE_Addr;  
            }
            l -> Number_Of_Elements ++;
            return p;
        }
        
    }
   
}
bool Delete_First(doubleList *l)
{
    if (NULL == l )
    {
        return FALSE;
    }
    else
    {   
        NODE *NODE_First;
        NODE_First = l->head;
        if(NODE_First->next == NULL)
        {
            l->head=l->tail = NULL;
            NODE_First->next = NULL;
            NODE_First->previous = NULL;
            free(NODE_First);
        }
        else
        {
            l->head = NODE_First->next;
            NODE_First->next->previous = NULL;
            NODE_First->next = NULL;
            free(NODE_First);
        }
        l->Number_Of_Elements--;
    }
    return TRUE;
}
bool Delete_Last(doubleList *l)
{
    if (NULL == l )
    {
        return FALSE;
    }
    else
    {   
        NODE *NODE_Last;
        NODE_Last = l->tail;
        if(NODE_Last->previous == NULL)
        {
            l->head=l->tail=NULL;
            NODE_Last->next = NODE_Last->previous = NULL;
            free(NODE_Last);
        }
        else
        {
            l->tail = NODE_Last->previous;
            NODE_Last->previous->next = NULL;
            NODE_Last->next = NODE_Last->previous = NULL;
            free(NODE_Last);
        }
        l->Number_Of_Elements--;
        return TRUE;
    }

}

bool Delete_Node_Addr(doubleList *l, int addr )
{
    if (NULL == l || addr < 0 || addr > l ->Number_Of_Elements)
    {
        return FALSE;
    }
    else if (0 == addr)
    {
        Delete_First(l);
    }
    else if (l->Number_Of_Elements == addr-1)
    {
        Delete_Last(l);
    }
    else
    {   
        
        NODE *q;
        q = l->head;
        while(addr--)
        {   
            q = q->next; 
        }
            q->previous->next = q->next;
            q->next->previous = q->previous;
            q->next = q->previous = NULL;
            free(q);
            l->Number_Of_Elements--;
            return TRUE;
    }

}

bool Delete_Node_Data(doubleList *l, int data )
{
    if (NULL == l )
    {
        return FALSE;
    }
    else
    {   
        NODE *q;
        q = l->head;
        while((q != NULL) && (q->data != data) )
        {
            q=q->next;
        }
        if (q != NULL)
        {   
            NODE *p;
            p = q;
            Delete_Node_Data((doubleList*)q,data);
            if(q->previous == NULL)
            {
                l->head = q->next;
                q->next->previous = NULL;
                q->next = NULL;
                free(q);
            }
            else if (q->next == NULL)
            {
                l->tail = q->previous;
                q->previous->next = NULL;
                q->next = q->previous = NULL;
                free(q);
            }
            else
            {
                q->previous->next = q->next;
                q->next->previous = q->previous;
                q->next = q->previous = NULL;
                free(q);
            }
            l->Number_Of_Elements--;
            return TRUE;
        }
    }
 
}


bool Show_List(doubleList *l)
{
    if (NULL == l)
    {
        return FALSE;
    }
    else
    {   NODE *p = l->head;
        while(p != NULL)
        {
            printf("%d\t",p->data);
            p = p->next;
        }
        return TRUE;
    }
    
}
bool Show_List_Invert(doubleList *l)
{
    if (NULL == l)
    {
        return FALSE;
    }
    else
    {   NODE *p = l->tail;
        while(p != NULL)
        {
            printf("%d\t",p->data);
            p = p->previous;
        }
       return TRUE;
    }
    
}
bool Sort(doubleList *l)
{
    if(NULL == l)
    {
        return FALSE;
    }
    else
    {
        NODE *p,*q;
        for(p = l->head; p->next ; p = p->next)
            for(q = p ->next; q ; q = q->next)
                if(p->data > q->data)
                    Swap(p->data,q->data);
    }
    return TRUE;
}

int main()
{
    doubleList h;
    init(&h);
    Insert_First(&h,2);
    Insert_First(&h,20);
    Insert_First(&h,5);
    Insert_First(&h,99);
    Insert_First(&h,12);
    Insert_First(&h,20);
    
    //Insert_First(&h,7);
    Insert_First(&h,26);
    Insert_Last(&h,17);
    Insert_Last(&h,20);
    Insert_Last(&h,7);
    Insert_After_Addr(&h,99,2);
    Show_List(&h);
    //printf("\n");
    // Sort(&h);
    // Show_List(&h);
    //printf("\n");
    //Show_List_Invert(&h);
    printf("\n");
    //Delete_Node_Addr(&h,0);
    //Delete_Node_Addr(&h,1);
    Delete_Node_Data(&h,99);
    // Delete_First(&h);
    // Delete_First(&h);
    // Delete_Last(&h);
    // Delete_Last(&h);
    //printf("%p",&h);
    Show_List(&h);



    return 0;
}
