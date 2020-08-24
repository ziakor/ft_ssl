#ifndef PARSING_H
# define PARSING_H

#include <stddef.h>

typedef struct s_flags
{
	int i;
	int q;
	int r;
	int s;
} t_flags;


typedef struct s_data
{
	char *fd_name;
	int fd;
	char *data;
	size_t data_length;
} t_data;

typedef struct s_list
{
	t_data *data;
	t_flags flags;

	struct s_list *next;
} t_list;


typedef struct s_parsing
{

	char *cmd;

	t_list *list_data;
} t_parsing;


#endif 