/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_right_rotate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 12:04:56 by dihauet           #+#    #+#             */
/*   Updated: 2020/09/18 17:45:38 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

uint32_t	ft_right_rotate(uint32_t value, unsigned int count)
{
	return ((value >> count) | (value << (32 - count)));
}
