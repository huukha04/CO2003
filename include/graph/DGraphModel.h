/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DGraphModel.h
 * Author: LTSACH
 *
 * Created on 23 August 2020, 19:36
 */

#ifndef DGRAPHMODEL_H
#define DGRAPHMODEL_H
#include "graph/AbstractGraph.h"
#include "stacknqueue/Queue.h"
#include "stacknqueue/Stack.h"
#include "hash/xMap.h"
//#include "stacknqueue/PriorityQueue.h"
#include "sorting/DLinkedListSE.h"


//////////////////////////////////////////////////////////////////////
///////////// GraphModel: Directed Graph Model    ////////////////////
//////////////////////////////////////////////////////////////////////


template<class T>
class DGraphModel: public AbstractGraph<T>{
private:
public:
    DGraphModel(
            bool (*vertexEQ)(T&, T&), 
            string (*vertex2str)(T&) ): 
        AbstractGraph<T>(vertexEQ, vertex2str)
        {
    }
    
    void connect(T from, T to, float weight=0)
    {
        //TODO
        typename AbstractGraph<T>::VertexNode* fromNode = this->getVertexNode(from);
        typename AbstractGraph<T>::VertexNode* toNode = this->getVertexNode(to);
        
        if (fromNode == nullptr) throw VertexNotFoundException(this->vertex2str(from));
        if (toNode == nullptr) throw VertexNotFoundException(this->vertex2str(to));

        if (this->connected(from, to)) fromNode->connect(toNode, weight);
    }

    void disconnect(T from, T to)
    {
        //TODO
        typename AbstractGraph<T>::VertexNode* fromNode = this->getVertexNode(from);
        typename AbstractGraph<T>::VertexNode* toNode = this->getVertexNode(to);
        
        if (fromNode == nullptr) throw VertexNotFoundException(this->vertex2str(from));
        if (toNode == nullptr) throw VertexNotFoundException(this->vertex2str(to));

        typename AbstractGraph<T>::Edge* edgeNode = fromNode->getEdge(toNode);
        typename AbstractGraph<T>::Edge edgeNodefail(fromNode, toNode);
        if (edgeNode == nullptr) throw EdgeNotFoundException(this->edge2Str(edgeNodefail));
        fromNode->removeTo(toNode);        
    }
    void remove(T vertex)
    {
        //TODO
        typename AbstractGraph<T>::VertexNode* vertexNode = this->getVertexNode(vertex);
        if (vertexNode == nullptr) throw VertexNotFoundException(this->vertex2str(vertex));

        DLinkedList<T> out = this->getOutwardEdges(vertex);
        for (auto it = out.begin();it !=out.end();++it)
        {
            this->disconnect(vertex, *it);
        }

        DLinkedList<T> in = this->getInwardEdges(vertex);
        for (auto it = in.begin();it !=in.end();++it)
        {
            this->disconnect(vertex, *it);
        }
        
        this->nodeList.removeItem(vertexNode);
    }
    
    static DGraphModel<T>* create(
            T* vertices, int nvertices, Edge<T>* edges, int nedges,
            bool (*vertexEQ)(T&, T&),
            string (*vertex2str)(T&))
    {
        //TODO
        DGraphModel<T>* graph = new DGraphModel<T>(vertexEQ, vertex2str);
        for (int i = 0; i < nvertices; i++) 
        {
            graph->add(vertices[i]);
        }

        for (int i = 0; i < nedges; i++) 
        {
            T from = edges[i].from;
            T to = edges[i].to;
            float weight = edges[i].weight;
            graph->connect(from, to, weight);
        }

        return graph;
    }
};

#endif /* DGRAPHMODEL_H */

