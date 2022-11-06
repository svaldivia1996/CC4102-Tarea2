#include "cyclic_doubly_linked_list.h"

CyclicDoublyLinkedList::CyclicDoublyLinkedList()
{
    std::cout << "CyclicDoublyLinkedList created.\n";
}

CyclicDoublyLinkedList::~CyclicDoublyLinkedList()
{
    std::cout << "CyclicDoublyLinkedList destroyed.\n";
}

NBNode* CyclicDoublyLinkedList::get_head()
{
    return m_head;
}

NBNode* CyclicDoublyLinkedList::get_tail()
{
    return m_head->getPrevSibling();
}

bool CyclicDoublyLinkedList::isEmpty()
{
    return m_head == nullptr;
}

/*
Insert at back of list.
*/
int CyclicDoublyLinkedList::insertBack(NBNode* newNode)
{
    if(newNode == nullptr)
    {
        return 1;
    }

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
int CyclicDoublyLinkedList::insertFront(NBNode* newNode)
{
    insertBack(newNode);
    m_head = newNode;
    return 0;
}

NBNode* CyclicDoublyLinkedList::popFront()
{
    if(m_head == nullptr)
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

NBNode* CyclicDoublyLinkedList::popBack()
{
    m_head = m_head->getPrevSibling();
    return popFront();
}

int CyclicDoublyLinkedList::removeNode(NBNode* removed)
{
    if (removed == get_head())
    {
        popFront();
    }  
    else
    {
        NBNode* prevSibling{ removed->getPrevSibling()};
        NBNode* nextSibling{ removed->getNextSibling()};
        prevSibling->setNextSibling(nextSibling);
        nextSibling->setPrevSibling(prevSibling);
    }
    
    removed->setNextSibling(nullptr);
    removed->setPrevSibling(nullptr);
    return 0;

}

int CyclicDoublyLinkedList::emptyList()
{
    m_head = nullptr;
    return 0;
}

NBNode* CyclicDoublyLinkedList::removeParent()
{
    NBNode* actual{ get_head()};
    if(actual != nullptr)
    {
        NBNode* parent{ actual->getParent() };
        do
        {
            actual->setParent(nullptr);
            actual = actual->getNextSibling();
        } while(actual != get_head() );
        parent->getChildrenList().emptyList();

        return parent;
    }
    else
    {
        return nullptr;
    }
}

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
