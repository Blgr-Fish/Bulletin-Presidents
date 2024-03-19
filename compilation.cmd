g++ -c TableDecharge.cpp -o TableDecharge.o
g++ -c Bureau.cpp -o Bureau.o
g++ -c ElecteurEngage.cpp -o ElecteurEngage.o
g++ -c Personne.cpp -o Personne.o
g++ -c TableVote.cpp -o TableVote.o
g++ -c Isoloire.cpp -o Isoloire.o
g++ -c main.cpp -o main.o
g++ Bureau.o TableDecharge.o ElecteurEngage.o Personne.o TableVote.o Isoloire.o main.o -o main.exe
