/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:37:02 by davidga2          #+#    #+#             */
/*   Updated: 2023/09/27 02:45:40 by davidga2         ###   ########.fr       */
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

void	ft_pipex(char **argv, char **envp, int total_childs, int middle_childs)
{
	int		pipe_a_fd[2];
	int		pipe_b_fd[2];
	int		*pipe_temp;
	int		cmd_count;

	cmd_count = 3;
	if (pipe(pipe_a_fd) == -1)
		ft_error("fds linking at pipe creation has failed");
	ft_infile_child(argv, envp, pipe_a_fd);
	while (middle_childs > 0)
	{
		ft_middle_child(argv[cmd_count], envp, pipe_a_fd, pipe_b_fd);
		middle_childs--;
		cmd_count++;
		ft_pipe_manage(&pipe_a_fd, &pipe_b_fd);
	}
	ft_outfile_child(argv[cmd_count], envp, pipe_a_fd);
	if (close(pipe_fd[0]) == -1)
		ft_error("Parent cant close pipe_fd[0]");
	if (close(pipe_fd[1]) == -1)
		ft_error("Parent cant close pipe_fd[1]");
	ft_wait_childs(total_childs);
}

int	main(int argc, char **argv, char **envp)
{
	int total_childs;

	if (argc >= 5)
		ft_pipex(argv, envp, argc - 3, argc - 5);
	else
	{
		ft_printf_error("pipex: invalid arguments\n");
		return (1);
	}
	return (0);
}
