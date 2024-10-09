/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:05:21 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/10/09 21:07:53 by hskrzypi         ###   ########.fr       */
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
    int i = 0;
    while (envp[i] != NULL)
    {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
        	return (envp[i] + 5);
        i++;
    }
    return NULL; // Return NULL if PATH is not found
}

char *get_command_path(const char *cmd, char *envp[])
{
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	char	*path_env = find_path_in_envp(envp);
	if (!path_env)
		return (NULL);
	char	**directories = ft_split(path_env, ':');
	if (!directories)
		return (NULL);
	int i = 0;
	while (directories[i] != NULL)
	{
		char *full_path = join_paths(directories[i], cmd);
		if (!full_path)
		{
			int j = 0;
			while (directories[j] != NULL)
			{
				free(directories[j]);
				j++;
			}
			free(directories);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
		{
			int j = 0;
			while (directories[j] != NULL)
			{
				free(directories[j]);
				j++;
			}
			free(directories);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	int k = 0;
	while (directories[k] != NULL)
	{
		free(directories[k]);
		k++;
	}
	free(directories);
	return (NULL);
}

int pipex(char *file1, char *cmd1[], char *cmd2[], char *file2, char **envp)
{
	int	fd[2];
	int	pid1;
	int	pid2;
	int	input_fd;
	int	output_fd;
	char	*cmd_path;
	if (pipe(fd) == -1)
	{
		perror("opening pipe error");
		exit(EXIT_FAILURE);
	}
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0) //first child process for 1st command
	{
		input_fd = open(file1, O_RDONLY);
		if (input_fd < 0)
		{
			perror("file1 open error");
			exit(EXIT_FAILURE);
		}
		dup2(input_fd, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(input_fd);
		close(fd[0]);
		close(fd[1]);
		cmd_path = get_command_path(cmd1[0], envp);
		if (!cmd_path)
		{
			perror("Command 1 not found");
			exit(EXIT_FAILURE);
		}
		execve(cmd_path, cmd1, envp);
		free(cmd_path);
		perror("execve cmd1 error");
		exit(EXIT_FAILURE);
	}
	pid2 = fork();
	if (pid2 < 0)
	{
		perror("2nd fork error");
		exit(EXIT_FAILURE);
	}
	if (pid2 == 0) // second child process for 2nd command
	{
		output_fd = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (output_fd < 0)
		{
			perror("file2 open error");
			exit(EXIT_FAILURE);
		}
		dup2(fd[0], STDIN_FILENO);
		dup2(output_fd, STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		close(output_fd);
		cmd_path = get_command_path(cmd2[0], envp);
		if (!cmd_path)
		{
			perror("Command 2 not found");
			exit(EXIT_FAILURE);
		}
		execve(cmd_path, cmd2, NULL);
		free(cmd_path);
		perror("execve cmd2 error");
		exit(EXIT_FAILURE);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	if (argc != 5)
	{
		write(2, "Params should be: file1 cmd1 cmd2 file2\n", 40);
		return (1);
	}
	char *cmd1[] = {argv[2], NULL};
	char *cmd2[] = {argv[3], NULL};
	pipex(argv[1], cmd1, cmd2, argv[4], envp);
	return (0);
}
