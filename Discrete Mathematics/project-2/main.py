
relnum =0
letter= [] #letter or number
relation=[] # all relation

def read_file() :
    
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
    #output_f.write("Reletion Number:" + str(relnum) + "\n")
    end='b' # randum letter
    #output_f.write(end)

    i=0
    
    while end != "\n" : #read letter or number
        letter.insert(i,str(input_file.readline(1)))
        end=input_file.readline(1)
        i=i+1
    i=0
    j=0
    #output_f.write(str(letter)+"\n")
    
    while j < relnum : #read relation
        first=input_file.readline(1)
        semi=input_file.readline(1)
        second=input_file.readline(1)
        relation.append((first,second))
        input_file.readline(1)
        
        j=j+1
    i=0
    

    return 1
def reflexive(): #add element for reflexivity
    
    for a in letter:
        if (a, a) not in relation:
            relation.append((a,a))
            #print("add ("+a+","+a+")")
    return True    
def symmetric(): #add element synmetric
    
    for a, b in relation:
        if (b, a) in relation:
            relation.remove((b,a))
            
    return True
def transitive(): #  add element for transitive
       
    for a in letter:
        for b in letter:
            if (a, b) in relation:
                for c in letter:
                    if (b, c) in relation and (a, c) not in relation:
                        relation.append((a,c))
    return 1                         

def remove_reflexive(): #remove all element reflexivity
   
    for a in letter:
        if (a, a) in relation:
            #print("remove reflexsive   "+a)
            relation.remove((a,a))
            
    return True
def remove_transitive():  # remove one element 
    
    for a in letter:
        for b in letter:
            if (a, b) in relation:
                for c in letter:
                    if (b, c) in relation and (a, c) in relation:
                        #print("remove transitive a b b c a c "+a+b+b+c+a+c )
                        relation.remove((a,c))
                        
    return True
def error_handling() : #find error
    i=0
    j=0
    while i < len(letter) : 
        #print(str(letter[0]+"   "+ str(relation[0][])))
        if letter[i]==relation[j][0]  :
            i=0
            while i < len(letter) :
                if letter[i]==relation[j][1] :
                    j=j+1
                    i=0
                    #print("len: "+ str(len(relation)))
                    if j == (len(relation)) :
                        return True
                else :
                    i=i+1        
        else  :  
            i=i+1
    
    return False    

input_file=open('input.txt','r')
output_f=open('output.txt','w')
flag=True
while True : # main loop
    output_f.write("n \n")
    read_file()
    output_f.write("poset:"+str(relation) +"\n")
    
    flag=error_handling()
    if flag==True :   # if there is wrong relation, skip function
        
        reflexive()
        symmetric()
        transitive()
        remove_reflexive()
        remove_transitive()
        output_f.write(str(relation))
        letter.clear()
        relation.clear()
        output_f.write("\n\n")
        
    else:
        output_f.write("This relation is wrong\n\n")
        letter.clear()
        relation.clear()

input_file.close()
output_f.close()
    
    
    
    
