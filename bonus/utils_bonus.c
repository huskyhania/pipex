/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:42:31 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/10/30 23:18:39 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_variables(char **argv, char **envp, t_var *px)
{
	(void)argv;
	px->error_cmd1 = 0;
	px->error_cmd2 = 0;
	px->cmd1 = NULL;
	px->cmd_path = NULL;
	px->envp = envp;
}

char	**get_command(const char *argv, t_var *px)
{
	if (is_empty_or_space(argv))
	{
		write(2, "pipex: ", 7);
		write(2, argv, ft_strlen(argv));
		write(2, ": command not found\n", 20);
		px->error_cmd1 = 1;
		px->exitcode = 127;
		return (NULL);
	}
	px->cmd1 = ft_split(argv, ' ');
	if (!px->cmd1)
	{
		perror("command split error");
		px->error_cmd1 = 1;
	}
	if (!px->error_cmd1)
		px->cmd_path = get_command_path(px->cmd1[0], px);
	if (!px->cmd_path)
	{
		free_array(&px->cmd1);
		px->error_cmd1 = 1;
		return (NULL);
	}
	return (px->cmd1);
}

void	clean_up(t_var *px_var)
{
	if (px_var->input_fd >= 0)
	{
		close(px_var->input_fd);
		px_var->input_fd = -1;
	}
	if (px_var->output_fd >= 0)
	{
		close(px_var->output_fd);
		px_var->output_fd = -1;
	}
}

int	is_empty_or_space(const char *cmd)
{
	if (!cmd || cmd[0] == '\0')
		return (1);
	while (*cmd)
	{
		if (*cmd != ' ')
			return (0);
		cmd++;
	}
	return (1);
}

void	free_array(char ***array)
{
	int	i;

	if (!array || !*array)
		return ;
	i = 0;
	while ((*array)[i] != NULL)
	{
		free((*array)[i]);
		(*array)[i] = NULL;
		i++;
	}
	free(*array);
	*array = NULL;
}
