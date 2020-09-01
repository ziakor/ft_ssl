/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 11:53:48 by dihauet           #+#    #+#             */
/*   Updated: 2020/09/01 17:31:13 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

static int	w(char *str, char c)
{
	int i;
	int words;

	i = 0;
	words = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] && str[i] != c)
			words++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (words);
}

static int	ft_strlen(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i + 1);
}

char		**ft_strsplit(char *str, char c)
{
	char	**t;
	int		i;
	int		j;
	int		count;

	if (!str || !c || !(t = (char **)malloc(sizeof(char *) * (w(str, c) + 1))))
		return (NULL);
	count = w(str, c);
	i = 0;
	while (i < count)
	{
		j = 0;
		while (*str == c)
			str++;
		if (!(t[i] = (char *)malloc(sizeof(char) * (ft_strlen(str, c)))))
			return (NULL);
		while (*str && *str != c)
			t[i][j++] = *str++;
		t[i][j] = '\0';
		while (*str == c)
			str++;
		i++;
	}
	t[i] = NULL;
	return (t);
}
