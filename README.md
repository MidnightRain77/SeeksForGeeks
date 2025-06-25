<h2>ENTRY QUEUE MANAGER SYSTEM</h2> 
<h4>PROJECT ID: P3</h4> 

<h4>TEAM MEMBERS : </h4>
1. Jiya Patel - 202301034<br /> 
2. Hiya Modi - 202301011<br /> 
3. Yashasvi Jadav - 202301069<br /> 
4. Kavya Parmar - 202301085<br /> 

<h4>TEAM ID: SeeksForGeeks </h4>

<h4>TIME COMPLEXITY: O(M)</h4>
<h4>SPACE COMPLEXITY: O(M)</h4>

<h4>ALGORITHM :</h4>

<h5>1. Initialize constants:<br />
    a. Constant M as the capacity of the stadium<br />
    b. Constant N as the number of entry gates<br />
    c. Constant p as the minutes it takes for a single attendee to enter any gate<br />

2. Create a class Stopwatch:<br />
    a. A private member variable 'start' is the time when the stopwatch starts.<br />
    b. A public constructor that initializes the 'start' with the current time high_resolution_clock time.<br />
    c. A public function 'ElapsedMinutes' calculates the elapsed time in minutes since the start time and returns it.<br />

3. Define a function 'HashFunction':<br />
    a. Takes input of Serial_No.<br />
    b. Return 1 if 'Serial_No' is divisible by M/8 not having remainder, which states that the spectator is VIP. <br />

4. Define function 'CreateSerialNo' :<br />
    a. Takes input of an array 'SerialStat' of pairs, where the pair has a short integer and integer.<br />
    b. For each index i, initialize the first element of the pair at index i in SerialStat to 0.<br />
    c. End the for loop.<br />

5. Define function 'AssignRandomGate' :<br />
    a. Takes input of an array 'SerialStat' of pairs, where the pair has a short integer and integer, and an array Queue of deques that is the gate queue.<br />
    b. Seed the random number generator with the current time for random numbers in each run.<br />
    c. Start the loop that iterates M/2 times, where M is the size of the array SerialStat.<br />
    d. Generate random gate number in the range 0 to N-1, where N is the number of gates.<br />
    e. Declare an integer variable 'serial'.<br />
    f. Start do-while loop for assignning unique serial number:<br />
        - Generate random gate number in the range 0 to M-1.<br />
        - Continue the loop if SerialStat is not 0.<br />
        - Exit the loop if unique serial number is found.<br />
    g. Push the serial number 'serial' to the front of the deque at index gate in Queue.<br />
    h. Set the first element of the pair at index serial in SerialStat to 1 as the serial number is now assigned.<br />
    i. End of the loop.<br />

6. Define function 'Distribute' :<br />
    a. Takes the input of an array Queue of deques, where each deque represents a queue at a gate. <br />
    b. Calculate the limit as the integer value of M by N, where M and N are the total number of people and number of gates respectively.<br />
    c. Set extra to 0, to keep the record of the total number of people requiring redistribution.<br />
    d. Declare the long variables data and shift.<br />
    e. Declare the vector<int> 'reshuff' to store the people that needs to be distributed.<br />
    f. Start the for loop iterating from 0 to N-1:<br />
        - If the size of the deque at index i in Queue is greater than the limit.<br />
        - If applicable, determine shift as the difference between the size of deque and limit.<br />
        - Increment extra by shift.<br />
        - While shift is greater than 0:<br />
            - Push the front element of the deque at index i into reshuff.<br />
            - Pop the front element from the deque at index i.<br />
            - Decrement shift by 1.<br />
    g. Start the for loop iterating from 0 to N-1:<br />
        - If the size of the deque at index i in Queue is less than limit.<br />
        - If applicable, determine shift as the difference between the limit and the size of deque.<br />
        - If extra is greater than data:<br />
            - Decrement extra by data.<br />
            - While data is greater than 0:<br />
                - Push the back element of reshuff to the front of the deque at index i.<br />
                - Pop the back element from reshuff.<br />
                - Decrement data by 1.<br />
            - Else, While extra is greater than 0:<br />
                - Push the back element of reshuff to the front of the deque at index i.<br />
                - Pop the back element from reshuff.<br />
                - Decrement extra by 1.<br />
                - Break the loop.<br />
        - If extra is less than or equal to 0, break the loop.<br />

