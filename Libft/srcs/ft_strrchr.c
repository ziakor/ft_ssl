/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 11:53:35 by dihauet           #+#    #+#             */
/*   Updated: 2020/08/24 11:53:36 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	if (c == 0)
		return (&((char *)s)[i]);
	while (s[i] != c && (i > 0))
		i--;
	if (s[i] == c)
		return (((char *)s) + i);
	return (0);
}
