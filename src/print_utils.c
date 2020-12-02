/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 14:43:01 by dihauet           #+#    #+#             */
/*   Updated: 2020/12/02 16:46:07 by dihauet          ###   ########.fr       */
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

void	print_hash_data(uint8_t *hash, size_t nb_bits, int write_hexa)
{
	size_t		i;
    
	i = 0;
	while (i < nb_bits)
	{
		if (write_hexa)
			ft_puthexa(hash[i]);
		else
			ft_putchar(hash[i]);
		i++;
	}
}

void	print_hash(t_hash hash, char *cmd, char *file_name, int write_hexa)
{
	print_algo_name(cmd);
	ft_putstr("(");
	ft_putstr(file_name);
	ft_putstr(")= ");
	print_hash_data(hash.hashed_data, hash.nb_bits, write_hexa);
}

void	print_reverse_hash(t_hash hash, char *filename)
{
	print_hash_data(hash.hashed_data, hash.nb_bits, 1);
	ft_putstr(" *");
	ft_putstr(filename);
}

void	print_error(char *error, char *file_name, int size_data)
{
	int i;

	i = 0;
	
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd(": ", 2);
	// ft_putstr_fd(error, 2);
	while (i < size_data)
	{
		ft_putchar_fd(error[i], 2);
		i++;
	}
	ft_putchar_fd('\n', 2);
}
