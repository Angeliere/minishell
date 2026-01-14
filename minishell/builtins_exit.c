/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atbicer <atbicer@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 20:00:00 by atbicer           #+#    #+#             */
/*   Updated: 2026/01/14 20:00:00 by atbicer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(char **argv)
{
	int	exit_code;

	ft_putstr_fd("exit\n", 1);
	if (!argv[1])
		exit(0);
	exit_code = ft_atoi(argv[1]);
	exit(exit_code);
}
