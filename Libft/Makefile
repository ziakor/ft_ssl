# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/24 12:26:36 by dihauet           #+#    #+#              #
#    Updated: 2020/08/24 12:26:49 by dihauet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

DIRSRCS = ./srcs/

DIROBJ = ./obj/

SRCS = 	ft_atoi.c \
		get_next_line.c \
		ft_bzero.c \
		ft_count_if.c \
		ft_find_next_prime.c \
		ft_is_prime.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_strndup.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_lstadd.c \
		ft_lstdel.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstmap.c \
		int_str.c \
		null_str.c \
		null_free.c \
		int_free.c \
		free_tab.c \
		ft_lstnew.c \
		ft_memalloc.c \
		ft_memccpy.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memdel.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar.c \
		ft_putchar_fd.c \
		ft_putendl.c \
		ft_putendl_fd.c \
		ft_putnbr.c \
		ft_putnbr_fd.c \
		ft_putstr.c \
		ft_putstr_fd.c \
		ft_sqrt.c \
		ft_strcat.c \
		ft_strchr.c \
		ft_strclr.c \
		ft_strcmp.c \
		ft_strncpy.c \
		ft_strcpy.c \
		ft_strdel.c \
		ft_strdup.c \
		ft_strequ.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strjoin_free.c \
		ft_strlcat.c \
		ft_strlen.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strncat.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strsplit.c \
		ft_strstr.c \
		ft_strsub.c \
		ft_strtrim.c \
		ft_strnequ.c \
		ft_strnew.c \
		ft_tolower.c \
		ft_toupper.c

CC = clang

SRCO = $(patsubst %.c,$(DIROBJ)%.o,$(SRCS))

INC = ./includes/libft.h

NO_COLOR    = \x1b[0m
OK_COLOR    = \x1b[32;01m
WARN_COLOR  = \x1b[33;01m
ERROR_COLOR = \x1b[31;01m
_BLACK = $'\033[30m
_RED = $'\033[31m
_GREEN = $'\033[32m
_YELLOW = $'\033[33m
_BLUE = $'\033[34m
_PURPLE = $'\033[35m
_CYAN = $'\033[36m
_GREY = $'\033[37m

verif = 0

all			 : $(NAME)

$(NAME)		 :	$(SRCO)
				@ar rc $(NAME) $(SRCO)
				@ranlib $(NAME)
				@echo "\n\n${OK_COLOR}Libft : Compilation complete${NO_COLOR}"

$(DIROBJ)%.o :	$(DIRSRCS)%.c $(INC)
				@mkdir -p $(DIROBJ)
				@if [[ $(verif) -eq 0 ]]; then printf "\n$(_BLUE)|==========================>  $(_PURPLE)$(NAME)   $(_BLUE)<==========================|$(_DEF)\n\n";\
				else printf "\e[1A"; fi
				$(eval FNCT = $(words $(SRCS)))
				$(eval verif = $(shell echo $(verif) + 1 | bc ))
				$(eval PCR = $(shell echo "$(verif) / $(FNCT) * 100" | bc -l))
				@printf " \n$(_GREEN)[%3d%%]$(_RED)\t$(_DEF)%-24s 👉$(_YELLOW)\t%-24s$(_DEF)" $(shell echo $(PCR) | sed -E "s:\.[0-9]{20}::") $< $@
				@$(CC) $(CFLAGS) -o $@ -c $<

clean 		 :
				@/bin/rm -f $(SRCO)
				@/bin/rm -rf $(DIROBJ)
				@echo "${WARN_COLOR}Libft : Object files deleted${NO_COLOR}"

fclean 		 :
				@/bin/rm -f $(SRCO)
				@/bin/rm -rf $(DIROBJ)
				@echo "${WARN_COLOR}Libft : Object files deleted${NO_COLOR}"
				@/bin/rm -f $(NAME)
				@echo "${OK_COLOR}Libft : Library deleted${NO_COLOR}"

re 			 :	fclean all

.PHONY		 :	all clean fclean re
