/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:12:29 by vsharma           #+#    #+#             */
/*   Updated: 2024/02/21 18:40:40 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_philo *philo)
{
	if (philo->table->is_dead == 1)
	{
		return (1);
	}
	return (0);
}

int	check_last_meal(t_philo *philo)
{
	if (get_time() - philo->table->start_timer > philo->time_to_die)
	{
		philo->table->is_dead = 1;
		printf("%d %d died\n", get_time() - philo->table->start_timer,
			philo->id);
		return (1);
	}
	else
		return (0);
}

int	check_dead_status(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philos)
	{
		if (check_last_meal(&table->philo[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_full_status(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philos)
	{
		if (table->num_of_meals == -1)
			return (0);
		if (table->philo[i].num_of_meals >= table->num_of_meals)
		{
			table->done_eating++;
			if (table->done_eating == table->num_of_philos)
				return (1);
		}
		i++;
	}
	table->done_eating = 0;
	return (0);
}

void	*init_monitoring(void *args)
{
	t_table	*table;

	table = (t_table *)args;
	while (table->simulation_running) 
	{
		pthread_mutex_lock(table->table_mutex);
		if (check_dead_status(table))
		{
			pthread_mutex_unlock(table->table_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(table->table_mutex);
		pthread_mutex_lock(table->table_mutex);
		if (table->num_of_meals != -1)
		{
			if (check_full_status(table))
			{
				table->is_dead = 1;
				table->simulation_running = 0;
			}
		}
		pthread_mutex_unlock(table->table_mutex);
		usleep(1000);
	}
	return (NULL);
}
