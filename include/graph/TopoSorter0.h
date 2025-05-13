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
#include "hash/xMap.h"


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
        : graph(graph), hash_code(hash_code) {}



    DLinkedList<T> sort(int mode=0, bool sorted=true){
        if (mode == DFS) 
        {
            return dfsSort(sorted);
        } 
        else if (mode == BFS) 
        {
            return bfsSort(sorted);
        }
        throw std::invalid_argument("Invalid sorting mode");

    }


   DLinkedList<T> bfsSort(bool sorted=true)
{
    DLinkedList<T> result;
    xMap<T, int> inDegrees = vertex2inDegree(hash_code);
    DLinkedList<T> zeroInDegree = listOfZeroInDegrees();

    if (sorted) {
        DLinkedListSE<T> sortable(zeroInDegree);
        sortable.sort();
        zeroInDegree = sortable;
    }

    while (!zeroInDegree.empty()) {
        T current = zeroInDegree.removeAt(0);
        result.add(current);

        DLinkedList<T> outwardEdges = graph->getOutwardEdges(current);
        typename DLinkedList<T>::Iterator it = outwardEdges.begin();
        while (it != outwardEdges.end()) {
            T neighbor = *it;
            int degree = inDegrees.get(neighbor);
            inDegrees.put(neighbor, degree - 1);
            if (degree - 1 == 0) {
                zeroInDegree.add(neighbor);
            }
            ++it;
        }
    }

    if (result.size() != graph->size()) {
        throw std::runtime_error("Graph contains a cycle");
    }

    return result;
}




    DLinkedList<T> dfsSort(bool sorted=true){
    DLinkedList<T> result;
    xMap<T, bool> visited(hash_code);
    typename DLinkedList<T>::Iterator it = graph->vertices().begin();

    if (sorted) {
        DLinkedListSE<T> sortable(graph->vertices());
        sortable.sort();
        it = sortable.begin();
    }

    while (it != graph->vertices().end()) {
        T vertex = *it;
        if (!visited.get(vertex)) {
            dfsVisit(vertex, visited, result);
        }
        ++it;
    }

    return result;


    }



protected:

    void dfsVisit(T vertex, xMap<T, bool>& visited, DLinkedList<T>& result) {
    visited.put(vertex, true);

    DLinkedList<T> outwardEdges = graph->getOutwardEdges(vertex);
    typename DLinkedList<T>::Iterator it = outwardEdges.begin();
    while (it != outwardEdges.end()) {
        T neighbor = *it;
        if (!visited.get(neighbor)) {
            dfsVisit(neighbor, visited, result);
        }
        ++it;
    }

    result.add(0, vertex);
    }

    //Helper functions
    xMap<T, int> vertex2inDegree(int (*hash)(T&, int)) {
        xMap<T, int> inDegrees(hash);

        typename DLinkedList<T>::Iterator it = graph->vertices().begin();
        while (it != graph->vertices().end()) {
            T vertex = *it;
            inDegrees.put(vertex, graph->inDegree(vertex));
            ++it;
        }

        return inDegrees;
    }

    xMap<T, int> vertex2outDegree(int (*hash)(T&, int)) {
        xMap<T, int> outDegrees(hash);

        typename DLinkedList<T>::Iterator it = graph->vertices().begin();
        while (it != graph->vertices().end()) {
            T vertex = *it;
            outDegrees.put(vertex, graph->outDegree(vertex));
            ++it;
        }

        return outDegrees;
    }

    DLinkedList<T> listOfZeroInDegrees() {
        DLinkedList<T> zeroInDegree;
        typename DLinkedList<T>::Iterator it = graph->vertices().begin();

        while (it != graph->vertices().end()) {
            T vertex = *it;
            if (graph->inDegree(vertex) == 0) {
                zeroInDegree.add(vertex);
            }
            ++it;
        }

        return zeroInDegree;
    }

}; //TopoSorter
template<class T>
int TopoSorter<T>::DFS = 0;
template<class T>
int TopoSorter<T>::BFS = 1;

/////////////////////////////End of TopoSorter//////////////////////////////////


#endif /* TOPOSORTER_H */

