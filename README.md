*This project has been created as part of the 42 curriculum by vpinto-g.*

# philosophers
#### Five philosophers walk into a dining room... what could possibly go wrong?

Milestone: **3**

## Description

Philosophers is an implementation of the classic Dining Philosophers concurrency problem using POSIX threads and mutexes.
The goal is to coordinate multiple philosophers who alternate between eating, sleeping, and thinking while sharing a limited number of forks. The challenge is to synchronize access to shared resources, prevent data races, avoid deadlocks, and correctly detect when a philosopher dies.
This project focuses on multithreading, synchronization, timing accuracy, and concurrent programming in C.

## Instructions

- Clone the project (``git clone from intra``)
- Compile the program (``make``)
- run with (``./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat])``)

As the project's build system is ``make``, multiple convenience rules are implemented. For specifics, run ``make help``.

## Resources

- **AI Usage: <u>0%</u>**
    - I mostly used AI for structure puposes simple error tracking and README.md

- **Sources & Research:**
	42 Philosophers Subject
	POSIX Threads documentation
	POSIX Mutex documentation
	Oceano's Philosophers video, which provides a clear explanation of the synchronization concepts used in this project.

- **External Libraries Used:**
    - pthread

- **Feature**

Multithreaded implementation using pthread
Thread synchronization with mutexes
Accurate timing for philosopher actions
Fork acquisition and release
Death monitoring
Optional meal limit
Graceful program termination
Memory leak free
Follows the 42 Norm