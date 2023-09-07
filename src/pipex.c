/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidga2 <davidga2@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 23:37:02 by davidga2          #+#    #+#             */
/*   Updated: 2023/09/07 18:21:38 by davidga2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_error(char *msg);
void	ft_infile_child(char **argv, char **binaries, char **envp);
void	ft_outfile_child(char **argv, char **binaries, char **envp);
char	**ft_get_paths(char **envp);
void	ft_pipex(char **argv, char **envp);
int		ft_exec(char binaries, char **cmd, char **envp);

void	ft_infile_child(char **argv, char **binaries, char **envp)
{
	pid_t child_pid;
	int pipe;
	char **cmd;
	int i;

	child_pid = fork();
	cmd = ft_split(argv[2], ' ');
	i = 0;

	if (child_pid == -1 || !cmd)
		ft_error("Creation process or command split failed.\n");
	else if (child_pid == 0)
	{
		pipe();
		while (binaries[i])
		{
			if (access(binaries[i], F_OK) != -1)
				execve(binaries[i], cmd, envp);
			else
				ft_error("");
			i++;
		}
		exit(0);
	}
}

void	ft_error(char *msg)
{
	perror(msg);
	exit(errno);
}

char **ft_get_paths(char **envp)
{
	int i;
	char **matrix;

	i = 0;
	mtx = NULL;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i]) // Esto evita un segmantation fault en caso de no existir la variable PATH.
		ft_error("PATH dont exits in the enviroment.\n");
	matrix = ft_split(&envp[i][5], ':');
	if (!matrix)
		ft_error("Binaries matrix reserve failed\n");
	return (matrix);
}

void ft_pipex(char **argv, char **envp)
{
	char	**binaries;
	int		infile_fd;
	int		outfile_fd;
	int		pipefd[2];

	binaries = ft_get_paths(envp);
	infile_fd = open(argv[1], O_RDONLY);
	outfile_fd = open(argv[4], O_WRONLY | );

	ft_infile_child(argv, binaries, envp);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 5)
		ft_pipex(argv, envp);
	else
		return (1);
	return (0);
}
