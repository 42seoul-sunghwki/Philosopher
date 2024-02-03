/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunghwki <sunghwki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 15:09:31 by sunghwki          #+#    #+#             */
/*   Updated: 2024/02/04 00:55:50 by sunghwki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_input_to_long(const char *input, long *output)
{
	int	ret;

	ret = ft_islong(input);
	if (ret)
		return (1);
	else
	{
		*output = ft_atol(input);
		if (*output > INT_MAX || *output < INT_MIN)
			return (1);
		return (0);
	}
}

int	main(int argc, char **argv)
{
	pthread_mutex_t	print;
	pthread_mutex_t	count_mutex;
	pthread_mutex_t	*fork_table;
	pthread_t		*th_name;
	t_info			info;
	t_thread		*ph;
	long			*fork;
	int				err[5];
	long			i;
	long	count_eat;

	//입력값 처리
	i = 0;
	if (argc == 5 || argc == 6)
	{
		err[i] = ft_input_to_long(argv[i + 1], &(info.num_philo));
		i++;
		err[i] = ft_input_to_long(argv[i + 1], &(info.time_to_die));
		info.time_to_die *= THOUSAND;
		i++;
		err[i] = ft_input_to_long(argv[i + 1], &(info.time_to_eat));
		info.time_to_eat *= THOUSAND;
		i++;
		err[i] = ft_input_to_long(argv[i + 1], &(info.time_to_sleep));
		info.time_to_sleep *= THOUSAND;
		i++;
		if (argc == 6)
		{
			err[i] = ft_input_to_long(argv[i + 1], &(info.num_must_eat));
			i++;
		}
		else
		{
			info.num_must_eat = 0;
			err[i] = 0;
		}
		while (i >= 0)
			if (err[--i])
				return (1);
	}
	else
	{
		printf("Error!");
		return (1);
	}
	
	//프로세싱
	i = 0;
	pthread_mutex_init(&print, NULL);
	pthread_mutex_init(&count_mutex, NULL);
	fork_table = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info.num_philo);
	while (i < info.num_philo)
		pthread_mutex_init(&(fork_table[i++]), NULL);
	i = 0;
	fork = (long *)malloc(sizeof(long) * info.num_philo);
	ph = (t_thread *)malloc((sizeof(t_thread) * info.num_philo));
	th_name = (pthread_t *)malloc(sizeof(pthread_t) * info.num_philo);
	memset((void *)fork, 0, sizeof(long) * info.num_philo);
	while (i < info.num_philo)
	{
		ph[i].print = &print;
		ph[i].count_mutex = &count_mutex;
		ph[i].left_fork = &fork_table[i];
		ph[i].right_fork = &fork_table[(i + 1) % info.num_philo];
		ph[i].info = info;
		ph[i].ph_name = i + 1;
		ph[i].left_f = &fork[i];
		ph[i].right_f = &fork[(i + 1) % info.num_philo];
		ph[i].count_eat = &count_eat;
		pthread_create(&th_name[i], NULL, philo, (void *)(&ph[i]));
		pthread_detach(th_name[i]);
		i += 1;
	}
	while (1)
	{
		if (count_eat < 0) //종료 확인
			break ;
		usleep(10);
	}
	//할당 해제
	i = 0;
	pthread_mutex_destroy(&print);
	pthread_mutex_destroy(&count_mutex);
	while (i < info.num_philo)
	{
		pthread_mutex_destroy(&(fork_table[i]));
		i++;
	}
	free(fork_table);
	free(th_name);
	free(ph);
	return (0);
}
