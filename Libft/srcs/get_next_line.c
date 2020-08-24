/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 11:55:29 by dihauet           #+#    #+#             */
/*   Updated: 2020/08/24 11:55:30 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int		newline(char **stock, char **line, int fd)
{
	char	*tmp;
	int		length;

	length = 0;
	while (stock[fd][length] != '\n' && stock[fd][length] != '\0')
		length++;
	if (stock[fd][length] == '\n')
	{
		if (!(*line = ft_strsub(stock[fd], 0, length)))
			return (-1);
		if (!(tmp = ft_strdup(stock[fd] + length + 1)))
			return (-1);
		free(stock[fd]);
		stock[fd] = tmp;
		if (stock[fd][0] == '\0')
			ft_strdel(&stock[fd]);
	}
	else if (stock[fd][length] == '\0')
	{
		if (!(*line = ft_strdup(stock[fd])))
			return (-1);
		ft_strdel(&stock[fd]);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char *stock[FD_MAX];
	char		buffer[BUFF_SIZE_LIBFT + 1];
	char		*tmp;
	int			ret;

	if (fd < 0 || fd > FD_MAX || line == NULL || BUFF_SIZE_LIBFT <= 0)
		return (-1);
	while ((ret = read(fd, buffer, BUFF_SIZE_LIBFT)) > 0)
	{
		buffer[ret] = '\0';
		if (stock[fd] == NULL)
			stock[fd] = ft_strnew(1);
		if (!(tmp = ft_strjoin(stock[fd], buffer)))
			return (-1);
		free(stock[fd]);
		stock[fd] = tmp;
	}
	if (ret < 0)
		return (-1);
	else if (ret == 0 && (stock[fd] == NULL || stock[fd][0] == '\0'))
		return (0);
	return (newline(stock, line, fd));
}
