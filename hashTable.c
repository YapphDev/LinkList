#include<stdio.h>
#include<stdlib.h>
#define M 13


struct Node
{
    struct Node *next;
    int data;
};
typedef struct Node Node;

struct hashtable
{
    int m;
    Node **table;
};
typedef struct hashtable hashtable;

hashtable *Creat_hashtable(int m)
{   
    hashtable *hash;
    if (m <= 0)
        return NULL;
    
    hash = malloc(sizeof(hashtable));
    if(NULL == hash)
        return NULL;
    
    hash->m = m;
    hash->table = malloc(m * sizeof(Node *));
    if(NULL == hash->table)
    {
        free(hash);
        return NULL;
    }
    
    return hash;
}

Node *CreNode(int value)
{
    Node *node;
    node = (Node *)malloc(sizeof(Node));
    if (NULL == node)
    {
        return NULL;
    }
    node->data = value;
    node->next = NULL;
    return node;
}

Node *Insert_Tail(Node **HT, int data)
{
    Node *node;
    node = CreNode(data);
    if (NULL == node)
    {
        return NULL;
    }
    if (NULL == *HT)
    {
        *HT = node;
    }
    else
    {
        Node *temp_node;
        temp_node = *HT;
        while(NULL != temp_node->next)
        {
            temp_node = temp_node->next;
        }
        temp_node->next = node;
    }
    return node;
}

int Hash(int data, int m)
{
    int x = data % m ;
    return x;
}
void Insert_To_Hashtable(hashtable *HT, int data)
{
    int i = Hash(data,HT->m);
    Insert_Tail(&(HT->table[i]), data);
}

void show_List(Node *node)
{
    while(node != NULL)
    {
        printf("%d ",node->data);
        node = node->next;
    }
    printf("\n");
}
void show_HashTable(hashtable *HashTable)
{
    int i ;
    for (i = 0 ; i< HashTable->m ; i++)
    {
        show_List(HashTable->table[i]);
    }
}
int main()
{   
    hashtable *HashTable1 = Creat_hashtable(7);
    Insert_To_Hashtable(HashTable1,10);
    Insert_To_Hashtable(HashTable1,11);
    Insert_To_Hashtable(HashTable1,12);
    Insert_To_Hashtable(HashTable1,13);
    Insert_To_Hashtable(HashTable1,20);
    Insert_To_Hashtable(HashTable1,1);
    Insert_To_Hashtable(HashTable1,7);
    Insert_To_Hashtable(HashTable1,14);
    show_HashTable(HashTable1);
    return 0;
}










