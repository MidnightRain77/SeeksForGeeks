<h2>ENTRY QUEUE MANAGEMENT SYSTEM</h2> 
<h4>PROJECT ID: P3</h4> 

<h4>TEAM MEMBERS : </h4>
1. Jiya Patel - 202301034<br /> 
2. Hiya Modi - 202301011<br /> 
3. Yashasvi Jadav - 202301069<br /> 
4. Kavya Parmar - 202301085<br /> 

<h4>TEAM ID: SeeksForGeeks </h4>

### 🧠 Efficiency & Data Structure Rationale

This system is designed for high efficiency and responsiveness in managing large crowds across multiple entry gates. To achieve this, we carefully selected data structures that balance performance, flexibility, and real-time adaptability.

---

#### ✅ Key Data Structures Used

- **Array of Deques (deque<int> Queue[N])**  
  Each entry gate is represented by a separate deque.

  **Why deque?**
  - Supports O(1) insertion and deletion at both ends — ideal for fast reshuffling and dequeuing.
  - Provides random access, enabling spectators to switch gates efficiently.
  - Dynamically adjusts to queue size without reallocations, unlike arrays or vectors.

- **Array of Pairs (pair<short int, int> SerialStat[M])**  
  Stores status and gate assignment for each of the M spectators.

  - first (short int): status of the spectator  
    - 0 – not yet in a queue  
    - 1 – currently in a queue  
    - 2 – already entered the stadium  
  - second (int): current assigned gate number

  **Why this structure?**
  - Allows O(1) access and updates for each person using their serial number as an index.
  - Reduces lookup time from O(MN) to O(M) by avoiding scanning queues.

- **Counter Class**  
  Tracks how many people have been processed and how many are VIPs. Helps determine loop termination and progress logic.

- **Stopwatch Class**  
  Uses high_resolution_clock to track total simulation time, mimicking real-world gate operation timings.

---

#### ⏱️ Time & Space Complexity

- **Time Complexity:**
  - Initialization, assignment, and gate switching: O(M)
  - VIP check (via hash function): O(1)
  - Queue balancing and reshuffling: O(M) in worst case
  - Auto-dequeue (background thread): O(M) over time

- **Space Complexity:**
  - O(M + N)  
    - M spectators stored in SerialStat  
    - N dynamic deques for the entry gates

---

#### 🎯 Why This Design Is Efficient

- Scales linearly with the number of spectators and gates
- Uses multi-threading to enable real-time processing (via AutoDequeue)
- Offers real-time suggestions for the least busy gates
- Minimizes memory overhead while maintaining fast responsiveness
- Provides VIP handling and queue switching with minimal cost

This design ensures smooth entry for all attendees and balances speed, scalability, and real-world simulation accuracy, making it ideal for applications like stadium crowd management systems.

---

### ⚙️ Algorithm Overview

#### 1. Initialize Constants
- M: Capacity of the stadium  
- N: Number of entry gates  
- p: Minutes it takes for one attendee to enter through any gate

#### 2. Stopwatch Class
- Private member: start time of type high_resolution_clock
- Constructor: Initializes start with current time
- ElapsedMinutes(): Returns the elapsed time in minutes

#### 3. HashFunction
- Takes Serial_No as input
- Returns 1 if Serial_No % (M/8) == 0, marking it as a VIP

#### 4. CreateSerialNo
- Takes array SerialStat of pairs (short, int)
- Sets each SerialStat[i].first to 0
- Ends loop after initialization

#### 5. AssignRandomGate
- Inputs: SerialStat array and Queue array of deques
- Randomly assigns M/2 spectators to gates
- Ensures no VIPs and no duplicates
- Updates SerialStat status and gate assignment

#### 6. Distribute
- Balances queue sizes across gates
- Calculates limit = M / N
- Moves excess spectators into reshuff vector
- Redistributes from reshuff to underfilled queues

#### 7. CountPeopleLeft
- Iterates over Queue array
- Returns total number of people left in all queues

#### 8. Suggestion
- Finds the queue(s) with minimum size
- Calculates and displays minimum waiting time
- Suggests all gate numbers with minimal queues

#### 9. Delete
- Removes a specific Serial_No from a given Gate queue
- Uses an iterator to erase element from the deque

#### 10. AutoDequeue
- Runs in a loop until all spectators are processed
- Sleeps for p minutes between dequeuing cycles
- Pops one spectator from the back of each non-empty deque
- Marks them as entered (SerialStat[i].first = 2)

#### 11. Main Function Logic
- Declares SerialStat, Queue, sr_num, queue_num, and a Counter instance
- Initializes serial numbers and gate assignments
- Starts the stopwatch and the AutoDequeue thread
- Begins infinite user interaction loop:
  - Prompts for 7-digit serial number
  - Validates and normalizes input
  - If valid:
    - If not yet in queue:
      - Check VIP status
      - If VIP: mark as entered
      - Else: suggest gate, accept preference, assign to chosen queue
    - If already in a queue: allow re-selection of gate
    - If already entered: show denial message
  - If invalid: prompt again
- Continues until all non-VIP spectators have entered
- Outputs total time taken using the stopwatch
- Ends program with return value 0
