/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunrodr <brunrodr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:47:36 by brunrodr          #+#    #+#             */
/*   Updated: 2024/01/22 18:47:37 by brunrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static t_bool	validate_argument(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (*str < 0x30 || *str > 0x39)
		{
			printf("Error: Arguments must be numbers\n");
			return (false);
		}
		str++;
	}
	return (true);
}

t_bool	check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (false);
	}
	while (*argv)
	{
		if (!validate_argument(*argv))
			return (false);
		argv++;
	}
	return (true);
}
