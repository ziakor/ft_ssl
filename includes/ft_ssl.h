/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 12:38:56 by dihauet           #+#    #+#             */
/*   Updated: 2020/08/26 18:16:50 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H

# include <stdio.h>

# include "../Libft/includes/libft.h"
# include "./md5.h"
# include "./parsing.h"


/*
** usage.c
** functions about usage error message
*/

void ft_ssl_usage();
void ft_list_commands();
void ft_list_message_digest();
void ft_list_cipher();
void ft_list_options();
void ft_invalid_command( char *command);
int ft_invalid_option(char *option, char *command);
static const t_parsing	g_all_cmd[] =
{
	{"md5", {0,0,0,0}, NULL},
	{"sha256",{0,0,0,0},NULL},
	{NULL,{0,0,0,0}, NULL},
};
#endif