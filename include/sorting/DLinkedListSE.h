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
class DLinkedListSE: public DLinkedList<T>
{
public:
    
    DLinkedListSE(
            void (*removeData)(DLinkedList<T>*)=0, 
            bool (*itemEQ)(T&, T&)=0 ) : 
            DLinkedList<T>(removeData, itemEQ)
            {
        
    };
    
    DLinkedListSE(const DLinkedList<T>& list)
    {
        this->copyFrom(list);
    }
    
    void sort(int (*comparator)(T&,T&) = 0) 
    {
        if (this->count <= 1) return;

        this->head->next = MergeSort(this->head->next, comparator);

        typename DLinkedList<T>::Node* current = this->head;
        while (current->next != this->tail && current->next) 
        {
            current = current->next;
        }
        this->tail->prev = current;
        current->next = this->tail;
    }
    
        


    
protected:
    typename DLinkedList<T>::Node* MergeSort(typename DLinkedList<T>::Node* start, int (*comparator)(T&, T&)) 
    {
        if (!start || start->next == this->tail) return start;
        {
            return start; 
        }

        typename DLinkedList<T>::Node* second = split(start);

        start = MergeSort(start, comparator);
        second = MergeSort(second, comparator);

        return merge(start, second, comparator);
    }
    typename DLinkedList<T>::Node *split(typename DLinkedList<T>::Node *start) 
    {
        typename DLinkedList<T>::Node *fast = start;
        typename DLinkedList<T>::Node *slow = start;

        while (fast->next != this->tail && fast->next->next != this->tail) 
        {
            slow = slow->next;
            fast = fast->next->next;
        }

        typename DLinkedList<T>::Node *second = slow->next;
        slow->next = this->tail;
        second->prev = nullptr;
        return second;
    }

    typename DLinkedList<T>::Node* merge(typename DLinkedList<T>::Node* first, typename DLinkedList<T>::Node* second, int (*comparator)(T&, T&)) 
    {
            typename DLinkedList<T>::Node dummy;  
            typename DLinkedList<T>::Node* current = &dummy;

            while (first != this->tail && second != this->tail) 
            {
                if (comparator(first->data, second->data) <= 0) 
                {
                    current->next = first;
                    first->prev = current;
                    first = first->next;
                } else 
                {
                    current->next = second;
                    second->prev = current;
                    second = second->next;
                }
                current = current->next;
            }

            while (first != this->tail) {
                current->next = first;
                first->prev = current;
                first = first->next;
                current = current->next;
            }

            while (second != this->tail) {
                current->next = second;
                second->prev = current;
                second = second->next;
                current = current->next;
            }

            current->next = this->tail;
            this->tail->prev = current;

            return dummy.next;
        }
   



    static int compare(T& lhs, T& rhs, int (*comparator)(T&,T&)=0)
    {
        if(comparator != 0) return comparator(lhs, rhs);
        else
        {
            if(lhs < rhs) return -1;
            else if(lhs > rhs) return +1;
            else return 0;
        }
    }
};

#endif /* DLINKEDLISTSE_H */

