# Threads
https://www.geeksforgeeks.org/difference-between-thread-id-and-thread-handle/?ref=gcse#

https://www.geeksforgeeks.org/concurrency-control-techniques/

https://gist.github.com/convict-git/9e4da852bb034f4aa97b66596f2270f5

https://gitlab.com/Lipovsky/awesome-concurrency

https://www.geeksforgeeks.org/difference-between-cache-coherence-and-memory-consistency/

https://github.com/google/sanitizers

https://stackoverflow.com/q/43019598/7690982

## Synchronization

According to the [Mutex lock for Linux Thread article](https://www.geeksforgeeks.org/mutex-lock-for-linux-thread-synchronization/):

>Thread synchronization is defined as a mechanism which ensures that two or more concurrent processes or threads do not simultaneously execute some particular program segment known as a [critical section][1]. Processes’ access to [critical section][1] is controlled by using synchronization techniques. When one thread starts executing the [critical section][1] (a serialized segment of the program) the other thread should wait until the first thread finishes. If proper synchronization techniques are not applied, it may cause a [race condition][2] where the values of variables may be unpredictable and vary depending on the timings of context switches of the processes or threads.





[1]: https://www.geeksforgeeks.org/g-fact-70/
[2]: https://www.geeksforgeeks.org/implementing-race-condition-in-c/