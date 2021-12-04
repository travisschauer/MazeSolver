project4: main.o DisjointSetForest.o sampler.o output.o
	g++ -o project4 main.o DisjointSetForest.o sampler.o output.o

main.o: main.cpp DisjointSetForest.h sampler.h stack.h pathfinder.h
	g++ -c main.cpp

DisjointSetForest.o: DisjointSetForest.cpp DisjointSetForest.h
	g++ -c DisjointSetForest.cpp 
	
sampler.o: sampler.cpp sampler.h
	g++ -c sampler.cpp

output.o: output.cpp pathfinder.h
	g++ -c output.cpp
