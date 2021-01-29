/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb_encode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:59:57 by dihauet           #+#    #+#             */
/*   Updated: 2021/01/29 20:41:13 by dihauet          ###   ########.fr       */
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
// >>>>>>>>>>>>>>>>>>>>>>>>>>>ENCULER DONNER MAL COPIER EN BINAIRE FDP
    i = 0;
    printf("str");
    for (size_t j = 0; j < length; j++)
    {
        printf("|%d|", str[j]);
    }
    printf("\n--data brute----\n");
    for (size_t j = 0; j < length; j++)
    {
        if (j > 0 && j % 8 == 0)
            printf("\n");
        for (size_t k = 7; k < -1; k--)
        {
            printf("%d", (str[j] >> k) & 1);
        }
    }
    printf("\n-----commencement algo----\n");
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
        for (size_t j = 63; j < -1; j--)
        {
            printf("%d", (data >> j) & 1);
        }
        printf("\n");
        
        data = ecb_algo(data,des->key48);
        des_put_data(&list->list_data->hash.hashed_data[i], data);
        i+= 8;
    }
    printf("ENCODE POST %d\n", length);
    printf("hash\n");
    for (size_t j = 0; j < list->list_data->hash.nb_bits; j++)
    {
        printf("|%d|", list->list_data->hash.hashed_data[j]);
    }

    printf("\nEND ENCODE POST\n");
    int fd = open("salsifi", O_WRONLY);
    write(1, list->list_data->hash.hashed_data, list->list_data->hash.nb_bits);
    exit (0);
    return (SUCCESS);
}

int     des_ecb_decode(t_parsing *list, t_des *des, unsigned char *str, size_t length)
{
    size_t i;
    size_t bit;
    i = 0;
    bit = str[length - 1];

    if (!(list->list_data->hash.hashed_data = (uint8_t*)malloc(sizeof(uint8_t) * (length))))
        return (FAILED);
    des_ecb_encode(list, des,str,length);
    list->list_data->hash.nb_bits = length - bit;
    
    return(SUCCESS);
}