7. Define function 'CountPeopleLeft' :<br />
    a. Takes input of an array Queue of deques, where each deque represents a queue at a gate.<br />
    b. Start with a long integer variable left and set it to 0. This will hold the count of people left.<br />
    c. Loop through the array of deques from index 0 to N-1:<br />
        - For each deque at index i add the size of the deque to left.<br />
    d. After the loop, left contains the total number of people left across all deques.<br />
    e. Return the value of left as the result of the function.<br />


8. Define function 'Suggestion' :<br />
    a. Takes input of an array Queue of deques, where each deque represents a queue at a gate.<br />
    b. Set a long variable min to the size of the first deque in Queue.<br />
    c. Start the for loop that iterates from index 0 to N-1, where N is the number of gates.<br />
        - For each i, check if size of the deque at index i in Queue is less than min.<br />
        - If it is, update min with the new smaller size of the deque.<br />
        - After finding minimum queue size, display a message indicating the shortest waiting time, which is the product of min, and a constant p representing the average processing time per person in minutes.<br />
        - Print a message indicating which queue numbers have minimum waiting time.<br />
    d. Start the for loop that iterates from index 0 to N-1, where N is the number of gates.<br />
        - For each i, check if the size of the deque at index i in Queue is equal to min.<br />
        - If it is, print the queue number i + 1.<br />
        - After listing all queues with the least waiting time, provide a message informing the user that they can select from queue number 1 to N.<br />
        - Flush the output to ensure immediate printing of all messages.<br />

9. Define function 'Delete' :<br />
    a.Takes input of an array Queue of deques, where each deque represents a queue at a gate, an integer Gate representing the gate number, and an integer Serial_No representing the serial number to be deleted.<br />
    b. Start the for loop which iterates over the deque at index Gate in the Queue array. Use variable i for iteration from 0 to the size of the deque at Gate minus 1.<br />
        - For each i, check if the element at the ith position in the deque at Gate is equal to Serial_No.<br />
        - If yes, obtain an iterator 'it' to the ith position in the deque by adding 'i' to the initial iterator of the deque.<br />
        - Erase the element at iterator 'it' from the deque at Gate.<br />

10. Define function 'AutoDequeue' :<br />
    a. Takes input of an array Queue of deques representing queues at each gate, an array SerialStat of pairs where each pair holds the status and additional information for each serial number, and a pointer counter to an integer.<br />
    b. Start the loop that will iterate as long as people are remaining in any of the queues.<br />
        - Put the current thread to sleep for p minutes. Here p is a predefined constant showing the processing time per person.<br />
        - After waking up from sleep, start for loop from 0 to N-1.<br />
            - Check if deque at index i in Queue contains any element.<br />
            - If there are, update the first element of the pair in SerialStat that corresponds to the serial number at the back of the deque at Queue[i] to 2, showing that the person has been processed or is no longer in the queue.<br />
            - Call pop_back() to remove the last element from the deque at Queue[i].<br />
    c. Continue iterating the process until CountPeopleLeft returns 0, showing that no more people are waiting in the queues.<br />

