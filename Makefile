# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/28 11:44:24 by dihauet           #+#    #+#              #
#    Updated: 2021/06/07 11:24:33 by dihauet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL := /bin/bash

NAME = ft_ssl

DIRSRCS = ./src/

DIROBJ = ./obj/

SRCS = main.c usage.c parsing.c parsing_functions.c list_usage.c data_list.c  error.c clean.c md5/md5.c md5/md5_utils.c hash.c print_utils.c print.c padding.c utils.c sha256/sha256.c sha256/sha256_utils.c sha3/sha3_256.c sha3/sha3.c sha3/sha3_utils.c sha3/sha3_512.c sha3/sha3_224.c sha3/sha3_384.c flag.c process.c parsing_file.c list_read_data.c parsing_stdin.c base64/base64_utils.c base64/base64.c des/des.c des/des_utils.c des/keys.c des/keys2.c  des/des_ecb_encode.c des/des_ecb_utils.c des/des_cbc.c flag_utils.c

INC = ./includes/

LIB = ./Libft/

LIB_H = ./Libft/libft.h

LIB_A = ./Libft/libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

OBJ = $(patsubst %.c,$(DIROBJ)%.o,$(SRCS))

NO_COLOR    = \x1b[0m
OK_COLOR    = \x1b[32;01m
WARN_COLOR  = \x1b[33;01m
ERROR_COLOR = \x1b[31;01m
_BLACK = \033[30m
_RED = \033[31m
_GREEN = \033[32m
_YELLOW = \033[33m
_BLUE = \033[34m
_PURPLE = \033[35m
_CYAN = \033[36m
_GREY = \033[37m

verif = 0

all:			$(NAME)

$(LIB_A):
				@make -C $(LIB)

$(NAME):		$(LIB_A) $(OBJ)
				@$(CC) $^ -I $(INC) -I $(LIB_H) $(CFLAGS) $(LIB_A) -o $@
				@echo "\n\n${OK_COLOR}${NAME} : Compilation complete${NO_COLOR}"

$(DIROBJ)%.o:	$(DIRSRCS)%.c $(INC)
				@mkdir -p $(DIROBJ)/md5 $(DIROBJ)/sha256 $(DIROBJ)/sha3 $(DIROBJ)/base64 $(DIROBJ)/des
				@if [[ $(verif) -eq 0 ]]; then printf "\n$(_BLUE)|==========================>  $(_PURPLE)$(NAME)   $(_BLUE)<==========================|$(_DEF)\n";\
				else printf "\e[1A"; fi
				$(eval FNCT = $(words $(SRCS)))
				$(eval verif = $(shell echo $(verif) + 1 | bc ))
				$(eval PCR = $(shell echo "$(verif) / $(FNCT) * 100" | bc -l))
				@printf " \n$(_GREEN)[%3d%%]$(_RED)\t$(_DEF)%-24s 👉$(_YELLOW)\t%-24s$(_DEF)" $(shell echo $(PCR) | sed -E "s:\.[0-9]{20}::") $< $@
				@$(CC) $(CFLAGS) -o $@ -c $<

clean:
				@make -C $(LIB) clean
				@rm -f $(OBJ)
				@echo "${OK_COLOR}${NAME} : Object files deleted${NO_COLOR}"

fclean:
				@make -C $(LIB) fclean
				@rm -f $(OBJ)
				@rm -rf $(DIROBJ)
				@echo "${WARN_COLOR}${NAME} : Object files deleted${NO_COLOR}"
				@rm -f $(NAME)
				@echo "${OK_COLOR}${NAME} : Executable deleted${NO_COLOR}"

re:				fclean all

.PHONY:			all clean fclean re
