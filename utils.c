/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 17:56:12 by mabbadi           #+#    #+#             */
/*   Updated: 2023/11/24 17:56:32 by mabbadi          ###   ########.fr       */
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
	int		i;
	char	**paths;
	char	*path;
	char	*tmpcmd;

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