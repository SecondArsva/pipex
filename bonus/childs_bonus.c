/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 20:24:27 by davidga2          #+#    #+#             */
/*   Updated: 2023/10/01 06:42:30 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

// Function suggested by samusanc to manage the possible failure of the
// creation of the child in the execution of the initialization of the
// variable that houses the pid.
int	ft_fork_manage(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_error("Infile child pid creation proccess failed");
	return (pid);
}

void	ft_outfile_child_b(char **argv, int cmd_argv, char **envp, int *pipe_fd)
{
	int		outfile_fd;
	pid_t	child_pid;


	ft_printf_error("[into LC] <---\na[0]: %i\na[1]: %i\n", pipe_fd[0], pipe_fd[1]);
	child_pid = ft_fork_manage();
	if (child_pid == 0)
	{
		outfile_fd = open(argv[cmd_argv + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (close(pipe_fd[1]) == -1)
			ft_error("Output child failed closing the write fd pipe");
		if (outfile_fd == -1 || dup2(pipe_fd[0], STDIN_FILENO) == -1
			|| dup2(outfile_fd, STDOUT_FILENO) == -1)
			ft_error("Outfile fd creation or dup2 failed");
		if (close(pipe_fd[0]) == -1 || close(outfile_fd) == -1)
			ft_error("Some fd close failed in the output child proccess");
		ft_exec(argv[cmd_argv], envp);
	}
	ft_printf_error("[out LC] --->\n");
}

void	ft_middle_child(char *cmd_argv, char **envp, int *a_fd, int *b_fd)
{
	pid_t	child_pid;

	ft_printf_error("[into MC] <---\na[0]: %i\na[1]: %i\nb[0]: %i\nb[1]: %i\n", a_fd[0], a_fd[1], b_fd[0], b_fd[1]);
	child_pid = ft_fork_manage();
	if (child_pid == 0)
	{
		close(a_fd[1]);
		close(b_fd[0]);
		dup2(a_fd[0], STDIN_FILENO);
		dup2(b_fd[1], STDOUT_FILENO);
		close(a_fd[0]);
		close(b_fd[1]);

/*
		if (close(a_fd[1]) == -1)
			ft_error("A Middle child failed closing unused pipe A fd");
		if (close(b_fd[0]) == -1)
			ft_error("A Middle child failed closing unused pipe B fd");
		if (dup2(a_fd[0], STDIN_FILENO) == -1) 
			ft_error("A Middle child failed in A dup2");
		if (dup2(b_fd[1], STDOUT_FILENO) == -1)
			ft_error("A Middle child failed in B dup2");
		if (close(a_fd[0]) == -1)
			ft_error("A Middle child failed closing pipe A fds post dups2");
		if (close(b_fd[1]) == -1)
			ft_error("A Middle child failed closing pipe B fds post dups2");*/
		ft_exec(cmd_argv, envp);
	}
	ft_printf_error("[out MC] --->\n");
}

void	ft_infile_child(char **argv, char **envp, int *pipe_fd)
{
	int		infile_fd;
	pid_t	child_pid;

	child_pid = ft_fork_manage();
	if (child_pid == 0)
	{
		if (close(pipe_fd[0]) == -1)
			ft_error("Input child failed closing the read fd pipe");
		infile_fd = open(argv[1], O_RDONLY);
		if (infile_fd == -1 || dup2(infile_fd, STDIN_FILENO) == -1
			|| dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			ft_error("Infile fd creation or dup2 failed");
		if (close(infile_fd) == -1 || close(pipe_fd[1]) == -1)
			ft_error("Some fd close failed in the infile child proccess");
		ft_exec(argv[2], envp);
	}
}
