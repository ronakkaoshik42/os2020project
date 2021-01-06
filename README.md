# Process Scheduling Visualizer

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

This is a course project for the course CS 301 : Operating Systems at IIT Gandhinagar, India.

Team Members: Ronak Kaoshik, Ribhu Vajpeyi, Shweta Pardeshi, Utsav Jethva, Deepika Soni

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

We have build a Process Scheduling Visulizer GUI program using Qt designer involving the following scheduling algorithms: Shortest Remaining Time First (SRTF), Round-robin (RR), First Come First Serve (FCFS), Fixed Priority Preemptive Scheduling (FPPS) and also Work Conserving algorithm.

## Motivation:
Process scheduling is an integral part of operating systems that ensures a fair and optimal execution of processes using the available resources. There are multiple-scheduling algorithms that can be used and there are a wide range of parameters and metrics associated with the scheduler. Having a graphics simulator for the scheduler will help in monitoring the process execution and the metrics. A simulator can also be used as a strong resource for teaching students about the working of schedulers.

## Assumptions:
We are taking into account the CPU cycles needed for each process as well as the I/O frequency (Disk access). Following are the assumptions taken into consideration while designing:
a. CPU and IO cycles requires equal amount of time to execute (1 sec).
b. There should be at least 2 processes to be scheduled
c. The parameter to control IO split is no. of CPU cycle after which an IO cycle should appear
d. FCFS, SRTF, RR and PR algorithms are in their non work conserving format
e. Work Conserving algorithm is based on Priority algorithm

## About the Algorithms: 

## 1. First Come First Serve (FCFS):
   a. Schedules according to arrival times of processes  
   b. Implemented by using the FIFO queue  

## 2. Shortest Remaining Time First (STRF-Preemptive):
   a. The processor is allocated to the job closest to completion  
   b. Preemptive scheduling is used when a process switches from running state to ready state or from waiting state to ready state  

## 3. Fixed Priority Preemptive Scheduling (FPPS):
   a. The highest priority task is  performed first ignoring the other task to be executed  
   b. Sorted FIFO queue is used for this strategy  

## 4. Round Robin Scheduling(RR):
   a. Each process is assigned a fixed time slot in a cyclic way  
   b. Starvation-free as all processes get fair share of CPU  
   c. The disadvantage of it is more overhead of context switching  

## 5. Work Conserving Scheduling:
   a. Always try to keep resource (CPU) busy  
   b. CPU Utilisation is nearly 100%  
   c. Any algorithm can be formatted as work conserving algorithm  
   
## Metrics Calculated:
Turn Around Time, Response Time, Waiting Time (for each process)

## Code Structure

![Code Structure](/images/code_structure.jpg)

## Working
One can input data manually or use a CSV file (format: arrival time - cpu cycles - io cycles - priority). The code has been written in such a way that it will generate a warning if the CSV file is of an incompatible format.

## Simulator

![FPPS implemetation](/images/demo1.png)


## Future Work:
a. To expand and incorporate more scheduling algorithms
b. Improving the GUI

We would like to thank Prof Nipun Batra and our TA Tom Glint Issac who helped and mentored us throughout.








