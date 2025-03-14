

% knowledge base
flight(canakkale,erzincan,6).
flight(istanbul,izmir,2).
flight(erzincan,antalya,3).
flight(antalya,izmir,2).
flight(izmir,ankara,6).
flight(istanbul,ankara,1).
flight(istanbul,rize,4).
flight(rize,ankara,5).
flight(ankara,diyarbakir,8).
flight(antalya,diyarbakir,4).
flight(istanbul,izmir,2).
flight(ankara,van,4).
flight(van,gaziantep,3).

flight(erzincan,canakkale,6).
flight(antalya,erzincan,3).
flight(izmir,antalya,2).
flight(izmir,istanbul,2).
flight(ankara,izmir,6).
flight(ankara,istanbul,1).
flight(rize,istanbul,4).
flight(ankara,rize,5).
flight(diyarbakir,ankara,8).
flight(diyarbakir,antalya,4).
flight(van,ankara,4).
flight(gaziantep,van,3).

route(X,Y,D) :- not(X==Y),flight(X,Y,D).
route(X,Y,D) :- flight(X,Z,A),flight(Z,Y,B),not(X==Y),not(Z==Y),not(X==Z),(D is A+B).
route(X,Y,D) :- flight(X,Z,A),flight(Z,T,B),flight(T,Y,C),not(X==Y),not(Z==T),not(Z==Y),not(T==Y),not(X==T),not(X==Z),(D is A+B+C).
route(X,Y,D) :- flight(X,Z,A),flight(Z,T,B),flight(T,K,C),flight(K,Y,E),not(X==K),not(Z==K),not(T==K),not(K==Y),not(X==Y),not(Z==T),not(Z==Y),not(T==Y),not(X==T),not(X==Z),(D is A+B+C+E).
route(X,Y,D) :- flight(X,Z,A),flight(Z,T,B),flight(T,K,C),flight(K,G,E),flight(G,Y,L),not(X==G),not(Z==G),not(T==G),not(K==G),not(Y==G),not(X==K),not(Z==k),not(T==K),not(K==Y),not(X==Y),not(Z==T),not(Z==Y),not(T==Y),not(X==T),not(X==Z)(D is A+B+C+E+L).
route(X,Y,D) :- flight(X,Z,A),flight(Z,T,B),flight(T,K,C),flight(K,G,E),flight(G,S,L),flight(S,Y,J),not(X==S),not(Z==S),not(T==S),not(K==S),not(G==S),not(S==Y),not(X==G),not(Z==G),not(T==G),not(K==G),not(Y==G),not(X==K),not(Z==k),not(T==K),not(K==Y),not(X==Y),not(Z==T),not(Z==Y),not(T==Y),not(X==T),not(X==Z),(D is A+B+C+E+L+J).






