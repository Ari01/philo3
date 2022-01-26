/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 07:00:52 by dchheang          #+#    #+#             */
/*   Updated: 2022/01/26 17:36:09 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_room(t_info *info)
{
	int	ret;

	ret = 0;
	if (info->n_philo == 1)
		return (1);
	pthread_mutex_lock(&info->room_mutex);
	if (info->room <= info->n_philo / 2)
	{
		info->room++;
		ret = 1;
	}
	//printf("%lu in room : %d\n", get_timediff(info->time_start), info->room);
	pthread_mutex_unlock(&info->room_mutex);
	return (ret);
}

void	*run_sim(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->info->death_mutex);
		if (philo->info->end_sim)
		{
			pthread_mutex_unlock(&philo->info->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->info->death_mutex);
		if (check_room(philo->info))
		{
			take_forks(philo);
			if (eat(philo))
			{
				print_status(philo, philo->info, "is sleeping");
				ft_sleep(philo, philo->info->time_to_sleep);
				//usleep(philo->info->time_to_sleep * 1000);
				print_status(philo, philo->info, "is thinking");
			}
		}
	}
	return (NULL);
}

pthread_t	*init_threads(t_philo *philo, t_info *info)
{
	pthread_t	*threads;
	int			i;

	threads = malloc(sizeof(*threads) * info->n_philo);
	if (threads == NULL)
		return (NULL);
	i = 0;
	info->time_start = get_time();
	while (i < info->n_philo)
	{
		philo[i].time_last_meal = info->time_start;
		if (pthread_create(&threads[i], NULL, run_sim, &philo[i]))
		{
			free(threads);
			return (NULL);
		}
		i++;
	}
	return (threads);
}

void	run_threads(t_info *info, t_philo *philo)
{
	pthread_t	*threads;
	int			i;

	threads = init_threads(philo, info);
	if (!threads)
		printf("error creating threads\n");
	else
	{
		check_end_sim(philo, info);
		i = 0;
		while (i < info->n_philo)
		{
			if (pthread_join(threads[i], NULL))
			{
				printf("error waiting threads\n");
				break ;
			}
			i++;
		}
		free(threads);
	}
}
