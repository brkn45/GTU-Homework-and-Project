#ifndef GTU_Vector
#define GTU_Vector
#include <iostream>
#include <memory>
#include <string>
#include "Iterable.h"

using namespace std;
namespace GTU{
    template<class T>
    class GTUVector: public Iterable<T>{
        
        public:
            
            GTUVector();
            GTUVector(GTUVector&& prm);
            GTUVector & operator=(GTUVector&& prm);
            GTUVector(const GTUVector & prm);
            GTUVector & operator=(const GTUVector& prm);
            void push_back(T&& data);
            void push_back(const T& data);
            void pop_back();
            T operator[](int index);
            void resize(int num);
            bool empty() override;
            int size() override;
            void clear() override;
            const typename Iterable<T>::GTUIteratorConst cbegin() override;
            const typename Iterable<T>::GTUIteratorConst cend() override;
            typename Iterable<T>::GTUIterator begin() override;
            typename Iterable<T>::GTUIterator end() override;
            bool erase(typename Iterable<T>::GTUIterator &value)override;
            shared_ptr<T[]> sptr;
        private:
            int sizeVector;
            int capacity;
            //shared_ptr<T[]> sptr;
            
    };
}
#endif