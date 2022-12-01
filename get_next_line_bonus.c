/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kace <ael-kace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 02:21:38 by ael-kace          #+#    #+#             */
/*   Updated: 2022/11/30 19:09:52 by ael-kace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read(int fd, char *res)
{
	char	*buff;
	int		ret_read;

	ret_read = 1;
	while (ret_read && !ft_strchr(res, '\n'))
	{
		buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return (free(res), NULL);
		ret_read = read(fd, buff, BUFFER_SIZE);
		if (ret_read < 0)
			return (free(buff), free(res), NULL);
		buff[ret_read] = '\0';
		if (!ft_strlen(buff))
		{
			free(buff);
			break ;
		}
		res = ft_strjoin(res, buff);
		if (!res)
			return (free(buff), NULL);
	}
	return (res);
}

char	*ft_line(char *save)
{
	char	*line;
	int		i;

	i = 0;
	if (!ft_strlen(save))
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_rest_line(char *res)
{
	char	*str;
	int		i;

	i = 0;
	while (res[i])
	{
		if (res[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	if (!res[i])
		return (free(res), NULL);
	str = ft_strdup(&res[i]);
	return (free(res), str);
}

char	*get_next_line(int fd)
{
	static char	*res[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	res[fd] = ft_read(fd, res[fd]);
	if (!res[fd])
		return (NULL);
	line = ft_line(res[fd]);
	res[fd] = ft_rest_line(res[fd]);
	return (line);
}
