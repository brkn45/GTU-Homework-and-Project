#include "Iterable.h"
#include "BaseIterator.h"
namespace GTU{  //  none const  iterator
template<class T>
BaseIterator<T> & Iterable<T>::GTUIterator::operator++(){
    arr = arr+1;
    
    return  *this;
}

template<class T>
BaseIterator<T> & Iterable<T>::GTUIterator::operator++(int ignore){
    
    arr = arr+1;
    
    return *this;
}

template<class T>
BaseIterator<T> & Iterable<T>::GTUIterator::operator--(){ 
    arr = arr-1;
    
    return  *this;
}

template<class T>
BaseIterator<T> & Iterable<T>::GTUIterator::operator--(int ignore){
    
    arr = arr-1;
    
    return *this;
}
template<class T>
bool Iterable<T>::GTUIterator::operator==(const BaseIterator<T> &other) const {
    return this->getArr()  == other.getArr() ;
}
template<class T>
T * Iterable<T>::GTUIterator::getArr()const{
    return arr;
}
template<class T>
T& Iterable<T>::GTUIterator::operator*()const{
    return *arr;
}
template<class T>
T* Iterable<T>::GTUIterator::operator->() const{
    return arr;
}
template<class T>
BaseIterator<T>& Iterable<T>::GTUIterator::operator=(const BaseIterator<T> &other){
    this->arr = other.getArr();
    return *this;
}

}