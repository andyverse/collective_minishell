/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chfederi <chfederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 21:55:44 by chfederi          #+#    #+#             */
/*   Updated: 2022/08/25 21:59:54 by chfederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(t_cmd *cmd)
{
	char	*line;
	int		fd[2];

	pipe(fd);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(cmd->file, line))
		{
			free(line);
			close(fd[1]);
			return (fd[0]);
		}
		ft_putendl_fd(line, fd[1]);
		free(line);
	}
}
