/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 12:50:59 by dihauet           #+#    #+#             */
/*   Updated: 2021/04/04 13:59:06 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

static void		calc_sha256(int i, t_sha256 *sha256)
{
	uint32_t s0;
	uint32_t s1;
	uint32_t tmp;
	uint32_t tmp2;

	s1 = ft_right_rotate(sha256->word_e, 6) ^ ft_right_rotate(sha256->word_e,
		11) ^ ft_right_rotate(sha256->word_e, 25);
	sha256->ch = ((sha256->word_e & sha256->word_f) ^ (~(sha256->word_e)
		& sha256->word_g));
	tmp = sha256->word_h + s1 + sha256->ch + g_k_sha256[i] + sha256->words[i];
	s0 = ft_right_rotate(sha256->word_a, 2) ^ ft_right_rotate(sha256->word_a,
		13) ^ ft_right_rotate(sha256->word_a, 22);
	sha256->maj = (sha256->word_a & sha256->word_b) ^ (sha256->word_a
		& sha256->word_c) ^ (sha256->word_b & sha256->word_c);
	tmp2 = s0 + sha256->maj;
	sha256->word_h = sha256->word_g;
	sha256->word_g = sha256->word_f;
	sha256->word_f = sha256->word_e;
	sha256->word_e = sha256->word_d + tmp;
	sha256->word_d = sha256->word_c;
	sha256->word_c = sha256->word_b;
	sha256->word_b = sha256->word_a;
	sha256->word_a = tmp + tmp2;
}

static void		round_sha256(t_sha256 *sha256)
{
	int			i;

	i = 0;
	while (i < 64)
	{
		calc_sha256(i, sha256);
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
	free(sha256->words);
}

static int		create_words(uint8_t *msg, t_sha256 *sha256)
{
	int			i;
	uint32_t	s0;
	uint32_t	s1;

	i = -1;
	if (!(sha256->words = (uint32_t*)malloc(sizeof(uint32_t) * 64)))
		return (FAILED);
	while (++i < 64)
	{
		if (i < 16)
		{
			ft_memcpy(&(sha256->words[i]), msg + (i * 4), 32);
			sha256->words[i] = swap_endian(sha256->words[i]);
		}
		else
		{
			s0 = func_s0(i, sha256);
			s1 = func_s1(i, sha256);
			sha256->words[i] = sha256->words[i - 16] + s0
				+ sha256->words[i - 7] + s1;
		}
	}
	return (SUCCESS);
}

static int		concat_sha256(t_hash *hash, t_sha256 *sha256)
{
	uint32_t	tmp[8];
	int			i;
	int			j;
	uint8_t		*word;

	hash->nb_bits = 32;
  if (hash->hashed_data)
    free(hash->hashed_data);
	if (!(hash->hashed_data = (uint8_t*)malloc(sizeof(uint8_t) * 32)))
		return (FAILED);
	tmp[0] = swap_endian(sha256->h0);
	tmp[1] = swap_endian(sha256->h1);
	tmp[2] = swap_endian(sha256->h2);
	tmp[3] = swap_endian(sha256->h3);
	tmp[4] = swap_endian(sha256->h4);
	tmp[5] = swap_endian(sha256->h5);
	tmp[6] = swap_endian(sha256->h6);
	tmp[7] = swap_endian(sha256->h7);
	i = -1;
	while (++i < 8)
	{
		j = -1;
		word = (uint8_t*)&(tmp[i]);
		while (++j < 4)
			hash->hashed_data[i * 4 + j] = word[j];
	}
	return (SUCCESS);
}

int				sha256(t_parsing *list, unsigned char *str, size_t length)
{
	t_sha256	sha256;

	init_sha256(&sha256);
	add_padding(&sha256.padding, str, length, 0);
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
		if (!(create_words(sha256.padding.data_with_padding
			+ sha256.offset, &sha256)))
		{
			free(sha256.padding.data_with_padding);
			return (0);
		}
		round_sha256(&sha256);
		sha256.offset += 64;
	}
	free(sha256.padding.data_with_padding);
	return (concat_sha256(&list->list_data->hash, &sha256));
}
