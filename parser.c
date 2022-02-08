/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 06:57:29 by dchheang          #+#    #+#             */
/*   Updated: 2022/02/08 13:02:35 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_info(char **av, t_info info)
{
	if (av[5] && info.n_eat <= 0)
		return (0);
	if (info.n_philo <= 0 || info.time_to_die <= 0 || info.time_to_eat <= 0
		|| info.time_to_sleep <= 0)
		return (0);
	return (1);
}

int	init_info(char **av, t_info *info)
{
	info->room = 0;
	info->end_sim = 0;
	info->all_ate = 0;
	info->n_philo = ft_atoi(av[1]);
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		info->n_eat = ft_atoi(av[5]);
	else
		info->n_eat = -1;
	if (!check_info(av, *info))
	{
		printf("error: arguments\n");
		return (0);
	}
	if (pthread_mutex_init(&info->death_mutex, NULL)
		|| pthread_mutex_init(&info->room_mutex, NULL))
	{
		printf("error: initializing mutex\n");
		return (0);
	}
	return (1);
}

pthread_mutex_t	*init_forks(int n_philo)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(*forks) * n_philo);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < n_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL))
		{
			free(forks);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

t_philo	*init_philo(t_info *info, pthread_mutex_t *forks)
{
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof(*philo) * (info->n_philo));
	if (!philo)
		return (NULL);
	i = 0;
	while (i < info->n_philo)
	{
		philo[i].id = i + 1;
		philo[i].n_eat = 0;
		philo[i].info = info;
		philo[i].lf = &forks[i];
		philo[i].rf = &forks[i + 1];
		if (philo[i].id == info->n_philo)
			philo[i].rf = &forks[0];
		i++;
	}
	return (philo);
}
