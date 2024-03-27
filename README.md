# DINING PHILOSOPHER PROBLEM

### 왜 설렁탕을 사왔는 데 밥을 먹지 못하니...

- 다익스트라의 원본 문제와 약간 다릅니다.
- 그래도 잘 먹어요 ~~얌얌~~

#### philo

- 철학자는 스레드로 생각함

- 철학자의 왼쪽, 오른쪽에 포크가 존재함.

- 포크가 복사되는 것을 방지하기 위해 적절한 atomic한 연산을 활용해야 함

- 철학자는 총 4가지 상태를 가짐

	- 포크를 두개 모두 집을 경우 eating
	- Sleeping
	- 포크를 집기 전까지 Thinking
	- 기아 상태가 사망 시간을 초과하면 Dying

- 프로그램의 인자는 다음과 같음.

	1. 철학자의 수
	1. 철학자가 굶으면 사망하는 시간
	1. 철학자의 식사 시간
	1. 철학자의 수면 시간
	1. (option) 철학자 하나 당 먹어야 하는 식사 횟수.

		- 모든 철학자가 식사 횟수를 만족하면 시뮬레이션 종료

``` Shell
$ make
$ ./philo 2 410 200 200 2
```


### Philo bonus

- 철학자는 프로세스로 생각함

- 포크가 한 가운데에 존재함

- IPC는 세마포어만 허용됨

- 이외에는 상단의 허용사양과 같음

``` Shell
$ make
$ ./philo 2 410 200 200 2
```

### 철학자를 오래 살리기 위한 팁

- 터미널에 출력하는 것은 렌더링 타임때문에 늦어진다.

- 리다이렉션을 통해 파일 입출력을 할 경우 죽지 않고 사는 것을 확인할 수 있다.

``` Shell
$ ./philo 200 410 200 200 > output
```

