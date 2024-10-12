/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:06:12 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/10/12 17:39:51 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./complete_Libft/libft.h"
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>

typedef struct  s_pipex_variables
{
	char	**envp;
 	char    **cmd1;
	char	**cmd2;
	char	*infile;
	char	*outfile;
	int	exitcode;
}       t_var;

int	pipex(t_var *px_var);
char	*join_paths(const char *dir, const char *cmd);
char	*find_path_in_envp(char *envp[]);
char	*get_command_path(const char *cmd, char **envp);

void	free_array(char **array);
void	exit_on_error(t_var *px_var, char *info, int is_file_error);

#endif
