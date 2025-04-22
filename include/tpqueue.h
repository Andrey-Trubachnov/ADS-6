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
    T* citem = new T(std::move(item));
    if (isEmpty()) {
      head = tail = citem;
      return;
    }

    T* temp = head;
    while (temp != nullptr && temp->prior >= citem->prior) {
      temp = temp->next;
    }

    if (temp == nullptr) {
      tail->next = citem;
      citem->prev = tail;
      tail = citem;
    } else if (temp == head) {
      citem->next = head;
      head->prev = citem;
      head = citem;
    } else {
      citem->next = temp;
      citem->prev = temp->prev;
      temp->prev->next = citem;
      temp->prev = citem;
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

  ~TPQueue() {
    while (!isEmpty()) {
      pop();
    }
  }
};

struct SYM {
  char ch;
  int prior;
  SYM* next = nullptr;
  SYM* prev = nullptr;
};

#endif  // INCLUDE_TPQUEUE_H_
