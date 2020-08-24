/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 11:35:47 by dihauet           #+#    #+#             */
/*   Updated: 2020/08/24 11:35:47 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*ptrd;
	char	*ptrs;

	ptrd = (char *)dst;
	ptrs = (char *)src;
	i = 0;
	if (dst < src)
	{
		while (i < n)
		{
			ptrd[i] = ptrs[i];
			i++;
		}
	}
	else
		while (n--)
		{
			ptrd[n] = ptrs[n];
		}
	return (dst);
}
