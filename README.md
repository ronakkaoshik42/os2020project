# Process Scheduling Visualizer

This is a course project for the course CS 301 : Operating Systems at IIT Gandhinagar, India.

We have build a Process Scheduling Visulizer GUI program using Qt designer involving four scheduling algorithms namely Shortest Remaining Time First (SRTF), Round-robin (RR), First Come First Serve (FCFS), Fixed Priority Preemptive Scheduling (FPPS - also Work Conserving).

## 1. First Come First Serve:
   a.Schedules according to arrival times of processes
   b.Implemented by using the FIFO queue

## 2. Shortest Remaining Time First (Preemptive):
   a.The processor is allocated to the job closest to completion
   b.Preemptive scheduling is used when a process switches from running state to ready state or from waiting state to ready state

## 3. Fixed Priority Preemptive Scheduling:
   a.The highest priority task is  performed first ignoring the other task to be executed
   b.Sorted FIFO queue is used for this strategy

## 4. Round Robin Scheduling:
   a.Each process is assigned a fixed time slot in a cyclic way
   b.Starvation-free as all processes get fair share of CPU
   c.The disadvantage of it is more overhead of context switching

## 5. Work Conserving Scheduling:
   a.Always try to keep resource (CPU) busy
   b.CPU Utilisation is nearly 100%
   c.Any algorithm can be formatted as work conserving algorithm




