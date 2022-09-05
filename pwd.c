/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chfederi <chfederi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 21:56:31 by chfederi          #+#    #+#             */
/*   Updated: 2022/08/25 21:59:54 by chfederi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_envp *envp_list)
{
	char	*pwd;

	if (!envp_list)
		return (1);
	pwd = get_value_from_envp(envp_list, "PWD");
	if (!pwd)
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
		{
			if (chdir("..") == -1)
			{
				perror("<3: pwd: ");
				return (1);
			}
			pwd = getcwd(NULL, 0);
		}
	}
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (0);
}
