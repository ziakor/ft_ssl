#ifndef PARSING_H
# define PARSING_H

#include <stddef.h>


typedef struct s_flags
{
	int p;
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

typedef struct s_lists
{

	t_data *data;
	struct s_list *next;
} t_lists;


typedef struct s_parsing
{

	char *cmd;

	t_flags flags;
	t_list *list_data;
	//add function pointeur do the job
	//add function print result
} t_parsing;

int parsing_args(t_parsing *list, char **argv, int argc);

#endif 