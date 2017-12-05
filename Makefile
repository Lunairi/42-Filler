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

SRC		= main.c 
OBJ 	= $(addprefix ./objects/, $(SRC:.c=.o))
CFLAG	= -Wall -Wextra -Werror -g
IFLAG	= -I libft -I includes -g

.SILENT:

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	gcc $(CFLAG) -L libft -lft -I libft -I includes $^ -o $(NAME)
	printf '\033[32m[ ✔ ] %s\n\033[0m' "Created filler player"

sanitize: $(OBJ)
	make -C libft/
	gcc -fsanitize=address $(CFLAG) -L libft -lft -I libft -I includes $^ -o $(NAME)
	printf '\033[32m[ ✔ ] %s\n\033[0m' "Fsanitize filler player"

./objects/%.o: ./sources/%.c
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

test: fclean sanitize

.PHONY: clean fclean re all test
