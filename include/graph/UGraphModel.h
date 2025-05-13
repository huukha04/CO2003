/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   UGraphModel.h
 * Author: LTSACH
 *
 * Created on 24 August 2020, 15:16
 */

#ifndef UGRAPHMODEL_H
#define UGRAPHMODEL_H

#include "graph/AbstractGraph.h"
//#include "stacknqueue/PriorityQueue.h"

//////////////////////////////////////////////////////////////////////
///////////// UGraphModel: Undirected Graph Model ////////////////////
//////////////////////////////////////////////////////////////////////

template <class T>
class UGraphModel : public AbstractGraph<T>
{
private:
public:
    // class UGraphAlgorithm;
    // friend class UGraphAlgorithm;

    UGraphModel(
        bool (*vertexEQ)(T &, T &),
        string (*vertex2str)(T &)) : AbstractGraph<T>(vertexEQ, vertex2str)
    {
    }

    void connect(T from, T to, float weight = 0)
    {
        // TODO
        typename AbstractGraph<T>::VertexNode*fromNode = this->getVertexNode(from);
        typename AbstractGraph<T>::VertexNode*toNode = this->getVertexNode(to);
        
        if (fromNode == nullptr) throw VertexNotFoundException(this->vertex2str(from));
        if (toNode == nullptr) throw VertexNotFoundException(this->vertex2str(to));

        

        if (this->connected(from, to)) fromNode->connect(toNode, weight);
        if (!this->vertexEQ(to, from) && this->connected(to, from)) toNode->connect(fromNode, weight);
    }
    void disconnect(T from, T to)
    {
        // TODO
        typename AbstractGraph<T>::VertexNode*fromNode = this->getVertexNode(from);
        typename AbstractGraph<T>::VertexNode*toNode = this->getVertexNode(to);
        
        if (fromNode == nullptr) throw VertexNotFoundException(this->vertex2str(from));
        if (toNode == nullptr) throw VertexNotFoundException(this->vertex2str(to));

        
        typename AbstractGraph<T>::Edge* edge = fromNode->getEdge(toNode);
        
        typename AbstractGraph<T>::Edge edgeNodefail(fromNode, toNode);
        if (edge == nullptr) throw EdgeNotFoundException(this->edge2Str(edgeNodefail));

        fromNode->removeTo(toNode);  
        if (!this->vertexEQ(from, to)) toNode->removeTo(fromNode); 
    }
    void remove(T vertex)
    {
        // TODO
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
    static UGraphModel<T> *create(
        T *vertices, int nvertices, Edge<T> *edges, int nedges,
        bool (*vertexEQ)(T &, T &),
        string (*vertex2str)(T &))
    {
        // TODO
        UGraphModel<T>* graph = new UGraphModel<T>(vertexEQ, vertex2str);
        
        for (int i = 0; i < nvertices; i++) 
        {
            graph->add(vertices[i]);
        }
        
        for (int i = 0; i < nedges; i++) 
        {
            graph->connect(edges[i].from, edges[i].to, edges[i].weight);
        }
        
        return graph;
    }
};

#endif /* UGRAPHMODEL_H */
