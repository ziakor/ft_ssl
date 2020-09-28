/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha3_256.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 11:25:38 by dihauet           #+#    #+#             */
/*   Updated: 2020/09/28 14:47:12 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

void    print_bits1(unsigned char octet)
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

int padding_sha3(t_padding *padding, char *data, size_t length)
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
    padding->data_with_padding[padding->new_length - 1] ^= SHA3_256_SUFFIX_D;

    i = 0;
    while (i < padding->new_length)
    {
        print_bits1(padding->data_with_padding[i]);
        ft_putchar(' ');
        i++;
    }
    return (SUCCESS);
}



int         sha3_256(t_hash *hash, char *str, size_t length)
{
    t_sha_3 sha3;
    ft_bzero(&sha3, sizeof(t_sha_3));
    padding_sha3(&sha3.padding, str, length);
}