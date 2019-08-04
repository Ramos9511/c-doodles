#ifndef LINKED_LIST
#define LINKED_LIST

    struct Node
    {
        int data;
        struct Node *next;
    } typedef Node;

    Node *list_new();
    void list_print(Node *head_ptr);
    void list_rprint(Node *head_ptr);
    void list_rrprint(Node *head_ptr);
    void list_reverse(Node **head_ptr);
    void list_remove(int n, Node **head_ptr);
    void list_rreverse(Node **head, Node *p);
    void list_insert(int x, int n, Node **head_ptr);

#endif