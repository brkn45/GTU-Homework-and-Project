#include "GTUVector.h"
#include "GTUVector.cpp"
#include "Iterator.cpp"
#include "GTUSet.h"
#include "GTUSet.cpp"
#include "GTUArray.h"
#include "GTUArray.cpp"
#include "GTUIteratorConst.cpp"
#include <algorithm>
#include <vector>
#include <exception>
#include "MyException.h"
#include "MyException.cpp"
using namespace std;
using namespace GTU;
void vectorTest();
void setTest();
void arrayTest();
int main(){
    try{
        vectorTest();    //  GTUVector test all fonction and iterator
    }
    catch(MyException &e){
        cout<<"exception GTUVector test: "<< e.getExceptionDetails();
    }
    try{
        setTest();  //  GTUSet test all fonction and iterator
    }
    catch(MyException &e){
        cout<<"exception GTUSet test: "<< e.getExceptionDetails();
    }
    try{
        arrayTest(); // GTUArray test all fonction and iterator
    }
    catch(MyException &e){
        cout<<"exception GTUArray test: "<< e.getExceptionDetails();
    }
    
      
    
    
    
    
    
    
    return 0;
}

void vectorTest(){
    GTUVector<int> tmp;
    cout<<"empty"<<tmp.empty()<<endl;
    tmp.push_back(10);
    tmp.push_back(20);
    tmp.push_back(30);
    tmp.push_back(40);
    tmp.push_back(10);
    tmp.push_back(20);
    tmp.push_back(30);
    tmp.push_back(40);
    tmp.push_back(10);
    tmp.push_back(20);
    tmp.push_back(30);
    tmp.push_back(40);
    tmp.push_back(10);
    tmp.push_back(20);
    
    tmp.push_back(33);
    tmp.push_back(40);
    tmp.push_back(10);
    tmp.push_back(20);
    tmp.push_back(30);
    tmp.push_back(40);
    for(int i=0;i<4;i++){
        cout<<tmp[i]<<endl;
    }
    cout<<"empty: "<<tmp.empty()<<endl;
    cout<<"size:  "<<tmp.size()<<endl;
    tmp.clear();   // delete all element
    
    int num=55;
    tmp.push_back(num);
    cout<<"num: "<<tmp[tmp.size()-1]<<endl;

    GTUVector<string> str; // testted another type
    str.push_back("berkan");
    str.push_back("akin");
    cout<<str[0]<<" "<<str[1]<<endl;

   tmp.pop_back();
   tmp.pop_back();
   

    tmp.push_back(20);
    tmp.push_back(33);
    tmp.push_back(40);
    tmp.push_back(20);
    tmp.push_back(30);
    tmp.push_back(40);
    cout<<"empty: "<<tmp.empty()<<endl; // test emty and size function
    cout<<"size:  "<<tmp.size()<<endl;

    GTUVector<int>::GTUIterator p =  tmp.begin();
    cout<<"p: "<<p.arr[0]<<endl;
    cout<<"p: "<<(p.arr++)[0]<<endl;

   GTUVector<int>::GTUIterator k=(p.arr++);
   k.arr++;
   cout<<"k: "<<k.arr[0]<<endl; 
    k.arr--;
    cout<<"k: "<<k.arr[0]<<endl;
    --k.arr; 
    cout<<"k: "<<k.arr[0]<<endl; 
   cout<<"bool: "<<(k == p)<<endl;
    
    cout<<"* operator overloading: "<<(*k)<<endl;
    //cout<<"-> operator overloading: "<<(->k)<<endl;
    *p = *k;
    cout<<"= operator overloading k: "<< (*k)<<endl;
    cout<<"= operator overloading p: "<< (*p)<<endl;
    GTUVector<int>::GTUIteratorConst vbegin = tmp.cbegin(); // const iterator
    GTUVector<int>::GTUIteratorConst vend = tmp.cend();
    cout<<"vector const iterator test"<<endl;
    for(;*vbegin != *vend;vbegin++  ){
        cout<<"const iterator: "<< *vbegin<<endl;
    }

    cout<<"STL find() test"<<endl;
    auto result3 =find(&(*tmp.cbegin()),&(*tmp.cend()),33); // return iterator address
    cout<<"result: "<<*result3<<endl;


    cout<<"GTUVector For_each test: "<< endl;
    auto printVec = [](const int& n) { std::cout << " " << n; };
    std::for_each(&(*tmp.cbegin()),&(*tmp.cend()) , printVec);
    cout<<endl;


    cout<<"Sort Test: "<<endl;
    sort(&(*tmp.begin()),&(*tmp.end()));
    std::for_each(&(*tmp.begin()),&(*tmp.end()) , printVec);
    cout<<endl;
}
void setTest(){  // tested Set all fonction
    GTUSet<int> set1;
    int num1 =5,num2=10 ,num3=30;
    set1.insert(num1);
    set1.insert(45);

    cout<<"size: "<< set1.size()<<endl;
    cout<<"is empty: "<<set1.empty()<<endl;
    set1.clear();
    cout<<"is empty after clear: "<<set1.empty()<<endl;
    
    set1.insert(num1);
    set1.insert(45);
    set1.insert(num2);
    set1.insert(num3);

    GTUSet<int>::GTUIterator setBegin = set1.begin(); // iterator test
    GTUSet<int>::GTUIterator setEnd = set1.end(); 

    for(;*setBegin !=*setEnd;setBegin++){
        cout<<"begin to end: "<< *setBegin<<endl;
    }
    
    
   GTUSet<int>::GTUIterator setBeg1 = set1.begin();
    
    set1.erase(setBeg1);
    //set1.erase(setBegin);
    //delete 5
    GTUSet<int>::GTUIterator setBeg2 = set1.begin();
     GTUSet<int>::GTUIterator setEnd1 = set1.end();
    for(;*setBeg2 !=*setEnd1;setBeg2++){
        cout<<"Delete: "<< setBeg2.getArr()[0]<<endl;
    }

    GTUSet<int> t1,t2;
    t1.insert(10);
    t1.insert(20);
    t1.insert(30);
    t1.insert(40);
    t1.insert(50);
    t1.insert(60);
    
    t2.insert(5);
    t2.insert(20);
    t2.insert(30);
    t2.insert(40);
    t2.insert(2);
    t2.insert(10);
   
    GTUSet<int>::GTUIteratorConst t2Begin = t2.cbegin(); // const iterator test
    GTUSet<int>::GTUIteratorConst t2End = t2.cend();
    cout<<"stl:find function  test"<<endl;
    vector<int> kk;
    
    auto result1= find(&(*t2Begin),&(*(t2End)),5); //find function test with my iterator
    cout<<"find() result: "<< endl;

    cout<<"For_each test: "<<*result1<< endl;
    auto print = [](const int& n) { std::cout << " " << n; };
    std::for_each(&(*t2Begin),&(*t2End) , print);
    cout<<endl<<endl;
    
    GTUSet<int> t3 = t1.intersect(t2); // intersect function test
    GTUSet<int>::GTUIterator t3Begin = t3.begin();
    GTUSet<int>::GTUIterator t3End = t3.end();
    

    
    for(;*t3Begin !=*t3End;t3Begin++){
        cout<<"İntersect: "<< t3Begin.getArr()[0]<<endl;
    }
    cout<<"Union test"<<endl;
    GTUSet<int> t4 = t1.unionSet(t2);
    GTUSet<int>::GTUIterator t4Begin = t4.begin();
    GTUSet<int>::GTUIterator t4End = t4.end();
    
    for(;*t4Begin !=*t4End;t4Begin++){
        cout<<"union: "<< *t4Begin<<endl;
    }

    GTUSet<int>::GTUIterator t5Begin = t4.begin();
    GTUSet<int>::GTUIterator t5End = t4.end();
    std::sort(&(*t5Begin), &(*t5End));

    for(;*t5Begin !=*t5End;t5Begin++){
        cout<<"sort Test : "<< *t5Begin<<endl;
    }

    cout<<"Const iterator Test for GTUSet"<<endl;

    GTUSet<int>::GTUIteratorConst  cbegin = t4.cbegin();
    GTUSet<int>::GTUIteratorConst cend = t4.cend();
    
    for(;*cbegin !=*cend;cbegin++){
        cout<<"const iterator test: "<< *cbegin<<endl;
    }
}
void arrayTest(){  // array test function
    cout<<"GTUArray test"<<endl;
    GTUArray<int,10> arr1,arr2;
    arr1[0] =5;
    arr1[1] =3;
    arr1[2]= 4;
    arr1[3] =5;
    arr1[4] =6;
    arr1[5]= 7;
    for(int i=0;i<6;i++){
        cout<<"Array "<<i<<": "<<arr1[i]<<endl;
    }
    arr2.fill(5);
    for(int i=0;i<arr2.size();i++){
        cout<<"Array fill function test: "<<i<<": "<<arr2[i]<<endl;
    }
    GTUArray<int,10>::GTUIterator iterArr1b = arr1.begin();
    GTUArray<int,10>::GTUIterator iterArr1e = arr1.end();
    cout<<"traverse on arr1"<<endl;
    for(;*iterArr1b != *iterArr1e;iterArr1b++ ){
        cout<<"iter movement: "<<*iterArr1b<<endl; 
    }
    cout<<"clear arr1"<<endl;
    arr1.clear();
    for(int i=0;i<arr1.size();i++){
        cout<<"clear test: " << arr1[i]<<endl;
    }
    cout<<"Array const iterator Test"<<endl;
    GTUArray<int,10>::GTUIteratorConst arcBegin = arr1.cbegin();
    GTUArray<int,10>::GTUIteratorConst arcEnd = arr1.cend();
    arr1.fill(5);
    cout<<"Array const iterator Test"<<endl;
    for(;*arcBegin != *arcEnd;arcBegin++ ){
        cout<<"const iter: "<<*arcBegin<<endl; 
    }
    cout<<"Find Test"<<endl;
    arr1.clear();
    arr1[0] =5;
    arr1[1] =3;
    arr1[2]= 4;
    arr1[3] =5;
    arr1[4] =6;
    arr1[5]= 7;
    auto arb1 = arr1.begin();
    auto are1= arr1.end(); // find function test
    auto result2 =find(&(*arb1),&(*are1),6); // return iterator address
    cout<<"result: "<<*result2<<endl;
    cout<<"fron() function test: "<<arr1.front()<<endl;
    cout<<"end() function test: "<<arr1.back()<<endl;
    cout<<"For_each test: "<< endl;
    auto printArr = [](const int& n) { std::cout << " " << n; };
    std::for_each(&(*arb1),&(*are1) , printArr);
    cout<<endl;
    cout<<"Sort Test: "<<endl; // sort function test
    sort(&(*arb1),&(*are1));
    std::for_each(&(*arb1),&(*are1) , printArr);
    cout<<endl;
}