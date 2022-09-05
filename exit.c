/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chfederi <chfederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 21:55:27 by chfederi          #+#    #+#             */
/*   Updated: 2022/08/25 21:59:54 by chfederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	arguments_handler(char **array, t_cmd *cmd, t_envp *envp_list)
{
	int	i;

	i = 0;
	if (array[0][i] == '+' || array[0][i] == '-')
		i++;
	while (array[0][++i])
	{
		if (array[0][i] < '0' || array[0][i] > '9')
		{
			ft_putendl_fd("Minisheldon: exit: numeric argument required", 2);
			free_com_list(cmd);
			free_envp_list(envp_list);
			exit(255);
		}
	}
	if (array[1])
		ft_putendl_fd("exit \nMinisheldon : exit: too many arguments", 2);
	else
	{
		i = ft_atoi(array[0]);
		ft_putendl_fd("exit", 1);
		free_com_list(cmd);
		free_envp_list(envp_list);
		exit(i);
	}
}

void	ft_exit(t_cmd *cmd, t_envp *envp_list)
{
	int	i;

	i = 0;
	if (!cmd->arg)
	{
		ft_putendl_fd("exit", 1);
		free_com_list(cmd);
		free_envp_list(envp_list);
		exit(0);
	}
	else
		arguments_handler(cmd->arg, cmd, envp_list);
}
