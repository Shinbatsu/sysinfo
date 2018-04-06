.PHONY : clean, fclean, re, all, $(NAME), lanch, debug, install, uninstall
.SUFFIXES :

# Colors :
WHITE = \033[7;49;39m
BLUE = \033[7;49;34m
GREEN = \033[0;49;32m
GREEN_BG = \033[1;49;32m
GRAY = \033[7;49;90m
NO_COLOR = \033[m


NAME = sys_info

SYSTEM = $(shell uname -s)

DEBUG = no
OPTI_FLAGS = -O2
DEBUG_FLAG = -pedantic -Weverything -std=c++98

CC = clang++
FLAG = -Wall -Wextra -Werror
ifeq ($(DEBUG), yes)
        SPE_FLAGS = $(DEBUG_FLAG)
else ifeq ($(OPTI), yes)
        SPE_FLAGS = $(OPTI_FLAGS)
else
		SPE_FLAGS =
endif
ifeq (SYSTEM, Darwin)
	DEPSFLAGS =
else
	DEPSFLAGS =
endif

INCLUDE_LIBS := -lncurses

SRC = src/

FILES =\
Core.cpp\
Displays/beautiful/BeautifulDisplay.cpp\
Displays/ncurses/NcursesDisplay.cpp\
main.cpp\
modules/Cat/Cat.cpp\
modules/Hostname/Hostname.cpp\
modules/CPU/MainCpu.cpp\
modules/Memory/MainMemory.cpp\
modules/Network/NetworkModule.cpp\
modules/OS/OSModule.cpp\
modules/Time/TimeModule.cpp

OBJ_DIR = bin/
OBJ_PATHS = $(addprefix $(OBJ_DIR), $(dir $(OBJ)))
OBJ = $(FILES:.cpp=.o)

INC_DIR = ./includes
INC = $(SRC)
INC_FILES = #$(SRC:.cpp=.hpp)# ls -1 > src.txt &&

AUTOR = shinbatsu

all : $(NAME)

$(NAME) : install $(OBJ_DIR) $(addprefix $(OBJ_DIR), $(OBJ)) $(addprefix $(INC), $(INC_FILES)) $(AUTOR)
	@($(CC) $(FLAGS) $(SPE_FLAGS) $(addprefix $(OBJ_DIR), $(OBJ)) -o $(NAME))
	@(echo creation de $(NAME))

$(OBJ_DIR)%.o : $(addprefix $(SRC), %.cpp) $(addprefix $(INC), $(INC_FILES))
	@($(CC) $(FLAG) $(SPE_FLAGS) -c $< -o $@)
	@(echo $< " created")

$(OBJ_DIR) :
	mkdir -p $(OBJ_PATHS)

clean :
	@(rm -f $(addprefix $(OBJ_DIR), $(OBJ)))
	@(rm -rf $(OBJ_DIR))
	@(echo suppression des $(OBJ_DIR).o)

fclean : clean
	@(rm -f $(NAME))
	@(echo suppression de $(NAME))

re : fclean all

debug :
	@($(CC) $(DEBUG_FLAG) $(addprefix $(SRC), $(FILES)) -I$(INC) -o $(NAME))
	./$(NAME)

lanch : re
	./$(NAME)