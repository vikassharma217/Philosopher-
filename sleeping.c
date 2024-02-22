/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsharma <vsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:12:29 by vsharma           #+#    #+#             */
/*   Updated: 2024/02/11 11:58:04 by vsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_sleeping(t_philo *philo)
{
	display_message("is sleeping", philo);
	ft_sleep(philo->table->time_to_sleep, philo);
}
