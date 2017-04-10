#---------------------------------------------------#
#													#
#	Gomoku Makefile.								#
#													#
#---------------------------------------------------#

NAME = Gomoku

SRC =  ./src/MainController.cpp \
./src/SDLHandler.cpp \
./src/main.cpp

OBJ = $(SRC:.cpp=.o)

CC = clang++ -g -Wall -Werror -Wextra

SDL = -framework SDL2 -framework Cocoa

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