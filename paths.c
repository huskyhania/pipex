/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:04:33 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/10/20 18:47:35 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

char *join_paths(const char *dir, const char *cmd)
{
    size_t dir_len = ft_strlen(dir);
    size_t cmd_len = ft_strlen(cmd);
    char *full_path = malloc(dir_len + cmd_len + 2); // +2 for "/" and null terminator
    if (!full_path)
        return NULL;
    ft_strlcpy(full_path, dir, dir_len + 1);
    full_path[dir_len] = '/';
    ft_strlcpy(full_path + dir_len + 1, cmd, cmd_len + 1);
    return (full_path);
}

char *find_path_in_envp(char *envp[])
{
    int i;
    i = 0;
    while (envp[i] != NULL)
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
        	return (envp[i] + 5);
        i++;
    }
    return (NULL); // Return NULL if PATH is not found
}

void free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
	return;
}

char *get_command_path(const char *cmd, char *envp[], t_var *px)
{
	char *path_env;
	char	**directories;
	int	i;
	int	found = 0;
	char *full_path;
	
	if (ft_strchr(cmd, '/')) 
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
		{
			if (access(cmd, F_OK) == 0)
			{
				errno = EACCES;
				display_error(px, cmd);
			}
			else
			{
				errno = ENOENT;
				display_error(px, cmd);
			}
			return (NULL);
		}
	}
	path_env = find_path_in_envp(envp);
	if (!path_env)
	{
		errno = ENOENT;
		display_error(px, cmd);
		return (NULL);
	}
	directories = ft_split(path_env, ':');
	if (!directories)
		return (NULL);
	i = 0;
	while (directories[i] != NULL)
	{
		full_path = join_paths(directories[i], cmd);
		if (!full_path)
		{
			free_array(directories);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
		{
			free_array(directories);
			return (full_path);
		}
		else if (access(full_path, F_OK) == 0)
			found = 1;
		free(full_path);
		i++;
	}
	free_array(directories);
	if (found)
	{
		errno = EACCES;
		display_error(px, cmd);
	}
	else
	{
		write(2, "pipex: ", 7);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": command not found\n", 20);
	}
	return (NULL);
}
