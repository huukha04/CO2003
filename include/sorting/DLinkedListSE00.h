/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DLinkedListSE.h
 * Author: LTSACH
 *
 * Created on 31 August 2020, 14:13
 */

#ifndef DLINKEDLISTSE_H
#define DLINKEDLISTSE_H
#include "list/DLinkedList.h"
#include "sorting/ISort.h"

template<class T>
class DLinkedListSE: public DLinkedList<T>{
public:
    
    DLinkedListSE(
            void (*removeData)(DLinkedList<T>*)=0, 
            bool (*itemEQ)(T&, T&)=0 ) : 
            DLinkedList<T>(removeData, itemEQ){
        
    };
    
    DLinkedListSE(const DLinkedList<T>& list)
    {
        this->copyFrom(list);
    }
    
    void sort(int (*comparator)(T&,T&)=0) {
        this->head = mergeSort(this->head, comparator);


    };
    
protected:

    typename DLinkedList<T>::Node* mergeSort(typename DLinkedList<T>::Node* head, int (*comparator)(T&, T&) = 0) {
        if (!head || !head->next) return head;

        typename DLinkedList<T>::Node* mid = getMiddle(head);
        typename DLinkedList<T>::Node* right = mid->next;
        mid->next = nullptr;

        auto* leftSorted = mergeSort(head, comparator);
        auto* rightSorted = mergeSort(right, comparator);

        return merge(leftSorted, rightSorted, comparator);
    }

    typename DLinkedList<T>::Node* getMiddle(typename DLinkedList<T>::Node* head) {
        if (!head) return head;

        typename DLinkedList<T>::Node* slow = head;
        typename DLinkedList<T>::Node* fast = head->next;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        return slow;
    }

    typename DLinkedList<T>::Node* merge(typename DLinkedList<T>::Node* left, typename DLinkedList<T>::Node* right, int (*comparator)(T&, T&) = 0) {
        typename DLinkedList<T>::Node dummy;
        typename DLinkedList<T>::Node* tail = &dummy;

        while (left && right) {
            if (compare(left->data, right->data, comparator) <= 0) {
                tail->next = left;
                left->prev = tail;
                left = left->next;
            } else {
                tail->next = right;
                right->prev = tail;
                right = right->next;
            }
            tail = tail->next;
        }

        if (left) {
            tail->next = left;
            left->prev = tail;
        } else {
            tail->next = right;
            if (right) right->prev = tail;
        }

        return dummy.next;
    }


    static int compare(T& lhs, T& rhs, int (*comparator)(T&,T&)=0){
        if(comparator != 0) return comparator(lhs, rhs);
        else{
            if(lhs < rhs) return -1;
            else if(lhs > rhs) return +1;
            else return 0;
        }
    }
};

#endif /* DLINKEDLISTSE_H */

