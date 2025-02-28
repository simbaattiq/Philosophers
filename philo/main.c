/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-atti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 13:13:28 by mel-atti          #+#    #+#             */
/*   Updated: 2024/12/22 19:02:06 by mel-atti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	main(int ac, char **av)
{
	t_rules		general;
	pthread_t	monitor;
	int			i;

	i = 0;
	if (input_checker(ac, av) == 0)
	{
		if (initialize_data(&general, av) == 0)
		{
			pthread_create(&monitor, NULL, monitor_routine, &general);
			i = -1;
			while (++i < general.philo_count)
				pthread_create(&general.threads[i],
					NULL, start_dinner, &general.philos[i]);
			i = -1;
			while (++i < general.philo_count)
				pthread_join(general.threads[i], NULL);
			pthread_join(monitor, NULL);
		}
		clean_everything(&general);
	}
	return (0);
}
