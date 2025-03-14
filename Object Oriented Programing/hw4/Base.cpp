#include "Base.h"
int DayofYearSet::DayofYear::liveobj=0;

DayofYearSet::DayofYearSet(){
    objectNum =0;
    dayofyear = nullptr;
}
DayofYearSet::DayofYearSet(int day,int mount){
   dayofyear = new DayofYear[1];
   objectNum=1;
    
   if(day>0 && day < 31 && mount <13 && mount >0){
        
        dayofyear[0].setDay(day);
        dayofyear[0].setMount(mount);
        
   }
   else{
        dayofyear[0].setDay(1);
        dayofyear[0].setMount(1);
   }
}
DayofYearSet::DayofYearSet(const vector<DayofYear> & vec){
    
    if(vec.size()>0){
        objectNum= 0;
        dayofyear = nullptr;
        
        for(int i=0;i<vec.size();i++){
            this->add(vec[i]);
            
            
        }
        
    }
    else{
        dayofyear = nullptr;
    }

}

DayofYearSet::DayofYearSet(const DayofYearSet::DayofYear &dy){
    cout<<"nerede"<<endl;
    objectNum =1;
    dayofyear = new DayofYear[1];
   
    dayofyear[0].setDay(dy.getDay());
    
    dayofyear[0].setMount(dy.getMount());
    
}
DayofYearSet::~DayofYearSet(){
    delete [] dayofyear;
    dayofyear=nullptr;
    
}
DayofYearSet::DayofYear::~DayofYear(){
    //liveobj--;
    
}
DayofYearSet::DayofYear::DayofYear(){
    day=0;
    mount=0;
    liveobj++;
    
}
DayofYearSet::DayofYear::DayofYear(int day,int mount){
    liveobj++;
    if(day>0 && day < 31 && mount <13 && mount >0){
        this->day=day;
        this->mount = mount;
    }
    else{
        this->day =0;
        this->mount =0;
    }
    
}

ostream &operator<<(ostream & stream,const DayofYearSet & dys){ // all dayofyearset object information return
    int i=0;
    stream<<"Size: "<< dys.size()<<endl;
    for(i=0;i<dys.size();i++){
        stream<<"DATE"<<endl;
        stream<<"  Day: "<<dys.getDayofYear(i).getDay();
        stream<<"  Mount: "<<dys.getDayofYear(i).getMount()<<endl;
        
    }
    return  stream;

}

