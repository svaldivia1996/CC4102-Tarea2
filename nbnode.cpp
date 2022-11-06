#include "nbnode.h"


NBNode::NBNode(int key, int degree, NBNode* parent, NBNode* child, NBNode* next, NBNode* prev):
    m_key{ key }, m_degree{ degree }, m_parent{ parent }, m_next{ next }, m_prev{ prev }
{
    m_childList =  new CyclicDoublyLinkedList();
    m_childList->insertFront(child);
    std::cout << "NBNode " << m_key << ", " << m_degree << " created.\n";
}

NBNode::NBNode(int key):
    NBNode(key, 0, nullptr, nullptr, nullptr, nullptr)
{}

NBNode::~NBNode()
{
    std::cout << "NBNode " << m_key << ", " << m_degree << " destroyed.\n";
    delete m_childList;
}

void NBNode::setParent(NBNode* parent)
{
    m_parent = parent;
}

void NBNode::setChild(NBNode* child)
{
    if(m_childList->isEmpty())
    {
        m_childList->insertFront(child);
        return;
    }
    m_childList->m_head = child;
}

void NBNode::setNextSibling(NBNode* next)
{
    m_next = next;
}

void NBNode::setPrevSibling(NBNode* prev)
{
    m_prev = prev;
}

void NBNode::setKey(int newKey)
{
    m_key = newKey;
}

NBNode* NBNode::getChild()
{
    return m_childList->get_head();
}

CyclicDoublyLinkedList& NBNode::getChildrenList()
{
    return *m_childList;
}

int NBNode::insertChildFront(NBNode* newChild)
{
    m_childList->insertFront(newChild);
    incrementDegree();
    newChild->setParent(this);
    newChild->wasPruned = false;

    return 0;
}

int NBNode::cutFromParent()
{
    if(getParent() != nullptr)
    {
        getParent()->decrementDegree();
        if(getParent()->getParent() != nullptr)
        {
            getParent()->mark();
        }
        getParent()->getChildrenList().removeNode(this);
        setParent(nullptr);
        return 0;
    }
    return 1;
}


NBNode* NBNode::getNextSibling()
{
    return m_next;
}

NBNode* NBNode::getPrevSibling()
{
    return m_prev;
}

NBNode* NBNode::getParent()
{
    return m_parent;
}

int NBNode::getKey()
{
    return m_key;
}

int NBNode::getDegree()
{
    return m_degree;
}

int NBNode::incrementDegree()
{
    m_degree +=1;
    return 0;
}

int NBNode::decrementDegree()
{
    m_degree -=1;
    return 0;
}

bool NBNode::hasChildren()
{
    return getChild() != nullptr;
}

bool NBNode::isMarked()
{
    return wasPruned;
}

int NBNode::mark()
{
    wasPruned = true;
}

int NBNode::unmark()
{
    wasPruned = false;
}

std::ostream& operator<<(std::ostream& out, NBNode& node)
{
    return out << "( " << node.m_key << ", " << node.m_degree << " )";
}
