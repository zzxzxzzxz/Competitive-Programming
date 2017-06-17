NODES ?= 10
PROB = sandwich

test:
	cp ${h} ${PROB}.h
	~/.dcj/dcj.sh test --source sol.cpp --nodes ${NODES} --language C++

prepare:
	mv ${PROB}.h ${PROB}0.h
	mv ${PROB}\(1\).h ${PROB}1.h
	mv ${PROB}\(2\).h ${PROB}2.h
	sed -i "3i #include \"${PROB}.h\"" sol.cpp
