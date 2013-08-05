SFML_INCLUDE_PATH=../SFML-2.0/include
SFML_LIBRARY_PATH=../SFML-2.0/lib

app: 
	@echo "\tRemoving previous executable"
	@rm -f sfml-app
	@echo "\tCompiling files into object files"
	@g++ -g -c ../src/Array.cpp -I${SFML_INCLUDE_PATH} -o Array.o
	@g++ -g -c CrossEntity.cpp -I${SFML_INCLUDE_PATH} -o CrossEntity.o
	@g++ -g -c CircleEntity.cpp -I${SFML_INCLUDE_PATH} -o CircleEntity.o
	@g++ -g -c main.cpp -I${SFML_INCLUDE_PATH} -o main.o
	@g++ -g -c ../src/App.cpp -I${SFML_INCLUDE_PATH} -o App.o
	@g++ -g -c BoardEntity.cpp -I${SFML_INCLUDE_PATH} -o BoardEntity.o
	@g++ -g -c TicTacApp.cpp -I${SFML_INCLUDE_PATH} -o TicTacApp.o
	@echo "\tLinking files together into executable"
	@g++ *.o -o sfml-app -L${SFML_LIBRARY_PATH} -lsfml-graphics -lsfml-window -lsfml-system
	@echo "\tCleaning up object files"
	@rm *.o
