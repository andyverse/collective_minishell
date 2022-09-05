/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chfederi <chfederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 21:57:06 by chfederi          #+#    #+#             */
/*   Updated: 2022/08/25 21:59:54 by chfederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	delete_from_env(t_envp **envp_list, char *arg)
{
	t_envp	*tmp;

	tmp = *envp_list;
	while (*envp_list)
	{
		if (*envp_list && !ft_strcmp((*envp_list)->key, arg))
		{
			tmp = (*envp_list)->next;
			free((*envp_list)->key);
			free((*envp_list)->value);
			free (*envp_list);
			*envp_list = tmp;
		}
		if ((*envp_list)->next && !ft_strcmp((*envp_list)->next->key, arg))
		{
			free((*envp_list)->next->key);
			free((*envp_list)->next->value);
			free((*envp_list)->next);
			(*envp_list)->next = (*envp_list)->next->next;
		}
		*envp_list = (*envp_list)->next;
	}
	*envp_list = tmp;
}

int	ft_unset(t_cmd *cmd, t_envp **envp_list)
{
	int	i;

	if (!envp_list || !cmd)
		return (1);
	if (!cmd->arg)
		return (0);
	i = 0;
	while (cmd->arg[i])
	{
		delete_from_env(envp_list, cmd->arg[i]);
		i++;
	}
	return (0);
}
