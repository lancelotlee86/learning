import socket

target_host = "127.0.0.1"
target_port = 9998

# 建立一个 socket 对象
client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# UDP 是一个无连接状态，所以不需要在发送数据前调用 connect()

# 发送一些数据
client.sendto(b"AAABBBCCC", (target_host, target_port))

# 接收一些数据
data, addr = client.recvfrom(4096)

print(data)
