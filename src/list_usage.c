/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_usage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 15:04:43 by dihauet           #+#    #+#             */
/*   Updated: 2020/08/26 15:16:01 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

void	ft_list_commands(void)
{
	ft_putstr_fd("Standard commands:\n\n", 2);
}

void	ft_list_message_digest(void)
{
	ft_putstr_fd("Message Digest commands:\n", 2);
	ft_putstr_fd("md5\nsha256\n\n", 2);
}

void	ft_list_cipher(void)
{
	ft_putstr_fd("Cipher commands:\n\n", 2);
}

void	ft_list_options(void)
{
	ft_putstr_fd("Options commands\n", 2);
	ft_putstr_fd("-p\t\t\techo STDIN to STDOUT and append the ", 2);
	ft_putstr_fd("checksum to STDOUT\n", 2);
	ft_putstr_fd("-r\t\t\treverse the format of the output\n", 2);
	ft_putstr_fd("-q\t\t\tquiet mode\n", 2);
	ft_putstr_fd("-s\t\t\tprint the sum of the given string\n", 2);
}
