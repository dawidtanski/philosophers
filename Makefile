# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dtanski <dtanski@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/01 16:45:03 by dtanski           #+#    #+#              #
#    Updated: 2025/04/01 16:45:03 by dtanski          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_DIR	=./src
OBJ_DIR	=./obj
INC_DIR =./inc

CC = gcc
##  
CFLAGS = -fsanitize=thread -Wall -Wextra -Werror -g -lpthread
INC		= -I $(INC_DIR)

#SRC
SRC			=	main.c \


OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

#TEXT COLORSS
GREEN		=	\033[0;32m
RED 		=	\033[0;31m
YELLOW		=	\033[0;33m
RESET		=	\033[0m

all:	$(NAME)

$(NAME):$(OBJ)
		@echo "$(RED)[ .. ] Compiling Mandatory..$(RESET)"
		@$(CC) $(CFLAGS) $(INC) $(OBJ) $(LIB) -o $@
		@echo "$(GREEN)[ OK ]$(RESET) $(YELLOW)Mandatory Ready!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC) -o	$@ -c $<


clean: 
		@rm -rf $(OBJ)
		@rm -rf $(SRC_DIR)/*.d
		@echo "Object files removed"

fclean: clean
		@rm -rf $(NAME)
		@echo "Binary files removed"

re:		fclean all

.PHONY:	all clean fclean re
