#include "Base.h"

/*
    *if object parameter is wrong, default day and mount zero
*/

int main(){
    // DayofYearSet Object Created
    DayofYearSet::DayofYear test1(2,1);
    DayofYearSet dys1,dys2(5,3),dys3(test1),dys4(4,5);
    DayofYearSet::DayofYear dy1,dy2(10,5),dy3(10,4),dy4(20,30),dy5(4,8),dy6(3,3),dy7(1,7),dy8(15,8);
    ofstream file;
   
    file.open("set.txt");
     file<<"Static Function Live Object Test"<<endl;
    file<<"Live DayofYear Object: "<<DayofYearSet::DayofYear::getLiveobj()<<endl;
    //DayofYearSet object  tested add fonction for dayofyear object parameter
    dys1.add(DayofYearSet::DayofYear(1,2));
    file<<"File dys1"<<endl;
    file<<dys1;
    cout<<dys1;
    dys1.add(DayofYearSet::DayofYear(50,15));
    cout<<dys2;
    file<<"File dys2"<<endl;
    file<<dys2;
     //DayofYearSet object  tested add fonction for dayofyearset object parameter
    cout<<"                 add() Function Test" <<endl;
    file<<"                 add() Function Test"<<endl;
    dys1.add(dys2);
    file<<dys1;
    cout<<"dys1 add fonction for DayofYear Object"<<endl;
    dys1.add(dys3);
    dys1.add(dys4);
    cout<<dys1;
    file<<"dys1 after add object"<<endl;
    file<<dys1<<endl; 
    cout<<"Constructer parameter for vector test"<<endl;
    file<<"Constructer parameter for vector test"<<endl;
    vector<DayofYearSet::DayofYear> vecdy;
    vecdy.push_back(dy1);
    vecdy.push_back(dy2);
    vecdy.push_back(dy3);
    vecdy.push_back(dy4); 
    
    DayofYearSet dys5(vecdy); // dys5 put 3 obje because dy1 and dy4 same thing
    file<<dys5<<endl;
    cout<<"DayofYear vector testing"<<endl;
    cout<<dys5<<endl<<endl;

    
    cout<<"                  Operator== and Operator!=  Overloading Testing"<<endl;
    file<<"                  Operator== and Operator!= Overloading Testing"<<endl;
    DayofYearSet dys6,dys7;
    dys6.add(dy5);
    dys6.add(dy2);

    dys7.add(dy2);
    dys7.add(dy5);
    cout<<"dys7 and dys6 is equal"<<endl;
    file<<"dys7 elements"<<endl;
    file<<dys7;
    file<<"dys6 elements"<<endl;
    file<<dys6;
    if(dys7 == dys6){
        cout<<" operator== result is true"<<endl;
    }
    if(dys7!=dys6){
         cout<<"operator!= result is true"<<endl;
    }
    else{
        cout<<" operator!= result is false"<<endl;
    }
    dys6.add(dy3);
    cout<<"dys7 and dys6 is'not equal"<<endl;
    if(dys7 == dys6){
        cout<<"operator== resultis true"<<endl;
    }
    else{
        cout<<" operator== result is false"<<endl;
    }
    if(dys7!=dys6){
         cout<<"operator!= result is true"<<endl;
    }
    else{
        cout<<" operator!= result is false"<<endl;
    }
    
    cout<<"         Remove() function testing"<<endl;
    file<<"         Remove() function testing"<<endl;
    cout<<"dys6 all elements"<<endl;
    file<<"dys6 all elements"<<endl;
    cout<<dys6<<endl;
    file<<dys6;
    dys6.remove(dy3);
    cout<<dys6;
    dys6.remove(dy2);
    dys6.remove(dy1); // there is'int int dys6 object
    cout<<dys6<<endl;
    file<<"dys6 after remove fuction"<<endl;
    file<<dys6;
    cout<<"            Size Test"<<endl;
    file<<"            Size Test"<<endl;
    
    cout<<"dys6 size: "<<dys6.size()<<endl<<"Put 3 elements"<<endl;
    file<<dys6;
    dys6.add(dy2);
    dys6.add(dy1);
    dys6.add(dy3);
    file<<"Size after add operation "<<endl;
    file<<dys6;
    cout<<"dys6 size:"<<dys6.size()<<endl<<endl;
    
    cout<<"           Operator+ Test"<<endl;
    file<<"           Operator+ Test"<<endl;

    cout<<"dys5 elements"<<endl<<dys5;
    cout<<"dys6 elements"<<dys6;
    file<<"dys5 elements"<<endl<<dys5;
    file<<"dys6 elements"<<dys6;
    cout<<"uniun set"<<endl;
    cout<<dys5+dys6;
    file<<"dys5 + dys6 result"<<endl;
    file<<dys5+dys6;
    dys6.add(dy3);
    cout<<"add elements"<<endl;
    cout<<dys5+dys6;

    cout<<"                    Operator- testing"<<endl;
    file<<"                    Operator- testing"<<endl;
    dys5.add(dy7);
    dys5.add(dy8);
    file<<"dys5 elements"<<endl;
    file<<dys5;
    file<<"dys6 elements"<<endl;
    file<<dys6;
    cout<<"dys5 elements"<<endl<<dys5;
    cout<<"dys6 elements"<<endl<<dys6;

    cout<<"Test 1"<<endl;
    file<<"Test 1"<<endl;
    cout<<dys5- dys6;
    file<<dys5- dys6;
    cout<<"Test 2"<<endl;
    cout<<dys6-dys5;
    file<<"Test 2"<<endl;
    file<<dys6-dys5;
    
    cout<<"                    Operator^ Testing"<<endl;
    file<<"                    Operator^ Testing"<<endl;
    cout<<"dys5 elements"<<endl<<dys5;
    cout<<"dys6 elements"<<endl<<dys6;
    file<<"dys5 elements"<<endl<<dys5;
    file<<"dys6 elements"<<endl<<dys6;
    cout<<"Test 1"<<endl;
    cout<<(dys6^dys5);
    file<<"Test 1"<<endl;
    file<<(dys6^dys5);
    cout<<"dys7 elements"<<endl<<dys7;
    cout<<"dys6 elements"<<endl<<dys6;
    cout<<"Test 2"<<endl;
    cout<<(dys7^dys6);

    file<<"dys7 elements"<<endl<<dys7;
    file<<"dys6 elements"<<endl<<dys6;
    file<<"Test 2"<<endl;
    file<<(dys7^dys6);

    cout<<"                 Operator! Test"<<endl;
    cout<<"Test1"<<endl;

    cout<<(!dys6)<<endl;

    file<<"                 Operator! Test"<<endl;
    file<<"Test1"<<endl;

    file<<(!dys6)<<endl;

    cout<<"                    Operator[] Test"<<endl;
    cout<<"     Test 1"<<endl;
    cout<<"Day: " <<(dys6[0].getDay())<<endl;
    cout<<"Mount: " <<(dys6[0].getMount())<<endl;
    cout<<"     Test 2"<<endl;
    cout<<"Day: " <<(dys6[1].getDay())<<endl;
    cout<<"Mount: " <<(dys6[1].getMount())<<endl;
    cout<<"     Test 3"<<endl;
    cout<<"Day: " <<(dys6[2].getDay())<<endl;
    cout<<"Mount: " <<(dys6[2].getMount())<<endl;


    file<<"                    Operator[] Test"<<endl;
    file<<"     Test 1"<<endl;
    file<<"Day: " <<(dys6[0].getDay())<<endl;
    file<<"Mount: " <<(dys6[0].getMount())<<endl;
    file<<"     Test 2"<<endl;
    file<<"Day: " <<(dys6[1].getDay())<<endl;
    file<<"Mount: " <<(dys6[1].getMount())<<endl;
    file<<"     Test 3"<<endl;
    file<<"Day: " <<(dys6[2].getDay())<<endl;
    file<<"Mount: " <<(dys6[2].getMount())<<endl;

    cout<<"Demorgan Rule Test"<<endl;
    cout<<" Test 1"<<endl;
    cout<<(!(dys6+dys7))<<endl;
    cout<<" Test 2"<<endl;
    cout<<dys6;
    cout<<(!(!dys6));

    file<<"Demorgan Rule Test"<<endl;
    file<<" Test 1"<<endl;
    file<<(!(dys6+dys7))<<endl;
    file<<" Test 2"<<endl;
    file<<dys6;
    file<<(!(!dys6));
    
    
   
    
}