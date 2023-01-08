# TCPchat

* TCP/IP chat based on Windows sockets.
* Multi-user chat using two threads in client part and N threads in server part where N - number of clients.

## Requirments

* IDE: Microsoft Visual Studio 2015 or newer
* Windows SDK 10.0.15063.0 or newer

## Instruction to run

* Run two cmd.exe instances
* Run Server.exe in the first one
* Run Client.exe 'server ip address' 'your nickname' in the second

## Example

```powershell
# Server
E:\Server.exe

# Client
E:\Client.exe 192.168.1.1 User
```
