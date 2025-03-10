CC=g++ -std=c++20

EXE = bomberman.out


all: ${EXE}

${EXE}: main.o Enemy.o Game_map.o Player.o Wall.o Bomb.o Power_up.o Key.o Door.o
	${CC} main.o Enemy.o Game_map.o Player.o Wall.o Bomb.o Power_up.o Key.o Door.o -lsfml-graphics -lsfml-window -lsfml-system -o bomberman.out

main.o: main.cpp Game_map.hpp Wall.hpp Enemy.hpp Player.hpp Bomb.hpp Power_up.hpp Key.hpp Door.o
	${CC} -c main.cpp

Game_map.o: Game_map.cpp Game_map.hpp Wall.hpp Enemy.hpp Player.hpp Bomb.hpp Power_up.hpp Key.hpp
	${CC} -c Game_map.cpp

Enemy.o: Enemy.cpp Enemy.hpp
	${CC} -c Enemy.cpp

Player.o: Player.cpp Player.hpp
	${CC} -c Player.cpp

Wall.o: Wall.cpp Wall.hpp
	${CC} -c Wall.cpp

Bomb.o: Bomb.cpp Bomb.hpp
	${CC} -c Bomb.cpp	

Power_up.o: Power_up.cpp Power_up.hpp
	${CC} -c Power_up.cpp

Key.o: Key.cpp Key.hpp
	${CC} -c Key.cpp

Door.o: Door.cpp Door.hpp
	${CC} -c Door.cpp	

clean:
	rm *.o
	rm ${EXE}