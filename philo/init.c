/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:58:36 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/12 22:23:40 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_check_value(int argc, char **argv, t_info *info)
{
	if (!(argc == 5 || argc == 6))
	{
		printf("Invalid Input Size");
		return (FUN_FAIL);
	}
	if (check_atol(argv[1], &(info->num_philo)))
	{
		return (FUN_FAIL);
	}
	else
	{
		if (info->num_philo <= 0)
		{
			printf("INVALID PHILO NUMBER!\n");
			return (FUN_FAIL);
		}
	}
	return (FUN_SUC);
}

int	init_value_thousand(char *argv, long *value, int mul)
{
	if (check_atol(argv, value))
		return (FUN_FAIL);
	*value *= mul;
	return (FUN_SUC);
}

int	init_value(int argc, char **argv, t_info *info)
{
	int	i;

	i = 2;
	if (init_check_value(argc, argv, info))
		return (FUN_FAIL);
	if (init_value_thousand(argv[i++], &(info->time_to_die), THOUSAND))
		return (FUN_FAIL);
	if (init_value_thousand(argv[i++], &(info->time_to_eat), THOUSAND))
		return (FUN_FAIL);
	if (init_value_thousand(argv[i++], &(info->time_to_sleep), THOUSAND))
		return (FUN_FAIL);
	if (argc == 6)
	{
		if (init_value_thousand(argv[i], &(info->num_must_eat), 1))
			return (FUN_FAIL);
		if (info->num_must_eat <= 0)
		{
			printf("INVALID EAT NUMBER!\n");
			return (FUN_FAIL);
		}
	}
	else
		info->num_must_eat = 0;
	return (FUN_SUC);
}

int	init_static_value(t_thread *ph, int size)
{
	pthread_mutex_t	*print;
	pthread_mutex_t	*count_mutex;
	long			start_time;
	long			*count_eat;
	int				*flag;

	print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	count_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	start_time = ft_microsec_now();
	count_eat = (long *)malloc(sizeof(long));
	flag = (int *)malloc(sizeof(int));
	*count_eat = 0;
	*flag = 0;
	pthread_mutex_init(print, NULL);
	pthread_mutex_init(count_mutex, NULL);
	while (--size >= 0)
	{
		ph[size].print = print;
		ph[size].count_mutex = count_mutex;
		ph[size].start_time = start_time;
		ph[size].count_eat = count_eat;
		ph[size].flag = flag;
	}
	return (TRUE);
}

t_thread	*init_thread(int argc, char **argv)
{
	pthread_mutex_t	*fork_table;
	t_thread		*ph;
	t_info			info;
	long			i;

	if (init_value(argc, argv, &info))
		return (NULL);
	i = 0;
	ph = (t_thread *)malloc((sizeof(t_thread) * info.num_philo));
	init_static_value(ph, info.num_philo);
	while (i < info.num_philo)
	{
		fork_table = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(fork_table, NULL);
		ph[i].right_fork = fork_table;
		ph[(i + 1) % info.num_philo].left_fork = fork_table;
		ph[i].info = info;
		ph[i].ph_name = i + 1;
		ph[i].right_f = (long *)malloc(sizeof(long));
		ph[(i + 1) % info.num_philo].left_f = ph[i].right_f;
		*(ph[i].right_f) = 0;
		i += 1;
	}
	return (ph);
}
