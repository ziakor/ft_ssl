/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:33:50 by dihauet           #+#    #+#             */
/*   Updated: 2020/08/26 15:28:50 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

void ft_ssl_usage()
{
	ft_putstr_fd("usage: ft_ssl command [command opts] [command args]\n\n", 2);
}

void ft_invalid_command( char *command)
{
	ft_putstr_fd("ft_ssl: Error: \'", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd("\' is an invalid command\n\n", 2);
	ft_list_commands();
	ft_list_message_digest();
	ft_list_cipher();

}


int ft_invalid_option(char *option, char *command)
{
	ft_putstr_fd("ft_ssl: ", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": unknown option \'", 2);
	ft_putstr_fd(option, 2);
	ft_putstr_fd("`\n\n", 2);
	ft_list_options();
	return (0);
}