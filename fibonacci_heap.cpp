#include "fibonacci_heap.h"

FibonacciHeap::FibonacciHeap()
{
    std::cout << "Fibonacci Heap created.\n";
}

FibonacciHeap::~FibonacciHeap()
{
    std::cout << "Fibonacci Heap destroyed.\n";
}

bool FibonacciHeap::isEmpty()
{
    return m_rootList.isEmpty();
}

/*
Puntero a mínima raíz
Costo O(1)
*/
NBNode* FibonacciHeap::getMinRoot()
{
    return m_rootList.get_head();
}

int FibonacciHeap::getNumNodes()
{
    return m_numNodes;
}

/*
Costo O(1) amortizado
*/
int FibonacciHeap::insertNode(NBNode* newNode)
{
    if(getMinRoot() == nullptr || newNode->getKey() < getMinRoot()->getKey())
    {
        m_rootList.insertFront(newNode);
    }
    else
    {
        m_rootList.insertBack(newNode);
    }
    newNode->unmark();
    m_numNodes += 1;
    return 0;
}

/*
Concatena root lists, haciendo cambios de punteros
Coste: O(1)
*/
int FibonacciHeap::mergeFibHeap(FibonacciHeap& aFibHeap)
{
    NBNode* newHead;
    NBNode* mergedHead;
    
    if(aFibHeap.isEmpty())
    {
        return 0;
    }

    if(isEmpty())
    {
        m_rootList.m_head = aFibHeap.m_rootList.m_head;
        m_numNodes = aFibHeap.m_numNodes;
        return 0;
    }

    if(getMinRoot()->getKey() < aFibHeap.getMinRoot()->getKey())
    {
        newHead = getMinRoot();
        mergedHead = aFibHeap.getMinRoot();
    }
    else
    {
        newHead = aFibHeap.getMinRoot();
        mergedHead = getMinRoot();
    }
    NBNode* mergedTail{ newHead->getPrevSibling() };
    NBNode* newTail{ mergedHead->getPrevSibling() };

    newHead->setPrevSibling(newTail);
    mergedTail->setNextSibling(mergedHead);

    mergedHead->setPrevSibling(mergedTail);
    newTail->setNextSibling(newHead);

    m_rootList.m_head = newHead;
    m_numNodes += aFibHeap.m_numNodes;
    
    return 0;
}

int FibonacciHeap::setMinimum()
{
    NBNode* first{ getMinRoot() };
    NBNode* actual{ first };
    if(actual != nullptr)
    {
        while(actual != first)
        {
            if(actual->getKey() < getMinRoot()->getKey())
            {
                m_rootList.m_head = actual;
            }
            actual = actual->getNextSibling();
        }
        return 0;
    }
    return 1;
}

NBNode* FibonacciHeap::extractMinimum()
{
    NBNode* extracted{ m_rootList.popFront() };
    if(extracted != nullptr)
    {
        if(extracted->hasChildren())
        {
            FibonacciHeap temp{ };
            temp.m_rootList.m_head = extracted->getChild();
            extracted->getChildrenList().removeParent();
             
            mergeFibHeap(temp);
        }

        m_numNodes -= 1;
        consolidate();
        setMinimum();
    }

    return extracted;
}

int FibonacciHeap::consolidate()
{
    int degreeSize{ static_cast<int>(std::ceil(std::log2(m_numNodes))) };
    std::vector<NBNode*> degreeList(degreeSize, nullptr);
    NBNode* actual{ m_rootList.get_head()};
    NBNode* newTree;
    int degree;
    do
    {
        degree = actual->getDegree();
        // actual = m_rootList.popFront();
        newTree = actual;
        actual = actual->getNextSibling();
        while(degree < degreeList.size() && degreeList[degree] != nullptr)
        {
            if( degreeList[degree]->getKey() < newTree->getKey())
            {
                m_rootList.removeNode(newTree);
                degreeList[degree]->insertChildFront(newTree);
                newTree = degreeList[degree];
            }
            else
            {
                m_rootList.removeNode(degreeList[degree]);
                newTree->insertChildFront(degreeList[degree]);
            }
            degreeList[degree] = nullptr;
            degree = newTree->getDegree();
        }
        // degreeList[degree] is empty
        degreeList[degree] = newTree;
    } while (actual != m_rootList.get_head());
    return 0;
}

int FibonacciHeap::decreaseKey(NBNode* aNode, int newKey)
{
    aNode->setKey(newKey);
    if(aNode->getParent() != nullptr)
    {
        NBNode* parent{ aNode->getParent() };
        if(aNode->getKey() < parent->getKey())
        {
            bool parentMarked; 
            do
            {
                parentMarked = parent->isMarked();
                aNode->cutFromParent();
                insertNode(aNode);
                aNode = parent;
                parent = parent->getParent();
            } while(parent != nullptr && parentMarked);    
        }     
    }
    else
    {
        m_rootList.removeNode(aNode);
        insertNode(aNode);
    }
    return 0;
}

int FibonacciHeap::deleteNode(NBNode* removed)
{
    int minimumKey{ getMinRoot()->getKey()-1 };
    decreaseKey(removed, minimumKey);
    extractMinimum();
    return 0;
}


#ifdef USE_GRAPHVIZ

