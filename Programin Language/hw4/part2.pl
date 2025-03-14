

% knowledge base
schedule(canakkale,erzincan,6).
schedule(istanbul,izmir,2).
schedule(erzincan,antalya,3).
schedule(antalya,izmir,2).
schedule(izmir,ankara,6).
schedule(istanbul,ankara,1).
schedule(istanbul,rize,4).
schedule(rize,ankara,5).
schedule(ankara,diyarbakir,8).
schedule(antalya,diyarbakir,4).
schedule(istanbul,izmir,2).
schedule(ankara,van,4).
schedule(van,gaziantep,3).

schedule(erzincan,canakkale,6).
schedule(antalya,erzincan,3).
schedule(izmir,antalya,2).
schedule(izmir,istanbul,2).
schedule(ankara,izmir,6).
schedule(ankara,istanbul,1).
schedule(rize,istanbul,4).
schedule(ankara,rize,5).
schedule(diyarbakir,ankara,8).
schedule(diyarbakir,antalya,4).
schedule(van,ankara,4).
schedule(gaziantep,van,3).

connection(X,Y,D) :- not(X==Y),schedule(X,Y,D).
connection(X,Y,D) :- schedule(X,Z,A),schedule(Z,Y,B),not(X==Y),not(Z==Y),not(X==Z),(D is A+B).
connection(X,Y,D) :- schedule(X,Z,A),schedule(Z,T,B),schedule(T,Y,C),not(X==Y),not(Z==T),not(Z==Y),not(T==Y),not(X==T),not(X==Z),(D is A+B+C).
connection(X,Y,D) :- schedule(X,Z,A),schedule(Z,T,B),schedule(T,K,C),schedule(K,Y,E),not(X==K),not(Z==K),not(T==K),not(K==Y),not(X==Y),not(Z==T),not(Z==Y),not(T==Y),not(X==T),not(X==Z),(D is A+B+C+E).
connection(X,Y,D) :- schedule(X,Z,A),schedule(Z,T,B),schedule(T,K,C),schedule(K,G,E),schedule(G,Y,L),not(X==G),not(Z==G),not(T==G),not(K==G),not(Y==G),not(X==K),not(Z==k),not(T==K),not(K==Y),not(X==Y),not(Z==T),not(Z==Y),not(T==Y),not(X==T),not(X==Z)(D is A+B+C+E+L).
connection(X,Y,D) :- schedule(X,Z,A),schedule(Z,T,B),schedule(T,K,C),schedule(K,G,E),schedule(G,S,L),schedule(S,Y,J),not(X==S),not(Z==S),not(T==S),not(K==S),not(G==S),not(S==Y),not(X==G),not(Z==G),not(T==G),not(K==G),not(Y==G),not(X==K),not(Z==k),not(T==K),not(K==Y),not(X==Y),not(Z==T),not(Z==Y),not(T==Y),not(X==T),not(X==Z),(D is A+B+C+E+L+J).















