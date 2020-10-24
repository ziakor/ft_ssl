/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 12:28:23 by dihauet           #+#    #+#             */
/*   Updated: 2020/10/24 15:23:26 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

void	error_open_directory(char *file_name, char *cmd)
{
	ft_putstr_fd("ft_ssl: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd(": Is a directory\n", 2);
}

void	error_open_file(char *file_name, char *cmd)
{
	ft_putstr_fd("ft_ssl: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putchar_fd('\n', 2);
}

char	*get_error_message_open_file(int type, int *size)
{
	if (type == -1)
	{
		*size = ft_strlen(strerror(errno));
		return (strerror(errno));
	}
	else if (type == -2)
	{
		*size = ft_strlen(strerror(EISDIR));
		return (strerror(EISDIR));
	}
	return (NULL);
}
