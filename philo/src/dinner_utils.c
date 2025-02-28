/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-atti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 04:13:51 by mel-atti          #+#    #+#             */
/*   Updated: 2024/12/22 17:33:09 by mel-atti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	handle_single_philo(t_philo *philo, t_rules *general)
{
	if (general->philo_count == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		message_log(general, philo, philo->id, "has taken a fork");
		safe_usleep(general->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	return (0);
}

int	handle_zero_meals(t_philo *philo, t_rules *general)
{
	pick_the_forks(philo, general);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (1);
}

void	pick_the_forks(t_philo *philo, t_rules *general)
{
	if (philo->id % 2 == 0)
	{
		usleep(37);
		if (pthread_mutex_lock(philo->right_fork) == 0)
		{
			if (pthread_mutex_lock(philo->left_fork) != 0)
				pthread_mutex_unlock(philo->right_fork);
			else
				message_log(general, philo, philo->id, "has taken a fork");
		}
	}
	else
	{
		if (pthread_mutex_lock(philo->left_fork) == 0)
		{
			if (pthread_mutex_lock(philo->right_fork) != 0)
				pthread_mutex_unlock(philo->left_fork);
			else
				message_log(general, philo, philo->id, "has taken a fork");
		}
	}
}
