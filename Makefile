#CMD = gcc -std=c++17 -Ofast -Wshadow -Wall -lstdc++ -Wl,-stack_size -Wl,1000000000

OUTPUT ?= "a.out"
VER ?= 14
LOCAL = -DLOCAL

CMD = g++ -std=c++${VER} -Wshadow -Wall -Wno-unused-const-variable \
	  -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG ${LOCAL}

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

clean_tu:
	find . -name '*.tu*' -delete
