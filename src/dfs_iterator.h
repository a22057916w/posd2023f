#if !defined(DFS_ITERATOR_H)
#define DFS_ITERATOR_H

class DfsIterator: public Iterator {
public:
    DfsIterator(Node* composite);

    void first();

    Node * currentItem() const;

    void next();
    
    bool isDone() const;
};

class BfsIterator: public Iterator {
public:
    BfsIterator(Node* composite);
    void first();
    Node * currentItem() const;
    void next();
    bool isDone() const;
};

#endif // DFS_ITERATOR_H
