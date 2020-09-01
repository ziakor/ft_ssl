/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 12:04:12 by dihauet           #+#    #+#             */
/*   Updated: 2020/09/01 18:19:14 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

char *read_line_stdin()
{
  char *tmp;
	char *stdin_data;
	char str[1001];
	int ret;
  int i;

  i = 0;
	if (!(stdin_data = (char*)malloc(sizeof(char))))
		return (NULL);
	stdin_data[0]  = '\0';
	while ((ret = read(0, str, 1000)) > 0)
	{ 
    i = 0;
		str[ret] = '\0';
    while(str[i] && str[i] != '\n')
      i++;
    str[i] = '\0';
    tmp = ft_strjoin(stdin_data, str);
    free(stdin_data);
    stdin_data = tmp;
    if (i  < ret)
      return (stdin_data);
	}
	if (ret == -1)
		return (NULL);
	return(stdin_data);
}

int ft_str_tablen(char **tab)
{
  int i;

  i = 0;
  while (tab[i])
    i++;
  return (i);
}

int free_interactive_mode(char *binary, char *line, char **args)
{
  if (binary != NULL)
  {  
    free(binary);
    binary = NULL;
  }
  if (line != NULL)
  {  
    free(line);
    line = NULL;
  }
  if(args != NULL)
  {
    free_tab(args);
    args = NULL;
  }
  return(0);
}

int interactive_mode(t_parsing *list)
{
  char *line;
  char **args;
  char *binary;

  line= NULL;
  args = NULL;
  binary = NULL;
  while (1)
  {
    ft_putstr("ft_ssl>");
    if (!(binary = ft_strdup("./ft_ssl ")))
      return free_interactive_mode(binary, line, args);
    if(!(line = read_line_stdin()))
      return free_interactive_mode(binary, line, args);
    if((ft_strlen(line) == 1 && line[0] == 'q' ))
      return free_interactive_mode(binary, line, args);
    if (!(line = ft_strjoin_free(binary, line)))
      return (0);
    if(!(args = ft_strsplit(line, ' ')))
      return free_interactive_mode(binary, line, args);
    if (parsing_args(list,args, ft_str_tablen(args)))
      break;
    free_tab(args);
    ft_strdel(&line);
  }
  free_tab(args);
  ft_strdel(&line);
  return (1);
}