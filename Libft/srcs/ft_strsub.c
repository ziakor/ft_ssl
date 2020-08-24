/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 11:54:25 by dihauet           #+#    #+#             */
/*   Updated: 2020/08/24 11:54:26 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char		*sub;
	int			i;
	size_t		j;

	i = 0;
	j = len;
	if (!s)
		return (NULL);
	if (!(sub = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	while (len--)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[j] = '\0';
	return (sub);
}
