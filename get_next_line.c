/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 06:24:52 by marihovh          #+#    #+#             */
/*   Updated: 2023/04/19 20:56:17 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*reading(int fd, char *stat_line)
{
	char	*buff;
	int		size;

	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (0);
	size = 1;
	while (size != 0 && !ft_strchr(stat_line, '\n'))
	{
		size = read(fd, buff, BUFFER_SIZE);
		if (size == -1)
		{
			free(buff);
			return (0);
		}
		buff[size] = '\0';
		stat_line = ft_strjoin(stat_line, buff);
	}
	free(buff);
	return (stat_line);
}

char	*ret(char *stat_line)
{
	char	*ret;
	int		i;

	i = 0;
	if (!stat_line[i])
		return (NULL);
	while (stat_line[i] != '\n' && stat_line[i])
		i++;
	ret = (char *)malloc((i + 2) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (stat_line[i] && stat_line[i] != '\n')
	{
		ret[i] = stat_line[i];
		i++;
	}
	if (stat_line[i] == '\n')
	{
		ret[i] = stat_line[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*save(char *stat_line)
{
	char	*save;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (stat_line[i] != '\n' && stat_line[i])
		i++;
	if (!stat_line[i])
	{
		free(stat_line);
		return (NULL);
	}
	save = (char *)malloc(sizeof(char) * ft_strlen(stat_line)-i + 1);
	if (!save)
		return (0);
	i++;
	while (stat_line[i])
		save[j++] = stat_line[i++];
	save[j] = '\0';
	free(stat_line);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*ret_line;
	static char	*stat_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	stat_line = reading(fd, stat_line);
	if (!stat_line)
		return (0);
	ret_line = ret(stat_line);
	stat_line = save(stat_line);
	return (ret_line);
}
