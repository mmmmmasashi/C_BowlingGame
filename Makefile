# 参考 : https://news.mynavi.jp/techplus/article/c-for-windows-14/
CMD=	Game.exe
SRCS=	main.c Game.c
OBJS = $(patsubst %.c,bin/%.o,$(SRCS))

CXX = g++
CXXFLAGS = -Wall
CXXFLAGS += -I"$(CPPUTEST_HOME)/include"
CXXFLAGS += -I"src"

CFLAGS+=-g

CC= gcc

build: $(CMD)

$(CMD): $(OBJS) | bin
	$(CXX) $(CXXFLAGS) -o $(CMD) $(OBJS)

bin/main.o: main.c | bin
	$(CXX) $(CXXFLAGS) -c $< -o $@

bin/%.o: src/%.c src/%.h | bin
	$(CXX) $(CXXFLAGS) -c $< -o $@

bin:
	mkdir bin

clean:
	del $(CMD)
	del "bin\*.o"
	del "bin\*.ilk"
	del "bin\*.pdb"