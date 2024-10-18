/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:42:31 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/10/17 16:15:54 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void	init_variables(char **argv, char **envp, t_var *px_var)
{
	px_var->exitcode = 0;
	px_var->infile = argv[1];
	px_var->input_fd = -1;
	px_var->output_fd = -1;
	px_var->input_fd = open(px_var->infile, O_RDONLY);
 	if (px_var->input_fd < 0)
	{
		clean_up(px_var);
		exit_file_error(px_var, px_var->infile);
	}
	px_var->cmd1 = NULL;
	px_var->cmd1 = ft_split(argv[2], ' ');
 	if (!px_var->cmd1)
	{
		clean_up(px_var);
		exit_command_error(px_var, argv[2]);
	}
	px_var->cmd2 = NULL;
	px_var->cmd2 = ft_split(argv[3], ' ');
	if (!px_var->cmd2)
	{
		clean_up(px_var);
		free_array(px_var->cmd1);
		exit_command_error(px_var, argv[3]);
	}
	px_var->outfile = argv[4];
	px_var->output_fd = open(px_var->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (px_var->output_fd < 0)
	{
		clean_up(px_var);
		free_array(px_var->cmd1);
		free_array(px_var->cmd2);
		px_var->cmd1 = NULL;
		px_var->cmd2 = NULL;
		exit_file_error(px_var, px_var->outfile);
	}
	px_var->envp = envp;
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