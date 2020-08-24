/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 11:43:00 by dihauet           #+#    #+#             */
/*   Updated: 2020/08/24 11:43:01 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	char		*dest2;
	const char	*src2;
	size_t		size;
	size_t		destsize;

	dest2 = dest;
	src2 = src;
	size = n;
	while (*dest2 != '\0' && n-- != 0)
		dest2++;
	destsize = dest2 - dest;
	n = size - destsize;
	if (n == 0)
		return (destsize + ft_strlen(src));
	while (*src2 != '\0')
	{
		if (n != 1)
		{
			*dest2++ = *src2;
			n--;
		}
		src2++;
	}
	*dest2 = '\0';
	return (destsize + (src2 - src));
}
