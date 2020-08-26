/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 11:56:28 by dihauet           #+#    #+#             */
/*   Updated: 2020/08/24 11:56:29 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*null_str(const char *s)
{
	ft_putstr_fd(s, 1);
	return (NULL);
}