/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 11:58:22 by dihauet           #+#    #+#             */
/*   Updated: 2020/08/24 11:58:22 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i] != c && s[i])
	{
		i++;
	}
	if (c == 0)
		return (&((char *)s)[i]);
	if (s[i] == c)
		return (&((char *)s)[i]);
	return (NULL);
}
