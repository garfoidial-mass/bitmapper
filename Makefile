PTHREADVERSION := -lpthread
EXAMPLENAME := test

ifeq ($(OS),Windows_NT)
	PTHREADVERSION = -lwinpthread
	EXAMPLENAME = test.exe
endif

all: lib test

lib:
	@echo $(PTHREADVERSION)
	mkdir build
	cc -std=gnu11 ./include/bitmapper/bitmapper.c -O2 -c -I./include -Wl,-Bstatic,--whole-archive $(PTHREADVERSION)  -Wl,-Bdynamic,--no-whole-archive -lSDL2main -lSDL2 -o ./build/bitmapper.o
	ar rcs ./build/libbitmapper.a ./build/bitmapper.o

test: lib
	cc -std=gnu11 ./test/test.c -I./include -O2 -L./build -Wl,-Bstatic -lpthread -lbitmapper -Wl,-Bdynamic -lSDL2main -lSDL2 -o ./test/$(EXAMPLENAME)

clean:
	rm -rf ./build
	rm ./test/test.exe