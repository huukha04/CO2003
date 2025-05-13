/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TopoSorter.h
 * Author: ltsach
 *
 * Created on July 11, 2021, 10:21 PM
 */

#ifndef TOPOSORTER_H
#define TOPOSORTER_H
#include "graph/DGraphModel.h"
#include "list/DLinkedList.h"
#include "sorting/DLinkedListSE.h"
#include "stacknqueue/Queue.h"
#include "stacknqueue/Stack.h"


template<class T>
class TopoSorter
{
public:
    static int DFS;
    static int BFS; 
    
protected:
    DGraphModel<T>* graph;
    int (*hash_code)(T&, int);
    
public:
    TopoSorter(DGraphModel<T>* graph, int (*hash_code)(T&, int)=0)
    {
        //TODO
        this->graph = graph; 
        this->hash_code = hash_code;
    }   
    DLinkedList<T> sort(int mode=0, bool sorted=true)
    {
        //TODO
        if (mode == DFS) 
        { 
            return dfsSort(sorted); 
        } 
        else 
        { 
            return bfsSort(sorted); 
        }
    }
    DLinkedList<T> bfsSort(bool sorted)
    {
        
        DLinkedList<T> result;
        Queue<T> queue;

        auto inDegreeMap = vertex2inDegree(hash_code);

        DLinkedListSE<T> se(graph->vertices());
        if (sorted)
        {
            se.sort();
        }
        for (auto vertex : se)
        {
            if (inDegreeMap.get(vertex) == 0)
            {
                queue.push(vertex);
            }
        }

        while (!queue.empty())
        {
            T vertex = queue.pop();
            result.add(vertex);

            for (auto neighbor : graph->getOutwardEdges(vertex))
            {
                inDegreeMap.put(neighbor, inDegreeMap.get(neighbor) - 1);
                if (inDegreeMap.get(neighbor) == 0)
                {
                    queue.push(neighbor);
                }
            }
        }
        

        
        return result;
    }
    DLinkedList<T> dfsSort(bool sorted = true) 
    {

        DLinkedList<T> result;
        Stack<T> stack;
        xMap<T, bool> visited(hash_code); 
        

        DLinkedListSE<T> se(graph->vertices());
        if (sorted)
        {
            se.sort();
        }
        for (auto vertex :  se) 
        {
            visited.put(vertex, false);
        }
        for (auto vertex : se) 
        {
            if (!visited.get(vertex)) 
            {
                dfsVisit(vertex, visited, stack); // Gọi DFS để thăm các đỉnh
            }
        }
        while (!stack.empty()) 
        {
            result.add(stack.pop());
        }

        return result;
    }

    void dfsVisit(T vertex, xMap<T, bool>& visited, Stack<T>& stack) 
    {
        visited.put(vertex, true);

        // Duyệt qua các đỉnh lân cận
        for (auto neighbor : graph->getOutwardEdges(vertex)) 
        {
            if (!visited.get(neighbor)) {
                dfsVisit(neighbor, visited, stack);  // Tiếp tục thăm đỉnh chưa được thăm
            }
        }

        // Thêm đỉnh vào stack khi không còn đỉnh con nào để thăm
        stack.push(vertex);
    }

   

   
protected:

    //Helper functions
    xMap<T, int> vertex2inDegree(int (*hash)(T&, int)) 
    { 
        xMap<T, int> inDegree(hash);
        for (auto it = graph->begin(); it != graph->end();it++)
        {
            T vertexValue = *it;
            inDegree.put(vertexValue, graph->inDegree(vertexValue));
        }
        return inDegree;

    }
        
    xMap<T, int> vertex2outDegree(int (*hash)(T&, int)) 
    {
        xMap<T, int> outDegree(hash);
        for (auto it = graph->begin(); it != graph->end();it++)
        {
            T vertexValue = *it;
            outDegree.put(vertexValue, graph->outDegree(vertexValue));
        }
        return outDegree;
    }    
    DLinkedList<T> listOfZeroInDegrees() 
    {
        auto inDegreeMap = vertex2inDegree(hash_code);
        DLinkedList<T> zeroInDegrees;

        for (auto it = graph->begin(); it != graph->end();it++)
        {
            T vertexValue = *it;
            if (inDegreeMap.get(vertexValue) == 0) 
            {
                zeroInDegrees.add(vertexValue);
            }
        }
        return zeroInDegrees;
    }
}; //TopoSorter
template<class T>
int TopoSorter<T>::DFS = 0;
template<class T>
int TopoSorter<T>::BFS = 1;

/////////////////////////////End of TopoSorter//////////////////////////////////


#endif /* TOPOSORTER_H */

