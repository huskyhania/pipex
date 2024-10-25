/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:42:31 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/10/22 19:17:14 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_variables(char **argv, char **envp, t_var *px)
{
	px->exitcode = 0;
	check_fd(argv, px);
	check_commands(argv, px);
	if (!is_empty_or_space(argv[2]))
		px->cmd1 = ft_split(argv[2], ' ');
	if (!px->cmd1)
	{
		clean_up(px);
		perror("fail from inits after split");
		exit_command_error(px, argv[2]);
	}
	//px->cmd2 = ft_split(argv[3], ' ');
	//if (!px->cmd2)
	//{
	//	clean_up(px);
	//	free_array(&px->cmd1);
	//	exit_command_error(px, argv[3]);
	//}
	px->cmd_path = NULL;
	px->envp = envp;
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