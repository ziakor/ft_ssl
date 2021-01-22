/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb_encode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:59:57 by dihauet           #+#    #+#             */
/*   Updated: 2021/01/22 16:04:22 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

uint64_t    ecb_encode_algo(uint64_t data, uint64_t keys[16])
{
    uint64_t tmp;
    uint64_t left0;
    uint64_t right0;
    uint64_t right1; // a supprimer(pas obligatoire)
    int i;

    tmp = make_initial_permutation(data);
    left0 = (tmp >> 32) & 0xffffffff;
    right0 = tmp & 0xffffffff;

    i = 0;
    while (i < 16)
    {
        tmp = make_substitution(make_expansion_permutation(right0) ^ keys[i]);

        right1 =  left0 ^ make_permutation(tmp);
        left0 = right0;
        right0 = right1;
        i++;
    }
    return(make_reverse_permutation((right1 << 32) + left0));
}

void    des_put_data(uint8_t *hash_data, uint64_t data)
{
    int i;
    
    while (i < 8)
    {
        hash_data[i] = (data >> (56 - ( i * 8))) & 0xff;
        i++;
    }
}

int     des_ecb_encode(t_parsing *list, t_des *des, char *str, size_t length)
{
    size_t i;
    uint64_t data;
    size_t bit;

    i = 0;
    bit = (((length / 8) + 1 ) * 8) - length; 
    if (!(list->list_data->hash.hashed_data = (uint8_t*) malloc(sizeof(uint8_t) * (bit + length) )))
        return (FAILED);
    list->list_data->hash.nb_bits = bit + length;
    while (i < length || i % 8 != 0)
    {
        data = ecb_get_64bit(&str[i], bit);
        data = ecb_encode_algo(data,des->key48);
        des_put_data(&list->list_data->hash.hashed_data[i], data);
        i+= 8;
    }
    return (SUCCESS);
}