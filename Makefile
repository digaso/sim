sim: ./out/main.o ./out/building.o ./out/character.o ./out/country.o ./out/culture.o ./out/population.o ./out/province.o ./out/world.o ./out/date.o ./out/good.o ./out/ai_character.o
		g++ -g -std=c++20 -Wall ./out/ai_character.o ./out/main.o ./out/building.o  ./out/country.o ./out/culture.o ./out/population.o ./out/character.o ./out/province.o ./out/world.o ./out/date.o ./out/good.o  -o sim -lraylib -lGL -lm  -DRAUDIO_STANDALONE -DSUPPORT_FILEFORMAT_WAV -DSUPPORT_FILEFORMAT_OGG -lpthread -ldl -lrt -lX11 -DRAYGUI_IMPLEMENTATION -O2

./out/main.o: main.cpp
	g++ -g -Wall -c main.cpp -o ./out/main.o -O2

./out/building.o: ./src/building.cpp
	g++ -Wall -g -c ./src/building.cpp -o ./out/building.o -O2

./out/character.o: ./src/character.cpp
	g++ -Wall -g -c ./src/character.cpp -o ./out/character.o -O2

./out/country.o: ./src/country.cpp
	g++ -Wall -g -c ./src/country.cpp -o ./out/country.o -O2

./out/culture.o: ./src/culture.cpp
	g++ -Wall -g -c ./src/culture.cpp -o ./out/culture.o	-O2

./out/population.o: ./src/population.cpp
	g++ -Wall -g -c ./src/population.cpp -o ./out/population.o	-O2

./out/province.o: ./src/province.cpp
	g++ -Wall -g -c ./src/province.cpp -o ./out/province.o	-O2

./out/world.o: ./src/world.cpp
	g++ -Wall -g -c ./src/world.cpp -o ./out/world.o	-O2

./out/date.o: ./src/utils/date.cpp
	g++ -Wall -g -c ./src/utils/date.cpp -o ./out/date.o	-O2

./out/good.o: ./src/economy/good.cpp
	g++ -Wall -g -c ./src/economy/good.cpp -o ./out/good.o	-O2

./out/ai_character.o: ./src/agents/ai_character.cpp
	g++ -Wall -g -c ./src/agents/ai_character.cpp -o ./out/ai_character.o -O2

clean:
	rm -f ./out/*.o sim

run: sim
	./sim