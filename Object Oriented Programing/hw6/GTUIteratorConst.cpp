#include "GTUVector.h"
#include "GTUSet.h"
namespace GTU{
template<class T>
const typename Iterable<T>::GTUIteratorConst & Iterable<T>::GTUIteratorConst::operator++(){
    arr = arr+1;
    return  *this;
}

template<class T>
const typename Iterable<T>::GTUIteratorConst & Iterable<T>::GTUIteratorConst::operator++(int ignore){
    arr = arr+1;
    return *this;
}

template<class T>
const  typename Iterable<T>::GTUIteratorConst & Iterable<T>::GTUIteratorConst::operator--(){
    arr = arr-1;
    
    return  *this;
}

template<class T>
const  typename Iterable<T>::GTUIteratorConst & Iterable<T>::GTUIteratorConst::operator--(int ignore){
    
    arr = arr-1;
    
    return *this;
}

template<class T>
bool Iterable<T>::GTUIteratorConst::operator==(const Iterable<T>::GTUIteratorConst &other) const {
    return this->getArr()  == other.getArr() ;
}

template<class T>
const T * Iterable<T>::GTUIteratorConst::getArr()const{
    return arr;
}

template<class T>
const  T& Iterable<T>::GTUIteratorConst::operator*()const{
    return *arr;
}
template<class T>
const  T* Iterable<T>::GTUIteratorConst::operator->() const{
    return arr;
}
template<class T>
const typename Iterable<T>::GTUIteratorConst& Iterable<T>::GTUIteratorConst::operator=(const Iterable<T>::GTUIteratorConst &other){
    this->arr = other.getArr();
    return *this;
}
}