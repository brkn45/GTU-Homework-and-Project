 #include "GTUSet.h"
 #include "MyException.h"
namespace GTU{ 
 template<class T>
GTUSet<T>::GTUSet():GTUSet<T>(10){
        //constructor delegation
}
template<class T>
GTUSet<T>::GTUSet(int cap) {
    if (cap>1500 || cap<0)
    {
        //throw MyException("Your capacity can not be grater than 1500 or less than 0");
    }
    else
    {
        capacity=cap;
        sizeSet=0;
        //allocate memory for shared pointer
        sptr = shared_ptr<T[]>(new T[cap]); 
    }
    
}
template<class T>
GTUSet<T>::GTUSet(GTUSet<T>&& prm) { // move constructer
        this->capacity=prm.capacity;
        sizeSet=prm.sizeSet;
        sptr = prm.sptr;
        prm.sptr = nullptr;    
}
template<class T>
GTUSet<T> & GTUSet<T>::operator=(GTUSet<T>&& prm){
    sptr = prm.sptr;
    this.sizeSet = prm.sizeSet;
    capacity = prm.capacity;
    return *this;
}
template<class T>
GTUSet<T>::GTUSet(const GTUSet<T> & prm){
    this = prm;
}
template<class T>
GTUSet<T> & GTUSet<T>::operator=(const GTUSet<T>& prm){ //  asigment operator overloading
    sptr = shared_ptr<T[]>(new T[prm.capacity]);
    for(int i=0;i<prm.capacity;i++){
        sptr[i] = prm.sptr[i];
    }
    capacity = prm.capacity;
    sizeSet = prm.sizeSet;
}
template<class T>
typename Iterable<T>::GTUIterator GTUSet<T>::insert(const T& data){
    bool is_in=false;
    int index=-1;
    for (int i = 0; i < sizeSet ; i++)
    {
        if (sptr[i]==data)
        {
            is_in=true;
            index=i;
        }
    }
    if(!is_in){
        if(capacity > sizeSet){
            
            sptr[sizeSet] =data;
            sizeSet++;
        }
        else{
            if (capacity>1500){
                    throw MyException("Your set capacity is full, you cannot insert a new element to the set.");
            }
            else{
                resize(1+sizeSet*2);
                sptr[sizeSet] = data;
                sizeSet++;
            }
        }
    }
    typename Iterable<T>::GTUIterator tmp(&sptr[sizeSet-1]);
    return tmp;
}
template<class T>
void GTUSet<T>::resize(int num){
    if(capacity < num){
        capacity = num;
        shared_ptr<T[]> tmptr = shared_ptr<T[]>(new T[capacity]);
        for(int i=0; i< sizeSet;i++){
            tmptr[i] =sptr[i];
        }
        sptr= tmptr;
        cout<<"capacity: "<<capacity<<endl;
    }

}
template<class T>
bool GTUSet<T>::empty(){
    if (sizeSet==0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
template<class T>
int GTUSet<T>::size(){
    return sizeSet;
}
template<class T>
void GTUSet<T>::clear(){
    sptr=nullptr;
    sizeSet=0;
    capacity=0;
}
template<class T>
typename Iterable<T>::GTUIterator GTUSet<T>::begin(){
    
    typename Iterable<T>::GTUIterator tmp(&sptr[0]);
    return tmp;
}

template<class T>
typename Iterable<T>::GTUIterator GTUSet<T>::end(){
    typename Iterable<T>::GTUIterator tmp(&sptr[size()]);
    return tmp;
}
template<class T>
const typename Iterable<T>::GTUIteratorConst GTUSet<T>::cbegin(){
    
    typename Iterable<T>::GTUIteratorConst tmp(&sptr[0]);
    return tmp;
}

template<class T>
const typename Iterable<T>::GTUIteratorConst GTUSet<T>::cend(){
    
    typename Iterable<T>::GTUIteratorConst tmp(&sptr[size()]);
    return tmp;
}  
template<class T>
typename Iterable<T>::GTUIterator GTUSet<T>::insert(T&& data){
    return insert(data);
}  

template<class T>
bool GTUSet<T>::erase(typename Iterable<T>::GTUIterator & data){
    bool is_in=false;
    int index=-1;
    for (int i = 0; i < sizeSet ; i++)
    {
        if (sptr[i]==*data)
        {
            is_in=true;
            index=i;
        }
    }
    if(is_in){
        
        int count =0;
        for(int i=0;i<sizeSet;i++){
            if(index == i){
                sptr[count] = sptr[i];
                
            }
            else{
                sptr[count] = sptr[i];
                count++;
            }
        }
        
        sizeSet--;
        return true;
    }
    return false;
}

template<class T>
bool GTUSet<T>::deleteElement(const T & value ){
    bool is_in=false;
    int index=-1;
    for (int i = 0; i < sizeSet ; i++)
    {
        if (sptr[i]==value)
        {
            is_in=true;
            index=i;
        }
    }
    if(is_in){
        
        int count =0;
        for(int i=0;i<sizeSet;i++){
            if(index == i){
                sptr[count] = sptr[i];
                
            }
            else{
                sptr[count] = sptr[i];
                count++;
            }
        }
        
        sizeSet--;
        return true;
    }
    return false;
}
template<class T>
int  GTUSet<T>::search(const T & value) const{ // if return -1 do not find other finded
    bool is_in=false;
    int index=-1;
    for (int i = 0; i < sizeSet ; i++)
    {
        if (sptr[i]==value)
        {
            is_in=true;
            index=i;
        }
    }
    return index;
}
template<class T>
GTUSet<T> GTUSet<T>::intersect(const GTUSet<T> & data)const{
    GTUSet<T> tmp;
    for(int i=0;i<sizeSet;i++){
        for(int k=0; k < data.sizeSet;k++){
            if(sptr[i] == data.sptr[k]){
                tmp.insert(sptr[i]);
            }
        }
    }
    return tmp;
}
template<class T>
GTUSet<T> GTUSet<T>::unionSet(const GTUSet<T> & data)const{
    GTUSet<T> tmp;
    for(int i=0;i<sizeSet;i++){
        tmp.insert(sptr[i]);
    }
    for(int i=0;i<data.sizeSet;i++){
        tmp.insert(data.sptr[i]);
    }
    return tmp;
}
template<class T>
int GTUSet<T>::max_size(){
    return 1500;
}
}