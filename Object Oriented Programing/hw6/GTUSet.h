#ifndef GTU_SET
#define GTU_SET
#include <iostream>
#include <memory>
#include <string>
#include "Iterable.h"
using namespace std;
namespace GTU{
    template<class T>
    class GTUSet : public Iterable<T>{
        public:
            GTUSet();
            GTUSet(int cap);
            GTUSet(GTUSet&& prm);
            GTUSet(const GTUSet& prm);
            GTUSet & operator=(const GTUSet& prm);
            GTUSet & operator=(GTUSet&& prm);
            typename Iterable<T>::GTUIterator insert(T&& data);
            typename Iterable<T>::GTUIterator insert(const T& data);
            bool empty() override;
            int size() override;
            void clear() override;
            typename Iterable<T>::GTUIterator begin() override;
            typename Iterable<T>::GTUIterator end() override;
            const typename Iterable<T>::GTUIteratorConst cbegin() override;
            const typename Iterable<T>::GTUIteratorConst cend() override;
            bool erase(typename Iterable<T>::GTUIterator & value)override;
            void resize(int num);
            bool deleteElement(const T & value);
            int search(const T & value) const;
            int max_size();
            GTUSet<T> intersect(const GTUSet<T> & data)const;
            GTUSet<T> unionSet(const GTUSet<T> & data)const;
        private:
            int sizeSet;
            int capacity;
            shared_ptr<T[]> sptr; 
    };
}    
#endif