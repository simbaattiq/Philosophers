/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-atti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 03:12:02 by mel-atti          #+#    #+#             */
/*   Updated: 2024/12/15 04:30:42 by mel-atti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	initialize_data(t_rules *general, char **av)
{
	int	i;

	i = -1;
	if (init_rules(general, av) == 1)
		return (1);
	while (++i < general->philo_count)
		pthread_mutex_init(&general->forks[i], NULL);
	pthread_mutex_init(&general->output_lock, NULL);
	pthread_mutex_init(&general->finished_lock, NULL);
	init_philosophers(general);
	return (0);
}

int	init_rules(t_rules *general, char **av)
{
	general->philo_count = ft_atol(av[1]);
	general->time_to_die = ft_atol(av[2]);
	general->time_to_eat = ft_atol(av[3]);
	general->time_to_sleep = ft_atol(av[4]);
	if (general->philo_count < 1 || general->time_to_die < 1
		|| general->time_to_eat < 1 || general->time_to_sleep < 1)
	{
		return (1);
	}
	if (av[5])
	{
		general->max_meals = ft_atol(av[5]);
		if (general->max_meals < 0)
			return (1);
	}
	else
		general->max_meals = -1;
	general->stop_simulation = 0;
	general->finished_count = 0;
	general->forks = malloc(sizeof(pthread_mutex_t) * general->philo_count);
	general->threads = malloc(sizeof(pthread_t) * general->philo_count);
	general->philos = malloc(sizeof(t_philo) * general->philo_count);
	if (!general->forks || !general->threads || !general->philos)
		return (error_msg("Not enough space for `Alloc'"));
	return (0);
}

void	init_philosophers(t_rules *general)
{
	int		i;
	t_philo	*current;

	i = -1;
	while (++i < general->philo_count)
	{
		current = &general->philos[i];
		pthread_mutex_init(&current->ph_lock, NULL);
		pthread_mutex_init(&current->last_meal_lock, NULL);
		current->id = i + 1;
		current->meals_count = 0;
		current->last_meal = get_timestamp();
		current->start_time = get_timestamp();
		current->eating = 0;
		current->left_fork = &general->forks[i];
		if (general->philo_count > 1)
			current->right_fork = &general->forks[(i + 1)
				% general->philo_count];
		current->rules = general;
	}
}

int	final_check(int ac, char **av)
{
	long long	result;
	int			i;

	i = 0;
	while (++i < ac - 1)
	{
		result = ft_atol(av[i]);
		if (result <= 0)
			return (error_msg("Zero is not a valid input"));
		else if (result > INT_MAX)
			return (error_msg("Use values <= INT_MAX"));
	}
	return (0);
}
