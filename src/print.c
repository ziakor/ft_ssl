/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 15:16:37 by dihauet           #+#    #+#             */
/*   Updated: 2020/11/14 03:16:57 by dihauet          ###   ########.fr       */
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
	while (list)
	{
		if (list->data.fd < 0)
			print_error(list->data.data, list->data.file_name,
			list->data.data_length);
		else if (flags.q)
			print_hash_data(list->hash.hashed_data, list->hash.nb_bits, 1);
		else if (flags.r)
			print_reverse_hash(list->hash, list->data.file_name);
		else
			print_hash(list->hash, cmd, list->data.file_name, write_hexa);
		if (flags.o)
			write_output(flags.o_file, list->hash.hashed_data, list->hash.nb_bits);
		if (list->data.fd >= 0)
			close(list->data.fd);
		ft_putchar('\n');
		list = list->next;
	}
}
