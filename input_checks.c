/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 15:34:03 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/10/30 23:15:24 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_fd(char **argv, t_var *px, int argc)
{
	px->exitcode = 0;
	px->infile = argv[1];
	px->outfile = argv[argc - 1];
	px->output_fd = open(px->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (px->output_fd < 0)
	{
		write(2, "pipex: ", 7);
		perror(argv[4]);
		px->exitcode = 1;
	}
	px->input_fd = open(px->infile, O_RDONLY);
	if (px->input_fd < 0)
	{
		write(2, "pipex: ", 7);
		perror(argv[1]);
		px->exitcode = 1;
	}
	if (px->exitcode != 0)
	{
		if (px->output_fd > -1)
			px->exitcode = 0;
	}
}

void	check_commands(char **argv, t_var *px)
{
	if (is_empty_or_space(argv[2]))
	{
		write(2, "pipex: ", 7);
		write(2, argv[2], ft_strlen(argv[2]));
		write(2, ": command not found", 20);
		px->error_cmd1 = 1;
		px->exitcode = 127;
	}
	if (is_empty_or_space(argv[3]))
	{
		if (is_empty_or_space(argv[2]))
			write(2, "\n", 1);
		write(2, "pipex: ", 7);
		write(2, argv[3], ft_strlen(argv[3]));
		write(2, ": command not found", 20);
		px->exitcode = 127;
		exit(px->exitcode);
	}
	else
		px->exitcode = 0;
}
