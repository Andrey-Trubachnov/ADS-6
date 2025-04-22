// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

template<typename T>
class TPQueue {
  T* head;
  T* tail;

 public:
  TPQueue() : head(nullptr), tail(nullptr) {}

  bool isEmpty() {
   return head == nullptr;
  }
  
  void push(T&& item) {
   if (isEmpty()) {
     head = tail = &item;
     return;
   }
  
   T* temp = head;
   while (temp != nullptr && temp->prior >= (&item)->prior) {
     temp = temp->next;
   }
  
   if (temp == nullptr) {
     tail->next = &item;
     (&item)->prev = tail;
     tail = (&item);
   } else if (temp == head) {
     (&item)->next = head;
     head->prev = (&item);
     head = (&item);
   } else {
     (&item)->next = temp;
     (&item)->prev = temp->prev;
     temp->prev->next = (&item);
     temp->prev = (&item);
   }
  }
  
  T pop() {
   if (isEmpty()) {
     throw("Список пуст");
   }
  
   T* t = head;
  
   if (head == tail) {
     head = tail = nullptr;
     return *t;
   }
  
   head = head->next;
   head->prev = nullptr;
   return *t;
  }
};

struct SYM {
  char ch;
  int prior;
  SYM* next = nullptr;
  SYM* prev = nullptr;
};

#endif  // INCLUDE_TPQUEUE_H_
