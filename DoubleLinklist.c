#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define SWAP( a, b ) do{ int t = a; a = b; b = t; }while(0)
typedef char bool;
struct node
{
    int data;
    struct node *next;
    struct node *previous;
};
typedef struct node node;
struct double_linked
{
    int total_elements; 
    node *head;
    node *tail;
};
typedef struct double_linked double_linked;

double_linked *init_double_linked()
{   
	double_linked *list;
	list = (double_linked*)calloc(1,sizeof(double_linked));
	if(NULL == list)
	{
		return NULL;
	}
	list->tail = NULL;
	list->head = NULL;
	list->total_elements = 0;
	return list; 
	
}

node *cre_node(int data)
{
    node *new_node;
    new_node = (node*)calloc(1,sizeof(node));
    
    if (NULL == new_node)
    {
        return FALSE;
    }
    
    new_node->data = data;
    new_node->next = NULL;
    new_node->previous = NULL;
    return new_node;
}
node *insert_head(double_linked *list, int data)
{
    node *new_node;
    if (NULL == list )
    {
        return NULL;
    }
    
    new_node = cre_node(data);
    if(NULL == new_node)
    {
    	return NULL;
	}

    if (NULL == list->head)
    {
        list->head = new_node;
        list->tail = new_node;
        list->total_elements++;
    }
    else
    {
        new_node->next = list->head;
        (list->head)->previous = new_node;
        list->head = new_node;
        list->total_elements++;
    }
    return new_node;
}
node *insert_tail(double_linked *list, int data)
{
    node *new_node;
    if (NULL == list)
    {
        return NULL;
    }
    
    new_node = cre_node(data);
    if(NULL == new_node)
    {
    	return NULL;
	}
    if (NULL == list->tail)
    {
        list->head = new_node;
		list->tail = new_node;
		list->total_elements ++;
    }
    else
    {   
        (list->tail)->next = new_node;
        new_node->previous = list->tail;
        list->tail = new_node;
        list->total_elements ++;
    }
    return new_node;
}

node *insert_after_index(double_linked *list, int data, int index)
{
	node *new_node,*temp_node;
    if (NULL == list)
    {
        return NULL;
    }
	if(index < 0 || index > list->total_elements)
	{
		return NULL;
	}
    temp_node = list->head;
    while(index--)
    {
        temp_node = temp_node->next;
    }
    
    if(list->head == temp_node)
    {
        return insert_head(list,data);
    }
    else if (list->tail == temp_node)
    {
    	return insert_tail(list,data);
	}
    else
    {   
		new_node = cre_node(data);
		if(NULL == new_node)
		{
			return NULL;
		}
        new_node->next = temp_node->next;
        (temp_node->next)->previous = new_node ;
        temp_node->next = new_node;
        new_node->previous = temp_node;  
		list->total_elements ++;
		return new_node; 
    }
}

bool delete_first(double_linked *list)
{   
	node *temp_node;
    if (NULL == list )
    {
        return FALSE;
    }

    temp_node = list->head;
    if(NULL == temp_node)
    {
    	return FALSE;
	}
	
    if(temp_node->next == NULL)
    {
        list->head= NULL;
		list->tail = NULL;
        free(temp_node);
        list->total_elements --;
        return TRUE;
    }
    else
    {
        list->head = temp_node->next;
        (temp_node->next)->previous = NULL;
        free(temp_node);
        list->total_elements --;
        return TRUE;
    }
    
}
bool delete_last(double_linked *list)
{	
	node *temp_node;
    if (NULL == list )
    {
        return FALSE;
    }
    
    temp_node = list->tail;
    if(NULL == temp_node)
    {
    	return FALSE;
	}

    if(temp_node->previous == NULL)
    {
        list->head = NULL;
		list->tail = NULL;
        free(temp_node);
        list->total_elements --;
        return TRUE;
    }
    else
    {
        list->tail = temp_node->previous;
        temp_node->previous->next = NULL;
        free(temp_node);
        list->total_elements --;
        return TRUE;
    }
}

bool delete_node_index(double_linked *list, int index )
{   
	node *temp_node;
    if (NULL == list)
    {
        return FALSE;
    }
    if (index < 0 || index >= list->total_elements)
    {
    	return FALSE;
	}
    
    
    if (0 == index)
    {
        return delete_first(list);
    }
    if (list->total_elements-1 == index)
    {
        return delete_last(list);
    }
    
    temp_node  = list->head;
    while(index--)
    {   
        temp_node = temp_node->next; 
    }
    temp_node->previous->next = temp_node->next;
    temp_node->next->previous = temp_node->previous;
    free(temp_node);
    list->total_elements--;
    return TRUE;
}

bool delete_node_data(double_linked *list, int data )
{	
	node *data_node;
    if (NULL == list || NULL == list->head)
    {
        return FALSE;
    }

    data_node = list->head;
    while((data_node != NULL) && (data_node->data != data))
    {
        data_node=data_node->next;
    }
    if(NULL == data_node)
    {
    	return FALSE;
	}


    if(data_node->previous == NULL)
    {
		return delete_first(list);
        
    }
    else if (data_node->next == NULL)
    {
        return delete_last(list);
    }
    else
    {
        data_node->previous->next = data_node->next;
        data_node->next->previous = data_node->previous;
        free(data_node);
        list->total_elements--;
        return TRUE;
    }

}
//
//
bool show_list(double_linked *list)
{
    if (NULL == list)
    {
        return FALSE;
    }
    node *temp_node = list->head;
    while(NULL != temp_node)
    {
        printf("%d\t",temp_node->data);
        temp_node = temp_node->next;
    }
    printf("\n");
    return TRUE;
}
bool show_list_invert(double_linked *list)
{	
	node *temp_node;
    if (NULL == list)
    {
        return FALSE;
    }
	temp_node = list->tail;
    while(temp_node != NULL)
    {
        printf("%d\t",temp_node->data);
        temp_node = temp_node->previous;
    }
    printf("\n");
    return TRUE;
}
bool sort(double_linked *list)
{
    if(NULL == list)
    {
        return FALSE;
    }
    else
    {
        node *i,*j;
        for(i = list->head; i->next ; i = i->next)
            for(j = i ->next; j ; j = j->next)
                if(i->data > j->data)
                    SWAP(i->data,j->data);
    }
    return TRUE;
}

int main()
{     
	double_linked *list;
	list = init_double_linked();
	insert_head(list,19);
	insert_head(list,11);
	insert_head(list,30);
	insert_head(list,14);
	insert_head(list,21);
	insert_head(list,22);
	
	
    show_list(list);
    printf("%d\n",delete_node_data(list,14));
    sort(list);
    show_list(list);
    return 0;
}
