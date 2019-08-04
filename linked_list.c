#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
} typedef Node;

Node *list_new()
{
    return NULL;
}

void list_print(Node *head_ptr)
{
    Node *temp = head_ptr;
    while (temp)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
}

// TODO: Implement append func

/* insertion at nth position of list */
void list_insert(int x, int n, Node **head_ptr)
{
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->data = x;
    temp->next = NULL;
    // insertion at first position
    if (n == 1)
    {
        temp -> next = *head_ptr;
        *head_ptr = temp;
    }
    // insertion at other positions
    else
    {
        Node *temp2 = (*head_ptr);
        for (int i = 0; i < n - 2; i++)
        {
            temp2 = temp2->next;
        }
        temp->next = temp2->next;
        temp2->next = temp;
    }

}

Node *list_remove(int n, Node *head_ptr)
{
    Node *temp = head_ptr;
    // remove first node
    if (n == 1)
    {
        head_ptr = temp->next;
        free(temp);
    }
    // nodes in the middle
    else
    {
        for (int i = 0; i < n - 2; i++)
            temp = temp->next;
        Node *temp2 = temp->next;
        temp->next = temp2->next;
        free(temp2);
    }
    return head_ptr;
}

Node *list_reverse(Node *head_ptr)
{
   Node *current = head_ptr;
   Node *prev = NULL;
   Node *next = NULL;
   while (current)
   {
       next = current -> next;
       current-> next = prev; 
       prev = current;          
       current = next;         
   }
   return prev;
}

// recursive reverse print
void list_rrprint(Node *head_ptr)
{
    if (!head_ptr)
        return;
    list_rrprint(head_ptr -> next);
    printf("%d ", head_ptr -> data);
}

// recursive print
void list_rprint(Node *head_ptr)
{
    if (!head_ptr) {
        printf("%d ", head_ptr -> data);
        return;
    }
    printf("%d ", head_ptr -> data);
    list_rprint(head_ptr -> next);
}

// recursive reverse
void list_rreverse(Node **head, Node *p)
{
    if (p -> next == NULL)
    {
        (*head) = p;
        return;
    }
    list_rreverse(head, p -> next);
    Node *q = p->next;
    q -> next = p;
    p -> next = NULL;  
}

/* Test cases */
int main(int argc, char *argv[])
{
    Node *head_ptr = list_new();
    list_insert(2, 1, &head_ptr);
    list_insert(3, 2, &head_ptr);
    list_insert(4, 1, &head_ptr);
    list_insert(5, 2, &head_ptr);
    list_print(head_ptr);
    //printf("\n");
    //list_rrprint(head_ptr);
    //printf("\n");
    //list_rreverse(&head_ptr, head_ptr);
    //list_rprint(head_ptr);
    return 0;
}