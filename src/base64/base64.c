/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 15:52:29 by dihauet           #+#    #+#             */
/*   Updated: 2021/09/13 10:43:22 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

int base64encode(const void* data_buf, size_t dataLength, char* result, size_t resultSize)
{
	 const char base64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	 const uint8_t *data = (const uint8_t *)data_buf;
	 size_t resultIndex = 0;
	 size_t x;
	 uint32_t n = 0;
	 int padCount = dataLength % 3;
	 uint8_t n0, n1, n2, n3;

	 for (x = 0; x < dataLength; x += 3) 
	 {

			n = ((uint32_t)data[x]) << 16; 
			
			if((x+1) < dataLength)
				 n += ((uint32_t)data[x+1]) << 8;
			
			if((x+2) < dataLength)
				 n += data[x+2];

			n0 = (uint8_t)(n >> 18) & 63;
			n1 = (uint8_t)(n >> 12) & 63;
			n2 = (uint8_t)(n >> 6) & 63;
			n3 = (uint8_t)n & 63;
						
	
			if(resultIndex >= resultSize) return 1;  
			result[resultIndex++] = base64chars[n0];
			if(resultIndex >= resultSize) return 1;  
			result[resultIndex++] = base64chars[n1];

			if((x+1) < dataLength)
			{
				 if(resultIndex >= resultSize) return 1;  
				 result[resultIndex++] = base64chars[n2];
			}

	
			if((x+2) < dataLength)
			{
				 if(resultIndex >= resultSize) return 1;   
				 result[resultIndex++] = base64chars[n3];
			}
	 }


	 if (padCount > 0) 
	 { 
			for (; padCount < 3; padCount++) 
			{ 
				 if(resultIndex >= resultSize) return 1; 
				 result[resultIndex++] = '=';
			} 
	 }
	 if(resultIndex >= resultSize) return 1;   
	 result[resultIndex] = 0;
	 return 0;  
}


static int  init_base64_encrypt(t_hash *hash, t_base64 *b64, size_t length)
{
	b64->pad_count = length % 3;

	hash->nb_bits = ((length + 2) / 3 * 4) + 1;
	if (!(hash->hashed_data = (uint8_t*)malloc(sizeof(uint8_t) * hash->nb_bits)))
		return (FAILED);
	return (SUCCESS);
}

static int init_base64_decrypt(t_hash *hash, t_base64 *b64, unsigned char *data, size_t length)
{
	b64->pad_count = 0;
	b64->decode_length = 0;
	b64->buffer = 0;
	b64->iter = 0;
		b64->j = 0;
		b64->i = 0;
	while (data[length - b64->pad_count - 1] == '=')
		b64->pad_count++;
	hash->nb_bits = (3 * (length / 4)) - b64->pad_count;
	if (hash->nb_bits == 0)
		return (FAILED);
	if (!(hash->hashed_data = (uint8_t*)malloc(sizeof(uint8_t) * hash->nb_bits)))
		return (FAILED);
	return (SUCCESS);
}

int convert_base64_decrypt(t_base64 *b64, t_parsing *list, unsigned char *data, size_t length)
{
  
		while (b64->i < length)
		{
				b64->c = g_base64_d[(int)data[b64->i++]];
		    if (b64->c == WHITESPACE)
		    	continue;
		    else if (b64->c == INVALID)
		    	return (FAILED);
		    else if (b64->c == EQUALS)
		    	break;
		    		else
		    {
						b64->buffer = b64->buffer << 6 | b64->c;
						if (++b64->iter == 4)
						{
						b64->decode_length +=3;
						list->list_data->hash.hashed_data[b64->j++] = (b64->buffer >> 16) & 255;
						list->list_data->hash.hashed_data[b64->j++] = (b64->buffer >> 8) & 255;
						list->list_data->hash.hashed_data[b64->j++] = b64->buffer & 255;
						b64->buffer = 0;
						b64->iter = 0;
						}
				}
		}
		return (SUCCESS);
}



int base64_decrypt(t_parsing *list, unsigned char *data, size_t length)
{
	t_base64 b64;

	if (!(init_base64_decrypt(&list->list_data->hash, &b64, data, length)))
		return (FAILED);
	if (!(convert_base64_decrypt(&b64, list, data, length)))
			return (FAILED);
	if (b64.iter == 3)
	{
			b64.decode_length += 2;
			list->list_data->hash.hashed_data[b64.j++] = (b64.buffer >> 10) & 255;
			list->list_data->hash.hashed_data[b64.j++] = (b64.buffer >> 2) & 255;
	}
	else if (b64.iter == 2)
	{
			b64.decode_length++;
			list->list_data->hash.hashed_data[b64.j++] = (b64.buffer >> 4) & 255;
	}
	list->list_data->hash.nb_bits = b64.decode_length;
	return (SUCCESS);
}

static void convert_base64_encrypt(t_base64 *b64, unsigned char *data, size_t i, size_t length)
{
				b64->n = ((uint32_t)data[i]) << 16;

				if ((i + 1) < length)
						b64->n += ((uint32_t)data[i + 1]) << 8;
				if ((i + 2) < length)
						b64->n += data[i + 2];
				b64->n0 = (uint8_t)(b64->n >> 18) & 63;
				b64->n1 = (uint8_t)(b64->n >> 12) & 63;
				b64->n2 = (uint8_t)(b64->n >> 6) & 63;
				b64->n3 = (uint8_t)(b64->n) & 63;

}

int     base64_encrypt(t_parsing *list, unsigned char *data, size_t length)
{
	size_t i;
	t_base64 b64;
	int res_i;

	res_i = 0;
	i = 0;
	if (!(init_base64_encrypt(&list->list_data->hash, &b64, length)))
		return (FAILED);
	while (i <  length)
	{

		convert_base64_encrypt(&b64, data, i, length);
		list->list_data->hash.hashed_data[res_i++] = g_base64_char[b64.n0];
		list->list_data->hash.hashed_data[res_i++] = g_base64_char[b64.n1];
		if ((i + 1 ) < length)
			list->list_data->hash.hashed_data[res_i++] = g_base64_char[b64.n2];
		if ((i + 2) < length)
			list->list_data->hash.hashed_data[res_i++] = g_base64_char[b64.n3];
		i += 3;
	}
	if (b64.pad_count > 0)
	{
		while (b64.pad_count++ < 3)
			list->list_data->hash.hashed_data[res_i++] = '=';
	}
  list->list_data->hash.hashed_data[res_i] = '\n';


	return (SUCCESS);
}




int base64(t_parsing *list, unsigned char *data, size_t length)
{

	if (list->flags.e)
	{
		if (!(base64_encrypt(list, data, length)))
			return (FAILED);
	}
	else
	{
		if (!(base64_decrypt(list, data, length)))
			return (FAILED);
	}
	return (SUCCESS);
}