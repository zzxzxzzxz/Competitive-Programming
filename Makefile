FLAGS = -std=c++14 -O2 -Wall -Wno-unused-result -Wno-unused-const-variable -Wno-pragmas

compile:
	g++ ${FLAGS} ${s}

openmp_compile:
	g++ ${FLAGS} -fopenmp ${s}

pA:
	g++ ${FLAGS} A.cpp -o A

pB:
	g++ ${FLAGS} B.cpp -o B

pC:
	g++ ${FLAGS} C.cpp -o C

pD:
	g++ ${FLAGS} D.cpp -o D

pE:
	g++ ${FLAGS} E.cpp -o E

pF:
	g++ ${FLAGS} F.cpp -o F

pG:
	g++ ${FLAGS} G.cpp -o G

clean:
	@rm -rf $(shell find ./ -name '.*.un~')
	@rm -f in*.txt a.out A B C D E F G *.in *.out
