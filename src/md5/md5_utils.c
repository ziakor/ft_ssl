/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 11:33:21 by dihauet           #+#    #+#             */
/*   Updated: 2020/10/28 11:45:47 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ssl.h"

void		func_f(t_md5 *md5, int i)
{
	md5->f = (md5->word_b & md5->word_c) | ((~md5->word_b) & md5->word_d);
	md5->g = i;
}

void		func_g(t_md5 *md5, int i)
{
	md5->f = (md5->word_d & md5->word_b) | ((~md5->word_d) & md5->word_c);
	md5->g = (5 * i + 1) % 16;
}

void		func_h(t_md5 *md5, int i)
{
	md5->f = md5->word_b ^ md5->word_c ^ md5->word_d;
	md5->g = (3 * i + 5) % 16;
}

void		func_i(t_md5 *md5, int i)
{
	md5->f = md5->word_c ^ (md5->word_b | (~md5->word_d));
	md5->g = (7 * i) % 16;
}