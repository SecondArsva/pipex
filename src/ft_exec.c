/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 03:05:27 by davidga2          #+#    #+#             */
/*   Updated: 2023/09/15 05:05:39 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_exec(char *cmd_argv, char **envp)
{
	char **cmd;
	//char *binary_path;

	cmd = ft_split(cmd_argv, ' ');
	if (!cmd)
		ft_error("Command matrix creation failed");
	//path = ft_get_paths(envp);
	//fprintf(stderr, "%i, %s\n", getpid(), cmd[0]); // v
	//pause(); // v
	execve(ft_strdoublejoin("/bin", "/", cmd[0]), cmd, envp);
}
