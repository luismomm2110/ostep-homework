1. First let’s make sure you understand how the programs generally work, and
some of the key options. Study the code in vector-deadlock.c, as well
as in main-common.c and related files.
Now, run ./vector-deadlock -n 2 -l 1 -v, which instantiates two
threads (-n 2), each of which does one vector add (-l 1), and does so in
verbose mode (-v). Make sure you understand the output. How does the
output change from run to run.

The result is not deterministic. Sometimes it goes from v1 to v2 and vice-versa

2. Now add the -d flag, and change the number of loops (-l) from 1 to higher
numbers. What happens? Does the code (always) deadlock?

Sometimes

3. How does changing the number of threads (-n) change the outcome of the
program? Are there any values of -n that ensure no deadlock occurs?

0 and 1 don't implies deadlock

4. . Now examine the code in vector-global-order.c. First, make sure you
understand what the code is trying to do; do you understand why the code
avoids deadlock? Also, why is there a special case in this vector add()
routine when the source and destination vectors are the same?

Ensure a order using adress. It needs a special case as this does not ocurrs when is the same.

5. Now run the code with the following flags: -t -n 2 -l 100000 -d. How long does the code take to complete? How does the total time change when you increase the number of loops, or the number of threads?

Time: 0.06 seconds  2 Thread
Time: 0.22 seconds  5 Threads
Time: 0.44 seconds 20 Threads

6. What happens if you turn on the parallelism flag (-p)? How much would you expect performance to change when each thread is working on adding different vectors (which is what -p enables) versus working on the same ones?

Threads can work in differents vectors

20 Threads and 100000 loops decrease from 0.44 seconds to 0.16s

7. Now let’s study vector-try-wait.c. First make sure you understand the code. Is the first call to pthread_mutex_trylock() really needed? Now run the code. How fast does it run compared to the global order approach? How does the number of retries, as counted by the code, change as the number of threads increases?

./vector-try-wait -t -n 3 -l 100000 
Retries: 46528
Time: 0.33 seconds

8. Now let’s look at vector-avoid-hold-and-wait.c. What is the main problem with this approach? How does its performance compare to the other versions, when running both with -p and without it?

As there's a global lock, just one thread can update at time

9. Finally, let’s look at vector-nolock.c. This version doesn’t use locks at all; does it provide the exact same semantics as the other versions? Why or why not?

Don't use lock, as the operation is done atomically.

10. Now compare its performance to the other versions, both when threads are working on the same two vectors (no -p) and when each thread is working on separate vectors (-p). How does this no-lock version perform?

./vector-nolock -t -n 2 -l 200000 -p   
Time: 0.17 seconds




