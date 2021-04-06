/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_usage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 15:04:43 by dihauet           #+#    #+#             */
/*   Updated: 2021/04/06 10:32:29 by dihauet          ###   ########.fr       */
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
	ft_putstr_fd("md5\nsha256\nsha3-224\nsha3-256\nsha3-384\n sha3-512\n", 2);
}

void	ft_list_cipher(void)
{
	ft_putstr_fd("Cipher commands:\n\n", 2);
}

void	ft_list_options_1(void)
{
	ft_putstr_fd("Options commands\n", 2);
	ft_putstr_fd("-p\t\t\techo STDIN to STDOUT and append the checksum to STDOUT\n", 2);
	ft_putstr_fd("-r\t\t\treverse the format of the output\n", 2);
	ft_putstr_fd("-q\t\t\tquiet mode\n", 2);
	ft_putstr_fd("-s\t\t\tprint the sum of the given string\n", 2);
}

void	ft_list_options_base64(void)
{
	ft_putstr_fd("Options commands\n", 2);
	ft_putstr_fd("-d\t\t\tdecode mode\n", 2);
	ft_putstr_fd("-e\t\t\tencode mode (default)\n", 2);
	ft_putstr_fd("-i\t\t\tinput file\n", 2);
	ft_putstr_fd("-o\t\t\toutput file\n", 2);
}

void    ft_list_options_des(void)
{
    ft_putstr_fd("Options commands\n", 2);
	ft_putstr_fd("-a\t\t\tdecode/encode the input/output in base64, depending on the encrypt mode\n", 2);
	ft_putstr_fd("-d\t\t\tdecrypt mode\n", 2);
	ft_putstr_fd("-e\t\t\tencrypt mode (default)\n", 2);
	ft_putstr_fd("-i\t\t\tinput file for message\n", 2);
	ft_putstr_fd("-k\t\t\tkey in hex is the next arguement\n", 2);
	ft_putstr_fd("-o\t\t\toutput file for message\n", 2);
	ft_putstr_fd("-p\t\t\tpassword in ascii is the next argument\n", 2);
	ft_putstr_fd("-s\t\t\tthe salt in hex is the next argument\n", 2);
	ft_putstr_fd("-v\t\t\tinitialization vector in hex is the next argument\n", 2);
	ft_putstr_fd("-P\t\t\tprint iv/salt/key and exit\n", 2);



}