#CXXFLAGS = -std=c++17 -Ofast -Wshadow -Wall -Wno-unused-const-variable -Wno-string-plus-int \
	  -lstdc++ -Wl,-stack_size -Wl,1000000000

VER ?= 14
LOCAL = -DLOCAL

CXXFLAGS = -O3 -std=c++${VER} -Wshadow -Wall -Wno-unused-const-variable -Wno-string-plus-int \
	  -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG ${LOCAL}

clean: clean_tu
	@find . -type f -perm +111 -delete

clean_tu:
	@find . -name '*.tu*' -delete
