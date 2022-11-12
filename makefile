all: main.exe

main.exe : 
	@g++ -Wall -Wextra -std=c++17 main.cpp -o main.exe

test :
	@make main.exe
	./main.exe dancing_men.txt
	@make clean

clean : 
	@rm main.exe
