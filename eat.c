/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:36:04 by dchheang          #+#    #+#             */
/*   Updated: 2022/02/08 17:35:12 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(t_philo *philo, long long t)
{
	long long	start;
	int			death;

	start = get_time();
	death = 0;
	while (1)
	{
		pthread_mutex_lock(&philo->info->death_mutex);
		if (philo->info->end_sim)
			death = 1;
		pthread_mutex_unlock(&philo->info->death_mutex);
		if (death || get_timediff(start) >= t)
			break ;
		usleep(100);
	}
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->rf);
	print_status(philo, philo->info, "has taken a fork");
	if (philo->info->n_philo != 1)
	{
		pthread_mutex_lock(philo->lf);
		print_status(philo, philo->info, "has taken a fork");
	}
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->lf);
	pthread_mutex_unlock(philo->rf);
}

int	eat(t_philo *philo)
{
	if (philo->info->n_philo == 1)
	{
		ft_sleep(philo, philo->info->time_to_die);
		return (0);
	}
	print_status(philo, philo->info, "is eating");
	pthread_mutex_lock(&philo->info->death_mutex);
	philo->time_last_meal = get_time();
	if (philo->info->n_eat >= 0 && philo->n_eat >= 0)
		philo->n_eat++;
	pthread_mutex_unlock(&philo->info->death_mutex);
	ft_sleep(philo, philo->info->time_to_eat);
	drop_forks(philo);
	return (1);
}
