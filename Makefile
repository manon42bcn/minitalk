# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/27 02:38:37 by mporras-          #+#    #+#              #
#    Updated: 2022/03/06 01:21:46 by mporras-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER			=	server
CLIENT			=	client
SRC_DIR			=	srcs
SRV_FILES		=	mt_server_main.c
CLT_FILES		=	mt_client_main.c
SRCS_SRV		=	$(addprefix $(SRC_DIR)/,$(SRV_FILES))
SRCS_CLT		=	$(addprefix $(SRC_DIR)/,$(CLT_FILES))
OBJS_SRV		=	$(SRV_FILES:.c=.o)
OBJS_CLT		=	$(CLT_FILES:.c=.o)
SERVER_BNS		=	server_bonus
CLIENT_BNS		=	client_bonus
SRV_FILES_BNS	=	mt_server_main_bonus.c
CLT_FILES_BNS	=	mt_client_main_bonus.c
SRCS_SRV_BNS	=	$(addprefix $(SRC_DIR)/,$(SRV_FILES_BNS))
SRCS_CLT_BNS	=	$(addprefix $(SRC_DIR)/,$(CLT_FILES_BNS))
OBJS_SRV_BNS	=	$(SRV_FILES_BNS:.c=.o)
OBJS_CLT_BNS	=	$(CLT_FILES_BNS:.c=.o)
CC				=	gcc
RM				= 	rm	-f
CFLAGS			=	-Wall -Wextra -Werror
INCLUDES		=	-Iinc -Ilib/mandatory/inc -Ilib/libft/inc
PRINTF			=	lib/libftprintf.a

all: $(PRINTF) $(SERVER) $(CLIENT)
 
$(SERVER): $(OBJS_SRV)
	$(CC) -o $(SERVER) $(OBJS_SRV) $(PRINTF)

$(CLIENT): $(OBJS_CLT)
	$(CC) -o $(CLIENT) $(OBJS_CLT) $(PRINTF)

$(OBJS_SRV): $(SRCS_SRV)
	$(CC) $(CFLAGS) -c $(SRCS_SRV) $(INCLUDES)

$(OBJS_CLT): $(PRINTF) $(SRCS_CLT)
	$(CC) $(CFLAGS) -c $(SRCS_CLT) $(INCLUDES)

bonus: $(PRINTF) $(SERVER_BNS) $(CLIENT_BNS)

$(SERVER_BNS): $(OBJS_SRV_BNS)
	$(CC) $(CFLAGS) -o $(SERVER_BNS) $(OBJS_SRV_BNS) $(PRINTF)

$(CLIENT_BNS): $(OBJS_CLT_BNS)
	$(CC) $(CFLAGS) -o $(CLIENT_BNS) $(OBJS_CLT_BNS) $(PRINTF)

$(OBJS_SRV_BNS): $(SRCS_SRV_BNS)
	$(CC) $(CFLAGS) -c $(SRCS_SRV_BNS) $(INCLUDES)

$(OBJS_CLT_BNS): $(SRCS_CLT_BNS)
	$(CC) $(CFLAGS) -c $(SRCS_CLT_BNS) $(INCLUDES)

$(PRINTF):
	$(MAKE) -C ./lib

clean:
	$(RM) $(OBJS_SRV) $(OBJS_CLT) $(OBJS_SRV_BNS) $(OBJS_CLT_BNS)
	$(MAKE) clean -C ./lib

fclean: clean
	$(RM) $(SERVER) $(CLIENT)
	$(MAKE) fclean -C ./lib

re:	fclean all

.PHONY: all clean fclean re client server bonus
