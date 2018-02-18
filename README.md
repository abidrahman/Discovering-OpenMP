# ECE420Lab3

1. Implement a multithreaded server that can handle multiple simultaneous incoming
TCP connections from client threads. The server must communicate
with clients via stream sockets, as shown in the sample code.

2. Maintain an array of n strings, char** theArray, in the memory of the
server, where each string i (i = 0, 1, 2, . . . , n − 1) is filled with the initial
value “String i: the initial value”.

3. Implement a client program that can launch x simultaneous write/read requests
to the server. Each request is launched in a separate Pthread and
performs either a read or a write operation to a random string in theArray
on the server. For a read request, the server returns the requested string to
the user. For a write request, the requesting thread will update the corresponding
string in theArray on the server to the following: “String pos has
been modified by a write request”, where pos is the id of the string that is
updated. Each request is a write operation with a probability of 5% and is
a read operation with a probability of 95%.

4. For a read request, the server will send the requested string back to the
requesting client thread. Upon receiving the string, the client thread will
display it, close the connection and terminate. For a write request, the
server will send the updated string back to the client. Upon receiving the
string, the client thread will display it, close the connection and terminate.