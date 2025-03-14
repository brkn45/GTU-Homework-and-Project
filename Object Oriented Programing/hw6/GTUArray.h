#ifndef GTU_ARRAY
#define GTU_ARRAY
#include <iostream>
#include <memory>
#include <string>
#include "Iterable.h"
using namespace std;
namespace GTU{
template<class T,int S>
class GTUArray : public Iterable<T>{ 
    public:
        GTUArray();
        GTUArray(GTUArray&& prm);
        GTUArray & operator=(GTUArray&& prm);
        GTUArray & operator=(const GTUArray& prm);
        GTUArray(const GTUArray & prm);
        int size() override;
        int max_size();
        bool empty() override;
        T& operator[](int index);
        T& at(int index);
        T& front();
        T& back();
        T* data();
        void fill(const T& value);
        void swap(GTUArray & other);
        typename Iterable<T>::GTUIterator begin() override;
        typename Iterable<T>::GTUIterator end() override;
        const typename Iterable<T>::GTUIteratorConst cbegin() override;
        const typename Iterable<T>::GTUIteratorConst cend() override;
        bool erase(typename Iterable<T>::GTUIterator & value)override;
        void clear() override;
    private:
        int sizeArray;
        int capacity;
        shared_ptr<T[]> sptr;

    };
}    
#endif