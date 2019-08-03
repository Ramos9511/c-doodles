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
        printf(" %d", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

/* insertion at nth position of list */
Node *list_insert(int x, int n, Node *head_ptr)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->data = x;
    temp->next = NULL;
    // if list isn't empty
    if (head_ptr)
    {
        // insertion at first position
        if (n == 1)
        {
            temp->next = head_ptr;
            // insertion at other positions
        }
        else
        {
            Node *temp2 = head_ptr;
            for (int i = 0; i < n - 2; i++)
            {
                temp2 = temp2->next;
            }
            temp->next = temp2->next;
            temp2->next = temp;
            return head_ptr;
        }
    }
    return temp;
}

Node * list_remove(int n, Node *head_ptr)
{
    Node *temp = head_ptr;
    // remove first node
    if (n == 1)
    {
        head_ptr = temp -> next;
        free(temp);
    }
    // nodes in the middle
    else
    {
        for (int i = 0; i < n - 2; i++)
            temp = temp -> next;
        Node *temp2 = temp -> next;
        temp -> next = temp2 -> next;
        free(temp2);
    }
    return head_ptr;
}

int main(int argc, char *argv[])
{
    Node *head_ptr = list_new();
    head_ptr = list_insert(2, 1, head_ptr);
    head_ptr = list_insert(3, 2, head_ptr);
    head_ptr = list_insert(4, 1, head_ptr);
    head_ptr = list_insert(5, 2, head_ptr);
    list_print(head_ptr);
    head_ptr = list_remove(4, head_ptr);
    head_ptr = list_remove(1, head_ptr);
    list_print(head_ptr);
    return 0;
}