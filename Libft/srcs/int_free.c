/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 11:55:51 by dihauet           #+#    #+#             */
/*   Updated: 2020/08/24 11:55:51 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		int_free(void *obj)
{
	free(obj);
	return (0);
}
