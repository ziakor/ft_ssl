/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 15:16:37 by dihauet           #+#    #+#             */
/*   Updated: 2021/09/14 15:43:26 by dihauet          ###   ########.fr       */
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


void	print_list_hash(t_list_data *list, t_flags flags)
{
	if (flags.p)
	{
		ft_putstr((const char*)list->data.data);
		if (list->data.data[list->data.data_length - 1] != '\n')
			ft_putchar('\n');
	}
}

void	print_one(t_list_data *list, t_flags flag, char *cmd)
{
 int first = 0;
	while (list)
	{

    if ( list->data.fd < 0)
    {
      print_error(list->data.data, list->data.data_length, list->data.file_name, list->data.fd);
      list = list->next;
      continue;
    }
    if (flag.p == 1 && list->data.fd == 0 && flag.q == 1)
    {
        ft_putnstr(list->data.data, list->data.data_length);
    }
    if (flag.q == 1)
    {
      print_flag_q(list->hash.hashed_data, list->hash.nb_bits, flag.q) ;
    }
    else if (flag.r == 1) 
    {
			if (flag.p == 1 && first == 0)
			{
        first = 1;
				ft_putstr("(");
				ft_putchar('\"');
				for (size_t x = 0; x < list->data.data_length; x++)
        {
          if (list->data.data[x] == '\n')
            break;
          ft_putchar(list->data.data[x]);
        }
        
				ft_putstr("\")= ");
				print_hash_data(list->hash.hashed_data, list->hash.nb_bits);
        ft_putchar('\n');
			}
			else
			{
				print_flag_r(list->hash.hashed_data, list->hash.nb_bits, list->data.file_name, flag.r);
			}
    }
    else 
    {
			print_algo_name(cmd, list->data.fd);
			ft_putstr("(");
      if (flag.p == 1 && first == 0){
        first = 1;
        ft_putchar('\"');
				for (size_t x = 0; x < list->data.data_length; x++)
        {
          if (list->data.data[x] == '\n')
            break;
          ft_putchar(list->data.data[x]);
        }
      }else {

			ft_putstr(list->data.file_name);		
      }
			ft_putstr(")= ");
			print_hash_data(list->hash.hashed_data, list->hash.nb_bits);
			ft_putchar('\n');
    }
		list = list->next;
	}
}

void    print_two(t_list_data *list, t_flags flag, char *cmd)
{
    (void)cmd;
		if (print_error(list->data.data, list->data.data_length, list->data.file_name, list->data.fd))
				return ;
		if (flag.o)
		{
			write_output(flag.o_file, list->hash.hashed_data, list->hash.nb_bits);
		}
		else {
			ft_putnstr((char*)list->hash.hashed_data, list->hash.nb_bits);
		}
}

void    print_des(t_list_data *list, t_flags flag, char *cmd)
{
  (void)cmd;
  if (list)
  {
    if (!print_error(list->data.data, list->data.data_length, list->data.file_name, list->data.fd))
    {
      if (flag.P && flag.e == 1)
      {
        flag_print(flag.key, flag.vector, flag.salt);
        if (flag.o)
          write_output(flag.o_file, (uint8_t*)"", 0);
      }
      else if (flag.o)
      {
          write_output(flag.o_file, list->hash.hashed_data, list->hash.nb_bits);
      }
      else {
        // for (size_t i = 0; i < list->hash.nb_bits; i++)
        // {
        //     int k = 8;
        //     while (k >= 0){
        //       printf("%d", ((list->hash.hashed_data[i] )>> k) & 1);
        //     k--;
        //   }
        //   printf(" ");
        // }
        
      }
    }
  }
}