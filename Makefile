# 参考 : https://news.mynavi.jp/techplus/article/c-for-windows-14/
CMD=	bowling.exe
SRCS=	main.c bowling.c
OBJS = $(patsubst %.c,bin/%.o,$(SRCS))

CFLAGS+=-g

CC= gcc

build: $(CMD)

$(CMD): $(OBJS) | bin
	$(CC) $(CFLAGS) -o $(CMD) $(OBJS)

bin/%.o: %.c | bin
	$(CC) -c $< -o $@

bin:
	mkdir bin

clean:
	del $(CMD)
	del "bin\*.o"
	del "bin\*.ilk"
	del "bin\*.pdb"