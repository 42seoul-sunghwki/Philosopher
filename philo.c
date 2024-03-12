/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:09:31 by sunghwki          #+#    #+#             */
/*   Updated: 2024/03/12 15:28:20 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_value(int argc, char **argv, t_info *info)
{
	int	i;

	i = 1;
	if (!(argc == 5 || argc == 6))
	{
		printf("Invalid Input Size");
		return (FUN_FAIL);
	}
	if (check_atol(argv[i++], &(info->num_philo)))
	{
		if (info->num_philo <= 0)
		{
			printf("INVALID PHILO NUMBER!\n");
			return (FUN_FAIL);
		}
	}
	if (check_atol(argv[i++], &(info->time_to_die)))
		return (FUN_FAIL);
	info->time_to_die *= THOUSAND;
	if (check_atol(argv[i++], &(info->time_to_eat)))
		return (FUN_FAIL);
	info->time_to_eat *= THOUSAND;
	if (check_atol(argv[i++], &(info->time_to_sleep)))
		return (FUN_FAIL);
	info->time_to_sleep *= THOUSAND;
	if (argc == 6)
	{
		if (check_atol(argv[i++], &(info->num_must_eat)))
			return (FUN_FAIL);
	}
	else
		info->num_must_eat = 0;
	return (FUN_SUC);
}

int			init_static_value(t_thread *ph, int size)
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
	long			*fork;
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
		fork = (long *)malloc(sizeof(long));
		*fork = 0;
		ph[(i + 1) % info.num_philo].left_fork = fork_table;
		ph[i].right_fork = fork_table;
		ph[i].info = info;
		ph[i].ph_name = i + 1;
		ph[(i + 1) % info.num_philo].left_f = fork;
		ph[i].right_f = fork;
		i += 1;
	}
	return (ph);
}

void	free_thread(t_thread *ph)
{
	int	i;

	i = ph[0].info.num_philo;
	pthread_mutex_destroy(ph[0].print);
	pthread_mutex_destroy(ph[0].count_mutex);
	free(ph[0].print);
	free(ph[0].count_mutex);
	free(ph[0].count_eat);
	free((void *)ph[0].flag);
	while (--i >= 0)
	{
		pthread_mutex_destroy(ph[i].left_fork);
		free(ph[i].left_fork);
		free(ph[i].left_f);
	}
}

int	main(int argc, char **argv)
{
	pthread_t		*th_name;
	t_thread		*ph;
	t_info			info;
	long			i;

	ph = init_thread(argc, argv);
	info = ph[0].info;
	th_name = (pthread_t *)malloc(sizeof(pthread_t) * info.num_philo);
	i = 0;
	while (i < info.num_philo)
	{
		pthread_create(&th_name[i], NULL, philo, (void *)(&ph[i]));
		//pthread_detach(th_name[i]); //refactoring to join
		i++;
	}
	while (1)
	{
		if (*(ph[0].flag) == DIE) //종료 확인
			break ;
		usleep(1000);
	}
	free_thread(ph);
	free(ph);
	free(th_name);
	return (0);
}
