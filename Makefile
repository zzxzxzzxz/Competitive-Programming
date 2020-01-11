#CMD = gcc -std=c++17 -Ofast -Wall -Wextra -Wno-unused-result -Wno-unused-const-variable -Wno-pragmas -lstdc++ -Wl,-stack_size -Wl,1000000000
CMD = g++ -std=c++17 -Wall -Wextra -Wno-unused-result -Wno-unused-const-variable -Wno-pragmas
OUTPUT ?= "a.out"

compile:
	${CMD} ${s} -o ${OUTPUT}

pA:
	${CMD} A.cpp -o A

pB:
	${CMD} B.cpp -o B

pC:
	${CMD} C.cpp -o C

pD:
	${CMD} D.cpp -o D

pE:
	${CMD} E.cpp -o E

pF:
	${CMD} F.cpp -o F

pG:
	${CMD} G.cpp -o G

clean:
	@rm -f in*.txt a.out A B C D E F G *.tu* *.in *.out *input* *output*
