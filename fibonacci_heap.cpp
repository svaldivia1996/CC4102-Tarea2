#include <iostream>
#include <bits/stdc++.h>
#include <vector>

/*
class CyclicDoublyLinkedList
{
    NBNode* m_head{ nullptr };

    public:
    CyclicDoublyLinkedList();
    ~CyclicDoublyLinkedList();

    NBNode* get_head();
    NBNode* get_tail();

    bool isEmpty();

    //Insert at back of list.
    int insertBack(NBNode* newNode);

    //Inserts at front of list. New node takes the head's place
    int insertFront(NBNode* newNode);

    NBNode* popFront();
    NBNode* popBack();

    friend std::ostream& operator<<(std::ostream& out, CyclicDoublyLinkedList& list);
    friend std::ostream& reversePrint(std::ostream& out, CyclicDoublyLinkedList& list);

    friend class FibonacciHeap;
};
*/

class NBNode
{
    NBNode* m_parent{ nullptr };
    int m_key{ };
    int m_degree{ };
    CyclicDoublyLinkedList m_childList{ };
    NBNode* m_next{ nullptr };
    NBNode* m_prev{ nullptr };

    bool wasPruned{ false };

public:
    NBNode(int key, int degree, NBNode* parent, NBNode* child, NBNode* next, NBNode* prev):
        m_key{ key }, m_degree{ degree }, m_parent{ parent }, m_next{ next }, m_prev{ prev }
    {
        m_childList.insertFront(child);
        std::cout << "NBNode " << m_key << ", " << m_degree << " created.\n";
    }

    NBNode(int key):
        NBNode(key, 0, nullptr, nullptr, nullptr, nullptr)
    {}

    ~NBNode()
    {
        std::cout << "NBNode " << m_key << ", " << m_degree << " destroyed.\n";
    }

    void setParent(NBNode* parent)
    {
        m_parent = parent;
    }

    void setChild(NBNode* child)
    {
        if(m_childList.isEmpty())
        {
            m_childList.insertFront(child);
            return;
        }
        m_childList.m_head = child;
    }

    void setNextSibling(NBNode* next)
    {
        m_next = next;
    }

    void setPrevSibling(NBNode* prev)
    {
        m_prev = prev;
    }

    NBNode* getChild()
    {
        return m_childList.get_head();
    }

    CyclicDoublyLinkedList& getChildrenList()
    {
        return m_childList;
    }

    int insertChildFront(NBNode* newChild)
    {
        m_childList.insertFront(newChild);
        incrementDegree();
        setParent(newChild);
    }

    NBNode* getNextSibling()
    {
        return m_next;
    }

    NBNode* getPrevSibling()
    {
        return m_prev;
    }

    friend std::ostream& operator<<(std::ostream& out, NBNode& node);

    int getKey()
    {
        return m_key;
    }

    int getDegree()
    {
        return m_degree;
    }

    int incrementDegree()
    {
        m_degree +=1;
        return 0;
    }

    int decrementDegree()
    {
        m_degree -=1;
        return 0;
    }

};

std::ostream& operator<<(std::ostream& out, NBNode& node)
{
    return out << "( " << node.m_key << ", " << node.m_degree << " )";
}


class CyclicDoublyLinkedList
{
    NBNode* m_head{ nullptr };

    public:
    CyclicDoublyLinkedList()
    {
        std::cout << "CyclicDoublyLinkedList created.\n";
    }

    ~CyclicDoublyLinkedList()
    {
        std::cout << "CyclicDoublyLinkedList destroyed.\n";
    }

    NBNode* get_head()
    {
        return m_head;
    }

    NBNode* get_tail()
    {
        return m_head->getPrevSibling();
    }

    bool isEmpty()
    {
        return m_head == nullptr;
    }

    /*
    Insert at back of list.
    */
    int insertBack(NBNode* newNode)
    {
        if(m_head == nullptr)
        {
            m_head = newNode;
            m_head->setPrevSibling(newNode);
            m_head->setNextSibling(newNode);
        }

        get_tail()->setNextSibling(newNode);
        newNode->setPrevSibling(get_tail());

        m_head->setPrevSibling(newNode);
        newNode->setNextSibling(m_head);
        return 0;
    }

    /*
    Inserts at front of list. New node takes the head's place
    */
    int insertFront(NBNode* newNode)
    {
        insertBack(newNode);
        m_head = newNode;
        return 0;
    }

