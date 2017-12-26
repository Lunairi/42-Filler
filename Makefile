#* ************************************************************************** */
#*                                                                            */
#*    Makefile               _             _              :::      ::::::::   */
#*    By: mlu               | |           | |           :+:      :+:    :+:   */
#*     ___  __ _  __ _ _ __ | | __ _ _ __ | |_        +:+ +:+         +:+     */
#*    / _ \/ _` |/ _` | '_ \| |/ _` | '_ \| __|     +#+  +:+       +#+        */
#*   |  __/ (_| | (_| | |_) | | (_| | | | | |_    +#+#+#+#+#+   +#+           */
#*    \___|\__, |\__, | .__/|_|\__,_|_| |_|\__|        #+#    #+#             */
#*          __/ | __/ | |                             ###   ########.fr       */
#*         |___/ |___/|_|                                                     */
#* ************************************************************************** */

#* I'm bad at makefiles, but I'm good at grilling eggplants

NAME	= mlu.filler

SRC		= main.c parse_stdin.c fill_board.c visual.c \
			place_bottom.c place_top.c pthread.c behavior.c \
			utility.c cut_player.c
CHK		=	./checker/filler_checker.c
OBJ 	= $(addprefix ./objects/, $(SRC:.c=.o))
CFLAG	= -Wall -Wextra -Werror -g
LFLAG	= -L minilibx ./libft/libft.a -lmlx
FFLAG	= -framework OpenGL -framework AppKit
IFLAG	= -I minilibx -I libft -I includes -g

.SILENT:

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	gcc $(CFLAG) $(LFLAG) $(FFLAG) -L minilibx -lmlx -L libft -lft -I libft -I includes $^ -o $(NAME)
	gcc $(CFLAG) $(LFLAG) $(FFLAG) -L minilibx -lmlx -L libft -lft -I libft -I includes $(CHK) -o checker
	printf '\033[32m[ ✔ ] %s\n\033[0m' "Created filler player"

./objects/%.o: ./sources/%.c
	mkdir -p objects
	gcc $(IFLAG) -c $< -o $@

clean:
	make fclean -C libft/
	/bin/rm -f *.o
	/bin/rm -rf ./objects/*.o
	printf '\033[31m[ ✔ ] %s\n\033[0m' "Cleaned filler player"

fclean: clean
	make fclean -C libft/
	/bin/rm -f $(NAME)
	printf '\033[31m[ ✔ ] %s\n\033[0m' "Fcleaned filler player"

re: fclean all

.PHONY: clean fclean re all test
