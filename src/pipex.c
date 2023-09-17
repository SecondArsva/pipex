/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:37:02 by davidga2          #+#    #+#             */
/*   Updated: 2023/09/17 22:11:36 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// En construcción. Equivale al padre.
void ft_pipex(char **argv, char **envp)
{
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		ft_error("La vinculación de fd en la creación del pipe ha fallado");
	ft_infile_child(argv, envp, pipe_fd);
	ft_outfile_child(argv, envp, pipe_fd);
	if (close(pipe_fd[0]) == -1)
		ft_error("Parent cant close pipe_fd[0]");
	if (close(pipe_fd[1]) == -1)
		ft_error("Parent cant close pipe_fd[1]");
	waitpid(-1, NULL, 0);
	waitpid(-1, NULL, 0);
}

// En construcción.
int	main(int argc, char **argv, char **envp)
{
	if (argc == 5)
		ft_pipex(argv, envp);
	else
		return (1);
	return (0);
}
