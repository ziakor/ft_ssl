/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 12:38:56 by dihauet           #+#    #+#             */
/*   Updated: 2020/09/07 13:39:12 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H //J'ai rajoutee ca ici parce que il me petait a la gueule

# include <stdio.h> //A supprimer evidement quand tu auras plus besoin
# include <stdlib.h>
# include <stdint.h>
# include <string.h>
# include <errno.h>
# include <stddef.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>

typedef struct	s_padding
{
	size_t	initial_length;
	size_t	new_length;
	size_t	nb_bits;
	uint8_t *data_with_padding;
}								t_padding;

# include "../Libft/includes/libft.h"
# include "./md5.h"
# include "./parsing.h"

static const t_parsing	g_all_cmd[] =
{
	{"md5", {0, 0, 0, 0}, NULL, md5, NULL},
	{"sha256", {0, 0, 0, 0}, NULL, NULL, NULL},
	{NULL, {0, 0, 0, 0}, NULL, NULL, NULL},
};



/*
** usage.c
** functions about usage error message
*/

void	ft_ssl_usage();
void	ft_list_commands();
void	ft_list_message_digest();
void	ft_list_cipher();
void	ft_list_options();
void	ft_invalid_command(char *command);
int		ft_invalid_option(char *option, char *command);

/*
** error.c
** functions about error message (open, read,...)
*/

void	error_open_directory(char *file_name, char *cmd);
void	error_open_file(char *file_name, char *cmd);

/*
** clean.c
** function free malloc
*/

void	clean_parsing(t_list_data *list_data);

/*
** hash.c
** function about hash(md5,sha256,etc..)
*/
	int hash_data(t_parsing *list);

#endif
