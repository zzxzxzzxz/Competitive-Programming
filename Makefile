LOCAL ?= 1
DEBUG ?= 1
VER ?= 14

ifeq (${LOCAL}, 1)
	F_LOCAL = -DLOCAL
else
	F_LOCAL =
endif

ifeq (${DEBUG}, 1)
	CXX = g++ -O3 -std=c++${VER} -Wshadow -Wall -Wno-unused-const-variable -Wno-string-plus-int \
		  -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG ${F_LOCAL}
else
	CXX = g++ -Ofast -std=c++17 -Wshadow -Wall -Wno-unused-const-variable -Wno-string-plus-int \
		  -lstdc++ -Wl,-stack_size -Wl,1000000000
endif

compile:
	${CXX} ${s} -o $(shell basename ${s} .cpp)

clean: clean_tu
	@find . -type f -perm +111 -and -not -name "*.py" -delete

clean_tu:
	@find . -name '*.tu*' -delete

clean_all:
	@find . -type f -maxdepth 1 -not -name "Makefile" -delete
