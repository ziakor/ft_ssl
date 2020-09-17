/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 15:26:42 by dihauet           #+#    #+#             */
/*   Updated: 2020/09/17 16:30:12 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

int		is_little_endian(void)
{
	unsigned int i = 1; 
	char *c = (char*)&i;
	return(*c ? 1 : 0);
}

uint32_t swap_endian(uint32_t x)
{
	uint32_t a;
	uint32_t b;
	uint32_t c;
	uint32_t d;

	a = x >> 24 & 0xff;
	b = x >> 8 & 0xff00; 
	c = x << 8 & 0xff0000;
	d = x << 24 & 0xff000000;

	return a | b | c | d;
}
