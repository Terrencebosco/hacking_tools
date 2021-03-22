import socket

target_host = "127.0.0.1"
target_port = 4141

client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

client.bind((target_host, target_port)) ##########
# one client and one server. In order to test the operation of the client program,
# one must also run the server program (perhaps in another command window). It seems from your question
# that you want your client program to run without the benefit of a server program.
# Adding .bind() allows your program to behave simultaneously as both client and server

# https://stackoverflow.com/questions/37191612/issue-with-receiving-response-from-127-0-0-1-with-udp-client-in-python

data_to_send = "AAABBBCCC"

client.sendto(data_to_send.encode(), (target_host, target_port))

recicedBytes= client.recvfrom(4096)

# message, location.
print(recicedBytes[0].decode(),recicedBytes[1])

