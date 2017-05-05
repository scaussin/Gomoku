#---------------------------------------------------#
#													#
#	Gomoku Makefile.								#
#													#
#---------------------------------------------------#

NAME = Gomoku

SRC =  ./src/MainController.cpp \
./src/ThreadPool.cpp \
./src/Board.cpp \
./src/GameImage.cpp \
./src/GameText.cpp \
./src/SDLHandler.cpp \
./src/MainMenuController.cpp \
./src/InGameController.cpp \
./src/GameController.cpp \
./src/GobanController.cpp \
./src/GameRules.cpp \
./src/GameUI.cpp \
./src/GameRules_FreeThrees.cpp \
./src/GameRules_Captures.cpp \
./src/GameRules_Victory.cpp \
./src/IA.cpp \
./src/Heuristic.cpp \
./src/Heuristic_ThreatSpaceSearch.cpp \
./src/Heuristic_SimpleSearch.cpp \
./src/Heuristic_VictorySearch.cpp \
./src/Heuristic_CaptureSearch.cpp \
./src/BoardTools.cpp \
./src/Tools.cpp \
./src/main.cpp

OBJ = $(SRC:.cpp=.o)

CC = clang++ -g -Wall -Werror -Wextra -Wno-unused-parameter -std=c++11

SDL =  -framework Cocoa -framework SDL2 -F./Frameworks -framework SDL2_ttf

#todo : create the ~/Library/Frameworks/ folder if needed,
# and copy the SDL2_ttf.framework in it.

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(SDL) $(OBJ) -o $@

%.o: %.cpp
	$(CC)  -o $@ -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re