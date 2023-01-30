# Assignments
---
#### Assignment 1: Producer and ConsumerActivity Directions:
In this project for design, implement, and evaluate a computing-based solution to meet a given set of computing requirements. 
It is a program of demonstrating the ability to create and manage processes and threads.
They will create two processes, Producer and Consumer, using the C++.
The Producer is simply creating numbers, which are “passed” to the Consumer in a static buffer. 
The task is to implement the put() and get() functions. Each function will use a buffer (implemented as a word). 
The objective is to ensure that the producer is always ahead of the consumer and the consumer does not have to wait.

<br>
The purpose of this task is to demonstrate the ability to implement synchronization using mutex in C++. The task requires two processes, the Producer and the Consumer, to be created and managed. The Producer and Consumer uses queue for getting a product and putting a product. The Producer generates products and passes them to the Consumer up to the size of 15. The aim is to ensure that the Consumer is always one step behind the Producer and does not have to wait for a product by using the mutex. A mutex is used to synchronize the access to the shared buffer between the two processes. The program runs in a single while loop where the Producer produces 15 products and then the Consumer consumes them. 
