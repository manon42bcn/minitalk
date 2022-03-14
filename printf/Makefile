# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/11 20:09:37 by mporras-          #+#    #+#              #
#    Updated: 2022/02/08 00:38:53 by mporras-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		 =	libftprintf.a
SRC_DIR		 =	srcs
LIB 		 =	libft.a
LIB_DIR 	 =	libft/
SRCS_FILES	 =	ft_printf.c \
			  	ft_token_numbers.c \
			  	ft_token_strings.c \
			  	ft_token_process.c
BONUS_FILES	 =	ft_printf_bonus.c \
			  	ft_printf_input_bonus.c \
			  	ft_printf_utils_bonus.c \
			  	ft_token_hexa_bonus.c \
			  	ft_token_numbers_bonus.c \
			  	ft_token_process_bonus.c \
			  	ft_token_strings_bonus.c
BONUS_SRCS	 =	$(addprefix $(SRC_DIR)/,$(BONUS_FILES))
BONUS_OBJS	 =	$(BONUS_FILES:.c=.o)
SRCS 		 =	$(addprefix $(SRC_DIR)/,$(SRCS_FILES))
OBJS		 =	$(SRCS_FILES:.c=.o)
CC			 =	gcc
RM			 =	rm	-f
CFLAGS		 =	-Wall -Wextra -Werror -c
INCLUDES	 =	-Iincludes/ft_printf.h
INCLUDES_BNS =	-Iincludes/ft_printf_bonus.h

all: $(NAME)
 
$(NAME): $(OBJS) $(LIB_DIR)$(LIB)
	cp libft/libft.a $(NAME)
	ar	rcs	$(NAME)	$(OBJS) $(LIB_DIR)$(LIB)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS) $(INCLUDES)

$(LIB_DIR)$(LIB):
	$(MAKE) -C $(LIB_DIR)

bonus: $(BONUS_OBJS) $(LIB_DIR)$(LIB)
	cp libft/libft.a $(NAME)
	ar	rcs	$(NAME)	$(BONUS_OBJS)

$(BONUS_OBJS): $(BONUS_SRCS)
	$(CC) $(CFLAGS) -c $(BONUS_SRCS) $(INCLUDES_BNS)

clean:
	$(MAKE) -C $(LIB_DIR) clean
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(MAKE) -C $(LIB_DIR) fclean
	$(RM) $(NAME)

re:	fclean $(NAME)

.PHONY: all clean fclean re bonus
