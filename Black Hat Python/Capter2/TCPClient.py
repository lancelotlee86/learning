import socket

target_host = "www.baidu.com"
target_port = 80

# 建立一个 socket 对象
# AF_INET 说明我们将使用标准的 IPv4, SOCK_STREAM 说明这将是一个 TCP 客户端，其实这两个值都是 default 的
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# client = socket.socket() is also okay...

# 连接客户端
client.connect((target_host, target_port))

# 发送一些数据
# python3 中要发送 bytes 类型。 python2 中是 string 类型的
client.send(b"GET / HTTP/1.1\r\nHost: baidu.com\r\n\r\n")

# 接收一些数据
response = client.recv(4096)

print(response)
