#FLAGS = -std=c++17 -Ofast -Wall -Wextra -Wno-unused-result -Wno-unused-const-variable -Wno-pragmas -lstdc++ -Wl,-stack_size -Wl,1000000000
FLAGS = -std=c++17 -Wall -Wextra -Wno-unused-result -Wno-unused-const-variable -Wno-pragmas -lstdc++
OUTPUT ?= "a.out"

compile:
	gcc ${FLAGS} ${s} -o ${OUTPUT}

pA:
	gcc ${FLAGS} A.cpp -o A

pB:
	gcc ${FLAGS} B.cpp -o B

pC:
	gcc ${FLAGS} C.cpp -o C

pD:
	gcc ${FLAGS} D.cpp -o D

pE:
	gcc ${FLAGS} E.cpp -o E

pF:
	gcc ${FLAGS} F.cpp -o F

pG:
	gcc ${FLAGS} G.cpp -o G

clean:
	@rm -f in*.txt a.out A B C D E F G *.tu* *.in *.out *input* *output*
