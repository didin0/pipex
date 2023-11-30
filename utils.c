/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 17:56:12 by mabbadi           #+#    #+#             */
/*   Updated: 2023/11/30 16:03:59 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	freetab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

char	**getcmd(char **argv, int i)
{
	char	**args;

	args = ft_split(argv[i], ' ');
	return (args);
}

char	*getenvpath(char **env)
{
	int	i;

	i = 0;
	while (!(ft_strncmp(env[i], "PATH", 4) == 0))
		i++;
	return (env[i]);
}

char	*getpath(char **cmd, char **env)
{
	char	**paths;
	char	*path;
	char	*tmpcmd;
	int		i;

	paths = ft_split(getenvpath(env) + 5, ':');
	i = 0;
	while (paths[i])
	{
		tmpcmd = ft_strjoin("/", cmd[0]);
		path = ft_strjoin(paths[i], tmpcmd);
		if (access(path, F_OK) == 0)
		{
			freetab(paths);
			free(tmpcmd);
			return (path);
		}
		free(tmpcmd);
		free(path);
		i++;
	}
	freetab(paths);
	return (NULL);
}

void	printerror(char *cmd)
{
	if (errno == EFAULT)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(":", 2);
		ft_putstr_fd(" Command not found", 2);
		ft_putstr_fd("\n", 2);
	}
}
