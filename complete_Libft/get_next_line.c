/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:03:45 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/07/25 20:21:15 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_line(int fd, char *buffer, char *save)
{
	int		read_check;
	char	*partial;

	read_check = 1;
	while (read_check != 0)
	{
		read_check = read(fd, buffer, BUFFER_SIZE);
		if (read_check == -1)
			return (freeing(&save));
		else if (read_check == 0)
			return (save);
		buffer[read_check] = '\0';
		if (!save)
			save = ft_strdup("");
		if (!save)
			return (NULL);
		partial = save;
		save = ft_strjoin(partial, buffer);
		freeing(&partial);
		if (!save)
			return (freeing(&save));
		if (ft_strchr(buffer, '\n'))
			return (save);
	}
	return (save);
}

static char	*get_remaining(char *save)
{
	size_t	index;
	char	*remaining;

	index = 0;
	while (save[index] != '\n' && save[index])
		index++;
	if (save[index] == '\n')
		index++;
	if (save[index] == '\0')
		return (freeing(&save));
	remaining = ft_strdup(&save[index]);
	if (!remaining)
		return (freeing(&save));
	freeing(&save);
	return (remaining);
}

static char	*build_line(char *save, char *line)
{
	int	i;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		line[i] = save[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*save;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
	{
		if (save != NULL)
			return (freeing(&save));
		return (NULL);
	}
	save = read_line(fd, buffer, save);
	freeing(&buffer);
	if (!save)
		return (NULL);
	line = build_line(save, line);
	if (!line)
		return (freeing(&save));
	save = get_remaining(save);
	return (line);
}
