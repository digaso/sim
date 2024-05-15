sim: ./out/main.o ./out/building.o ./out/character.o ./out/country.o ./out/culture.o ./out/population.o ./out/province.o ./out/world.o ./out/date.o ./out/good.o ./out/ai_character.o ./out/diplomacy.o ./out/market.o ./out/screen_loading.o ./out/screen_menu.o ./out/screen_game.o ./out/render_maps.o
		g++ -g -std=c++20 -Wall ./out/province.o ./out/screen_game.o ./out/screen_loading.o ./out/screen_menu.o ./out/ai_character.o ./out/main.o ./out/building.o ./out/market.o ./out/diplomacy.o ./out/country.o ./out/culture.o ./out/render_maps.o ./out/population.o ./out/character.o  ./out/world.o ./out/date.o ./out/good.o  -o sim -lraylib -lGL -lm  -DRAUDIO_STANDALONE -DSUPPORT_FILEFORMAT_WAV -DSUPPORT_FILEFORMAT_OGG -lpthread -ldl -lrt -lX11 -DRAYGUI_IMPLEMENTATION -O3

./out/main.o: main.cpp
	g++ -g -Wall -c main.cpp -o ./out/main.o -O3

./out/building.o: ./src/building.cpp
	g++ -Wall -g -c ./src/building.cpp -o ./out/building.o -O3

./out/province.o: ./src/province.cpp
	g++ -Wall -g -c ./src/province.cpp -o ./out/province.o	-O3

./out/character.o: ./src/character.cpp
	g++ -Wall -g -c ./src/character.cpp -o ./out/character.o -O3

./out/country.o: ./src/country.cpp
	g++ -Wall -g -c ./src/country.cpp -o ./out/country.o -O3

./out/culture.o: ./src/culture.cpp
	g++ -Wall -g -c ./src/culture.cpp -o ./out/culture.o	-O3

./out/population.o: ./src/population.cpp
	g++ -Wall -g -c ./src/population.cpp -o ./out/population.o	-O3

./out/world.o: ./src/world.cpp
	g++ -Wall -g -c ./src/world.cpp -o ./out/world.o	-O3

./out/date.o: ./src/utils/date.cpp
	g++ -Wall -g -c ./src/utils/date.cpp -o ./out/date.o	-O3

./out/good.o: ./src/economy/good.cpp
	g++ -Wall -g -c ./src/economy/good.cpp -o ./out/good.o	-O3

./out/ai_character.o: ./src/agents/ai_character.cpp
	g++ -Wall -g -c ./src/agents/ai_character.cpp -o ./out/ai_character.o -O3

./out/diplomacy.o: ./src/diplomacy.cpp
	g++ -Wall -g -c ./src/diplomacy.cpp -o ./out/diplomacy.o -O3

./out/market.o: ./src/economy/market.cpp
	g++ -Wall -g -c ./src/economy/market.cpp -o ./out/market.o -O3

./out/screen_loading.o: ./src/graphics/screen_loading.cpp
	g++ -Wall -g -c ./src/graphics/screen_loading.cpp -o ./out/screen_loading.o -O3

./out/screen_menu.o: ./src/graphics/screen_menu.cpp
	g++ -Wall -g -c ./src/graphics/screen_menu.cpp -o ./out/screen_menu.o -O3

./out/screen_game.o: ./src/graphics/screen_game.cpp
	g++ -Wall -g -c ./src/graphics/screen_game.cpp -o ./out/screen_game.o -O3

./out/render_maps.o: ./src/graphics/render_maps.cpp
	g++ -Wall -g -c ./src/graphics/render_maps.cpp -o ./out/render_maps.o -O3

clean:
	rm -f ./out/*.o sim

run: sim
	./sim