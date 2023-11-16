/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 12:23:39 by mabbadi           #+#    #+#             */
/*   Updated: 2023/11/15 18:18:30 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
char **getcmd(char **argv)
{
	char **args = ft_split(argv[1], ' ');
	return args;
}

int	main(int argc, char **argv, char **env)
{
	char **cmd = getcmd(argv);
	char **path = ft_split(env[31], ':');
	char *ping = ft_strjoin("/", cmd[0]);
	ping = ft_strjoin(path[5], ping);

	int fd[2];
	if (pipe(fd) == -1)
		return (1);

	int pid1 = fork();
	if (pid1 < 0)
		return (2);

	char *args1[5];
	args1[0] = "ping";
	args1[1] = "-c";
	args1[2] = "2";
	args1[3] = "google.com";
	args1[4] = NULL;

	if (pid1 == 0)
	{
		//Child 1
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(ping, cmd, NULL);
	}

	int pid2 = fork();
	if (pid2 < 0)
		return 0;

	char *args2[3];
	args2[0] = "grep";
	args2[1] = "packets";
	args2[2] = NULL;

	if (pid2 == 0)
	{
		// Child 2
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve("../../../../usr/bin/grep", args2, NULL);
	}

	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}