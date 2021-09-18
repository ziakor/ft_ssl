/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_cbc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 15:01:05 by dihauet           #+#    #+#             */
/*   Updated: 2021/09/18 11:32:30 by dihauet          ###   ########.fr       */
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
    length = des->pad_bit + length;
    if (!(list->list_data->hash.hashed_data = (uint8_t*) malloc(sizeof(uint8_t) * (length) )))
        return (FAILED);
    list->list_data->hash.nb_bits = length + des->pad_bit;
    iv = des->iv;
    while (i < length)
	{
		data = ecb_get_64bit((char*)&str[i], des->pad_bit, length - i - des->pad_bit);
		data ^= iv;


		data = ecb_algo(data, des->key48);
		iv = data;
		des_put_data(&(list->list_data->hash.hashed_data[i]), data);
		i += 8;
	}
  
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
  return(SUCCESS);
}

static int  des_cbc_decode(t_parsing *list, t_des *des, unsigned char *str, size_t length)
{
    size_t i;
    uint64_t iv;
    uint64_t next_iv;
    uint64_t data;
    uint8_t*  tmp;
    
    iv = des->iv;
    i = 0;

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
    
    if (!(list->list_data->hash.hashed_data = (uint8_t*) malloc(sizeof(uint8_t) * (length) )))
        return (FAILED);
    list->list_data->hash.nb_bits = length;
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
    des.pad_bit = 0;
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