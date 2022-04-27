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
};
typedef struct node node;

struct single_linked
{
    int total_elements;
    node *head;
};
typedef struct single_linked single_linked;

single_linked *init_single_linked()
{   
    single_linked *list;
    list = (single_linked*)calloc(1,sizeof(single_linked));
    if(NULL == list)
    {
        return NULL;
    }
    list->head = NULL;
    list->total_elements = 0;
    return NULL;
}

node *cre_node(int data)
{
    node *new_node;
    new_node = (node*)calloc(1,sizeof(node));
    if (NULL == new_node)
    {
        return NULL;
    } 
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}
node *insert_tail(single_linked *list, int data)
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
    if (0 == list->total_elements)
    {
        list->head = new_node;
        list->total_elements = 1;
    }
    else
    {
    	node *temp_node;
    	temp_node = list->head;
    	while(NULL != temp_node->next)
    	{
    		temp_node = temp_node->next;
		}
		temp_node->next = new_node;
		list->total_elements++;
    }
    return new_node;
}
node *insert_head(single_linked *list, int data)
{
    node *node;
    if (NULL == list)
    {
        return NULL;
    }
    node = cre_node(data);
    if(NULL == node)
    {
    	return NULL;
	}
    if (0 == list->total_elements)
    {
        list->head = node;
        list->total_elements = 1;
    }
    else
    {   
    	node->next = list->head;
        list->head = node;
        list->total_elements++;
    }
    return node;
}
node *insert_after_index(single_linked *list, int data, int index)
{
    node *new_node;
    if (NULL == list)
    {
        return NULL;
    }
    if(index < 0 || index > list ->total_elements)
    {
    	return NULL;
	}
    new_node = cre_node(data);
    if(NULL == new_node )
    {
    	return NULL;
	} 
    node *temp_node;
    temp_node = list->head;
    while(index--)
    {
        temp_node = temp_node->next;
    }
    new_node->next = temp_node->next;
    temp_node->next = new_node;
    list->total_elements++;
    return new_node;
}
bool delete_first(single_linked *list)
{
    if (NULL == list )
    {
        return FALSE;
    }
    node *temp_node;
    temp_node = list->head;
    list->head = temp_node->next;
    free(temp_node);
    list->total_elements--;
    return TRUE;
}
bool delete_node_index(single_linked *list, int index )
{
    if (NULL == list)
    {
        return FALSE;
    }
    if(index < 0 || index > list->total_elements)
    {
    	return FALSE;
	}
    if (0 == index)
    {
    	delete_first(list);
    }
    else
    {   
        node *temp_node , *pretemp_node;
        temp_node = list->head;
        pretemp_node = NULL;
        while(index--)
        {   
            pretemp_node = temp_node;
            temp_node = temp_node->next; 
        }
        pretemp_node->next = temp_node->next;
        free(temp_node);
        list->total_elements--;
    }
    return TRUE;
}

bool delete_node_data(single_linked *list, int data )
{
    if (NULL == list )
    {
        return FALSE;
    }
    
    node *temp_node , *pretemp_node; 
	temp_node = list->head;
	pretemp_node = NULL;
    while(temp_node->data != data && NULL != temp_node)
    {   
        pretemp_node = temp_node;
        temp_node = temp_node->next; 
    }
 
    if(NULL == temp_node)
	{
		return FALSE;
    }
    
    if (NULL != temp_node)
    {
        if(NULL == pretemp_node)
	    {
	        delete_first(list);
	    }
	    else
	    {
	        pretemp_node->next = temp_node->next;
	        free(temp_node);
	        list->total_elements--;
	    }
	}
    return TRUE;
}
bool show_list(single_linked *list)
{	
	node *temp_node;
    if (NULL == list)
    {
        return FALSE;
    }
    temp_node = list->head;
    while(NULL != temp_node)
    {
        printf("%d\t",temp_node->data);
        temp_node = temp_node->next;
    }
    printf("\n");
    return TRUE;
}
bool sort(single_linked *list)
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
	single_linked *list;
	list = init_single_linked();
    insert_head(&list,2);
    insert_head(&list,3);
    insert_head(&list,4);
    insert_head(&list,5);
    insert_head(&list,6);
    insert_tail(&list,7);
    insert_tail(&list,20);
    insert_after_index(&list,99,2);
    show_list(&list);
	delete_node_data(&list,4);
	sort(&list);
	show_list(&list);
    return 0;
}
