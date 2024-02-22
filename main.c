/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 10:39:18 by vsharma           #+#    #+#             */
/*   Updated: 2024/02/11 11:40:18 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (validate_input(argc, argv) == 0)
	{
		if (init_resources(&table, argv) == 0)
		{
			run_simulation(&table);
		}
		else
		{
			printf("MALLOC ERROR: RESOURCE INIT FAILED\n");
		}
	}
	else
	{
		printf("INVALID ARGUMENTS!!\n");
	}
	return (0);
}
