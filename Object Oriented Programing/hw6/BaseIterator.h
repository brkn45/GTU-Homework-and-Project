#ifndef Base_Iterator
#define Base_Iterator
#include <memory>
#include <iostream>
namespace GTU{
using namespace std;
template<class T>
class BaseIterator{ // none const iterator
    protected:
       
    public:
        
        virtual T& operator*()const =0;
        virtual T* operator->() const =0;
        virtual BaseIterator & operator++(int ignorme) =0;
        virtual BaseIterator & operator++() =0;
        virtual BaseIterator &operator--() =0;
        virtual BaseIterator &operator--(int ignorme) =0;
        virtual bool operator==(const BaseIterator &other) const =0;
        virtual BaseIterator& operator=(const BaseIterator &other) =0;
        virtual T * getArr() const =0;
        
};
}
#endif