/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 13:38:38 by dihauet           #+#    #+#             */
/*   Updated: 2021/06/07 11:01:33 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

int		add_padding(t_padding *padding, unsigned char *data, size_t length,
	size_t endian)
{
	int i;

	padding->initial_length = length;
	padding->nb_bits = length * 8;
	padding->new_length = (448 - (padding->nb_bits + 1)) % 512;
	padding->new_length += padding->nb_bits + 64 + 1;
	padding->new_length = padding->new_length / 8;
	if (!(padding->data_with_padding = (uint8_t*)
		ft_memalloc(sizeof(uint8_t) * padding->new_length)))
		return (FAILED);
	ft_memcpy(padding->data_with_padding, data, length);
	padding->data_with_padding[length] |= 1 << 7;
	if (endian == 1)
		ft_memcpy(padding->data_with_padding + padding->new_length - 8,
		&padding->nb_bits, 8);
	else
	{
		i = -1;
		while (++i < 8)
		{
			padding->data_with_padding[padding->new_length - 8 + i] = (
				(uint8_t*)&(padding->nb_bits))[7 - i];
		}
	}
	return (SUCCESS);
}