/*
compatibilidad con c++

No implementa c_str() y usa directamente un for loop para copiar el 
string en su lugar puesto que la firma pide un char *, que es 
incompatible con el tipo retornado const char *
*/
CGRAPH_API Agnode_t *agnode(Agraph_t * g, std::string name, int createflag)
{
    size_t largo{ name.size() };
    char name_c[largo+1];
    for(size_t i{ }; i < largo; i++)
    {
        name_c[i] = name[i];
    }
    name_c[largo] = 0;
    return agnode(g, name_c, createflag);
}

int FibonacciHeap::drawDescendants(NBNode* parent, Agraph_t* h)
{
    CyclicDoublyLinkedList& siblings{ parent->getChildrenList() };
    NBNode* actual{ siblings.get_head() };
    if(actual != nullptr)
    {   
        std::string parent_name{ std::to_string(parent->getKey()) };
        Agnode_t *p = agnode(h, parent_name, 1);

        do
        {
            std::string child_name{ std::to_string(actual->getKey()) };

            // draw edge for descendants
            Agnode_t *c = agnode(h, child_name, 1);
            Agedge_t *e = agedge(h, p, c, 0, 1);

            if(actual->isMarked())
            {
                agsafeset(c, "color", "red", "");
            }
        
            drawDescendants(actual, h);
            actual = actual->getNextSibling();
        } while(actual != siblings.get_head());
        
    }
    return 0;
}

int FibonacciHeap::drawHeap(Agraph_t* h)
{
    //drawDescendants()
    NBNode* actual{ m_rootList.get_head() };
    if(actual == nullptr)
    {
        return 1;
    }
    else
    {
        std::string actual_name{ std::to_string(actual->getKey()) };
        Agnode_t *a{ agnode(h, actual_name, 1) };

        // green root
        agsafeset(a, "color", "green", "");

        Agnode_t *n;
        drawDescendants(actual, h);
        NBNode* next{ actual->getNextSibling() };

        while(next != m_rootList.get_head())
        {
            std::string next_name{ std::to_string(next->getKey()) };
            n = agnode(h, next_name, 1);
            Agedge_t *e = agedge(h, a, n, 0, 1);
            Agedge_t *eRev = agedge(h, n, a, 0, 1);

            if(next->isMarked())
            {
                agsafeset(n, "color", "red", "");
            }

            a = n;
            actual = next;
            next = next->getNextSibling();

            drawDescendants(actual, h);

        }

    }
    
    return 0;
}

int FibonacciHeap::dumpHeapToImage(GVC_t* graphContext)
{
    // Create a simple digraph
    Agraph_t *h = agopen("g", Agundirected, 0);
    drawHeap(h);
    // Use the directed graph layout engine
    gvLayout(graphContext, h, "dot");

    char address[sizeof(this)*2+1];
    snprintf(address, sizeof(this)*2+1, "%p", static_cast<void*>(this));

    std::cout << address << ' ' << strlen(address) << '\n';

    //std::cout << sizeof(this) << '\n';
    size_t nameLength{ 14+1+ strlen(address) };
    char dotName[nameLength];
    char dotName2[nameLength];

    char svgName[nameLength];
    char svgName2[nameLength];

    FILE *fp;
    snprintf(dotName, nameLength, "./fibheap_%s.dot", address);
    snprintf(svgName, nameLength, "./fibheap_%s.svg", address);
    dotName[nameLength-1] = 0;
    svgName[nameLength-1] = 0;

    strcpy(dotName2, dotName);
    strcpy(svgName2, svgName);
    
    std::cout << "Opening dot file at " << dotName << '\n';
    fp = fopen(dotName, "w+");

    // Output in .dot format
    gvRender(graphContext, h, "dot", fp);
    std::cout << "Render complete!\n";

    fclose(fp);

    gvFreeLayout(graphContext, h);

    agclose(h);

    // Use neato to get a more balanced graph
    // see: https://graphviz.org/docs/layouts/neato/
    //system("neato -Tsvg hello.dot -o temp.svg");

    char dotCommand[13+1+strlen(dotName)+strlen(svgName)] { "dot -Tsvg " };
    char hypen[] {" > "};
    char space[] {" "};
    char rmCommand[3+1+strlen(svgName2)] {"rm "};
    char rmCommand2[3+1+strlen(dotName2)] {"rm "};
    

    std::cout << "Dumping dot file to svg file: " << svgName << '\n';
    //char* fullDotCommand {strcat(dotCommand, strcat(dotName, strcat(hypen, svgName)))};
    char* fullDotCommand {strcat(strcat(strcat(dotCommand, dotName), hypen), svgName)};
    system(fullDotCommand);

    std::cout << "Calling command "<< IMVIEWER_COMMAND_NAME << " to view svg file in image viewer\n";

    char imViewerCommand[strlen(IMVIEWER_COMMAND_NAME)+strlen(svgName)+1+1];
    strcpy(imViewerCommand, IMVIEWER_COMMAND_NAME);

    char* fullImViewerCommand { strcat(strcat(imViewerCommand, space), svgName) };
    system(fullImViewerCommand);
    //system(strcat("eog", strcat(" ", dotName)));
    std::cout << "Deleting temporary files\n";
    char* fullrmSvgCommand{ strcat(rmCommand, svgName2) };
    char* fullrmDotCommand{ strcat(rmCommand2, dotName2) };
    system(fullrmSvgCommand);
    system(fullrmDotCommand);
    std::cout << "Done!\n";


    return 0;
}

#endif

