/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ecb_encode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:59:57 by dihauet           #+#    #+#             */
/*   Updated: 2021/09/18 10:47:55 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

uint64_t    ecb_algo(uint64_t data, uint64_t keys[16])
{
    uint64_t tmp;
    uint64_t left0;
    uint64_t right0;
    uint64_t right1;
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

static void  des_core(t_parsing *list, t_des *des, unsigned char *str, size_t length)
{
    size_t i;
    uint64_t data;

    i = 0;
    while (i < length)
    {
        data = ecb_get_64bit((char*)&str[i], des->pad_bit, length - i - des->pad_bit);
        data = ecb_algo(data,des->key48);
  
        des_put_data(&list->list_data->hash.hashed_data[i], data);
        i+= 8;
    }

    
}

int     des_ecb_encode(t_parsing *list, t_des *des, unsigned char *str, size_t length)
{
    uint8_t* tmp;

    des->pad_bit = (((length / 8) + 1 ) * 8) - length; 
    
    length = des->pad_bit + length;
    if (!(list->list_data->hash.hashed_data = (uint8_t*) malloc(sizeof(uint8_t) * (length) )))
        return (FAILED);
    list->list_data->hash.nb_bits =  length;
    des_core(list, des, str, length);

    uint8_t* res;
    if (!(res = (uint8_t*)malloc(sizeof(uint8_t) * ( list->list_data->hash.nb_bits + 16)))){
      return(FAILED);
    }
    res = ft_strcpy(res, "Salted__");
    int v = 0;
    for (size_t i = 0; i < 16; i+=2)
    {
      res[8 + v] = ahex2int(list->flags.salt[i], list->flags.salt[i+1]);
      v++;
    }
    for (size_t j = 0; j < list->list_data->hash.nb_bits; j++)
    {
      res[16 + j] = list->list_data->hash.hashed_data[j];
    }
    free(list->list_data->hash.hashed_data);
    list->list_data->hash.hashed_data = res;
    list->list_data->hash.nb_bits = list->list_data->hash.nb_bits + 16;

    if (list->flags.a)
    {
      tmp = list->list_data->hash.hashed_data;
      if (!(base64(list, list->list_data->hash.hashed_data, list->list_data->hash.nb_bits)))
          return (FAILED);
      free(tmp);
    }


    return (SUCCESS);
}

int     des_ecb_decode(t_parsing *list, t_des *des, unsigned char *str, size_t length)
{
    uint8_t*  tmp;
    tmp = NULL;
    if (list->flags.a)
    {
        if (!(base64(list,str,length)))
            return (FAILED);
        tmp = list->list_data->hash.hashed_data;
        str = &tmp[16];
        length = list->list_data->hash.nb_bits - 16;
    }
    else {
      str = &str[16];
      length = length - 16;
    }
    if (!(list->list_data->hash.hashed_data = (uint8_t*)malloc(sizeof(uint8_t) * (length ))))
        return (FAILED);
    list->list_data->hash.nb_bits = length;
    des_core(list,des,str,length);
    des->pad_bit = list->list_data->hash.hashed_data[list->list_data->hash.nb_bits - 1];

    list->list_data->hash.nb_bits = length - des->pad_bit;
    if (tmp)
        free(tmp);
    return(SUCCESS);
}