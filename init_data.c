/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 15:25:32 by vsharma           #+#    #+#             */
/*   Updated: 2024/02/19 12:07:38 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead_2(t_philo *philos)
{
	pthread_mutex_lock(philos->table->table_mutex);
	if (philos->table->is_dead == 1)
	{
		pthread_mutex_unlock(philos->table->table_mutex);
		return (1);
	}
	pthread_mutex_unlock(philos->table->table_mutex);
	return (0);
}

int	init_philo(t_table *table)
{
	int	i;

	i = 0;
	table->philo = malloc(sizeof(t_philo) * table->num_of_philos);
	if (!table->philo)
		return (1);
	while (i < table->num_of_philos)
	{
		table->philo[i].id = i + 1;
		table->philo[i].last_meal = 0;
		table->philo[i].is_eating = 0;
		table->philo[i].time_to_die = table->time_to_die;
		table->philo[i].time_to_sleep = table->time_to_sleep;
		table->philo[i].time_to_eat = table->time_to_eat;
		table->philo[i].num_of_meals = 0;
		table->philo[i].left_fork = &table->fork_mutex[i];
		table->philo[i].right_fork = &table->fork_mutex[(i + 1)
			% table->num_of_philos];
		table->philo[i].table = table;
		i++;
	}
	return (0);
}

int	init_mutex(t_table *table)
{
	int	i;

	i = 0;
	table->fork_mutex = malloc(sizeof(pthread_mutex_t) * table->num_of_philos);
	if (!table->fork_mutex)
		return (1);
	while (i < table->num_of_philos)
	{
		pthread_mutex_init(&table->fork_mutex[i], NULL);
		i++;
	}
	table->table_mutex = malloc(sizeof(pthread_mutex_t));
	if (!table->table_mutex)
		return (1);
	pthread_mutex_init(table->table_mutex, NULL);
	return (0);
}

int	init_resources(t_table *table, char **argv)
{
	table->num_of_philos = ft_atoi(argv[1]);
	table->kill_switch = 0;
	if (table->num_of_philos == 1)
	{
		table->kill_switch = 1;
	}
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		table->num_of_meals = ft_atoi(argv[5]);
	}
	else
	{
		table->num_of_meals = -1;
	}
	table->is_dead = 0;
	table->done_eating = 0;
	table->simulation_running = 1;
	if (init_mutex(table) != 0)
		return (1);
	if (init_philo(table) != 0)
		return (1);
	return (0);
}
