/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:12:29 by vsharma           #+#    #+#             */
/*   Updated: 2024/02/19 11:34:35 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pickup_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	if (check_dead_2(philo) == 0)
		display_message("has taken a fork", philo);
	if (philo->table->kill_switch)
		return (pthread_mutex_unlock(philo->left_fork), 1);
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_lock(philo->left_fork) != 0)
			return (pthread_mutex_unlock(philo->right_fork), 1);
		if (check_dead_2(philo) == 0)
			display_message("has taken a fork", philo);
	}
	else
	{
		if (pthread_mutex_lock(philo->right_fork) != 0)
			return (pthread_mutex_unlock(philo->left_fork), 1);
		if (check_dead_2(philo) == 0)
			display_message("has taken a fork", philo);
	}
	return (0);
}

int	start_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->table->table_mutex);
	if (check_full_status(philo->table))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->table->table_mutex);
		return (0);
	}
	pthread_mutex_unlock(philo->table->table_mutex);
	display_message("is eating", philo);
	pthread_mutex_lock(philo->table->table_mutex);
	philo->last_meal = get_time() - philo->table->start_timer;
	philo->time_to_die = philo->last_meal + philo->table->time_to_die;
	pthread_mutex_unlock(philo->table->table_mutex);
	ft_sleep(philo->table->time_to_eat, philo);
	pthread_mutex_lock(philo->table->table_mutex);
	if (philo->num_of_meals != -1)
	{
		philo->num_of_meals++;
	}
	pthread_mutex_unlock(philo->table->table_mutex);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (1);
}
