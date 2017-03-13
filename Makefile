NAME = ft_retro

CLANG = clang++

FLAG = -Wall -Wextra -Werror -g

SRC = main.cpp \
	  Game.cpp \
	  Player.cpp \
	  AEntity.cpp \
	  Weapon.cpp \
	  Missile.cpp \
	  Enemy.cpp \
	  Boss.cpp \
	  Bonus.cpp \
	  WeapTwoMissSameSide.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CLANG) $(FLAG) -o $@ $^ -lncurses
	@echo "\033[92m[ft_retro] compilation SUCESS"

%.o:%.cpp
	@$(CLANG) $(FLAG) -c -o $@ $<

clean:
	@rm -f $(OBJ)
	@echo "cleaning object files (.o)"

fclean: clean
	@rm -f $(NAME)
	@echo "cleaning executable ft_retro"

re: fclean all

.PHONY: clean fclean re
