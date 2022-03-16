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
LIB				=	libftprintf.a
LIB_DIR			=	printf/
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
INCLUDES		=	-Iinc/minitalk.h
INCLUDES_BNS	=	-Iinc/minitalk.h

all: $(SERVER) $(CLIENT)
 
$(SERVER): $(OBJS_SRV) $(LIB_DIR)$(LIB)
	$(CC) -o $(SERVER) $(OBJS_SRV) $(LIB_DIR)$(LIB)

$(CLIENT): $(OBJS_CLT) $(LIB_DIR)$(LIB)
	$(CC) -o $(CLIENT) $(OBJS_CLT) $(LIB_DIR)$(LIB)

$(OBJS_SRV): $(SRCS_SRV)
	$(CC) $(CFLAGS) -c $(SRCS_SRV) $(INCLUDES)

$(OBJS_CLT): $(SRCS_CLT)
	$(CC) $(CFLAGS) -c $(SRCS_CLT) $(INCLUDES)

$(LIB_DIR)$(LIB):
	$(MAKE) -C $(LIB_DIR)

bonus: $(SERVER_BNS) $(CLIENT_BNS)

$(SERVER_BNS): $(OBJS_SRV_BNS) $(LIB_DIR)$(LIB)
	$(CC) $(CFLAGS) -o $(SERVER_BNS) $(OBJS_SRV_BNS) $(LIB_DIR)$(LIB)
	mv server_bonus server

$(CLIENT_BNS): $(OBJS_CLT_BNS) $(LIB_DIR)$(LIB)
	$(CC) $(CFLAGS) -o $(CLIENT_BNS) $(OBJS_CLT_BNS) $(LIB_DIR)$(LIB)
	mv client_bonus client

$(OBJS_SRV_BNS): $(SRCS_SRV_BNS)
	$(CC) $(CFLAGS) -c $(SRCS_SRV_BNS) $(INCLUDES_BNS)

$(OBJS_CLT_BNS): $(SRCS_CLT_BNS)
	$(CC) $(CFLAGS) -c $(SRCS_CLT_BNS) $(INCLUDES_BNS)

clean:
	$(MAKE) -C $(LIB_DIR) clean
	$(RM) $(OBJS_SRV) $(OBJS_CLT) $(OBJS_SRV_BNS) $(OBJS_CLT_BNS)

fclean: clean
	$(MAKE) -C $(LIB_DIR) fclean
	$(RM) $(SERVER) $(CLIENT)

re:	fclean all

.PHONY: all clean fclean re client server bonus
