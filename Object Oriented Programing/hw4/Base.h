
#include <iostream>
#include <vector>
#include <fstream>
#ifndef Base
#define Base
using namespace std;

class DayofYearSet{
    public:
        class DayofYear{
            public:
                DayofYear();
                DayofYear(int day,int mount);
                ~DayofYear();

                int getDay()const{return day;}
                void setDay(int day){this->day = day; }
                int getMount()const{return mount;}
                void setMount(int mount){this->mount = mount;}
                static int liveobj;
                static int getLiveobj(){return liveobj;}
            private:
                int day;
                int mount;
                
        };
        DayofYearSet();
        DayofYearSet(const vector<DayofYear>  & vec);
        DayofYearSet(const DayofYearSet::DayofYear & dy);
        DayofYearSet(int day,int mount);
        ~DayofYearSet();
        friend ostream & operator<<(ostream & stream,const DayofYearSet & dys );
        bool compareSame(const DayofYear & dy)const ;
        bool operator==(const DayofYearSet & rDys);
        bool operator!=(const DayofYearSet & rDys);
        bool add(const DayofYear & dy);
        bool add(const DayofYearSet & dys);
        bool remove(const DayofYear & dy);
    
        int size()const {return objectNum;};
        void setSize(int size){if(size >-1) this->objectNum = size;}
        const DayofYearSet operator=(const DayofYearSet &Dys);
        DayofYearSet  operator+(const DayofYearSet &dys);
        DayofYearSet  operator-(const DayofYearSet &dys);
        DayofYearSet operator^(const DayofYearSet &dys);
        DayofYearSet operator!();
        DayofYear operator[](int index);
        const DayofYear getDayofYear(int index)const;
        
    private:
        DayofYear * dayofyear;
        int objectNum;
        
        
       

};

#endif
