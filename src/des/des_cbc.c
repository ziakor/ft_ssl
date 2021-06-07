/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_cbc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 15:01:05 by dihauet           #+#    #+#             */
/*   Updated: 2021/06/07 12:47:03 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

static int  des_cbc_encode(t_parsing *list, t_des *des, unsigned char *str, size_t length)
{
    size_t i;
    uint64_t iv;
    uint64_t data;
    uint8_t* tmp;
    i = 0;

    des->pad_bit = (((length / 8) + 1 ) * 8) - length; 
    if (!(list->list_data->hash.hashed_data = (uint8_t*) malloc(sizeof(uint8_t) * (des->pad_bit + length) )))
        return (FAILED);
    list->list_data->hash.nb_bits = length + des->pad_bit;
    iv = des->iv;

    while (i < list->list_data->hash.nb_bits)
	{
		data = ecb_get_64bit((char*)str + i, des->pad_bit, length - i);

		data ^= iv;

		data = ecb_algo(data, des->key48);
		iv = data;
		des_put_data(&(list->list_data->hash.hashed_data[i]), data);
		i += 8;
	}
  if (list->flags.a)
  {
    tmp = list->list_data->hash.hashed_data;
    if (!(base64(list, list->list_data->hash.hashed_data, list->list_data->hash.nb_bits)))
        return (FAILED);
    free(tmp);
  }
  return(SUCCESS);
}

static int  des_cbc_decode(t_parsing *list, t_des *des, unsigned char *str, size_t length)
{
    size_t i;
    uint64_t iv;
    uint64_t next_iv;
    uint64_t data;
    uint8_t*  tmp;
    
    if (!(list->list_data->hash.hashed_data = (uint8_t*) malloc(sizeof(uint8_t) * (length) )))
        return (FAILED);
    list->list_data->hash.nb_bits = length;
    iv = des->iv;
    i = 0;

    if (list->flags.a)
    {
        if (!(base64(list,str,length)))
            return (FAILED);
        tmp = list->list_data->hash.hashed_data;
        str = tmp;
        length = list->list_data->hash.nb_bits;
    }
    while (i < length)
    {
      data = ecb_get_64bit((char*)&str[i], des->pad_bit, length - i);
      next_iv = data;
      data = ecb_algo(data, des->key48);
      data ^= iv;
      iv = next_iv;
      des_put_data(&(list->list_data->hash.hashed_data[i]), data);
      i+= 8;
    }
    des->pad_bit = list->list_data->hash.hashed_data[length - 1];
    list->list_data->hash.nb_bits = length - des->pad_bit;
    return (SUCCESS);
}

int     des_cbc(t_parsing *list, unsigned char *str, size_t length)
{

    t_des des;
    if (list->flags.vector[0] == 0)
    {
        free(list->list_data->data.data);
        if (!(list->list_data->data.data = (unsigned char*)ft_strdup("iv undefined")))
            return (FAILED);
        list->list_data->data.data_length = 12;
        list->list_data->data.fd = -2;
        return (FAILED);
    }
    des.iv = hex_to_uint64(list->flags.vector);
    create_key_des_ecb(list, &des);

    if (list->flags.e)
    {
        if (!(des_cbc_encode(list, &des, str, length)))
            return (FAILED);
    }
    else
    {
        if (!(des_cbc_decode(list, &des, str, length)))
            return (FAILED); 
    }
    return (SUCCESS);
}