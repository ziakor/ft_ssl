/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 13:01:04 by dihauet           #+#    #+#             */
/*   Updated: 2020/09/29 10:27:32 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>//
char    *ft_strjoin_size(const char *s1, const char *s2, int size_s1, int size_s2)
{
    int i;
    int j;
    char *join;

    i = 0;
    j = 0;
    if (!s1 || !s2)
        return (NULL);
    if (!(join = (char*) malloc(sizeof(char) * (size_s1 + size_s2))))
        return (NULL);
    while (i < size_s1)
    {
        join[i] = s1[i];
        i++;
    }
    while (j <size_s2)
    {
        join[i + j] = s2[j];
        j++;
    }
    return (join);
}