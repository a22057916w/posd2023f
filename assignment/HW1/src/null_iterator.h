#if !defined(NULL_ITERATOR_H)
#define NULL_ITERATOR_H

class NullIterator : public Iterator {
    void first() override {};
    Node * currentItem() const override { return nullptr; };
    void next() override {};
    bool isDone() const override { return true; };
};

#endif // NULL_ITERATOR_H
