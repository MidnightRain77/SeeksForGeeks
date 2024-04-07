<h2>ENTRY QUEUE MANAGER SYSTEM</h2> 
<h4>PROJECT ID: P3</h4> 

<h4>TEAM MEMBERS : </h4>
1. Jiya Patel - 202301034<br /> 
2. Hiya Modi - 202301011<br /> 
3. Yashasvi Jadav - 202301069<br /> 
4. Kavya Parmar - 202301085<br /> 

<h4>TEAM ID: SeeksForGeeks </h4><br />

<h4>ALGORITHM :</h4><br /> 

1. Initialize constants:<br /> <br /> 
    a. Constant M as the capacity of the stadium<br /> 
    b. Constant N as the number of entry gates<br /> 
    c. Constant p as the minutes it takes for a single attendee to enter any gate<br /> 

2. Create a class Counter :<br /> <br /> 
    a. A member variable 'Done' to keep the record of the total number of processed entries.<br /> 
    b. A member variable 'count_VIP' to keep the record of the number of VIP entries processed.<br /> 
    c. Define a Constructor Counter():<br /> 
        - Initialize the Done variable to 0.<br /> 
    d. Define a public member function 'increase()':<br /> 
        - Increment done variable by 1. This function is called whenever a VIP or non-VIP entry is processed.<br /> 
    e. Define a public member function 'increase_VIP()':<br /> 
        - Increment count_VIP by 1. This function is called when a VIP entry is processed.<br /> 
    f. Define a public member function 'isEmpty()' :<br /> 
        - Verify if all non-VIP entries have been processed by comparing Done the total number of entries (M) minus the number of VIP entries (count_VIP).<br /> 
        - Return 1 if Done is equal to M minus count_VIP, showing that there are no more non-VIP entries to process.<br /> 
        - Otherwise, Return 0. <br /> 

3. Create a class Stopwatch:<br /> <br /> 
    a. A private member variable 'start' is the time when the stopwatch starts.<br /> 
    b. A public constructor that initializes the 'start' with the current time high_resolution_clock time.<br /> 
    c. A public function 'ElapsedMinutes' calculates the elapsed time in minutes since the start time and returns it.<br /> 

4. Define a function 'HashFunction':<br /> <br /> 
    a. Takes input of Serial_No.<br /> 
    b. Return 1 if 'Serial_No' is divisible by M/8 not having remainder, which states that the spectator is VIP.<br /> 

5. Define function 'CreateSerialNo' :<br /> <br /> 
    a. Takes input of an array 'SerialStat' of pairs, where the pair has a short integer and integer.<br /> 
    b. For each index i, initialize the first element of the pair at index i in SerialStat to 0.<br /> 
    c. End the for loop.<br /> 

6. Define function 'AssignRandomGate' :<br /> <br /> 
    a. Takes input of an array 'SerialStat' of pairs, where the pair has a short integer and integer, and an array Queue of deques that is the gate queue, a reference to an instance of the Counter class named counter.<br /> 
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

7. Define function 'Distribute' :<br /> <br /> 
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

8. Define function 'Suggestion' :<br /> <br /> 
Takes input of an array Queue of deques, where each deque represents a queue at a gate.<br /> 
Set a long variable min to the size of the first deque in Queue.<br /> 
 Start the for loop that iterates from index 0 to N-1, where N is the number of gates.<br /> 
        - For each i, check if size of the deque at index i in Queue is less than min.<br /> 
        - If it is, update min with the new smaller size of the deque.<br /> 
        - After finding minimum queue size, display a message indicating the shortest waiting time, which is the product of min, and a constant p representing the average processing time per person in minutes.<br /> 
        - Print a message indicating which queue numbers have minimum waiting time.<br /> 
     d. Start the for loop that iterates from index 0 to N-1, where N is the number of gates.<br /> 
        - For each i, check if the size of the deque at index i in Queue is equal to min.<br /> 
        - If it is, print the queue number i + 1.<br /> 
        - After listing all queues with the least waiting time, provide a message informing the user that they can select from queue number 1 to N.<br /> 
        - Flush the output to ensure immediate printing of all messages.<br /> 

