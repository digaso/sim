sim: ./out/main.o ./out/building.o ./out/character.o ./out/country.o ./out/culture.o ./out/population.o ./out/province.o ./out/world.o ./out/date.o
		g++ -g -O2 -Wall ./out/main.o ./out/building.o ./out/character.o ./out/country.o ./out/culture.o ./out/population.o ./out/province.o ./out/world.o ./out/date.o -o sim -lsfml-graphics -lsfml-window -lsfml-system

./out/main.o: main.cpp
	g++ -g -O2 -Wall -c main.cpp -o ./out/main.o

./out/building.o: ./src/building.cpp
	g++ -O2 -Wall -g -c ./src/building.cpp -o ./out/building.o

./out/character.o: ./src/character.cpp
	g++ -O2 -Wall -g -c ./src/character.cpp -o ./out/character.o

./out/country.o: ./src/country.cpp
	g++ -O2 -Wall -g -c ./src/country.cpp -o ./out/country.o

./out/culture.o: ./src/culture.cpp
	g++ -O2 -Wall -g -c ./src/culture.cpp -o ./out/culture.o

./out/population.o: ./src/population.cpp
	g++ -O2 -Wall -g -c ./src/population.cpp -o ./out/population.o

./out/province.o: ./src/province.cpp
	g++ -O2 -Wall -g -c ./src/province.cpp -o ./out/province.o

./out/world.o: ./src/world.cpp
	g++ -O2 -Wall -g -c ./src/world.cpp -o ./out/world.o

./out/date.o: ./src/utils/date.cpp
	g++ -O2 -Wall -g -c ./src/utils/date.cpp -o ./out/date.o

clean:
	rm -f ./out/*.o sim

run: sim
	./sim