/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 15:16:37 by dihauet           #+#    #+#             */
/*   Updated: 2021/04/06 10:28:53 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

int 	write_output(char *output_file, uint8_t *data, size_t size)
{
	int fd;

	if (!output_file)
		return (FAILED);
	if ((fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0)
		return (FAILED);

	write(fd, data, size);

	return (SUCCESS);
}


void	print_list_hash(t_list_data *list, t_flags flags, char *cmd, int write_hexa)
{
	if (flags.p)
	{
		ft_putstr(list->data.data);
		if (list->data.data[list->data.data_length - 1] != '\n')
			ft_putchar('\n');
	}
}

void	print_one(t_list_data *list, t_flags flag, char *cmd, int is_cipher)
{
	(void)is_cipher;
	while (list)
	{
		if (!print_error(list->data.data, list->data.data_length, list->data.file_name, list->data.fd) && !print_flag_q(list->hash.hashed_data, list->hash.nb_bits, flag.q) &&
				!print_flag_r(list->hash.hashed_data, list->hash.nb_bits, list->data.file_name, flag.r))
		{
			print_algo_name(cmd, list->data.fd);
			ft_putstr("(");
			ft_putstr(list->data.file_name);
			ft_putstr(")= ");
			print_hash_data(list->hash.hashed_data, list->hash.nb_bits);
			ft_putchar('\n');
		}
		if (list->data.fd > 0)
			close(list->data.fd);
		list = list->next;
	}
}

void    print_two(t_list_data *list, t_flags flag, char *cmd, int is_cipher)
{
		if (print_error(list->data.data, list->data.data_length, list->data.file_name, list->data.fd))
				return ;
		if (flag.o)
		{
			write_output(flag.o_file, list->hash.hashed_data, list->hash.nb_bits);
		}
		else {
			ft_putnstr(list->hash.hashed_data, list->hash.nb_bits);
		}
}

void    print_des(t_list_data *list, t_flags flag, char *cmd, int is_cipher)
{
  if (list)
  {
    if (!print_error(list->data.data, list->data.data_length, list->data.file_name, list->data.fd))
    {
      if (flag.P && flag.e == 1)
      {
        flag_print(flag.key, flag.vector, flag.salt);
        if (flag.o)
          write_output(flag.o_file, "", 0);
      }
      else if (flag.o)
      {
          write_output(flag.o_file, list->hash.hashed_data, list->hash.nb_bits);
      }
      else {
        ft_putnstr(list->hash.hashed_data, list->hash.nb_bits);
        
      }
    }
  }
}