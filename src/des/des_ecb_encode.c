/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb_encode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:59:57 by dihauet           #+#    #+#             */
/*   Updated: 2021/02/01 14:11:55 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

uint64_t    ecb_algo(uint64_t data, uint64_t keys[16])
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
    
    i = 0;
    while (i < 8)
    {
        hash_data[i] = (data >> (56 - (i * 8))) & 0xff;
        i++;
    }
}

int     des_ecb_encode(t_parsing *list, t_des *des, unsigned char *str, size_t length)
{
    size_t i;
    uint64_t data;
    size_t bit;
    
    i = 0;
    bit = (((length / 8) + 1 ) * 8) - length; 
    if (list->flags.e)
    {
        if (!(list->list_data->hash.hashed_data = (uint8_t*) malloc(sizeof(uint8_t) * (bit + length) )))
            return (FAILED);
        list->list_data->hash.nb_bits = bit + length;
    }
    while (i < list->list_data->hash.nb_bits)
    {
        data = ecb_get_64bit(&str[i], bit);
        data = ecb_algo(data,des->key48);
        des_put_data(&list->list_data->hash.hashed_data[i], data);
        i+= 8;
    }


    return (SUCCESS);
}

int     des_ecb_decode(t_parsing *list, t_des *des, unsigned char *str, size_t length)
{
    size_t i;
    size_t bit;
    i = 0;

   if (!(list->list_data->hash.hashed_data = (uint8_t*)malloc(sizeof(uint8_t) * (length))))
        return (FAILED);
        list->list_data->hash.nb_bits = length;
    des_ecb_encode(list, des,str,length);
    bit = list->list_data->hash.hashed_data[list->list_data->hash.nb_bits - 1];
    list->list_data->hash.nb_bits = length - bit;
    return(SUCCESS);
}