Computer Network Assignment 4 README
====

## Implementation

For this assignment, a basic simulation of GNUtella flooding protocol is implementation in C. The outline of the program could be described as follows:

* Main thread:

 * Read in arguments, save neighbors, then send connection request to all neighbors.
 * Spawn a thread to handle the server work.
 * Start sender work as follows:

    * Loop and read search input from terminal.
    * Generate a packet for query.
    * Flood to all neighbors.

* Server thread:

    * Loop and receive packet
    * Read in the packet, determine type of the packet.
    * If CONNECT type, add sender info to neighbors, and recognize it as a new neighbor.
    * If RESPON type, print out the search response.
    * If QUERY type:

        * Determine by ID of the query packet if it's a duplicate query (The host has seen the same query before). If so, ignore the packet.
        * Search the target directory for the file
        * If found, send the request back to the host initiating the query
        * If not found and the TTL>0, then flood the query to all the neighbors instead of the sender

## Design Details

### Packet Format

The packet format does not comply to the GNUtella standard packet format, to simplfiy this implementation.


```c
typedef struct packet {
  // ID to avoid handling same packet twice 
  int ID; 
  
  // Descriptor: what type of packet
  unsigned char Descript;

  // Time To Live 
  unsigned char TTL;
  
  // Query or responder hostname
  char hostname[MAX_STRLEN];
  
  // payload, the name of the search string 
  char payload_data[MAX_STRLEN];

} packet_t;

```

### Design Decisions

* This implementation chooses UDP packets for all communications.
* The following data structure are shared by two threads and protected by mutex when reading and writing:
  * neighbors structure to store all neighbor information.
  * IDlist struture for all previous query ID.
* Each host would first search its own directory. If not found, then send out query request.
* The neighbor records binary IP address of newly connected neighbor for simplicity
* The search would fail siliently if there are any search results from any reachable machine, and the host may receive multiple response if query is flooded to multiple machines. 


## Testing

The testing is all conducted on the csug cycle machines. 3 Directories are prepared for each program running on different machines.

<pre>
dir1/ - cycle1
 file11
 file12
 file13
dir2/ - cycle2
 file21
 file22
 file23
dir3/ - cycle3
 file31
 file32
 file33
</pre>

The testcase needs to prove the following functionalities, which would be carried out in the following testcases.

* Basic query flooding
* Loop avoidance
* TTL control

### Test1

The test is launched on 3 machines with following parameters:

```
xhu9@cycle1$ ./query_flood 10000 1 dir1
xhu9@cycle2$ ./query_flood 10000 2 dir2 cycle1
xhu9@cycle3$ ./query_flood 10000 2 dir3 cycle2
```

For search from cycle3:

```
file11
[DEBUG] Packet sent. size: 72
[INFO] SEARCH: 
[DEBUG] Package recved, size: 72
[DEBUG] Received new packet: RESPON package

[INFO] File file11 found on cycle1.csug.rochester.edu, with IP: 128.151.69.85
```

The cycle2 would propagate packet to cycle1 since TTL here is still alive.
cycle1 log:

```
[DEBUG] Received new packet: QUERY package
[DEBUG] Packet sent. size: 72
[INFO] File file11 found, responding to query.
```

However, for search from cycle1:

```
file31
[DEBUG] Packet sent. size: 72
```

The cycle2 would not forward packet to cycle3 since the origin TTL is 1, and would die on cycle2.

Therefore this testcase proves the basic query flooding and TTL control.


### Test2

The test is launched on 3 machines with following parameters:

```
xhu9@cycle1$ ./query_flood 10000 2 dir1
xhu9@cycle2$ ./query_flood 10000 2 dir2 cycle1
xhu9@cycle3$ ./query_flood 10000 2 dir3 cycle1 cycle2
```

Therefore all 3 machines are connected as neighbors. And when cycle1 now issues a query request, it would flood to both cycle2, cycle3. For example cycle1 searches for 'file31', the cycle2 does not find it, and would again forward to cycle3:

```
[DEBUG] Received new packet: QUERY package
[DEBUG] Packet sent. size: 72
[INFO] Not found, flooding to next neighbor IP: 128.151.69.87
```

But cycle3 now already handled this query from cycle1, and would not repond to the same query again. Therefore it would simply ignore:

```
[DEBUG] Received new packet: QUERY package
[DEBUG] Packet sent. size: 72
[INFO] File file31 found, responding to query.
[DEBUG] Package recved, size: 72
[DEBUG] Received new packet: QUERY package
[INFO] Packet with duplicate ID flooding back. Ignoring
```

Hence the ability to avoid loops is proved.
