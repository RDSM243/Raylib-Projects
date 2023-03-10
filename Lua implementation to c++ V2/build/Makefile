build:
	g++ -w -std=c++17 -Wfatal-errors ../src/*.cpp -o test.exe -O2 -Wall -Wno-missing-braces -I ../include/ -I ../lib/lua/ -L ../lib/ -L ../lib/lua -lraylib -lopengl32 -lgdi32 -lwinmm -llua53

clean:
	rm ./test.exe

run:
	./test.exe