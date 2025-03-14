#include "GTUArray.h"
#include "MyException.h"
namespace GTU{ // GTUArray class implementation
template<class T,int S>
GTUArray<T,S>::GTUArray(){
        if (S>1500 || S<0)
    {
        throw MyException("Your capacity can not be grater than 1500 or less than 0");
    }
    else{
        capacity=S;
        sizeArray=S;
        //allocate memory for shared pointer
        sptr = shared_ptr<T[]>(new T[capacity]);
    }
         
}
template<class T,int S>
GTUArray<T,S>::GTUArray(GTUArray&& prm) {
    if (S>1500 || S<0)
    {
        throw MyException("Your capacity can not be grater than 1500 or less than 0");
    }
    else
    {
        this.capacity=prm.capacity;
        sizeArray=prm.sizeArray;
        //allocate memory for shared pointer
        sptr = prm.sptr;
        prm.sptr =nullptr;
    }
    
}
template<class T,int S>
GTUArray<T,S> & GTUArray<T,S>::operator=(GTUArray&& prm){
    sptr = prm.sptr;
    this.sizeArray = prm.sizeArray;
    capacity = prm.capacity;
    return *this;
}
template<class T,int S>
GTUArray<T,S>::GTUArray(const GTUArray & prm){
    this = prm;
}
template<class T,int S>
GTUArray<T,S> & GTUArray<T,S>::operator=(const GTUArray<T,S>& prm){ // 
    sptr = shared_ptr<T[]>(new T[prm.capacity]);
    for(int i=0;i<prm.capacity;i++){
        sptr[i] = prm.sptr[i];
    }
    capacity = prm.capacity;
    sizeArray = prm.sizeArray;
}
template<class T,int S>
bool GTUArray<T,S>::empty(){
    return sizeArray == 0;
}
template<class T,int S>
T& GTUArray<T,S>::operator[](int index){
    if(sizeArray > index && index > -1){
        return sptr[index];
    }
    else{
        throw MyException("index size wrong range");
        return sptr[0];
    }
    
}
template<class T,int S>
T& GTUArray<T,S>::at(int index){
    if(sizeArray > index && index > -1){
        return sptr[index];
    }
    else{
        throw MyException("index size wrong range");
        return sptr[0];
    }
}
template<class T,int S>
T& GTUArray<T,S>::front(){
    return sptr[0];
}
template<class T,int S>
T& GTUArray<T,S>::back(){
    return sptr[size()-1];
}
template<class T,int S>
T* GTUArray<T,S>::data(){
    return &sptr[0];
}
template<class T,int S>
int GTUArray<T,S>::size(){
    return sizeArray;
}
template<class T,int S>
int GTUArray<T,S>::max_size(){
    return S;
}
template<class T,int S>
void GTUArray<T,S>::fill(const T& value){
    for(int i=0;i<sizeArray;i++){
        sptr[i] = value;
    }
}
template<class T,int S>
void GTUArray<T,S>::swap(GTUArray & other){
    GTUArray<T,S> tmp;
    tmp= other;
    other =this;
    this = tmp;

}
template<class T,int S>
typename Iterable<T>::GTUIterator GTUArray<T,S>::begin(){
    
    typename Iterable<T>::GTUIterator tmp(&sptr[0]);
    return tmp;
}
template<class T,int S>
typename Iterable<T>::GTUIterator GTUArray<T,S>::end(){
    typename Iterable<T>::GTUIterator tmp(&sptr[size()]);
    return tmp;
}
template<class T,int S>
const typename Iterable<T>::GTUIteratorConst GTUArray<T,S>::cbegin(){
    
    typename Iterable<T>::GTUIteratorConst tmp(&sptr[0]);
    return tmp;
}

template<class T,int S>
const typename Iterable<T>::GTUIteratorConst GTUArray<T,S>::cend(){
    
    typename Iterable<T>::GTUIteratorConst tmp(&sptr[size()]);
    return tmp;
}    
template<class T,int S>
bool GTUArray<T,S>::erase(typename Iterable<T>::GTUIterator & data){
    bool is_in=false;
    int index=-1;
    for (int i = 0; i < sizeArray ; i++)
    {
        if (sptr[i]==*data)
        {
            is_in=true;
            index=i;
        }
    }
    if(is_in){
        
        sptr[index] = 0;
    }
    return false;
}
template<class T,int S>
void GTUArray<T,S>::clear(){
    for(int i=0;i<sizeArray;i++){
        sptr[i] =0;
    }
}
}