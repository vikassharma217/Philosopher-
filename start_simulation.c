/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:12:29 by vsharma           #+#    #+#             */
/*   Updated: 2024/02/19 12:07:13 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	handel_mutex(t_philo *philos)
{
	pthread_mutex_lock(philos->table->table_mutex);
	if (check_dead(philos) != 0)
	{
		pthread_mutex_unlock(philos->table->table_mutex);
		return (0);
	}
	pthread_mutex_unlock(philos->table->table_mutex);
	return (1);
}

void	*routine(void *args)
{
	t_philo	*philos;

	philos = (t_philo *)args;
	while (check_dead_2(philos) == 0)
	{
		handel_mutex(philos);
		if (pickup_forks(philos))
			return (0);
		pthread_mutex_lock(philos->table->table_mutex);
		if (check_dead(philos) != 0)
		{
			pthread_mutex_unlock(philos->table->table_mutex);
			pthread_mutex_unlock(philos->left_fork);
			pthread_mutex_unlock(philos->right_fork);
			return (0);
		}
		pthread_mutex_unlock(philos->table->table_mutex);
		if (!start_eating(philos))
			return (0);
		handel_mutex(philos);
		start_sleeping(philos);
		handel_mutex(philos);
		start_thinking(philos);
	}
	return (0);
}

int	create_philo_thread(t_table *table)
{
	int	i;

	i = 0;
	table->start_timer = get_time();
	while (i < table->num_of_philos)
	{
		if (pthread_create(&table->philo[i].thread_id, NULL, &routine,
				(void *)&table->philo[i]) != 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	join_thread(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philos)
	{
		pthread_join(table->philo[i].thread_id, NULL);
		i++;
	}
}

int	run_simulation(t_table *table)
{
	pthread_t	monitor_thread;

	create_philo_thread(table);
	if (pthread_create(&monitor_thread, NULL, init_monitoring, table) != 0)
	{
		return (1);
	}
	pthread_join(monitor_thread, NULL);
	join_thread(table);
	free_all(table);
	return (0);
}
