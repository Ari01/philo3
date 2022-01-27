/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:36:04 by dchheang          #+#    #+#             */
/*   Updated: 2022/01/27 18:44:11 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(t_philo *philo, int t)
{
	long long	start;
	long long	t_die;
	long long	t_slept;

	start = get_time();
	t_die = philo->info->time_to_die;
	while ((t_slept = get_timediff(start)) < t && get_timediff(philo->time_last_meal) < t_die)
		usleep(1);
}

int	take_fork(t_philo *philo, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	if (check_end_sim(philo, philo->info))
	{
		pthread_mutex_unlock(mutex);
		return (0);
	}
	return (1);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->lf);
		print_status(philo, philo->info, "has taken a fork");
		if (philo->info->n_philo != 1)
		{
			pthread_mutex_lock(philo->rf);
			print_status(philo, philo->info, "has taken a fork");
		}
	}
	else
	{
		pthread_mutex_lock(philo->rf);
		print_status(philo, philo->info, "has taken a fork");
		pthread_mutex_lock(philo->lf);
		print_status(philo, philo->info, "has taken a fork");
	}
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->rf);
	pthread_mutex_unlock(philo->lf);
}

int	eat(t_philo *philo)
{
	if (philo->info->n_philo == 1)
	{
		ft_sleep(philo, philo->info->time_to_die);
		return (0);
	}
	philo->time_last_meal = get_time();
	print_status(philo, philo->info, "is eating");
	if (philo->info->n_eat >= 0 && philo->n_eat >= 0)
		philo->n_eat++;
	ft_sleep(philo, philo->info->time_to_eat);
	drop_forks(philo);
	pthread_mutex_lock(&philo->info->room_mutex);
	philo->info->room--;
	pthread_mutex_unlock(&philo->info->room_mutex);
	return (1);
}
