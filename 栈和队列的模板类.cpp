#include <iostream>
#include <cstdio>

using namespace std;

typedef int ElemType;
typedef void Status;

typedef struct Node{
    ElemType data;
    struct Node* next;
}Node,*LinkStack,*Ptr;

typedef struct{
    Ptr front;
    Ptr rear;
}LinkQueue;

class Queue {
public:
    Ptr front;
    Ptr rear;
    Queue() {
        front = rear = (Ptr)malloc(sizeof(struct Node));
        if (!front)	//return并报错
            return;
        front->next = NULL;
    }
    void push(ElemType e) {
        Ptr p = (Ptr)malloc(sizeof(struct Node));
        if (!p)
            return;
        p->data = e;
        p->next = NULL;
        rear->next = p;
        rear = p;
    }
    void pop(ElemType& e) {
        if (front == rear)
            return;
        Ptr p = front->next;
        e = p->data;
        front->next = p->next;
        if (rear == p)	rear = front;
        free(p);
    }
};


Status InitQueue(LinkQueue& Q){
    Q.front = Q.rear = (Ptr)malloc(sizeof(struct Node));
    if(!Q.front)	//return并报错
        return;
    Q.front->next = NULL;
}

Status EnQueue(LinkQueue& Q,ElemType e){
    Ptr p = (Ptr)malloc(sizeof(struct Node));
    if(!p)
        return;
    p->data = e;
    p->next = NULL;
    Q.rear -> next = p;
    Q.rear = p;
}

Status DeQueue(LinkQueue& Q,ElemType& e){
    if(Q.front ==Q.rear)
        return;
    Ptr p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if(Q.rear == p)	Q.rear = Q.front;
    free(p);
}

Status Push(LinkStack& S,ElemType e){
    Ptr p = (Ptr)malloc(sizeof(struct Node));
    p->data = e;
    p->next = S->next;
    S->next = p;
}

Status Pop(LinkStack& S,ElemType& e){
    if(S){
        Ptr p;
        p = S->next;
        e = p->data;
        S->next = p->next;
        free(p);
    }
    else
        return;
}

