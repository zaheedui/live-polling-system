# Live Polling and Voting System (Socket Programming in C)

## 📌 Description

This project implements a real-time polling system using socket programming in C. A server hosts the poll and multiple clients can connect over a network to cast votes and view live results.

## ⚙️ Technologies Used

* C Programming
* Winsock2 (Windows Socket API)
* TCP Client-Server Architecture

## 🚀 Features

* Multiple clients can vote simultaneously
* Real-time vote counting
* Network communication using TCP sockets
* Data consistency using network byte order (htonl/ntohl)

## 🖥️ How to Run

### Step 1: Compile

```
gcc server.c -o server -lws2_32
gcc client.c -o client -lws2_32
```

### Step 2: Run Server

```
server
```

### Step 3: Run Client

```
client
```

⚠️ Make sure to replace the IP address in `client.c` with the server's IP.

## 📡 Example Network Setup

* Server IP: 10.x.x.x
* Clients connect using the server IP

## 📊 Output

Displays live vote count for all options.

## 📚 Concepts Used

* Socket Programming
* Client-Server Model
* TCP Communication
* Network Byte Order Handling

## 👨‍💻 Author

Syed Zaheed, Syed Junaid Ahmed , Yakshit Naidu

