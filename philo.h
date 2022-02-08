/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchheang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 04:51:39 by dchheang          #+#    #+#             */
/*   Updated: 2022/02/08 14:01:44 by dchheang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <limits.h>

/************* CONSTS ***************/

# define THINKING	0
# define EATING		1
# define SLEEPING	2

/************* STRUCTS **************/

typedef struct s_info
{
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_eat;
	int				all_ate;
	int				end_sim;
	int				room;
	pthread_mutex_t	room_mutex;
	pthread_mutex_t	death_mutex;
	long long		time_start;
}	t_info;

typedef struct s_philo
{
	int				id;
	int				n_eat;
	long long		time_last_meal;
	t_info			*info;
	pthread_mutex_t	*lf;
	pthread_mutex_t	*rf;
}	t_philo;

/************* FUNCS **************/

/*	UTILS	*/
int				check_limit(int n, int sign, int x);
int				ft_atoi(char *s);
long long		get_time(void);
long long		get_timediff(long long start);
void			print_status(t_philo *philo, t_info *info, char *msg);

/*	PARSER	*/
int				check_info(char **av, t_info info);
int				init_info(char **av, t_info *info);
pthread_mutex_t	*init_forks(int n_philo);
t_philo			*init_philo(t_info *info, pthread_mutex_t *forks);

/*	THREADS	*/
void			run_threads(t_info *info, t_philo *philo);

/*	END SIM	*/
void			check_end_sim(t_philo *philo, t_info *info);

/*	EAT	*/
void			take_forks(t_philo *philo);
int				eat(t_philo *philo);
void			ft_sleep(t_philo *philo, long long t);

#endif
