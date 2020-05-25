#CMD = gcc -std=c++17 -Ofast -Wshadow -Wall -Wno-unused-const-variable -Wno-string-plus-int \
	  -lstdc++ -Wl,-stack_size -Wl,1000000000

OUTPUT ?= "a.out"
VER ?= 14
LOCAL = -DLOCAL

CMD = g++ -O2 -std=c++${VER} -Wshadow -Wall -Wno-unused-const-variable -Wno-string-plus-int \
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

pH:
	${CMD} H.cpp -o H

clean:
	@rm -f in*.txt a.out A B C D E F G H *.tu* *.in *.out *input* *output*

clean_tu:
	find . -name '*.tu*' -delete
