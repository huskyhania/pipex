# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/12 13:49:32 by hskrzypi          #+#    #+#              #
#    Updated: 2024/10/30 23:07:46 by hskrzypi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= pipex

NAME_BONUS	:= pipex_bonus

CFLAGS	:= -Wextra -Wall -Werror

LIBLIBFT	:= ./complete_Libft

HEADERS	:= -I ./include -I $(LIBLIBFT)

LIBS	:= -L$(LIBLIBFT) -lft -ldl -lglfw -pthread -lm

SRCS	:= main.c paths.c error_handling.c utils.c helper_pipex.c input_checks.c
SRCS_BONUS	:= ./bonus/main_bonus.c ./bonus/paths_bonus.c ./bonus/error_handling_bonus.c ./bonus/utils_bonus.c ./bonus/helper_pipex_bonus.c ./bonus/input_checks_bonus.c

OBJS	:= ${SRCS:.c=.o}
OBJS_BONUS	:= ${SRCS_BONUS:.c=.o}

RM = rm -rf

all: libft $(NAME)

bonus: libft $(NAME_BONUS)

libft:
	@$(MAKE) -C $(LIBLIBFT)

%.o: %.c
	@$(CC) $(CFLAGS) $< -c -o $@ $(HEADERS) 
	@printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "$(NAME) compiled successfully.\n"

$(NAME_BONUS): $(OBJS_BONUS)
	@$(CC) $(OBJS_BONUS) $(LIBS) $(HEADERS) -o $(NAME_BONUS)
	@echo "$(NAME_BONUS) compiled successfully with bonuses.\n"
	
.bonus: $(OBJS_BONUS)\
	@$(CC) $(OBJS_BONUS) $(LIBS) $(HEADERS) -o $(NAME_BONUS)
	@echo "Bonus build completed.\n"
	@touch .bonus

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	@$(MAKE) clean -C $(LIBLIBFT)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	@$(MAKE) fclean -C $(LIBLIBFT)

re: fclean all

.PHONY: all clean fclean re libft bonus
