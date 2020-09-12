/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 14:54:36 by dihauet           #+#    #+#             */
/*   Updated: 2020/09/12 15:31:54 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

static void	put_hexa(int nb)
{
	if (nb > 15)
		put_hexa(nb / 16);
	nb %= 16;
	if (nb < 10)
		ft_putnbr(nb);
	else
		ft_putchar(nb + 'a' - 10);
}

void		ft_puthexa(int nb)
{
	if (nb < 16)
		ft_putchar('0');
	put_hexa(nb);
}




static void print_hash_md5(t_md5 *md5)
{
    int i;
    int j;
    uint8_t *word;

    i = 0;
    while (i < 4)
    {
        j = 0;
        word = (uint8_t*)&md5->hashed_data[i];
        while (j < 4)
        {
            ft_puthexa(word[j]);
            j++;
        }
        i++;
    }
}

static int     add_padding(t_md5 *md5, char* data, size_t length)
{
    md5->padding.initial_length = length;
    md5->padding.nb_bits = length * 8;
    md5->padding.new_length = (448 - (md5->padding.nb_bits + 1)) % 512;

    md5->padding.new_length += md5->padding.nb_bits + 64 + 1;
    md5->padding.new_length = md5->padding.new_length / 8;
		
    if (!(md5->padding.data_with_padding = (uint8_t*)ft_memalloc(sizeof(uint8_t) * md5->padding.new_length)))
        return (0);
    ft_memcpy(md5->padding.data_with_padding, data, length);
    md5->padding.data_with_padding[length] |= 1 << 7;
    ft_memcpy(md5->padding.data_with_padding + md5->padding.new_length - 8, &md5->padding.nb_bits, 8);
    return(1);
}

static void round_md5(t_md5 *md5)
{
    int i;
    uint32_t tmp;
		
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
		
        md5->word_b = left_rotate((md5->word_a + md5->f + g_k_md5[i]
					+ md5->endian_w[md5->g]), g_r_md5[i]) + md5->word_b;
        md5->word_a = tmp;
        i++;
    }
}

static int  concat_words_md5(t_md5 *md5)
{
    free(md5->padding.data_with_padding);

    if (!(md5->hashed_data = (uint32_t*) malloc(sizeof(uint32_t) * 4)))
        return (0);
    md5->hashed_data[0]= md5->h0;
    md5->hashed_data[1]= md5->h1;
    md5->hashed_data[2]= md5->h2;
    md5->hashed_data[3]= md5->h3;  

    return(1);
}

int     md5(char *str, size_t length)
{
    t_md5 md5;

    ft_bzero(&md5, sizeof(t_md5));
    add_padding(&md5, str, length);    
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
        md5.offset +=64;
    }
    concat_words_md5(&md5);
		print_hash_md5(&md5);
    return (1);
}
