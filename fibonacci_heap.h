#ifndef FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_H

#ifdef USE_GRAPHVIZ

#include <cgraph.h>
#include <gvc.h>

#endif

#include "nbnode.h"
#include "cyclic_doubly_linked_list.h"

class NBNode;
class CyclicDoublyLinkedList;

class FibonacciHeap
{
    CyclicDoublyLinkedList m_rootList{ };
    int m_numNodes{ };

    public:
    FibonacciHeap();

    ~FibonacciHeap();

    bool isEmpty();

    /*
    Puntero a mínima raíz
    Costo O(1)
    */
    NBNode* getMinRoot();

    int getNumNodes();

    /*
    Costo O(1) amortizado
    */
    int insertNode(NBNode* newNode);

    /*
    Concatena root lists, haciendo cambios de punteros
    Coste: O(1)
    */
    int mergeFibHeap(FibonacciHeap& aFibHeap);

    NBNode* extractMinimum();

    int setMinimum();

    int consolidate();

    int decreaseKey(NBNode* aNode, int newKey);
    int deleteNode(NBNode* removed);

#ifdef USE_GRAPHVIZ

    int drawDescendants(NBNode* parent, Agraph_t* h);
    int drawHeap(Agraph_t* h);
    int dumpHeapToImage(GVC_t* graphContext);

#endif

};


#endif
