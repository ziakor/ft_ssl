/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 14:43:01 by dihauet           #+#    #+#             */
/*   Updated: 2021/09/18 16:27:20 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

void	print_algo_name(char *cmd, int fd)
{
	int i;

	i = 0;
    if (fd > 0)
    {
        while (cmd[i])
        {
            ft_putchar(ft_toupper(cmd[i]));
            i++;
        }
    }
}

void	print_hash_data(uint8_t *hash, size_t nb_bits)
{
	size_t		i;
    
	i = 0;
	while (i < nb_bits)
	{
		ft_puthexa(hash[i]);
		i++;
	}
}

void	print_hash(t_hash hash, char *file_name, int write_hexa)
{
    ft_putnbr(write_hexa);
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
}

//
int	print_flag_p(uint8_t *data, size_t length, int flag_p)
{
	if (flag_p)
	{
		ft_putnstr((char*)data, length);
    print_hash_data(data, length);
		if (!(data[length - 1] == '\n'))
			ft_putchar('\n');
    return (SUCCESS);
	}
    return (FAILED);
}

int print_flag_q(uint8_t *data, size_t length, int flag_q)
{
	if (flag_q)
	{
		print_hash_data(data, length);
    ft_putchar('\n');
    return(SUCCESS);
	}
    return(FAILED);
}

int print_flag_r(uint8_t *data, size_t length, char *filename, int flag_r, int fd)
{
    if (flag_r)
    {
        print_hash_data(data, length);
        ft_putstr(" ");
        if (fd == 1)
          ft_putstr("\"");
        ft_putstr(filename);
        if (fd == 1)
          ft_putstr("\"");

        ft_putchar('\n');
        return (SUCCESS);
    }
    return (FAILED);
}

int print_error(uint8_t *data, size_t length, char *filename, int fd)
{
	if (fd < 0)
  {
    if (fd == -1)
    {
      ft_putstr_fd(filename, 2);
      ft_putstr_fd(": ", 2);
    }
    ft_putnstr((char*)data, length);
    ft_putchar_fd('\n', 2);
    return (SUCCESS);
  }
  return (FAILED);
}

