# tcp client can be used for services, send garbage data, fuzz...

import socket

tarket_host = "www.google.com"
target_port = 80

# create socket object
## af_inet is saying we're going to use the standard ipv4 or hostname
## af_stream sates that this will be a simple tcp client.
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# connect the client
client.connect((tarket_host, target_port))

# data
data = "GET / HTTP/1.1\nHost: google.com\r\n\r\n"

# send some data
client.send(data.encode())

# receive some data
response = client.recv(4096)

# print(response)

if __name__ == "__main__":
    print(response)

'''
some assumptions are being made here.
1) our connection will always succeed.
2) the server is always expecting us to send data first.
3) the server will alwasy send us back data in a timely fashion.
'''