11. Define Main Function :<br />
    a. Declare a global array SerialStat of pairs, where each pair contains a short int and an int. <br />
    b. Declare a global deque Queue.<br />
    c. Declare a variable sr_num for serial number input by the user.<br />
    d. Declare a variable queue_num.<br />
    e. Set the counter to 0.<br />
    f. Call CreateSerialNo function to initialize the SerialStat array with serial numbers.<br />
    g. Call AssignRandomGate function to assign serial numbers to different queues.<br />
    h. Call Distribute function to distribute the serial numbers across the queues.<br />
    i. Start the Stopwatch object stat.<br />
    j. Create and start a detached thread t that runs the AutoDequeue function, passing the queues, serial status array, and address of counter.   <br />
    k. Start the infinite while loop.<br />
        - Increment count by 1.<br />
        - Start another infinite loop.<br />
            - Print a welcome message.<br />
            - Display a prompt to user to enter their 7-digit serial number.<br />
            - Read the serial number. If the user input is successful, subtract 1000000 from the serial number to normalize it and use it as an index.<br />
            - Verify if the normalized serial number falls within a range greater than or equal to 0 and less than M.<br />
            - If the serial number is valid and its status in SerialStat indicates it is not already processed, then check if it qualifies as a VIP using the HashFunction.<br />
            - If the serial number is valid and its status is 0, evaluate if it qualifies VIP status using HashFunction.<br />
            - If the serial number qualifies as VIP, set its status to 2 and display a welcome message for VIPs.<br />
            - If the serial number is not VIP, set its status to 1, display available entry gates using Suggestion(Queue), and prompt for a preferred gate number.<br />
            - Read the preferred gate number and validate it to ensure it is between 1 and N.<br />
            - If the gate number is valid, update the serial number's associated queue number in SerialStat and add the serial number to the front of the selected queue in Queue.<br />
            - Display a message with recommended entry gates based on the current wait time by calling the Suggestion(Queue) function.<br />
            - Display a prompt for the user to input their preferred entry gate number, and proceed to read the input.<br />
            - Validate the entered gate number to ensure it is in the range 1 and N. If the number is invalid, prompt the user to enter a valid gate number until a valid one is provided.<br />
            - Modify the queue number associated with the serial number in SerialStat to the chosen gate number, considering the zero-based indexing.<br />
            - Append the serial number to the front of the selected queue in Queue.<br />
            - Print a confirmation message showing that their queue has been updated to the new gate number.<br />
            - If the serial number indicates that you've already entered the stadium, inform the user that re-entry is not allowed.<br />
            - After processing the user's serial number, exit the inner loop.<br />
            - If the serial number is invalid, print an error message and proceed with the inner loop to prompt for a new input.<br />
            - If the user input is not a number, clear the input stream and print an error message.<br />
            - Enter a loop that continues as long as counter is less than half of M (rounded up) or there are still people left in the queues:<br />
                - Print "Next, please!" to the console and flush the output.<br />
                - Increment 'counter' by 1.<br />
                - Break out of the loop.<br />
            - Check if the loop should continue as long as counter is less than half of M (rounded up) or if there are still people left in the queues:<br />
                - If the condition is true, use continue to proceed to the next iteration of the loop.<br />
                - If the condition is false, use break to exit the loop.<br />
        - Once the loop is exited, print "All attendees have been processed." along with the total processing time obtained from stat.ElapsedMinutes() to the console and flush the output.<br />
    l. Return 0 to indicate successful completion of the program.<br /><br />





<h4>WHY DID WE CHOOSE THE SPECIFIC DATA STRUCTURE?<br /> </h4>


<h5>An array of deque, in which each deque represents the queue at each gate, is used in this code to efficiently manage people waiting to enter the stadium. <br />
Unlike arrays, deque allows dynamic allocation of memory which is very useful in this scenario as the people in the queue keep changing which requires more insertion and deletion operations. <br />
It also allows insertion and deletion at both ends of the queue in constant time complexity O(1). <br />
The random access of the deque allows us to efficiently implement the switching queue functionality of the program.<br />
Space complexity is O(n) where n is the total number of people in the waiting lines.<br />
An array of pair of size M stores two components: first stores a short integer type data which indicates the status of an individual either <br />
0 - has not entered any queue, <br />
1 - is already in a queue or <br />
2 - has already entered the stadium. <br />
The second of the pair is an integer type data which stores the queue number in which an individual is waiting as of now (if the first of the said individual is 1). This data structure is essentially added to decrease the time complexity to O(M) instead of O(MN), as there is direct access of the elements in the array of pair. <br />
<br /> 