bool DayofYearSet::operator==(const DayofYearSet & dys){ // check two dayofyearset opeartion
    int i=0,k=0;
    int tmpDay,tmpMount;
    bool flag = false;
    if(dys.size() == this->size()){

        for(i=0;i<dys.size();i++){
            tmpDay = dys.getDayofYear(i).getDay();
            tmpMount = dys.getDayofYear(i).getMount();
            for(k=0;k <this->size();k++){
                if(tmpDay == this->getDayofYear(k).getDay() && tmpMount == this->getDayofYear(k).getMount()){
                    
                    flag=true;
                }
            }
            if(flag==false){
                return false;
            }
            else{
                flag=false;
            }
        }
        
    }
    else{
        return false;
    }
    return true;
}
bool DayofYearSet::operator!=(const DayofYearSet & dys){ // 
    return !(*this == dys);
}
const DayofYearSet::DayofYear DayofYearSet::getDayofYear(int index)const{ // return getofyear object
    if(index <size() && index >-1)
        return dayofyear[index];
    else{
        return DayofYearSet::DayofYear(0,0);
    }   
}
const DayofYearSet DayofYearSet::operator=(const DayofYearSet & dys){ // asigment opeartor for big three
    auto i=0;
    if(&dys != this){
        delete [] this->dayofyear;
        this->setSize(dys.size());
        this->dayofyear = new DayofYear[dys.size()];
        for(i=0;i<dys.size();i++){
            this->dayofyear[i].setDay(dys.getDayofYear(i).getDay());
            this->dayofyear[i].setMount(dys.getDayofYear(i).getMount());

        }

    }
    return *this;
}
DayofYearSet DayofYearSet::operator+(const DayofYearSet & dys){ // return union set 
    int i=0;
    DayofYearSet tmpDys; 
    
    for(i=0;i<dys.size();i++){
        tmpDys.add(dys.getDayofYear(i));
        
    }
    for(i=0;i<this->size();i++){
        if(!tmpDys.compareSame(this->dayofyear[i])){
            tmpDys.add(this->dayofyear[i]);
        }
        
    }
    return tmpDys;
}
DayofYearSet DayofYearSet::operator^(const DayofYearSet & dys){ // return intersection between two dayofyearset object
    int i=0,k=0;
    DayofYearSet tmpDys;
    for(i=0;i<dys.size();i++){
        for(k=0;k<this->size();k++){
            if(dys.getDayofYear(i).getDay()==this->dayofyear[k].getDay() && dys.getDayofYear(i).getMount() == this->dayofyear[k].getMount()){
                tmpDys.add(dys.getDayofYear(i));

            }
        }
    }
    return tmpDys;
}
DayofYearSet DayofYearSet::operator-(const DayofYearSet & dys){ // return  between diffirence Dayofyear objcet
    int k=0,mountCount=1;
    decltype(0) i;
    DayofYearSet tmpDys;
    for(i=0;i<size();i++){
        if(!dys.compareSame(this->dayofyear[i])){
            tmpDys.add(this->dayofyear[i]);
        }
        
    }
    
    
    return tmpDys;
}
DayofYearSet DayofYearSet::operator!(){ // return external days 
    int i=0,mountNum=1;
    DayofYearSet tmpdys;
    for(i=1;i<366;i++){
        if(0 == i%30){
            
             mountNum++;
        }
        if(!this->compareSame(DayofYearSet::DayofYear(i%31,mountNum))){
            tmpdys.add(DayofYearSet::DayofYear(i%31,mountNum));
        }
        
    }
    return tmpdys ;
}
DayofYearSet::DayofYear DayofYearSet::operator[](int index){ // return dayofyear object
    if(index<size() && index >-1){
        return dayofyear[index];
    }
    else{
        return DayofYearSet(0,0).dayofyear[0];
    }
}
bool DayofYearSet::add(const DayofYearSet::DayofYear & dy){ // add elemenet dayofyear object
    int i=0;
    
    if(!compareSame(dy)){
        DayofYear * tmpDy = new DayofYear[size()+1];
        
        
        for(i=0;i<size();i++){
            tmpDy[i].setDay(this->getDayofYear(i).getDay());
            tmpDy[i].setMount(this->getDayofYear(i).getMount());
        }
        tmpDy[size()] =dy;
        if(dayofyear!=nullptr){
            delete [] dayofyear;
        }
        
       
        dayofyear = tmpDy;
        
       objectNum++;
    }
    else{
        return false;
    }
    
    return true;
}
bool DayofYearSet::add(const DayofYearSet & dys){ // add all elements add dayofyearset object
    int i=0;
    if(&dys!=nullptr){
        for(i=0;i<dys.size();i++){
            this->add(dys.getDayofYear(i));
        }
        return true;
    }
    else{
        return false;
    }
    
}

bool DayofYearSet::remove(const DayofYearSet::DayofYear & dy){ // remove element Dayofyear object
    int i=0;
        if(compareSame(dy)){
            setSize(size()-1);
           DayofYearSet::DayofYear * tmp = new DayofYear[size()];
            
            for(int i =0; i< size();i++){
                if(!compareSame(dy)){
                    tmp[i] = dayofyear[i];
                }
            }
            delete [] dayofyear;
            dayofyear = tmp;
            
            return true;
        }
        else{
            return false;
        }
    
}

bool DayofYearSet::compareSame(const DayofYearSet::DayofYear & dy)const{

    int i=0;
    for(i=0;i<size();i++){
        if(dy.getDay()== this->getDayofYear(i).getDay() && dy.getMount() == this->getDayofYear(i).getMount()){
            return true;
        }
    }
    return false;
}
