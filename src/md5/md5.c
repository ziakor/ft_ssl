/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 14:54:36 by dihauet           #+#    #+#             */
/*   Updated: 2020/11/14 12:45:15 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

static void		round_md5(t_md5 *md5)
{
	int			i;
	uint32_t	tmp;

	i = 0;
	while (i < 64)
	{
		if (i >= 0 && i <= 15)
			func_f(md5, i);
		else if (i >= 16 && i <= 31)
			func_g(md5, i);
		else if (i >= 32 && i <= 47)
			func_h(md5, i);
		else if (i >= 48 && i <= 63)
			func_i(md5, i);
		tmp = md5->word_d;
		md5->word_d = md5->word_c;
		md5->word_c = md5->word_b;
		md5->word_b = ft_left_rotate((md5->word_a + md5->f + g_k_md5[i]
					+ md5->endian_w[md5->g]), g_r_md5[i]) + md5->word_b;
		md5->word_a = tmp;
		i++;
	}
}

static int		concat_words_md5(t_md5 *md5, t_hash *hash)
{
	uint32_t	tmp[4];
	int			i;
	int			j;
	uint8_t		*word;

	free(md5->padding.data_with_padding);
	if (!(hash->hashed_data = (uint8_t*)malloc(sizeof(uint8_t) * 16)))
		return (FAILED);
	tmp[0] = md5->h0;
	tmp[1] = md5->h1;
	tmp[2] = md5->h2;
	tmp[3] = md5->h3;
	i = -1;
	while (++i < 4)
	{
		j = -1;
		word = (uint8_t*)&(tmp[i]);
		while (++j < 4)
			hash->hashed_data[i * 4 + j] = word[j];
	}
	hash->nb_bits = 16;
	return (SUCCESS);
}

int				md5(t_parsing *list, char *str, size_t length)
{
	t_md5	md5;

	ft_bzero(&md5, sizeof(t_md5));
	add_padding(&md5.padding, str, length, 1);
	md5.h0 = MD5_H0;
	md5.h1 = MD5_H1;
	md5.h2 = MD5_H2;
	md5.h3 = MD5_H3;
	while (md5.offset < md5.padding.new_length)
	{
		md5.endian_w = (uint32_t*)(md5.padding.data_with_padding + md5.offset);
		md5.word_a = md5.h0;
		md5.word_b = md5.h1;
		md5.word_c = md5.h2;
		md5.word_d = md5.h3;
		round_md5(&md5);
		md5.h0 = md5.h0 + md5.word_a;
		md5.h1 = md5.h1 + md5.word_b;
		md5.h2 = md5.h2 + md5.word_c;
		md5.h3 = md5.h3 + md5.word_d;
		md5.offset += 64;
	}
	if (!(concat_words_md5(&md5, &list->list_data->hash)))
		return (FAILED);
	return (SUCCESS);
}
