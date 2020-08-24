/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 11:52:27 by dihauet           #+#    #+#             */
/*   Updated: 2020/08/24 11:52:27 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] &&
			((unsigned char)s1[i] == (unsigned char)s2[i]) && i < n - 1)
		i++;
	return (((unsigned char)s1[i]) - ((unsigned char)s2[i]));
}