    NBNode* popFront()
    {
        if(m_head == NULL)
        {
            return nullptr;
        }
        else
        {
            NBNode* popped{ m_head };
            if (m_head->getNextSibling() == m_head)
            {
                m_head = nullptr;
            }
            else
            {
                m_head->getPrevSibling()->setNextSibling(m_head->getNextSibling());
                m_head->getNextSibling()->setPrevSibling(m_head->getPrevSibling());
                m_head = m_head->getNextSibling();
            }
            popped->setNextSibling(nullptr);
            popped->setPrevSibling(nullptr);
            return popped;            
        }

    }

    NBNode* popBack()
    {
        m_head = m_head->getPrevSibling();
        return popFront();
    }

    friend std::ostream& operator<<(std::ostream& out, CyclicDoublyLinkedList& list);
    friend std::ostream& reversePrint(std::ostream& out, CyclicDoublyLinkedList& list);

    friend class FibonacciHeap;
    friend class NBNode;
};

std::ostream& operator<<(std::ostream& out, CyclicDoublyLinkedList& list)
{
    out << "{ ";
    if (!list.isEmpty())
    {
        NBNode* temp{ list.get_head() };
        out << *temp;
        while(temp->getNextSibling() != list.get_head())
        {
            temp = temp->getNextSibling();
            out << ", " << *temp;
        } 
    }
    out << " }\n";
    return out;
}

std::ostream& reversePrint(std::ostream& out, CyclicDoublyLinkedList& list)
{
    out << "{ ";
    if (!list.isEmpty())
    {
        NBNode* temp{ list.get_head()->getPrevSibling() };
        out << *temp;
        while(temp->getPrevSibling() != list.get_head()->getPrevSibling())
        {
            temp = temp->getPrevSibling();
            out << ", " << *temp;
        } 
    }
    out << " }\n";
    return out;
}


class FibonacciHeap
{
    CyclicDoublyLinkedList m_rootList{ };
    int m_numNodes{ };

    public:
    FibonacciHeap()
    {
        std::cout << "Fibonacci Heap created.\n";
    }

    ~FibonacciHeap()
    {
        std::cout << "Fibonacci Heap destroyed.\n";
    }

    bool isEmpty()
    {
        return m_rootList.isEmpty();
    }

    /*
    Puntero a mínima raíz
    Costo O(1)
    */
    NBNode* getMinRoot()
    {
        return m_rootList.get_head();
    }

    int getNumNodes()
    {
        return m_numNodes;
    }

    /*
    Costo O(1) amortizado
    */
    int insertNode(NBNode* newNode)
    {
        if(getMinRoot() == nullptr || newNode->getKey() < getMinRoot()->getDegree())
        {
            m_rootList.insertFront(newNode);
        }
        else
        {
            m_rootList.insertBack(newNode);
        }
        m_numNodes += 1;
        return 0;
    }

    /*
    Concatena root lists, haciendo cambios de punteros
    Coste: O(1)
    */
    int mergeFibHeap(FibonacciHeap& aFibHeap)
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

    NBNode* extractMinimum()
    {
        NBNode* extracted{ m_rootList.popFront() };
        if(extracted != nullptr)
        {
            FibonacciHeap temp{ };
            temp.m_rootList.m_head = extracted->getChild();
            mergeFibHeap(temp);


            m_numNodes -= 1;
        }
    }

    int consolidate()
    {
        int degreeSize{ std::floor(std::log2(m_numNodes)) };
        std::vector<NBNode*> degreeList(degreeSize, nullptr);
        NBNode* actual{ m_rootList.get_head() };
        while(actual->getNextSibling() != m_rootList.get_head())
        {
            int degree{ actual->getDegree() };
            if(degreeList[degree] != nullptr)
            {
                NBNode* newTree;
                if( degreeList[degree]->getKey() < actual->getKey())
                {
                    degreeList[degree]->insertChildFront(actual);
                    newTree = degreeList[degree];
                }
                else
                {
                    actual->insertChildFront(degreeList[degree]);
                    newTree = actual;
                }
                degreeList[degree+1] = newTree;
            }
            else 
            {
                degreeList[degree] = actual;
            }
            actual = actual->getNextSibling();
        }
    }

};

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

    return 0;
}
