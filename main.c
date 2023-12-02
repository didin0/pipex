/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:50:03 by mabbadi           #+#    #+#             */
/*   Updated: 2023/12/02 21:21:45 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	checkexec(char *path, char **cmd, char **argv, int i)
{
	if (execve(path, cmd, NULL) == -1)
	{
		if (cmd)
			printerror(cmd[0]);
		else
		{
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd(":", 2);
			ft_putstr_fd(" Command not found", 2);
			ft_putstr_fd("\n", 2);
		}
		if (cmd)
			freetab(cmd);
		if (path)
			free(path);
		exit(127);
	}
}

void	child(int fd[2], char **argv, char **env)
{
	int		infile;
	char	**cmd;
	char	*path;

	path = NULL;
	close(fd[0]);
	infile = open(argv[1], O_RDONLY, 0777);
	if (infile < 0)
	{
		close(fd[1]);
		perror(argv[1]);
		exit(errno);
	}
	cmd = getcmd(argv, 2);
	if (cmd && (!(access(cmd[0], F_OK) == 0)))
		path = getpath(cmd, env);
	else if (cmd && cmd[0])
		path = cmd[0];
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	checkexec(path, cmd, argv, 2);
	close(infile);
}

void	parent(int fd[2], char **argv, char **env)
{
	int		outfile;
	char	**cmd2;
	char	*path2;

	path2 = NULL;
	close(fd[1]);
	outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (outfile < 0)
	{
		close(fd[0]);
		perror("open");
		exit(errno);
	}
	cmd2 = getcmd(argv, 3);
	if (cmd2 && (!(access(cmd2[0], F_OK) == 0)))
		path2 = getpath(cmd2, env);
	else if (cmd2 && cmd2[0])
		path2 = cmd2[0];
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[0]);
	checkexec(path2, cmd2, argv, 3);
	close(outfile);
}

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	pid_t	pid1;

	if (argc != 5)
		return (1);
	if (pipe(fd) < 0)
	{
		perror("pipe");
		return (2);
	}
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("fork");
		return (3);
	}
	if (pid1 == 0)
		child(fd, argv, env);
	else
	{
		parent(fd, argv, env);
		waitpid(pid1, NULL, 0);
	}
	return (0);
}
