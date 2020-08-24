/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 14:33:50 by dihauet           #+#    #+#             */
/*   Updated: 2020/08/24 16:59:41 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

void ft_ssl_usage()
{
	ft_putstr_fd("usage: ft_ssl command [command opts] [command args]\n", 2);
}

void list_commands()
{
	ft_putstr_fd("Standard commands:\n", 2);
	ft_putstr_fd("\n", 2);
}

void list_message_digest()
{
	ft_putstr_fd("Message Digest commands:\n", 2);
	ft_putstr_fd("md5\nsha256\n", 2);
}

void list_cipher()
{
	ft_putstr_fd("Cipher commands:\n", 2);
	ft_putstr_fd("\n", 2);
}

void ft_invalid_command( char *command)
{
	ft_putstr_fd("ft_ssl: Error: \'", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd("\' is an invalid command\n", 2);
	list_commands();
	list_message_digest();
	list_cipher();

}