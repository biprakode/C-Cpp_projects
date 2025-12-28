#ifndef STACK_LINKED_LIST
#define STACK_LINKED_LIST

template <class T>
class Stack_Linked_List {
public:
    struct Node {
        T data;
        Node *next
    };

    Node *head;
    
    Stack_Linked_List() = default;
    Stack_Linked_List(Stack_Linked_List &other) = delete; // 

    void push(Node * newNode) {
        newNode->next = head;
        head = newNode;
    }
    Node* pop() {
        Node *temp = head;
        head = head->next;
        return temp;
    }
};

#endif