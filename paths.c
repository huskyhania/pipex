/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 16:04:33 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/10/22 19:29:44 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

char	*join_paths(const char *dir, const char *cmd)
{
	size_t	dir_len;
	size_t	cmd_len;
	char	*full_path;

	dir_len = ft_strlen(dir);
	cmd_len = ft_strlen(cmd);
	full_path = malloc(dir_len + cmd_len + 2);
	if (!full_path)
		return (NULL);
	ft_strlcpy(full_path, dir, dir_len + 1);
	full_path[dir_len] = '/';
	ft_strlcpy(full_path + dir_len + 1, cmd, cmd_len + 1);
	return (full_path);
}

char	*find_path_in_envp(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

void free_array(char ***array)
{
    int i;

    if (!array || !*array) // Check if array or dereferenced array is NULL
        return;

    i = 0;
    while ((*array)[i] != NULL) // Iterate through the array of strings
    {
        free((*array)[i]); // Free each string
        (*array)[i] = NULL; // Set to NULL to avoid dangling pointer
        i++;
    }
    free(*array); // Free the array of strings itself
    *array = NULL; // Set the pointer to NULL to avoid dangling pointer
}

char	*get_command_path(const char *cmd, char *envp[], t_var *px)
{
	int		i;
	int		found;
	char	*path_env;
	char	*full_path;
	char	**directories;

	px->exitcode = 0;
	found = 0;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
		{
			px->exitcode = 0;
			return (ft_strdup(cmd));
		}
		else
		{
			if (access(cmd, F_OK) == 0)
			{
				errno = EACCES;
				px->exitcode = 126;
				display_error(px, cmd);
			}
			else
			{
				errno = ENOENT;
				px->exitcode = 127;
				display_error(px, cmd);
			}
			return (NULL);
		}
	}
	path_env = find_path_in_envp(envp);
	if (!path_env)
	{
		errno = ENOENT;
		px->exitcode = 127;
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
			free_array(&directories);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
		{
			free_array(&directories);
			px->exitcode = 0;
			return (full_path);
		}
		else if (access(full_path, F_OK) == 0)
			found = 1;
		free(full_path);
		i++;
	}
	free_array(&directories);
	if (found)
	{
		errno = EACCES;
		px->exitcode = 126;
		display_error(px, cmd);
	}
	else
	{
		write(2, "pipex: ", 7);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": command not found\n", 20);
		px->exitcode = 127;
	}
	return (NULL);
}
