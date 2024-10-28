/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:11:43 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/10/22 19:16:09 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_file_error(t_var *px, char *filename)
{
	write(2, "pipex: ", 7);
	perror(filename);
	if (errno == EACCES || errno == ENOENT)
	{
		px->exitcode = 0;
		if (filename == px->outfile)
			px->exitcode = 1;
	}
	else
		px->exitcode = 1;
	exit(px->exitcode);
}

void	display_error(t_var *px, const char *cmd)
{
	write(2, "pipex: ", 7);
	perror(cmd);
}

void	exit_command_error(t_var *px, char *cmd)
{
	if (px->cmd1)
		free_array(&px->cmd1);
	if (px->cmd2)
		free_array(&px->cmd2);
	exit(px->exitcode);
}

void	set_error_and_display(int code, t_var *px, const char *cmd)
{
	px->exitcode = code;
	if (code == 126)
	{
		errno = EACCES;
		display_error(px, cmd);
	}
	else if (code == 127)
	{
		errno = ENOENT;
		write(2, "pipex: ", 7);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": command not found\n", 20);
	}
}