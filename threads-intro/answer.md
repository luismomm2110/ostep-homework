1. Let’s examine a simple program, “loop.s”. First, just read and understand it. Then, run it with these arguments (./x86.py -p loop.s
-t 1 -i 100 -R dx) This specifies a single thread, an interrupt
every 100 instructions, and tracing of register %dx. What will %dx
be during the run? Use the -c flag to check your answers; the answers, on the left, show the value of the register (or memory value)
after the instruction on the right has run.

_ 0 -> -1 _


Same code, different flags: (./x86.py -p loop.s -t 2 -i 100
-a
dx=3,dx=3 -R dx) This specifies two threads, and initializes each
%dx to 3. What values will %dx see? Run with -c to check. Does
the presence of multiple threads affect your calculations? Is there a
race in this code?

%dx will see 3,2,1,0-1. No. No race, its registers are unique.


Run this:./x86.py -p loop.s -t 2 -i 3 -r -a dx=3,dx=3 -R dx This makes the interrupt interval small/random; use different seeds (-s) to see different interleavings. Does the interrupt frequency change anything?

Same answer as above.


Now, a different program, looping-race-nolock.s, which accesses a shared variable located at address 2000; we’ll call this variable value. Run it with a single thread to confirm your understanding: ./x86.py -p looping-race-nolock.s -t 1 -M 2000 What is value(i.e.,at memory address 2000) throughout the run? Use -c to check.

0->1

Run with multiple iterations/threads: ./x86.py -p looping-race-nolock.s -t 2 -a bx=3 -M 2000 Why does each thread loop three times? What is final value of value?

Each thread loop three times because %bx initiliazes with 3. The final value in address 2000 is 6.



Run with random interrupt intervals: ./x86.py -p looping-race-nolock.s -t 2 -M 2000 -i 4 -r -s 0 with different seeds (-s 1, -s 2, etc.) Can you tell by looking at the thread interleaving what the final value of value will be? Does the timing of the interrupt matter? Where can it safely occur? Where not? In other words, where is the critical section exactly? 

If value is not stored in 2000 before interrupts, each thread overwrite the other and the computation is not deterministic.


Now examine fixed interrupt intervals: ./x86.py -p looping-race-nolock.s -a bx=1 -t 2 -M 2000 -i 1 What will the final value of the shared variable value be? What about when you change -i 2, -i 3, etc.? For which interrupt intervals does the program give the “correct” answer? 

Only after interruption is 3 it does give correct answer, the number of instructions to move to register, add and move to memory.


Run the same for more loops (e.g., set -a bx=100). What interrupt intervals (-i) lead to a correct outcome? Which intervals are surprising?

Every multiple of three works, Other interrupt before the whole operation, so both thread enter together at critical section


One last program: wait-for-me.s. Run: ./x86.py -p wait-for-me.s -a ax=1,ax=0 -R ax -M 2000 This sets the %ax register to 1 for thread 0, and 0 for thread 1, and watches %ax and memory location 2000. How should the code behave? How is the value at location 2000 being used by the threads? What will its final value be? 

The code should transfer 1 to 2000 in T1, then T2 should catch to your %cx anad test. 1



 Now switch the inputs: ./x86.py -p wait-f.s -a
ax=0,ax=1 -R ax -M 2000 How do the threads behave? What
is thread 0 doing? How would changing the interrupt interval (e.g.,
-i 1000, or perhaps to use random intervals) change the trace outcome? Is the program efficiently using the CPU? 

Thread 0 runs for a long time because it's never gets the test right; Longer interrupts intervals only increases the desnecessary CPU use. 
