# Item 14: Think carefully about copying behaviour in resource-managing classes

The dir. contains UDP based Server, Client & a File Manager. File Manager is the resource managing class for
fstream based files. The copying behaviour is implemented in File Manager's copy constructor.

## Execution & Expected output

1. `Server.cpp` is main executing class. It waits for the Client to send data,
   once it receives the data it creates a new file & appends new data to it.
1. `Client.cpp` is next executing class. It reads a from a file & sends data to the server.
