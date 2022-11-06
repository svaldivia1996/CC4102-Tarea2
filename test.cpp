#include "fibonacci_heap.h"

int main()
{
    CyclicDoublyLinkedList c;
    std::cout <<  c;
    for(int i{ }; i < 5; i++)
    {
        NBNode* nodePtr{ new NBNode{ i } };
        c.insertFront(nodePtr);
        std::cout << c;
        reversePrint(std::cout, c);
    }
    for(int i{ }; i < 5; i++)
    {
        std::cout << c;
        reversePrint(std::cout, c);
        NBNode* poppedPtr{ c.popBack() };
        delete poppedPtr;
    }
    std::cout << c;

    NBNode* nodePtrA{ new NBNode{ 0 }};
    NBNode* nodePtrB{ new NBNode{ 1 }};

    std::cout << "A: "<<*nodePtrA << '\n';
    std::cout << "B: "<<*nodePtrB << '\n';

#ifdef USE_GRAPHVIZ
    // set up a graphviz context - but only once even for multiple graphs
    GVC_t *gvc = gvContext();
#endif
    //std::vector<int> numNodes{ {23, 7, 21, 3, 18, 52, 38, 39, 41, 17, 30, 24, 26, 46, 35} };
    //std::vector<int> numNodes{ {17, 30, 0} };
    std::vector<int> numNodesA{ {46, 24, 26, 0, 35} };
    std::vector<NBNode*> testNodesA(numNodesA.size(), nullptr);

    FibonacciHeap fA{ };

    for(int i{ }; i < numNodesA.size(); i++)
    {
        NBNode* newNode{ new NBNode{ numNodesA[i] } };
        testNodesA[i] = newNode;
        fA.insertNode(newNode);
    }
    fA.extractMinimum();
    
    //f.insertNode(nodePtrA);
    //f.insertNode(nodePtrB);

    std::cout << "num nodes: " <<fA.getNumNodes() << '\n';
    //fA.dumpHeapToImage(gvc);

    NBNode* nodePtr18{ new NBNode{ 18 }};
    NBNode* nodePtr39{ new NBNode{ 39 }};

    FibonacciHeap fB{ };
    fB.insertNode(nodePtr39);
    fB.insertNode(nodePtr18);
    fB.insertNode(nodePtrA);

    fB.extractMinimum();

    NBNode* nodePtr38{ new NBNode{ 38 }};
    NBNode* nodePtr41{ new NBNode{ 41 }};

    FibonacciHeap fC{ };
    fC.insertNode(nodePtr38);
    fC.insertNode(nodePtr41);
    fC.insertNode(nodePtrA);

    fC.extractMinimum();

    NBNode* nodePtr17{ new NBNode{ 17 }};
    NBNode* nodePtr30{ new NBNode{ 30 }};

    FibonacciHeap fD{ };
    fD.insertNode(nodePtr17);
    fD.insertNode(nodePtr30);
    fD.insertNode(nodePtrA);

    fD.extractMinimum();

    NBNode* nodePtr23{ new NBNode{ 23 }};
    NBNode* nodePtr7{ new NBNode{ 7 }};
    NBNode* nodePtr21{ new NBNode{ 21 }};
    NBNode* nodePtr52{ new NBNode{ 52 }};

    FibonacciHeap fE{ };
    fE.insertNode(nodePtr23);
    fE.insertNode(nodePtr7);
    fE.insertNode(nodePtr21);
    fE.mergeFibHeap(fB);
    fE.insertNode(nodePtr52);
    fE.mergeFibHeap(fC);
    fE.insertNode(nodePtrA);
    fE.mergeFibHeap(fD);
    fE.mergeFibHeap(fA);

    std::cout << "num nodes fE: " <<fE.getNumNodes() << '\n';
    //fE.dumpHeapToImage(gvc);

    fE.extractMinimum();
    //fE.dumpHeapToImage(gvc);

    fE.decreaseKey(nodePtr38, 20);
    fE.decreaseKey(nodePtr52, 19);
    //fE.dumpHeapToImage(gvc);

    fE.extractMinimum();
    
    fE.deleteNode(nodePtr39);
    fE.deleteNode(testNodesA[2]);
    //fE.dumpHeapToImage(gvc);

    delete nodePtrA;
    delete nodePtrB;

    delete nodePtr18;
    delete nodePtr39;
    delete nodePtr38;
    delete nodePtr41;

    delete nodePtr17;
    delete nodePtr30;
    delete nodePtr23;
    delete nodePtr7;
    delete nodePtr21;
    delete nodePtr52;

    for(int i{ }; i < numNodesA.size(); i++)
    {
        delete testNodesA[i];
    }

    return 0;
}