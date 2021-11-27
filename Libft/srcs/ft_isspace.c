/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 11:32:43 by dihauet           #+#    #+#             */
/*   Updated: 2021/09/18 11:49:58 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int ft_isspace(char c){
  if (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f' || c == '\r')
    return(1);
  return(0);
}