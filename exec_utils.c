/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chfederi <chfederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 21:55:16 by chfederi          #+#    #+#             */
/*   Updated: 2022/08/25 21:59:54 by chfederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lstsize(t_cmd *lst)
{
	int	i;

	i = 0;
	if (lst)
	{
		while (lst)
		{
			i++;
			lst = lst->next;
		}
	}
	return (i);
}

int	envsize(t_envp *lst)
{
	int	i;

	i = 0;
	if (lst)
	{
		while (lst)
		{
			i++;
			lst = lst->next;
		}
	}
	return (i);
}

int	count_array(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->arg[i])
		i++;
	return (i);
}

int	count_pipes(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		pipes;

	pipes = 0;
	tmp = cmd;
	while (tmp)
	{
		if (tmp->redir == 1)
			pipes++;
		tmp = tmp->next;
	}
	return (pipes);
}
