/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errandfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabbadi <mabbadi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:06:19 by mabbadi           #+#    #+#             */
/*   Updated: 2023/12/02 16:06:53 by mabbadi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	freetab(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
			free(str[i++]);
		free(str);
	}
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
