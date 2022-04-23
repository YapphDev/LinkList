#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
    if (NULL == l )
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

    if (NULL == l || addr < 0 || addr > l ->Number_Of_Elements)
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
        if(q == l->tail)
        {
            Insert_Last(l,n);
        }
        else
        {   
            NODE *p;
            p = CreNode(n);
            p->next = q->next;
            q->next->previous = p;
            q->next = p;
            p->previous = q;   
        }
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
        if(q->next == NULL)
        {
            l->head=l->tail=NULL;
            q->next = q->previous = NULL;
            free(q);
        }
        else
        {
            l->head = q->next;
            q->next->previous = NULL;
            q->next = NULL;
            free(q);
        }
    }
    l->Number_Of_Elements--;
    return true;
}
bool Delete_Last(doubleList *l)
{
    if (NULL == l )
    {
        return flase;
    }
    else
    {   
        NODE *q;
        q = l->tail;
        if(q->previous == NULL)
        {
            l->head=l->tail=NULL;
            q->next = q->previous = NULL;
            free(q);
        }
        else
        {
            l->tail = q->previous;
            q->previous->next = NULL;
            q->next = q->previous = NULL;
            free(q);
        }
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
        }
    }
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
bool Search_arr(int arr[],int data, int size)
{
    for (int i=0; i < size ; i++)
    {
        if (arr[i]=data)
        {  
            return true;
        }
    }
    return flase;
}
NODE *Search_Node(doubleList * list, int data)
{
    if (NULL == list)
    {
        return NULL;
	}
	
	NODE *data_node;
	data_node = list->head;
    while((data_node != NULL) && (data_node->data != data) )
    {
        data_node=data_node->next;
    }
    return data_node;
}
void Delete_Arr_Data(int arr[], int data, int size)
{   

    for(  int i = data; i < size-1; i++)
    {
        arr[i] = arr[i+1];
    }
}
int main()
{   
    clock_t start, end;
    
    doubleList h;
    init(&h);
    for (int i = 0; i <100000 ; i++)
    {
        Insert_First(&h,i);
    }
    start = clock();
    Delete_Node_Data(&h,2);
    end = clock();
    double time_linked = (double)(end - start) / CLOCKS_PER_SEC;
    printf ("time_linked: %f\n",time_linked);
    
    int arr[1000000];
    for (int i = 0; i <100000 ; i++)
    {
        arr[i]=i;
    }
    start = clock();
    Delete_Arr_Data(arr,1,sizeof(arr)/sizeof(arr[0]));
    end = clock();
    double time_arr = (double)(end - start) / CLOCKS_PER_SEC;
    printf ("time_arr: %f\n",time_arr);
    return 0;
}
