DEBUG ?= 2
VER ?= 14

ifeq (${DEBUG}, 0)
	CXX = g++ -Ofast -std=c++17 -Wshadow -Wall -Wno-unused-const-variable -Wno-string-plus-int \
		  -lstdc++ -Wl,-stack_size -Wl,1000000000
else
	CXX = g++ -O3 -std=c++${VER} -Wshadow -Wall -Wno-unused-const-variable -Wno-string-plus-int \
		  -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG -DDEBUG=${DEBUG}
endif

compile:
	${CXX} ${s} -o $(shell basename ${s} .cpp)

clean: clean_tu
	@find . -type f -perm +111 -and -not -name "*.py" -delete

clean_tu:
	@find . -name '*.tu*' -delete

clean_all:
	@find . -type f -maxdepth 1 -not -name "Makefile" -delete
