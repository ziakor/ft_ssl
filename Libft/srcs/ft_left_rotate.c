/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_left_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 11:43:36 by dihauet           #+#    #+#             */
/*   Updated: 2020/09/16 12:15:59 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

uint32_t	ft_left_rotate(uint32_t value, unsigned int count)
{
	const unsigned int mask = CHAR_BIT * sizeof(value) - 1;

	count &= mask;
	return (value << count) | (value >> (-count & mask));
}
