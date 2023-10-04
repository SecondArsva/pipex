/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:37:02 by davidga2          #+#    #+#             */
/*   Updated: 2023/10/04 05:27:01 by davidga2         ###   ########.fr       */
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
	int		left[2];
	int		right[2];
	int		cmd_count;

	cmd_count = 3;
	if (pipe(left) == -1)
		ft_error("fds linking at pipe creation has failed");
	ft_infile_child(argv, envp, left);
	while (middle_childs > 0)
	{
		ft_printf_error("--- MD%i---\n", cmd_count - 2);
		if (pipe(right) == -1)
			ft_error("fds linking at pipe creation has failed");
		
		ft_middle_child(argv[cmd_count], envp, left, right);
		middle_childs--;
		cmd_count++;

		ft_printf_error("---------------------\n");
	}
	ft_outfile_child_b(argv, cmd_count, envp, left);
	if (close(left[0]) == -1)
	{
		ft_printf_error("[P] pipe_a_0: %i\n", left[0]);/////////
		//ft_error("Parent cant close pipe_fd[0]");
	}
	if (close(left[1]) == -1)
	{
		ft_printf_error("[P] pipe_a_1: %i\n", left[1]);/////////
		//ft_error("Parent cant close pipe_fd[1]");
	}
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
