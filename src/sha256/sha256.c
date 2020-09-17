/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 12:50:59 by dihauet           #+#    #+#             */
/*   Updated: 2020/09/17 19:06:20 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

void    print_bits(unsigned char octet)
{
	int z = 128, oct = octet;
   write(1, "0", 1);
	while (z > 0)
	{
		if (oct & z)
			write(1, "1", 1);
		else
			write(1, "0", 1);
		z >>= 1;
	}
}

void printbits(uint32_t n) {
	if (n) {
		printbits(n >> 1);
		printf("%d", n & 1);
	}
}

void init_sha256(t_sha256 *sha256)
{
	sha256->h0 = SHA256_H0;
	sha256->h1 = SHA256_H1;
	sha256->h2 = SHA256_H2;
	sha256->h3 = SHA256_H3;
	sha256->h4 = SHA256_H4;
	sha256->h5 = SHA256_H5;
	sha256->h6 = SHA256_H6;
	sha256->h7 = SHA256_H7;
}


static void round_sha256(t_sha256 *sha256)
{
	int i;
	uint32_t s0;
	uint32_t s1;

	uint32_t tmp;
	uint32_t tmp2;

	i = 0;
	while (i < 64)
	{
		s1 = ft_right_rotate(sha256->word_e, 6) ^ ft_right_rotate(sha256->word_e, 11) ^ ft_right_rotate(sha256->word_e, 25);
		sha256->ch = ((sha256->word_e & sha256->word_f) ^ (~(sha256->word_e) & sha256->word_g));
		tmp = sha256->word_h + s1 + sha256->ch + g_k_sha256[i] + sha256->words[i];
		s0 = ft_right_rotate(sha256->word_a, 2) ^ ft_right_rotate(sha256->word_a, 13) ^ ft_right_rotate(sha256->word_a, 22);
		sha256->maj = (sha256->word_a & sha256->word_b) ^ (sha256->word_a & sha256->word_c) ^ (sha256->word_b & sha256->word_c);
		tmp2 = s0 + sha256->maj; 
		
		sha256->word_h = sha256->word_g;
		sha256->word_g = sha256->word_f;
		sha256->word_f = sha256->word_e;
		sha256->word_e = sha256->word_d + tmp;
		sha256->word_d = sha256->word_c;
		sha256->word_c = sha256->word_b;
		sha256->word_b = sha256->word_a;
		sha256->word_a = tmp + tmp2;
		i++;
	}
	sha256->h0 = sha256->h0 + sha256->word_a;
	sha256->h1 = sha256->h1 + sha256->word_b;
	sha256->h2 = sha256->h2 + sha256->word_c;
	sha256->h3 = sha256->h3 + sha256->word_d;
	sha256->h4 = sha256->h4 + sha256->word_e;
	sha256->h5 = sha256->h5 + sha256->word_f;
	sha256->h6 = sha256->h6 + sha256->word_g;
	sha256->h7 = sha256->h7 + sha256->word_h;
}

static int  create_words(uint8_t *msg, t_sha256 *sha256)
{
	int i;
	i = -1;
	uint32_t s0;
	uint32_t s1;

	if (!(sha256->words = (uint32_t*)malloc(sizeof(uint32_t) * 64)))
		return (FAILED);
	while (++i < 64)
	{
		if (i < 16)
		{
			ft_memcpy(&(sha256->words[i]), msg + (i * 4), 32);
			if (is_little_endian() == 1)
				sha256->words[i] = swap_endian(sha256->words[i]);
		}
		else
		{
			s0 = ft_right_rotate(sha256->words[i - 15], 7) ^ ft_right_rotate(sha256->words[i - 15], 18) ^ sha256->words[i - 15] >> 3;
			s1 = ft_right_rotate(sha256->words[i - 2], 17) ^ ft_right_rotate(sha256->words[i - 2], 19) ^ sha256->words[i - 2] >> 10;
			sha256->words[i] = sha256->words[i - 16] + s0 + sha256->words[i - 7] + s1;
		}
	}
	return (SUCCESS);
}

static int  concat_sha256(t_hash *hash, t_sha256 *sha256)
{
	free(sha256->padding.data_with_padding);
	if (!(hash->hashed_data = (uint32_t*)malloc(sizeof(uint32_t) * 8)))
		return (FAILED);
	hash->nb_words = 8;
	hash->hashed_data[0] = swap_endian(sha256->h0);
	hash->hashed_data[1] = swap_endian(sha256->h1);
	hash->hashed_data[2] = swap_endian(sha256->h2);
	hash->hashed_data[3] = swap_endian(sha256->h3);
	hash->hashed_data[4] = swap_endian(sha256->h4);
	hash->hashed_data[5] = swap_endian(sha256->h5);
	hash->hashed_data[6] = swap_endian(sha256->h6);
	hash->hashed_data[7] = swap_endian(sha256->h7);
}

int     sha256(t_hash *hash, char *str, size_t length)
{
	t_sha256 sha256;
	ft_bzero(&sha256, sizeof(t_sha256));
	add_padding(&sha256.padding, str, ft_strlen(str), 0);
	init_sha256(&sha256);
	while (sha256.offset < sha256.padding.new_length)
	{
		sha256.word_a = sha256.h0; 
		sha256.word_b = sha256.h1; 
		sha256.word_c = sha256.h2; 
		sha256.word_d = sha256.h3; 
		sha256.word_e = sha256.h4; 
		sha256.word_f = sha256.h5; 
		sha256.word_g = sha256.h6; 
		sha256.word_h = sha256.h7; 
		if (!(create_words(sha256.padding.data_with_padding + sha256.offset, &sha256)))
		{
			free(sha256.padding.data_with_padding);
			return (0);
		}
		round_sha256(&sha256);
		free(sha256.words);
		sha256.offset+= 64;
	}
	concat_sha256(hash, &sha256);
	return(SUCCESS);
}
