CXX=g++
LD=g++
CXXFLAGS=-Wall -pedantic -std=c++17 -g -Wsuggest-override
LDFLAGS=-g -fsanitize=address
OBJS=alexandr.o attackers.o burakov.o clear.o coordinates.o entrance.o exit.o exit_game.o \
fixed_model.o freak.o free.o game.o main.o map.o max.o megadurum.o models.o moves.o nagibator.o neptune.o \
non_fixed_model.o patriot.o record_game.o run.o start_game.o towers.o viking.o wall.o write.o 

all: borovdmy

borovdmy: ${OBJS}

compile: ${OBJS}
	${LD} ${LDFLAGS} $^ -o borovdmy

clean:
	rm -f borovdmy ${OBJS}

run:
	./borovdmy

doc:

%.o: src/%.cpp 
	${CXX} ${CXXFLAGS} -c $< -o $@


alexandr.o: src/alexandr.cpp src/alexandr.h src/attackers.h \
 src/coordinates.h src/models.h src/constants.h src/map.h \
 src/non_fixed_model.h
attackers.o: src/attackers.cpp src/attackers.h src/coordinates.h \
 src/models.h src/constants.h src/map.h src/non_fixed_model.h
burakov.o: src/burakov.cpp src/burakov.h src/towers.h src/coordinates.h \
 src/models.h src/constants.h src/map.h src/non_fixed_model.h
clear.o: src/clear.cpp src/clear.h
coordinates.o: src/coordinates.cpp src/coordinates.h
entrance.o: src/entrance.cpp src/entrance.h src/fixed_model.h \
 src/models.h src/coordinates.h src/constants.h src/map.h
exit.o: src/exit.cpp src/exit.h src/fixed_model.h src/models.h \
 src/coordinates.h src/constants.h src/map.h
exit_game.o: src/exit_game.cpp src/exit_game.h src/clear.h
fixed_model.o: src/fixed_model.cpp src/fixed_model.h src/models.h \
 src/coordinates.h src/constants.h src/map.h
freak.o: src/freak.cpp src/freak.h src/attackers.h src/coordinates.h \
 src/models.h src/constants.h src/map.h src/non_fixed_model.h
free.o: src/free.cpp src/free.h src/fixed_model.h src/models.h \
 src/coordinates.h src/constants.h src/map.h
game.o: src/game.cpp src/game.h src/attackers.h src/coordinates.h \
 src/models.h src/constants.h src/map.h src/non_fixed_model.h \
 src/neptune.h src/towers.h src/viking.h src/moves.h
main.o: src/main.cpp src/run.h src/moves.h src/game.h src/attackers.h \
 src/coordinates.h src/models.h src/constants.h src/map.h \
 src/non_fixed_model.h src/neptune.h src/towers.h src/viking.h \
 src/entrance.h src/fixed_model.h src/exit.h src/wall.h
map.o: src/map.cpp src/viking.h src/attackers.h src/coordinates.h \
 src/models.h src/constants.h src/map.h src/non_fixed_model.h src/exit.h \
 src/fixed_model.h src/entrance.h src/free.h src/neptune.h src/towers.h \
 src/wall.h
max.o: src/max.cpp src/max.h src/attackers.h src/coordinates.h \
 src/models.h src/constants.h src/map.h src/non_fixed_model.h
megadurum.o: src/megadurum.cpp src/megadurum.h src/towers.h \
 src/coordinates.h src/models.h src/constants.h src/map.h \
 src/non_fixed_model.h src/neptune.h
models.o: src/models.cpp src/models.h src/coordinates.h src/constants.h \
 src/map.h
moves.o: src/moves.cpp src/moves.h
nagibator.o: src/nagibator.cpp src/nagibator.h src/attackers.h \
 src/coordinates.h src/models.h src/constants.h src/map.h \
 src/non_fixed_model.h
neptune.o: src/neptune.cpp src/neptune.h src/towers.h src/coordinates.h \
 src/models.h src/constants.h src/map.h src/non_fixed_model.h
non_fixed_model.o: src/non_fixed_model.cpp src/non_fixed_model.h \
 src/coordinates.h src/map.h src/models.h src/constants.h
patriot.o: src/patriot.cpp src/patriot.h src/towers.h src/coordinates.h \
 src/models.h src/constants.h src/map.h src/non_fixed_model.h
record_game.o: src/record_game.cpp src/record_game.h src/game.h \
 src/attackers.h src/coordinates.h src/models.h src/constants.h src/map.h \
 src/non_fixed_model.h src/neptune.h src/towers.h src/viking.h \
 src/moves.h src/alexandr.h src/burakov.h src/freak.h src/max.h \
 src/megadurum.h src/nagibator.h src/patriot.h src/write.h \
 src/exit_game.h src/clear.h
run.o: src/run.cpp src/run.h src/moves.h src/game.h src/attackers.h \
 src/coordinates.h src/models.h src/constants.h src/map.h \
 src/non_fixed_model.h src/neptune.h src/towers.h src/viking.h \
 src/clear.h src/start_game.h src/exit_game.h src/write.h \
 src/record_game.h
start_game.o: src/start_game.cpp src/start_game.h src/attackers.h \
 src/coordinates.h src/models.h src/constants.h src/map.h \
 src/non_fixed_model.h src/game.h src/neptune.h src/towers.h src/viking.h \
 src/moves.h src/exit_game.h src/clear.h src/write.h src/megadurum.h \
 src/patriot.h src/burakov.h src/nagibator.h src/alexandr.h src/max.h \
 src/freak.h src/free.h src/fixed_model.h
towers.o: src/towers.cpp src/towers.h src/coordinates.h src/models.h \
 src/constants.h src/map.h src/non_fixed_model.h
viking.o: src/viking.cpp src/viking.h src/attackers.h src/coordinates.h \
 src/models.h src/constants.h src/map.h src/non_fixed_model.h
wall.o: src/wall.cpp src/wall.h src/fixed_model.h src/models.h \
 src/coordinates.h src/constants.h src/map.h
write.o: src/write.cpp src/write.h
