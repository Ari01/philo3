/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 04:48:14 by dchheang          #+#    #+#             */
/*   Updated: 2022/01/25 11:28:45 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_info(t_info info)
{
	printf("nphilo = %d\n", info.n_philo);
	printf("time to die = %d\n", info.time_to_die);
	printf("time to eat = %d\n", info.time_to_eat);
	printf("time to sleep = %d\n", info.time_to_sleep);
	printf("n eat = %d\n", info.n_eat);
}

void	print_philo(t_philo *philo, int n_philo)
{
	int	i;

	i = 0;
	while (i < n_philo)
	{
		printf("id = %d\n", philo[i].id);
		printf("neat = %d\n", philo[i].n_eat);
		printf("lf = %p\n", philo[i].lf);
		printf("rf = %p\n", philo[i].rf);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_info			info;
	t_philo			*philo;
	pthread_mutex_t	*forks;

	if (ac != 5 && ac != 6)
		printf("error: number arguments\n");
	else
	{
		if (!init_info(av, &info))
			return (1);
		forks = init_forks(info.n_philo);
		if (!forks)
			return (1);
		philo = init_philo(&info, forks);
		if (!philo)
		{
			free(forks);
			return (1);
		}
		run_threads(&info, philo);
		free(philo);
		free(forks);
	}
	return (0);
}
