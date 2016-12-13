NAME = ft_retro

CLANG = clang++

FLAG = -Wall -Wextra -Werror

SRC = main.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CLANG) $(FLAG) -o $@ $^ -lncurses

%.o:%.cpp
	@$(CLANG) $(FLAG) -c -o $@ $<
	@echo "\033[92m[ft_retro] compilation SUCESS"

clean:
	@rm -f $(OBJ)
	@echo "cleaning object files (.o)"

fclean: clean
	@rm -f $(NAME)
	@echo "cleaning executable ft_retro"

re: fclean all

.PHONY: clean fclean re
