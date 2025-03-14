#ifndef Base_Iterable
#define Base_Iterable

#include <iostream>
#include <memory>
#include "BaseIterator.h"
using namespace std;
namespace GTU{
    template<class T>
    class Iterable{ // base ıterable class
        
        public :
            class GTUIterator : public BaseIterator<T>{
                
                public:
                GTUIterator() {};
                GTUIterator( T * ptr){
                    arr= ptr;
                
                    
                };
                T& operator*()const;
                T* operator->() const;
                BaseIterator<T> &operator++(int ignorme) override;
                BaseIterator<T> & operator++() override; 
                BaseIterator<T> &operator--(int ignorme) override;
                BaseIterator<T> & operator--() override;
                bool operator==(const BaseIterator<T> &other) const override;
                BaseIterator<T>& operator=(const BaseIterator<T> &other) override;
                T * getArr() const override;
                T * arr;
                
                private:
                     
                
            };
            
            class GTUIteratorConst {
                
                public:
                GTUIteratorConst() {};
                GTUIteratorConst( T * ptr){
                    arr= ptr;
                
                    
                };
                const T& operator*()const;
                const T* operator->() const;
                const GTUIteratorConst &operator++(int ignorme);
                const GTUIteratorConst & operator++(); 
                const GTUIteratorConst &operator--(int ignorme);
                const GTUIteratorConst & operator--();
                bool operator==(const GTUIteratorConst &other) const ;
                const GTUIteratorConst& operator=(const GTUIteratorConst &other);
                const T * getArr() const;
                T * arr;
                
                private:
                     
                
            };
            virtual bool empty() = 0;
            virtual int size() = 0;
            virtual bool erase(GTUIterator& value) = 0;
            virtual void clear() = 0;
            virtual GTUIterator begin() = 0;
            virtual GTUIterator end() = 0;
            virtual const GTUIteratorConst cbegin() = 0;
            virtual const GTUIteratorConst cend() = 0;

    };



}

#endif