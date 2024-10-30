/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:05:21 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/10/30 21:12:49 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_var	px;

	if (argc < 5)
	{
		write(2, "Params should be: file1 cmd1 cmd2 file2\n", 40);
		exit(EXIT_FAILURE);
	}
	check_fd(argv, &px, argc);
	init_variables(argv, envp, &px);
	pipex(&px, argv, argc);
	if (px.cmd1)
		free_array(&px.cmd1);
	return (px.exitcode);
}
