# AtomicQueue

Single producer / single consumer atomic queue which:
* Supports variable message size
* Is cache line aware
* Uses a limited memory. I.e. the real implementation is a ring buffer and the queue interface is overlayed on it.
Ideally the producer and the consumer should be bound to isolated cores.
