ENTRY QUEUE MANAGER SYSTEM :

PROJECT ID: P3

TEAM MEMBERS :
1. Jiya Patel - 202301034
2. Hiya Modi - 202301011
3. Yashasvi Jadav - 202301069
4. Kavya Parmar - 202301085

TEAM ID: SeeksForGeeks

ALGORITHM :

1. Initialize constants:
    a. Constant M as the capacity of the stadium<br /> 
    b. Constant N as the number of entry gates<br /> 
    c. Constant p as the minutes it takes for a single attendee to enter key<br /> 

2. Create a class Counter :
    a. A member variable 'Done' to keep the record of the total number of processed entries.
    b. A member variable 'count_VIP' to keep the record of the number of VIP entries processed.
    c. Define a Constructor Counter():
        - Initialize the Done variable to 0.
    d. Define a public member function 'increase()':
        - Increment done variable by 1. This function is called whenever a VIP or non-VIP entry is processed.
    e. Define a public member function 'increase_VIP()' :
        - Increment count_VIP by 1. This function is called when a VIP entry is processed.
    f. Define a public member function 'isEmpty()' :
        - Verify if all non-VIP entries have been processed by comparing Done the total number of entries (M) minus the number of VIP entries (count_VIP).
        - Return 1 if Done is equal to M minus count_VIP, showing that there are no more non-VIP entries to process.
        - Otherwise, Return 0. 

3. Create a class Stopwatch:
    a. A private member variable 'start' is the time when the stopwatch starts.
    b. A public constructor that initializes the 'start' with the current time high_resolution_clock time.
    c. A public function 'ElapsedMinutes' calculates the elapsed time in minutes since the start time and returns it.

4. Define a function 'HashFunction':
    a. Takes input of Serial_No.
    b. Return 1 if 'Serial_No' is divisible by M/8 not having remainder, which states that the spectator is VIP. 

5. Define function 'CreateSerialNo' :
    a. Takes input of an array 'SerialStat' of pairs, where the pair has a short integer and integer.
    b. For each index i, initialize the first element of the pair at index i in SerialStat to 0.
    c. End the for loop.

6. Define function 'AssignRandomGate' :
    a. Takes input of an array 'SerialStat' of pairs, where the pair has a short integer and integer, and an array Queue of deques that is the gate queue, a reference to an instance of the Counter class named counter.
    b. Seed the random number generator with the current time for random numbers in each run.
    c. Start the loop that iterates M/2 times, where M is the size of the array SerialStat.
    d. Generate random gate number in the range 0 to N-1, where N is the number of gates.
    e. Declare an integer variable 'serial'.
    f. Start do-while loop for assignning unique serial number:
        - Generate random gate number in the range 0 to M-1.
        - Continue the loop if SerialStat is not 0.
        - Exit the loop if unique serial number is found.
    g. Push the serial number 'serial' to the front of the deque at index gate in Queue.
    h. Set the first element of the pair at index serial in SerialStat to 1 as the serial number is now assigned.
    i. End of the loop.

7. Define function 'Distribute' :
    a. Takes the input of an array Queue of deques, where each deque represents a queue at a gate. 
    b. Calculate the limit as the integer value of M by N, where M and N are the total number of people and number of gates respectively.
    c. Set extra to 0, to keep the record of the total number of people requiring redistribution.
    d. Declare the long variables data and shift.
    e. Declare the vector<int> 'reshuff' to store the people that needs to be distributed.
    f. Start the for loop iterating from 0 to N-1:
        - If the size of the deque at index i in Queue is greater than the limit.
        - If applicable, determine shift as the difference between the size of deque and limit.
        - Increment extra by shift.
        - While shift is greater than 0:
            - Push the front element of the deque at index i into reshuff.
            - Pop the front element from the deque at index i.
            - Decrement shift by 1.
    g. Start the for loop iterating from 0 to N-1:
        - If the size of the deque at index i in Queue is less than limit.
        - If applicable, determine shift as the difference between the limit and the size of deque.
        - If extra is greater than data:
            - Decrement extra by data.
            - While data is greater than 0:
                - Push the back element of reshuff to the front of the deque at index i.
                - Pop the back element from reshuff.
                - Decrement data by 1.
            - Else, While extra is greater than 0:
                - Push the back element of reshuff to the front of the deque at index i.
                - Pop the back element from reshuff.
                - Decrement extra by 1.
                - Break the loop.
        - If extra is less than or equal to 0, break the loop.

8. Define function 'Suggestion' :
Takes input of an array Queue of deques, where each deque represents a queue at a gate.
Set a long variable min to the size of the first deque in Queue.
 Start the for loop that iterates from index 0 to N-1, where N is the number of gates.
        - For each i, check if size of the deque at index i in Queue is less than min.
        - If it is, update min with the new smaller size of the deque.
        - After finding minimum queue size, display a message indicating the shortest waiting time, which is the product of min, and a constant p representing the average processing time per person in minutes.
        - Print a message indicating which queue numbers have minimum waiting time.
     d. Start the for loop that iterates from index 0 to N-1, where N is the number of gates.
        - For each i, check if the size of the deque at index i in Queue is equal to min.
        - If it is, print the queue number i + 1.
        - After listing all queues with the least waiting time, provide a message informing the user that they can select from queue number 1 to N.
        - Flush the output to ensure immediate printing of all messages.

