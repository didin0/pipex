/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:50:03 by mabbadi           #+#    #+#             */
/*   Updated: 2023/11/29 21:13:37 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	checkexec(char *path, char **cmd)
{
	if (execve(path, cmd, NULL) == -1)
	{
		freetab(cmd);
		free(path);
		perror("bash");
		exit(127);
	}
}

void	child(int fd[2], char **argv, char **env)
{
	int		infile;
	char	**cmd;
	char	*path;

	close(fd[0]);
	infile = open(argv[1], O_RDONLY, 0777);
	if (infile < 0)
	{
		close(fd[1]);
		perror("open");
		exit(errno);
	}
	cmd = getcmd(argv, 2);
	path = getpath(cmd, env);
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	checkexec(path, cmd);
	freetab(cmd);
	free(path);
	close(infile);
}

void	parent(int fd[2], char **argv, char **env)
{
	int		outfile;
	char	**cmd2;
	char	*path2;

	close(fd[1]);
	outfile = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (outfile < 0)
	{
		close(fd[0]);
		perror("open");
		exit(errno);
	}
	cmd2 = getcmd(argv, 3);
	path2 = getpath(cmd2, env);
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[0]);
	checkexec(path2, cmd2);
	close(outfile);
	free(path2);
	freetab(cmd2);
}

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	pid_t	pid1;

	if (argc < 4)
		return (0);
	if (pipe(fd) < 0)
	{
		perror("pipe");
		return (1);
	}
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("fork");
		return (2);
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
