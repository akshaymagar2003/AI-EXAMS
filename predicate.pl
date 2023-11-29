female(babita).
female(kareena).
female(karishma).
female(sara).
male(saif).
male(taimur).
male(aarav).
male(randhir).
male(raj).

parent(babita,kareena).
parent(randhir,kareena).
parent(randhir,karishma).
parent(saif,taimur).
parent(kareena,taimur).
parent(kareena,sara).
parent(karishma,raj).
parent(sara,aarav).

husband(X,Y):- parent(X,Z),parent(Y,Z),male(X).
wife(X,Y):- parent(X,Z),parent(Y,Z),female(X).
mother(X,Y):- parent(X,Y),female(X).
father(X,Y):- parent(X,Y),male(X).
son(X,Y):- male(X),parent(Y,X).
daughter(X,Y):- female(X),parent(Y,X).
haschild(X):- parent(X,_).
sister(X,Y):- parent(Z,X),parent(Z,Y),female(X),X\==Y.
brother(X,Y):-parent(Z,X),parent(Z,Y),male(X),X\==Y.

paternal_uncle(X,Y):- father(Z,Y),brother(X,Z).
maternal_uncle(X,Y):- mother(Z,Y),brother(X,Z).
paternal_aunt(X,Y):- father(Z,Y),sister(X,Z).
maternal_aunt(X,Y):- mother(Z,Y),sister(X,Z).
niece(X,Y):- female(X),parent(Z,X),parent(W,Z),parent(W,Y),Z\==Y.
nephew(X,Y):- male(X),parent(Z,X),parent(W,Z),parent(W,Y),Z\==Y.
grandfather(X,Y):- parent(X,Z),parent(Z,Y),male(X).
grandmother(X,Y):- parent(X,Z),parent(Z,Y),female(X).
cousin_brother(X,Y):-
male(X),parent(Z,Y),parent(W,X),parent(T,W),parent(T,Z),Z\==W,X\==Y.
cousin_sister(X,Y):-
female(X),parent(Z,Y),parent(W,X),parent(T,W),parent(T,Z),Z\==W,X\==Y.
soninlaw(X,Y):- husband(X,Z),parent(Y,Z).
fatherinlaw(X,Y):- husband(Y,Z),parent(X,Z).
daughterinlaw(X,Y):- wife(X,Z),parent(Y,Z).
brotherinlaw(X,Y):- husband(X,Z),parent(W,Y),parent(W,Z),Y\==Z.
sisterinlaw(X,Y):- wife(X,Z),parent(W,Y),parent(W,Z),Y\==Z.
predecessor(X,Y):- parent(X,Y).
predecessor(X,Y):- parent(X,Z),predecessor(Z,Y).

