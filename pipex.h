/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:06:12 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/10/11 18:10:47 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./complete_Libft/libft.h"
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>

int	pipex(char *file1, char *cmd1[], char *cmd2[], char *file2, char **envp);
char	*join_paths(const char *dir, const char *cmd);
char	*find_path_in_envp(char *envp[]);
char	*get_command_path(const char *cmd, char **envp);
void	free_array(char **array);

#endif
