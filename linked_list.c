#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
} typedef Node;

Node * list_new() {
    return NULL;
}

void list_print(Node *head_ptr) {
    Node *temp = head_ptr;
    while (temp) {
        printf(" %d", temp -> data);
        temp = temp -> next;
    }
    printf("\n");
}

/* insertion at beginning of list */
Node * list_insert(int x, Node *head_ptr) {
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->data = x;
    if (head_ptr)
       temp -> next = head_ptr; 
    else
        temp->next = NULL;
    return temp;
}

int main(int argc, char *argv[]) {
    Node *head_ptr = list_new();
    printf("How many numbers?\n");
    int n, x;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter the number: \n");
        scanf("%d", &x);
        head_ptr = list_insert(x, head_ptr);
        list_print(head_ptr);
    }
    
    return 0;
}