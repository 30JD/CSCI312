#Junda An
import string
 

def main():
    #input maximum length and filename
    maxlength = int(input("Length? "));
    filename = input("Filename: ");

    #create worklist to store candidate terminal strings
    #create dictionary to store productions with key being the lhs nonterminal and the value being a list of strings.
    worklist = [ ];
    dict = { };
    productionlist = [ ];

    #store productions in dictionary
    for line in open(filename, "r"):
        list = line.split();
        productionlist.append(list);
        lhs = list[0];
        list.pop(0);
        list.pop(0);
        rhs = '';
        rhslist = [ ];
        if lhs not in dict.keys():
            for i in range(len(list) - 1):
                rhs = rhs + list[i] + ' ';
            rhs = rhs + list[-1];
            #print(list);
            #print(rhs);
            rhslist.append(rhs);
            dict[lhs] = rhslist;
        else:
            newrhs = ''
            for i in range(len(list) - 1):
                newrhs = newrhs + list[i] + ' ';
            newrhs = newrhs + list[-1];
            #print(newrhs);
            dict[lhs].append(newrhs);

    #push the startsymbol to the worklist
    startsymbol = productionlist[0][0];
    worklist.append(startsymbol);

    #print(dict);
    #print(startsymbol);

    printedsentence = [ ];

    while len(worklist) != 0:
        s = worklist.pop(0);
        nt = "";
    
        #if |s| > maxlength, continue
        slist = s.split();
        if len(slist) > maxlength:
            continue;
        else:
            #check if s has nonterminal. If yes, choose the leftmost nonterminal
            for element in slist:
                if element in dict.keys():
                    nt = element;
                    break;
            
            #if s has no nonterminal
            if nt == "":
                print(s);
                continue;
        
            else:
                #print("nt" + nt);
                
                #for all productions nt -> rhs
                for rhs in dict[nt]:
                    tmplist = s.split();
                    #print("s" + s);
                    
                    #replace nt in s with rhs
                    for i in range(len(tmplist)):
                        if(tmplist[i] == nt):
                            tmplist[i] = rhs;
                            break;
                    #print(tmplist);
                    tmp = '';
                    for i in range(len(tmplist) - 1):
                        tmp = tmp + tmplist[i] + ' ';
                    tmp = tmp + tmplist[-1];
                    
                    #if tmp is not printed before, store it in the worklist
                    if tmp not in printedsentence:
                        printedsentence.append(tmp);
                        worklist.append(tmp);
                        #print(worklist);

main();
        



