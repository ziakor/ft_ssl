/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 14:43:01 by dihauet           #+#    #+#             */
/*   Updated: 2020/10/06 14:43:42 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

void	print_algo_name(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		ft_putchar(ft_toupper(cmd[i]));
		i++;
	}
}

void	print_hash_data(uint8_t *hash, size_t nb_bits)
{
	int		i;
	int		j;
	uint8_t	*word;

	i = 0;
	while (i < nb_bits)
	{
		ft_puthexa(hash[i]);
		i++;
	}
}

void	print_hash(t_hash hash, char *cmd, char *file_name)
{
	print_algo_name(cmd);
	ft_putstr("(");
	ft_putstr(file_name);
	ft_putstr(")= ");
	print_hash_data(hash.hashed_data, hash.nb_bits);
	ft_putchar('\n');
}

void	print_reverse_hash(t_hash hash, char *filename)
{
	print_hash_data(hash.hashed_data, hash.nb_bits);
	ft_putstr(" *");
	ft_putstr(filename);
	ft_putchar('\n');
}

void	print_error(char *error, char *file_name)
{
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putchar_fd('\n', 2);
}