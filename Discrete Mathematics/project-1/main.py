import argparse
import os

relnum =0
letter= [] #letter or number
relation=[] # all relation
def read_file () :
    
    temp=input_file.readline(1)
    if len(temp) == 0 :
        exit()
        return 0
    
    end = input_file.readline(1)
    relnum=int(temp)
    while end != '\n' : #read relation number
        relnum=relnum*10
        relnum=relnum + int(end)
        end = input_file.readline(1)
    output_f.write("Reletion Number:" + str(relnum) + "\n")
    end='b' # randum letter
    #output_f.write(end)

    i=0
    
    while end != "\n" : #read letter or number
        letter.insert(i,str(input_file.readline(1)))
        end=input_file.readline(1)
        i=i+1
    i=0
    j=0
    output_f.write(str(letter)+"\n")
    
    while j < relnum : #read relation
        relation.insert(i,str(input_file.readline(1)))
        input_file.readline(1)
        i=i+1
        relation.insert(i,str(input_file.readline(1)))
        input_file.readline(1)
        i=i+1
        j=j+1
    i=0
    output_f.write("[")
    while i < len(relation) : # to write file all relation
        output_f.write("("+relation[i]+","+relation[i+1]+"),")
        i=i+2
    output_f.write("]\n")
    return 1
    
def reflection (letter,relation) :  # fining reflection
    i=0
    k=0
    while i < (len(letter))  :
        if letter[i] ==relation[k] :
            if relation[k]==relation[k+1] :
                i=i+1
                k=0
        k=k+2      
        if (len(relation)-2) < k :
            output_f.write("reflexsive No. There arent (" + str(letter[i]) + ',' + str(letter[i]) + ")\n" )
            return 0
         
    output_f.write("Reflexive: Yes, all elements are present.\n")

def symmetric (relation) : # to find symmetric
    i=0
    k=0
    while i < (len(relation)-2) and k < (len(relation)-2) :
        first =relation[k]
        second = relation[k+1]
        i=i+2
        
        if (first == relation[i+1] and second == relation[i]) or first == second :
            k=k+2
            i=0
        if (len(relation)-2) <= i  : 
            output_f.write("Symmetric No Element (" +first + "," + second + ")" + "is not symmetric\n" ) 
            return 0


    output_f.write("Symmetric Yes, all elements are present.\n")
    return 1

def anti_symmetric(relation) : # to find anti-symmetric
    i=0
    k=0
    while k < (len(relation)-2)  :
        first =relation[k]
        second = relation[k+1]
        i=0
        
        while i < (len(relation)) :
            if (first == relation[i+1] and second == relation[i]) and (first != second) and (relation[i] != relation[i+1]) and (i!=k) :
                
                output_f.write("Anti Symmetrics. No (" +first + "," + second +")" + 
                        "and (" + relation[i] +"," +relation[i+1] + ") is synmetric\n"  )
                return 1
            i=i+2
        k=k+2                




    output_f.write("Anti Symmetric. Yes\n")
    return 0

def transitive(A, R):
    """Returns True if a relation R on set A is transitive, False otherwise."""
    #print(R)
    for a in A:
        for b in A:
            if (a, b) in R:
                for c in A:
                    if (b, c) in R and (a, c) not in R:
                        output_f.write ("Transitive No because there are,("+a+","+b+"),and ("+b+","+c+") There isnt  ("+a+","+c+")\n\n")
                        return False
    
    output_f.write("Transitive Yes\n\n")                   
    return True
def error_handling(letter,relation) : #find error
    i=0
    j=0
    while i < len(letter) :
        
        if letter[i]==relation[j] :
            j=j+1
            i=0
            if j == (len(relation)) :
                return 1
        else  :  
            i=i+1
    
    return 0

def new_list(relation) :
    arr=[]
    i = 0
    while i < len(relation) :
        arr.append((relation[i],relation[i+1]))
        i =i+2
    #print(arr)
    return arr;


input_file=open('input.txt','r')
output_f=open('output.txt','w')
flag=1
while True :
    read_file()
    flag=error_handling(letter,relation)
    if flag==1 :   # if there is wrong relation, skip function
        reflection(letter,relation)
        symmetric(relation)
        anti_symmetric(relation)
        transitive(letter,new_list(relation))
        letter.clear()
        relation.clear()
        output_f.write("\n\n")
        
    else:
        output_f.write("This relation is wrong")
        output_f.write("\n\n")
        letter.clear()
        relation.clear()
input_file.close()
output_f.close()     


    


