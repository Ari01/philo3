/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end_sim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 09:33:29 by dchheang          #+#    #+#             */
/*   Updated: 2022/02/08 15:29:21 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo, t_info *info)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&info->death_mutex);
	if (get_timediff(philo->time_last_meal) >= (long long)info->time_to_die)
	{
		info->end_sim = 1;
		printf("%lld %d %s\n", get_timediff(info->time_start), philo->id, "died");
		ret = 1;
	}
	pthread_mutex_unlock(&info->death_mutex);
	return (ret);
}

int	check_eat(t_philo *philo, t_info *info)
{
	int	ret;

	ret = 0;
	if (info->n_eat > 0)
	{
		pthread_mutex_lock(&info->death_mutex);
		if (philo->n_eat >= info->n_eat)
		{
			info->all_ate++;
			philo->n_eat = -1;
		}
		if (info->all_ate >= info->n_philo)
		{
			info->end_sim = 1;
			ret = 1;
		}
		pthread_mutex_unlock(&info->death_mutex);
	}
	return (ret);
}

void	check_end_sim(t_philo *philo, t_info *info)
{
	int	i;
	int	end_sim;

	end_sim = 0;
	while (!end_sim)
	{
		i = 0;
		while (!end_sim && i < info->n_philo)
		{
			end_sim = check_death(&philo[i], info);
			i++;
			usleep(100);
		}
		i = 0;
		while (!end_sim && i < info->n_philo)
		{
			end_sim = check_eat(&philo[i], info);
			i++;
		}
	}
}
