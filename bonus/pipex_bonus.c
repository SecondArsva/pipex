/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:37:02 by davidga2          #+#    #+#             */
/*   Updated: 2023/09/28 22:30:08 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_wait_childs(int total_childs)
{
	while (total_childs > 0)
	{
		waitpid(-1, NULL, 0);
		total_childs--;
	}
}
/*
int	ft_pipe_manage(int *pipe_a_fd, int *pipe_b_fd)
{
	int *temp_fd;

	close(pipe_a_fd[1]);
	close(pipe_a_fd[0]);
	close(pipe_b_fd[1]);

	return (temp_fd);
}*/

void	ft_pipex(char **argv, char **envp, int total_childs, int middle_childs)
{
	int		pipe_a_fd[2];
	int		pipe_b_fd[2];
	//int		*tmp;
	int		cmd_count;

	cmd_count = 3;
	if (pipe(pipe_a_fd) == -1)
		ft_error("fds linking at pipe creation has failed");
	ft_infile_child(argv, envp, pipe_a_fd);
	while (middle_childs > 0)
	{
		if (pipe(pipe_b_fd) == -1)
			ft_error("fds linking at pipe creation has failed");
		
		ft_middle_child(argv[cmd_count], envp, pipe_a_fd, pipe_b_fd);
		middle_childs--;
		cmd_count++;

		close(pipe_a_fd[1]);
		close(pipe_a_fd[0]);
		pipe_a_fd[1] = pipe_b_fd[1];
		pipe_a_fd[0] = pipe_b_fd[0];
		close(pipe_b_fd[1]);
		close(pipe_b_fd[0]);
	}
	ft_outfile_child_b(argv, cmd_count, envp, pipe_a_fd);
	if (close(pipe_a_fd[0]) == -1)
		ft_error("Parent cant close pipe_fd[0]");
	if (close(pipe_a_fd[1]) == -1)
		ft_error("Parent cant close pipe_fd[1]");
	ft_wait_childs(total_childs);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc >= 5)
		ft_pipex(argv, envp, argc - 3, argc - 5);
	else
		return (ft_printf_error("pipex: invalid arguments\n"), 1);
	return (0);
}
