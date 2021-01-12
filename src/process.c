/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dihauet <dihauet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:45:24 by dihauet           #+#    #+#             */
/*   Updated: 2021/01/12 16:08:50 by dihauet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

int			process_one(char **argv, t_parsing *list, int i)
{
	while (argv[i] && argv[i][0] == '-')
	{
		if (!(get_option_process_one(&list->flags, argv[i++], list->cmd)))
			return(FAILED);
		if (list->flags.s)
			break;
	}
	if ((!argv[i] && !list->flags.s) || list->flags.p)
	{
		if (!(get_file_data(list, NULL)))
			return (FAILED);
	}
	if (list->flags.s)
	{
		if (!(get_data_s_flag(&list->list_data, argv[i++])))
			return (FAILED);
	}
	while (argv[i])
	{
		if (!(get_file_data(list, argv[i])))
			return (FAILED);
		i++;
	}
	return(SUCCESS);
}

int			process_two(char **argv, t_parsing *list, int i)
{
	list->is_cipher = 1;
	while (argv[i] && argv[i][0] == '-')
	{
		if (!(parse_flag_base64(list, argv, &i)))
			return(FAILED);
		i++;
	}
	if (!list->flags.i)
	{
		if (!(get_file_data(list, NULL)))
			return (FAILED);
	}
	return (SUCCESS);
}

int     get_password(t_parsing *list, char *prompt)
{
    char *password;
    if (!(password = getpass(prompt)))
        return (FAILED);
    if (!(password = ft_strdup(password)))
        return (FAILED);
    write(1, "Verifying - ", 12);
    if (!(list->flags.password = getpass(prompt)))
    {
        free(password);
        return (FAILED);
    }
    if (ft_strcmp(password, list->flags.password) != 0)
    {
        write(1, "Verify failure\nbad password read\n", 35);
        free(password);
        return (FAILED);
    }
    free(password);
    return (SUCCESS);
}


void        generate_salt(t_parsing *list)
{
    int i;
    const char tab[]= "0123456789ABCDEF";
    unsigned char data[8];
    int fd;
    int j;

    j = 0;
    i = 0;
    fd = open("/dev/urandom", O_RDONLY);
    read(fd, data, 8);
    while (i < 16)
    {
        list->flags.salt[i] = data[j]  < 16 ? '0' : tab[data[j] / 16];
        list->flags.salt[i + 1] = tab[data[j] % 16];
        i = i + 2;
        j++;
    }
}

void    put_key(t_parsing *list, int nb, int *count_key)
{
	if (nb > 15)
		put_key(list ,nb / 16, count_key);
	nb %= 16;
	if (nb < 10)
    {
        if (*count_key < 16)
            list->flags.key[*count_key] = '0' + nb;
    }
	else
    {
        if (*count_key < 16)
            list->flags.key[*count_key] = nb + 'a' - 10;
    }
     *count_key = *count_key + 1;

}

void         pbfdk2(t_parsing *list, char *data, size_t length)
{
    char *tmp;
    size_t len;
    int i;
    const char tab[]= "0123456789ABCDEF";
    int j;
    
    j = 0;
    i = 0;
    tmp = data;
    len = length;
    while (i < 1)
    {
        if (list->list_data->hash.hashed_data)
            free(list->list_data->hash.hashed_data);
        sha256(list, tmp, len);
        tmp = list->list_data->hash.hashed_data;
        len = list->list_data->hash.nb_bits;
        i++;
    }
    print_hash_data(list->list_data->hash.hashed_data, list->list_data->hash.nb_bits);
    i = 0;
    while (i < list->list_data->hash.nb_bits)
    {
        if (list->list_data->hash.hashed_data[i] < 16)
            list->flags.key[j++] = '0';
        put_key(list, list->list_data->hash.hashed_data[i], &j);
        i++;
    }
    ft_putchar('\n');

}

int         generate_key(t_parsing *list)
{
    printf("GENERATEKEY\n");
    char *password_with_salt;
    const char tab[]= "0123456789ABCDEF";
    size_t len;
    int i;
    int j;
    
    j = 0;
    i = 0;
    len = (ft_strlen(list->flags.password) * 2) + 16;
    password_with_salt = NULL;
    if (!(password_with_salt = (char*) malloc(sizeof(char) * len)))
        return (FAILED);
    while (list->flags.password[j])
    {
        password_with_salt[i] = list->flags.password[j] < 16 ? '0' : tab[list->flags.password[j] / 16];
        password_with_salt[i + 1] = tab[list->flags.password[j] % 16];
        i = i + 2;
        j++;
    }
    j = 0;
    while (j < 16)
        password_with_salt[i++] = list->flags.salt[j++];
    i = 0;
    pbfdk2(list, password_with_salt, len);
    free(password_with_salt);
}


int         process_des(char **argv, t_parsing *list, int i)
{
    printf("PROCESS DES\n");
    while (argv[i] && argv[i][0] == '-')
    {
        if (!(parse_flag_des(list, argv, &i)))
            return (FAILED);
        i++;
    }
    if (!list->flags.password)
    {
        if (!(get_password(list, "enter des-cbc encryption password:")))
            return (FAILED);
    }
    if (!list->flags.i)
	{
		if (!(get_file_data(list, NULL)))
			return (FAILED);
	}
    if (list->flags.a && list->flags.e)
        flag_a(list);
    if (list->flags.salt[0] == 0)
        generate_salt(list);
    if (list->flags.key[0] == 0)
    {
        if (!(generate_key(list)))
            return (FAILED);
    }
    return (SUCCESS);
}