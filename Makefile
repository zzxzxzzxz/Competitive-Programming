#CXXFLAGS = -Ofast -std=c++17 -Wshadow -Wall -Wno-unused-const-variable -Wno-string-plus-int \
	  -lstdc++ -Wl,-stack_size -Wl,1000000000

VER ?= 14
LOCAL = -DLOCAL

CXXFLAGS = -O3 -std=c++${VER} -Wshadow -Wall -Wno-unused-const-variable -Wno-string-plus-int \
	  -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG ${LOCAL}

%:
	g++ ${CXXFLAGS} $@.cpp -o $(shell basename $@)

clean: clean_tu
	@find . -type f -perm +111 -and -not -name "*.py" -delete

clean_tu:
	@find . -name '*.tu*' -delete
