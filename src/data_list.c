/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 10:56:05 by dihauet           #+#    #+#             */
/*   Updated: 2020/09/28 17:15:16 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

void    print_bits(unsigned char octet)
{
    int z = 128, oct = octet;

    while (z > 0)
    {
        if (oct & z)
            write(1, "1", 1);
        else
            write(1, "0", 1);
        z >>= 1;
    }
}

t_list_data	*create_new_elem(char *str, char *file_name, int fd, int size_data)
{
	t_list_data	*new_elem;
	int i;

	i = -1;
	new_elem = NULL;
	if (!(new_elem = (t_list_data*)malloc(sizeof(t_list_data))))
		return (NULL);
	if (!(new_elem->data.data = (char*)malloc(sizeof(char) * size_data)))
		return (NULL);
	while(++i < size_data)
		new_elem->data.data[i] = str[i];
	if (!(new_elem->data.file_name = ft_strdup(file_name)))
		return (NULL);
	new_elem->data.data_length = size_data;
	new_elem->data.fd = fd;
	new_elem->next = NULL;

	
	for (size_t t = 0; t < size_data; t++)
	{
		if(t > 0 && t % 8 == 0)
			ft_putchar('\n');
		print_bits(new_elem->data.data[t]);
		ft_putchar(' ');
	}
	return (new_elem);
}

void		add_new_elem(t_list_data **list, t_list_data *new_elem)
{
	t_list_data *last;

	last = *list;
	if (*list == NULL)
	{
		*list = new_elem;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_elem;
}

void		read_data_list(t_list_data *list)
{
	while (list)
	{
		ft_putstr("ELEM\n");
		ft_putstr(list->data.file_name);
		ft_putchar('\n');
		ft_putstr(list->data.data);
		list = list->next;
		ft_putstr("\n--------\n");
	}
}
