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

#include "../include/philo_bonus.h"

/**
 * Function: Validate argument
 * -----------------
 * This function is used to check if the arguments passed are valid. Here we
 * check if the arguments are numbers, and if they are not, we print an error
 * message and return false.
 *  
 * @param: *str: The argument that is going to be checked.
 * 
 * @return: Returns true if the argument is valid, false otherwise.
 *
 */

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

/**
 * Function: Check args
 * -----------------
 * This function is used to check if the arguments passed are valid. Here we
 * check if the number of arguments is correct, and if they are not, we print
 * an error message and return false. Then we call the validate_argument
 * function to check if the arguments are numbers.
 *  
 * @param: argc: The number of arguments.
 * @param: **argv: The arguments that are going to be checked.
 * 
 * @return: Returns true if the argument is valid, false otherwise.
 *
 */

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