9. Define function 'Delete' :
 Takes input of an array Queue of deques, where each deque represents a queue at a gate, an integer Gate representing the gate number, and an integer Serial_No representing the serial number to be deleted.
 Start the for loop which iterates over the deque at index Gate in the Queue array. Use variable i for iteration from 0 to the size of the deque at Gate minus 1.
        - For each i, check if the element at the ith position in the deque at Gate is equal to Serial_No.
        - If yes, obtain an iterator 'it' to the ith position in the deque by adding 'i' to the initial iterator of the deque.
        - Erase the element at iterator 'it' from the deque at Gate.

10. Define function 'AutoDequeue' :
 Takes input of an array Queue of deques representing queues at each gate, an array SerialStat of pairs where each pair holds the status and additional information for each serial number, and a pointer counter to an integer.
 Start the loop that will iterate as long as people are remaining in any of the queues.
        - Put the current thread to sleep for p minutes. Here p is a predefined constant showing the processing time per person.
        - After waking up from sleep, start for loop from 0 to N-1.
            - Check if deque at index i in Queue contains any element.
            - If there are, update the first element of the pair in SerialStat that corresponds to the serial number at the back of the deque at Queue[i] to 2, showing that the person has been processed or is no longer in the queue.
            - Call pop_back() to remove the last element from the deque at Queue[i].
Continue iterating the process until CountPeopleLeft returns 0, showing that no more people are waiting in the queues.

11. Define Main Function :
    a. Declare a global array SerialStat of pairs, where each pair contains a short int and an int. 
    b. Declare a global deque Queue.
    c. Declare a variable sr_num for serial number input by the user.
    d. Declare a variable queue_num.
    e. Declare a Counter object counter.
    f. Call CreateSerialNo function to initialize the SerialStat array with serial numbers.
    g. Call AssignRandomGate function to assign serial numbers to different queues.
    h. Call Distribute function to distribute the serial numbers across the queues.
    i. Start the Stopwatch object stat.
    j. Create and start a detached thread t that runs the AutoDequeue function, passing the queues, serial status array, and counter by reference.    
    k. Start the infinite while loop.
        - Start another infinite loop.
            - Print a welcome message.
            - Display a prompt to user to enter their 7-digit serial number.
            - Read the serial number. If the user input is successful, subtract 1000000 from the serial number to normalize it and use it as an index.
            - Verify if the normalized serial number falls within a range greater than or equal to 0 and less than M.
            - If the serial number is valid and its status in `SerialStat` indicates it is not already processed, then check if it qualifies as a VIP using the `HashFunction`.
            - If the serial number is valid and its status is 0, evaluate if it qualifies VIP status using 'HashFunction'.
            - If the serial number qualifies as VIP, set its status to 2 and display a welcome message for VIPs.
            - If the serial number is not VIP, set its status to 1, display available entry gates using `Suggestion(Queue)`, and prompt for a preferred gate number.
            - Read the preferred gate number and validate it to ensure it is between 1 and `N`.
            - If the gate number is valid, update the serial number's associated queue number in `SerialStat` and add the serial number to the front of the selected queue in `Queue`.
            - Display a message with recommended entry gates based on the current wait time by calling the Suggestion(Queue) function.
            - Display a prompt for the user to input their preferred entry gate number, and proceed to read the input.
            - Validate the entered gate number to ensure it is in the range 1 and N. If the number is invalid, prompt the user to enter a valid gate number until a valid one is provided.
            - Modify the queue number associated with the serial number in SerialStat to the chosen gate number, considering the zero-based indexing.
            - Append the serial number to the front of the selected queue in Queue.
            - Print a confirmation message showing that their queue has been updated to the new gate number.
            - If the serial number indicates that you've already entered the stadium, inform the user that re-entry is not allowed.
            - After processing the user's serial number, exit the inner loop.
            - If the serial number is invalid, print an error message and proceed with the inner loop to prompt for a new input.
            - If the user input is not a number, clear the input stream and print an error message.
            - After exiting the inner loop, check if the counter is empty to determine if there are no more users to process.
        - If the counter is not empty, proceed with the outer loop.
        - Once the counter is empty, exit the outer loop.
        - Print the total processing time using stat.ElapsedMinutes().
        - Return 0 to indicate successful completion of the program.



WHY DID WE CHOOSE THE SPECIFIC DATA STRUCTURE?

An array of deque, in which each deque represents the queue at each gate, is used in this code to efficiently manage people waiting to enter the stadium. 
Unlike arrays, deque allows dynamic allocation of memory which is very useful in this scenario as the people in the queue keep changing which requires more insertion and deletion operations. 
It also allows insertion and deletion at both ends of the queue in constant time complexity O(1). 
The random access of the deque allows us to efficiently implement the switching queue functionality of the program.
Space complexity is O(n) where n is the total number of people in the waiting lines.