9. Define function 'Delete' :<br /> <br /> 
 Takes input of an array Queue of deques, where each deque represents a queue at a gate, an integer Gate representing the gate number, and an integer Serial_No representing the serial number to be deleted.<br /> 
 Start the for loop which iterates over the deque at index Gate in the Queue array. Use variable i for iteration from 0 to the size of the deque at Gate minus 1.<br /> 
        - For each i, check if the element at the ith position in the deque at Gate is equal to Serial_No.<br /> 
        - If yes, obtain an iterator 'it' to the ith position in the deque by adding 'i' to the initial iterator of the deque.<br /> 
        - Erase the element at iterator 'it' from the deque at Gate.<br /> 

10. Define function 'AutoDequeue' :<br /> <br /> 
 Takes input of an array Queue of deques representing queues at each gate, an array SerialStat of pairs where each pair holds the status and additional information for each serial number, and a pointer counter to an integer.<br /> 
 Start the loop that will iterate as long as people are remaining in any of the queues.<br /> 
        - Put the current thread to sleep for p minutes. Here p is a predefined constant showing the processing time per person.<br /> 
        - After waking up from sleep, start for loop from 0 to N-1.<br /> 
            - Check if deque at index i in Queue contains any element.<br /> 
            - If there are, update the first element of the pair in SerialStat that corresponds to the serial number at the back of the deque at Queue[i] to 2, showing that the person has been processed or is no                 longer in the queue.<br /> 
            - Call pop_back() to remove the last element from the deque at Queue[i].<br /> 
                Continue iterating the process until CountPeopleLeft returns 0, showing that no more people are waiting in the queues.<br /> 

11. Define Main Function :<br /> <br /> 
    a. Declare a global array SerialStat of pairs, where each pair contains a short int and an int. <br /> 
    b. Declare a global deque Queue.<br /> 
    c. Declare a variable sr_num for serial number input by the user.<br /> 
    d. Declare a variable queue_num.<br /> 
    e. Declare a Counter object counter.<br /> 
    f. Call CreateSerialNo function to initialize the SerialStat array with serial numbers.<br /> 
    g. Call AssignRandomGate function to assign serial numbers to different queues.<br /> 
    h. Call Distribute function to distribute the serial numbers across the queues.<br /> 
    i. Start the Stopwatch object stat.<br /> 
    j. Create and start a detached thread t that runs the AutoDequeue function, passing the queues, serial status array, and counter by reference.    <br /> 
    k. Start the infinite while loop.<br /> 
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
            - After exiting the inner loop, check if the counter is empty to determine if there are no more users to process.<br /> 
        - If the counter is not empty, proceed with the outer loop.<br /> 
        - Once the counter is empty, exit the outer loop.<br /> 
        - Print the total processing time using stat.ElapsedMinutes().<br /> 
        - Return 0 to indicate successful completion of the program.<br /> <br /> 




<h4>WHY DID WE CHOOSE THE SPECIFIC DATA STRUCTURE?<br /> <br /> </h4>


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
<h4>CONTRIBUTION TABLE: <br /><br /> </h4>


| FUNCTIONS          | Jiya Patel | Hiya Modi | Yashasvi Jadav | Kavya Parmar |
| ---------          | ---------- | --------- | ---------      | --------     |
| Main Function      | 20%        | 65%       | 10%            | 5%           |
| CountPeopleLeft    | 100%       | 0%        | 0%             | 0%           |
| Class Stopwatch    | 65%        | 5%        | 10%            | 20%          |
| HashFunction       | 0%         | 0%        | 100%           | 0%           |
| CreateSerialNo     | 0%         | 0%        | 0%             | 100%         |
| AssignRandomGate   | 20%        | 10%       | 65%            | 5%           |
| Distribute         | 20%        | 65%       | 10%            | 5%           |
| Suggestion         | 10%        | 65%       | 20%            | 5%           |
| Delete             | 20%        | 10%       | 65%            | 5%           |
| AutoDequeue        | 65%        | 20%       | 10%            | 5%           |




