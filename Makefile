CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = chess
OBJECTS = main.o game.o player.o human.o computer.o computerLevel.o window.o board.o square.o chesspiece.o king.o queen.o rook.o knight.o bishop.o pawn.o observer.o textdisplay.o graphicsdisplay.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
