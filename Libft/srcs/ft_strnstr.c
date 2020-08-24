/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 11:53:21 by dihauet           #+#    #+#             */
/*   Updated: 2020/08/24 11:53:22 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *haystack, const char *ne, size_t n)
{
	size_t	i;
	char	*str;

	if (*ne == '\0')
		return ((char *)haystack);
	i = ft_strlen(ne);
	str = (char *)haystack;
	while (*str && n-- >= i)
	{
		if (ft_memcmp(str, ne, i) == 0)
			return (str);
		str++;
	}
	return (NULL);
}
