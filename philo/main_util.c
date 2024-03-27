/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:58:36 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/27 11:15:16 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_check_value(int argc, char **argv, t_info *info)
{
	if (!(argc == 5 || argc == 6))
	{
		printf("INVALID ARGUMENT NUMBER!\n");
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

static int	init_value_thousand(char *argv, long *value, int mul)
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
	long			*count_eat;
	int				*flag;

	print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	count_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
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
		ph[size].count_eat = count_eat;
		ph[size].flag = flag;
		ph[size].how_many_eat = 0;
	}
	return (FUN_SUC);
}

int	init_mutex_thread(t_thread *ph, int size)
{
	pthread_mutex_t	*fork_table;
	pthread_mutex_t	*flag_mutex;
	int				i;

	flag_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(flag_mutex, NULL);
	i = 0;
	while (i < size)
	{
		fork_table = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(fork_table, NULL);
		ph[i].flag_mutex = flag_mutex;
		ph[i].right_fork = fork_table;
		ph[(i + 1) % size].left_fork = fork_table;
		ph[i].ph_name = i + 1;
		i += 1;
	}
	return (FUN_SUC);
}
