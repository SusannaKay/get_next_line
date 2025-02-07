/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skayed <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:20:26 by skayed            #+#    #+#             */
/*   Updated: 2025/01/11 12:20:28 by skayed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4
#endif

#ifndef N_FD
# define N_FD 1024
#endif

#include "get_next_line_bonus.h"

static char	*ft_bytes(char **tmp, char *buf, int bytes_read)
{
	char	*rtn;

	if (bytes_read == 0)
	{
		if (*tmp && **tmp)
		{
			rtn = *tmp;
			*tmp = NULL;
			free(buf);
			return (rtn);
		}
		free(buf);
		free(*tmp);
		*tmp = NULL;
		return (NULL);
	}
	if (bytes_read < 0)
	{
		free (buf);
		free (*tmp);
		*tmp = NULL;
		return (NULL);
	}
	return (NULL);
}

static char	*ft_nl_tmp(char **tmp, char *buf)
{
	char	*new_pos;
	char	*rtn;
	char	*old_tmp;

	new_pos = ft_strchr(*tmp, '\n');
	rtn = ft_substr(*tmp, 0, new_pos - *tmp + 1);
	old_tmp = *tmp;
	*tmp = ft_strdup(new_pos + 1);
	free(old_tmp);
	free(buf);
	return (rtn);
}

static char	*ft_nl_buf(char **tmp, char *buf)
{
	char	*rtn;
	char	*new_pos;
	char	*subs;

	new_pos = ft_strchr(buf, '\n');
	subs = ft_substr(buf, 0, new_pos - buf + 1);
	if (*tmp)
	{
		rtn = ft_strjoin(*tmp, subs);
		free(*tmp);
		free(subs);
		*tmp = ft_strdup(new_pos + 1);
	}
	else
	{
		rtn = subs;
		*tmp = ft_strdup(new_pos + 1);
	}
	free(buf);
	return (rtn);
}

static void	ft_append(char **tmp, char *buf)
{
	char	*old_tmp;

	if (*tmp)
	{
		old_tmp = *tmp;
		*tmp = ft_strjoin(old_tmp, buf);
		free(old_tmp);
	}
	else
		*tmp = ft_strdup(buf);
}

char	*get_next_line(int fd)
{
	char		*buf;
	int			bytes_read;
	static char	*tmp[N_FD];

	if (fd < 0 || fd >= N_FD || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	while (1)
	{
		if (tmp[fd] && ft_strchr(tmp[fd], '\n'))
			return (ft_nl_tmp(&tmp[fd], buf));
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read <= 0)
			return (ft_bytes(&tmp[fd], buf, bytes_read));
		buf[bytes_read] = '\0';
		if (ft_strchr(buf, '\n'))
			return (ft_nl_buf(&tmp[fd], buf));
		ft_append(&tmp[fd], buf);
	}
}
