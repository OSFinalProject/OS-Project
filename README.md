# OS-Project

## Using Combinational Scheduling: SPN for People & RR for Elevators
### Why Choose SPN?
SPN is a scheduling algorithm that prioritizes processes (in our case, passengers) based on their shortest travel distance. It is beneficial for our elevator OS due to the following reasons:

1. Efficiency: SPN optimizes elevator usage by prioritizing passengers with shorter travel distances, thereby reducing overall travel time. This is achieved because passengers with longer trips are less likely to encounter as many intermediate stops, as the smaller trips between floors have already been completed.

2. Completes Entire Processes: SPN is an algorithm that completes entire processes without interruption by other processes. Therefore, there is less time required for elevator acceleration or deceleration.

### Why choose RR?
Round Robin is used for assigning passengers to available elevators in a cyclic manner. It offers several advantages in our elevator OS:

1. Fair Allocation: Each elevator receives an equal share of passenger assignments, promoting fairness and equitable service across all elevators.

2. Fault Tolerance: RR can handle unexpected failures or disruptions more effectively due to its cyclic assignment approach, ensuring continued operation even in challenging situations. If a person cannot get on an elevator, they are re-assigned. 

### Potential Flaws
While there are benefits to our scheduling algorithm, there are areas where further optimization and enhancements could be explored:

1. Wait Time: Passengers with longer processes will be penalized with extended wait times before their process start.

2. Capacity: In our current program version, we are not accounting for elevator capacity. While this is not a problem in the tests conducted for this assignment, it may become a concern in practical scenarios with heavier passenger loads.

### Conclusion 
In conclusion, our goal was to either surpass or match the performance time of Professor Rees's algorithm, and we have successfully achieved that with our program.

## Git Commit Template

### Your Name Here: Title of what you just did

#### Brief Summary:
Write a more in-depth summary of what you just added and why.

#### Time Spent:
time in hours (#.# Hours)

#### Additional Notes (optional):
Sometimes write what you learned, issue you had, or a concern that might come up. If someone helps you, you should write them in the additional notes.