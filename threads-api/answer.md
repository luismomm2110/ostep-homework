1) It shows memory and address, in right numbers

2) When I remove, there's no error. 
When I use only one lock, its creation appears but there's race condition.
When I create two locks, the problem dissapear, as each thread must pass it.

3)Both thread could get stuck after its initials locks.

4) Helgrind says that was observed wrong order of acquistions of lock. It makessense with previous answer, as, let's say, p1 gets m1 but stops before unlock it. After this, p2 enters in else block, gets m2 and then tries to unlock m1 at line 15, but it is not possible! P1 will try to get m2 and it cannot too.

5) The global lock eliminates the wrong order, but helgrind shows it because its sound but not complete. Even with if the error is not effective, it's still there.

6) Let's imagine that p is created but parent gets the processor. It will run for a while until gives processor back to p1 to change variable done to 1.

7) Error in done and printf

8) It's correct. There are no conflict erros and thread 1 will wait, not run unnecessary.

9) No error
