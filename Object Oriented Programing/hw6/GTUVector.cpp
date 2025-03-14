#include "GTUVector.h"
#include "MyException.h"
namespace GTU{
template<class T>
GTUVector<T>::GTUVector(){ // vector class implementation
    sizeVector=0;
    capacity =5;
    sptr =  shared_ptr<T[]>(new T[capacity]);
    
}
template<class T>
GTUVector<T>::GTUVector( GTUVector<T>&& prm){
    this->capacity=prm.capacity;
    sizeVector=prm.sizeVector;
    sptr = prm.sptr;
    prm.sptr = nullptr; 
}
template<class T>
GTUVector<T> & GTUVector<T>::operator=(GTUVector<T>&& prm){
    this->capacity=prm.capacity;
        sizeVector=prm.sizeVector;
        sptr = prm.sptr;
        return *this; 
}
template<class T>
GTUVector<T>::GTUVector(const GTUVector<T> & prm){
    this = prm;
}
template<class T>
GTUVector<T> & GTUVector<T>::operator=(const GTUVector<T>& prm){ // 
    sptr = shared_ptr<T[]>(new T[prm.capacity]);
    for(int i=0;i<prm.sizeVector;i++){
        sptr[i] = prm.sptr[i];
    }
    capacity = prm.capacity;
    sizeVector = prm.sizeVector;
}
template<class T>
void GTUVector<T>::clear(){
    sptr=nullptr;
    sizeVector=0;
    capacity=0;
}

template<class T>
void GTUVector<T>::push_back(const T& data){
    if(sizeVector == capacity){
        resize(1+capacity*2);
    }
    sptr[sizeVector] =data;
    sizeVector++;
}
template<class T>
void GTUVector<T>::pop_back(){
    if(sizeVector != 0){
        capacity--;
        shared_ptr<T[]> tmp = shared_ptr<T[]>(new T[capacity]);
        sizeVector--;
        T rtValue = sptr[sizeVector+1];
        for(int i=0;i < sizeVector;i++){
            tmp[i] = sptr[i];
        }
        sptr =tmp;
        
    }
   
    
    
}
template<class T>
void GTUVector<T>::push_back(T&& data){
    if(sizeVector == capacity){
        resize(1+capacity*2);
    }
    sptr[sizeVector] =data;
    sizeVector++;
}
template<class T>
bool GTUVector<T>::empty(){
    return sizeVector == 0;
}
template<class T>
int GTUVector<T>::size(){
    return sizeVector;
}
/*
template<class T>
void GTUVector<T>::insert(const T&& data){
    if(sizeVector==capacity){
        resizeVector(capacity*2);
    }
    shared_ptr<T[]> tmp = shared_ptr<T[]>(new T[sizeVector+1]);
}*/
template<class T>
void GTUVector<T>::resize(int num){
    if(capacity < num){
        capacity = num;
        shared_ptr<T[]> tmptr = shared_ptr<T[]>(new T[capacity]);
        for(int i=0; i< sizeVector;i++){
            tmptr[i] =sptr[i];
        }
        sptr= tmptr;
        cout<<"capacity: "<<capacity<<endl;
    }

}
template<class T>
T GTUVector<T>::operator[](int index){
    if(index < sizeVector){
        return sptr[index];
    }
    else{
        return sptr[0];
    }
}

template<class T>
typename Iterable<T>::GTUIterator GTUVector<T>::begin(){
    
    typename Iterable<T>::GTUIterator tmp(&sptr[0]);
    return tmp;
}

template<class T>
typename Iterable<T>::GTUIterator GTUVector<T>::end(){
    
    typename Iterable<T>::GTUIterator tmp(&sptr[size()]);
    return tmp;
}
template<class T>
const typename Iterable<T>::GTUIteratorConst GTUVector<T>::cbegin(){
    
    typename Iterable<T>::GTUIteratorConst tmp(&sptr[0]);
    return tmp;
}

template<class T>
const typename Iterable<T>::GTUIteratorConst GTUVector<T>::cend(){
    
    typename Iterable<T>::GTUIteratorConst tmp(&sptr[size()]);
    return tmp;
}
template<class T>
bool GTUVector<T>::erase(typename Iterable<T>::GTUIterator & data){
    bool is_in=false;
    int index=-1;
    for (int i = 0; i < sizeVector ; i++)
    {
        if (sptr[i]==*data)
        {
            is_in=true;
            index=i;
        }
    }
    if(is_in){
        shared_ptr<T[]> tmptr = shared_ptr<T[]>(new T[capacity]);
        int count =0;
        for(int i=0;i<sizeVector;i++){
            if(index != i){
                tmptr[count] = sptr[i];
                count++;
            }
        }
        sptr = tmptr;
        sizeVector--;
        return true;
    }
    return false;
}

}