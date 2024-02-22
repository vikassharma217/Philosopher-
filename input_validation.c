/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:54:35 by vsharma           #+#    #+#             */
/*   Updated: 2024/02/11 14:48:37 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	validate_args_numeric(int argc, char **argv)
{
	int	i;
	int	k;

	i = 1;
	while (i < argc)
	{
		k = 0;
		while (argv[i][k] != '\0')
		{
			if (argv[i][k] < '0' || argv[i][k] > '9' || ft_atoi(argv[i]) == 0)
			{
				return (1);
			}
			k++;
		}
		i++;
	}
	return (0);
}

int	validate_input(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		return (1);
	}
	if (validate_args_numeric(argc, argv) != 0)
	{
		return (1);
	}
	return (0);
}
