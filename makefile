topo:
	g++ -g -o Topo.out Topo.cpp Node.cpp Edge.cpp Runiform_rand.cpp env.cpp Request.cpp

simple:
	g++ -g -o Simple_Method.out Simple_Method.cpp Node.cpp Edge.cpp Link.cpp Request.cpp env.cpp
Average:
	g++ -g -o Average.out Average.cpp
clean:
	rm -f Topo.out Simple_Method.out Medium_Method.out Hard_Method.out