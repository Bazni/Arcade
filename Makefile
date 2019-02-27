##
## EPITECH PROJECT, 2018
## ArcadeApplication
## File description:
## Makefile
##

CXX		=	g++

INC		=	-I src/

CXXFLAGS	+=	-Wall -Wextra -pedantic -std=c++17 -fPIC $(INC)

LDFLAGS		=	-ldl

## arcade

NAME		=	arcade

SRC_DIR		=	src/

SRC		=	$(SRC_DIR)Main.cpp			\
			$(SRC_DIR)ArcadeApplication.cpp		\
			$(SRC_DIR)Core/Core.cpp			\
			$(SRC_DIR)Core/HighScoreManager.cpp	\
			$(SRC_DIR)LibraryLoader.cpp

OBJ		=	$(SRC:.cpp=.o)

## plugin sfml

NAME_SFML	=	lib/lib_arcade_sfml.so

SRC_SFML	=	$(SRC_DIR)Libraries/SFML.cpp

OBJ_SFML	=	$(SRC_SFML:.cpp=.o)

LDFLAGS_SFML	=	-shared -fPIC -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio

## plugin sdl

NAME_SDL	=	lib/lib_arcade_sdl.so

SRC_SDL		=	$(SRC_DIR)Libraries/SDL.cpp

OBJ_SDL		=	$(SRC_SDL:.cpp=.o)

LDFLAGS_SDL	=	-shared -fPIC -lSDL2 -lSDL2_ttf -lSDL2_image

## plugin libcaca

NAME_CACA	=	lib/lib_arcade_libcaca.so

SRC_CACA	=	$(SRC_DIR)Libraries/LibCaca.cpp

OBJ_CACA	=	$(SRC_CACA:.cpp=.o)

LDFLAGS_CACA	=	-shared -fPIC -lcaca

## plugin allegro

NAME_ALLEGRO	=	lib/lib_arcade_allegro.so

SRC_ALLEGRO	=	$(SRC_DIR)Libraries/Allegro.cpp

OBJ_ALLEGRO	=	$(SRC_ALLEGRO:.cpp=.o)

LDFLAGS_ALLEGRO	=	-shared -fPIC -lallegro -lallegro_image -lallegro_ttf

## pacman

NAME_PACMAN	=	games/lib_arcade_pacman.so

SRC_PACMAN	=	$(SRC_DIR)Games/Pacman/Pacman.cpp   \
			$(SRC_DIR)Games/Pacman/AIGhost.cpp

OBJ_PACMAN	=	$(SRC_PACMAN:.cpp=.o)

LDFLAGS_PACMAN	=	-shared -fPIC

## snake

NAME_SNAKE	=	games/lib_arcade_nibbler.so

SRC_SNAKE	=	$(SRC_DIR)Games/Snake/Snake.cpp

OBJ_SNAKE	=	$(SRC_SNAKE:.cpp=.o)

LDFLAGS_SNAKE	=	-shared -fPIC

## solarfox

NAME_SOLAR	=	games/lib_arcade_solarfox.so

SRC_SOLAR	=	$(SRC_DIR)Games/SolarFox/SolarFox.cpp

OBJ_SOLAR	=	$(SRC_SOLAR:.cpp=.o)

LDFLAGS_SOLAR	=	-shared -fPIC

all:			core games graphicals

core:			$(NAME)

games:			$(NAME_PACMAN)  $(NAME_SNAKE) $(NAME_SOLAR)

graphicals:		$(NAME_SFML) $(NAME_SDL) $(NAME_CACA) $(NAME_ALLEGRO)

$(NAME_SFML):		$(OBJ_SFML)
			$(CXX) $(OBJ_SFML) -o $(NAME_SFML) $(LDFLAGS_SFML)

$(NAME_SDL):		$(OBJ_SDL)
			$(CXX) $(OBJ_SDL) -o $(NAME_SDL) $(LDFLAGS_SDL)

$(NAME_CACA):		$(OBJ_CACA)
			$(CXX) $(OBJ_CACA) -o $(NAME_CACA) $(LDFLAGS_CACA)

$(NAME_ALLEGRO):	$(OBJ_ALLEGRO)
			$(CXX) $(OBJ_ALLEGRO) -o $(NAME_ALLEGRO) $(LDFLAGS_ALLEGRO)

$(NAME_PACMAN):		$(OBJ_PACMAN)
			$(CXX) $(OBJ_PACMAN) -o $(NAME_PACMAN) $(LDFLAGS_PACMAN)

$(NAME_SNAKE):		$(OBJ_SNAKE)
			$(CXX) $(OBJ_SNAKE) -o $(NAME_SNAKE) $(LDFLAGS_SNAKE)

$(NAME_SOLAR):		$(OBJ_SOLAR)
			$(CXX) $(OBJ_SOLAR) -o $(NAME_SOLAR) $(LDFLAGS_SOLAR)

$(NAME):		$(OBJ)
			$(CXX) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
			$(RM) $(OBJ_SFML) $(OBJ_SDL) $(OBJ_CACA) $(OBJ_PACMAN) $(OBJ_SNAKE) $(OBJ) $(OBJ_ALLEGRO) $(OBJ_SOLAR)

fclean:			clean
			$(RM) $(NAME_SFML) $(NAME_SDL) $(NAME_CACA) $(NAME_PACMAN) $(NAME_SNAKE) $(NAME) $(NAME_ALLEGRO) $(NAME_SOLAR)

re:			fclean all

.PHONY:			clean fclean re all
