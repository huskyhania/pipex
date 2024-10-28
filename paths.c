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

// Check if the command is executable or handle errors
static char	*check_command(const char *cmd, t_var *px)
{
	if (access(cmd, X_OK) == 0)
	{
		px->exitcode = 0;
		return (ft_strdup(cmd));
	}
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

static int	check_access(const char *full_path, t_var *px, int *found)
{
	if (access(full_path, X_OK) == 0)
	{
		px->exitcode = 0;
		return (1);
	}
	else if (access(full_path, F_OK) == 0)
	{
		*found = 1;
		return (0);
	}
	return (-1);
}

// Create full path and check it
static char	*check_full_path(const char *cmd, const char *dir,
	t_var *px, int *found)
{
	char	*full_path;

	full_path = join_paths(dir, cmd);
	if (!full_path)
		return (NULL);
	if (check_access(full_path, px, found) == 1)
	{
		return (full_path);
	}
	free(full_path);
	return (NULL);
}

// Iterate through directories to find the command
static char	*search_in_path(const char *cmd, char **directories, t_var *px)
{
	int		i;
	int		found;
	char	*result;

	i = 0;
	found = 0;
	while (directories[i] != NULL)
	{
		result = check_full_path(cmd, directories[i], px, &found);
		if (result)
		{
			free_array(&directories);
			return (result);
		}
		i++;
	}
	free_array(&directories);
	if (found)
		set_error_and_display(126, px, cmd);
	else
		set_error_and_display(127, px, cmd);
	return (NULL);
}

char	*get_command_path(const char *cmd, t_var *px)
{
	char	*path_env;
	char	**directories;

	px->exitcode = 0;
	if (ft_strchr(cmd, '/'))
		return (check_command(cmd, px));
	path_env = find_path_in_envp(px->envp);
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
	return (search_in_path(cmd, directories, px));
}
