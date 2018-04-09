# =========================================================
# Makefile for sys_info
# =========================================================

.PHONY: all clean fclean re debug launch install uninstall
.SUFFIXES:

# ---------------------
# Colors
# ---------------------
WHITE    := \033[7;49;39m
BLUE     := \033[7;49;34m
GREEN    := \033[0;49;32m
GREEN_BG := \033[1;49;32m
GRAY     := \033[7;49;90m
NO_COLOR := \033[m

# ---------------------
# Project settings
# ---------------------
NAME       := sys_info
SYSTEM     := $(shell uname -s)
DEBUG      := no
OPTI       := yes
OPTI_FLAGS := -O2
DEBUG_FLAGS:= -pedantic -Weverything -std=c++98

CC         := clang++
FLAGS      := -Wall -Wextra -Werror
SPE_FLAGS  := $(if $(filter yes,$(DEBUG)),$(DEBUG_FLAGS),$(if $(filter yes,$(OPTI)),$(OPTI_FLAGS),))

INCLUDE_LIBS := -lncurses

SRC_DIR    := src/
OBJ_DIR    := bin/
INC_DIR    := includes

FILES := \
Core.cpp \
Displays/beautiful/BeautifulDisplay.cpp \
Displays/ncurses/NcursesDisplay.cpp \
main.cpp \
modules/Cat/Cat.cpp \
modules/Hostname/Hostname.cpp \
modules/CPU/MainCpu.cpp \
modules/Memory/MainMemory.cpp \
modules/Network/NetworkModule.cpp \
modules/OS/OSModule.cpp \
modules/Time/TimeModule.cpp

OBJ := $(FILES:.cpp=.o)
OBJ_PATHS := $(addprefix $(OBJ_DIR), $(OBJ))

# ---------------------
# Rules
# ---------------------
all: $(NAME)

$(NAME): install $(OBJ_DIR) $(OBJ_PATHS)
	@$(CC) $(FLAGS) $(SPE_FLAGS) $(OBJ_PATHS) -o $@
	@echo "Created $(NAME)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@$(CC) $(FLAGS) $(SPE_FLAGS) -c $< -o $@
	@echo "$< compiled"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Removed object files"

fclean: clean
	@rm -f $(NAME)
	@echo "Removed $(NAME)"

re: fclean all

debug:
	@$(CC) $(DEBUG_FLAGS) $(addprefix $(SRC_DIR), $(FILES)) -I$(INC_DIR) -o $(NAME)
	@./$(NAME)

launch: re
	@./$(NAME)
