/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 11:34:16 by dihauet           #+#    #+#             */
/*   Updated: 2020/08/24 11:34:16 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memalloc(size_t size)
{
	void	*dest;

	if (!(dest = (void *)malloc(size * sizeof(size_t))))
		return (NULL);
	ft_memset(dest, 0, size);
	return (dest);
}
