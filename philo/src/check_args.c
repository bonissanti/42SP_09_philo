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

t_bool	check_args(int argc, char **argv)
{
	char	*str;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (false);
	}
	while (*argv)
	{
		str = *argv;
		while (*str)
		{
			if (*str < '0' || *str > '9')
			{
				printf("Error: Arguments must be numbers\n");
				return (false);
			}
			if (ft_atol(str) < 0 || ft_atol(str) > 2147483647)
			{
				printf("Error: Arguments must be between 0 and 2147483647\n");
				return (false);
			}
			str++;
		}
		argv++;
	}
	return (true);
}