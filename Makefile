#---------------------------------------------------#
#													#
#	Gomoku Makefile.								#
#													#
#---------------------------------------------------#

NAME = Gomoku

SRC =  ./src/MainController.cpp \
./src/GameImage.cpp \
./src/GameText.cpp \
./src/SDLHandler.cpp \
./src/MainMenuController.cpp \
./src/InGameController.cpp \
./src/Tools.cpp \
./src/main.cpp

OBJ = $(SRC:.cpp=.o)

CC = clang++ -g -Wall -Werror -Wextra

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