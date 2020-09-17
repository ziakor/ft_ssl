/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stricmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 12:20:09 by dihauet           #+#    #+#             */
/*   Updated: 2020/09/16 12:25:25 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		ft_stricmp(const char *s1, const char *s2)
{
	while (ft_tolower((unsigned char)*s1) == ft_tolower((unsigned char)*s2))
	{
		if (*s1 == '\0')
			return (0);
		s1++;
		s2++;
	}
	return (ft_tolower((unsigned char)*s1) - ft_tolower((unsigned char)*s2));
}
