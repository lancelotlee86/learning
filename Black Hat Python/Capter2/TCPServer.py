import socket
import threading

bind_ip = "0.0.0.0"
bind_port = 9998

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server.bind((bind_ip, bind_port))

# 参数为最大连接数
server.listen(5)

print("[*] Listening on %s:%d" % (bind_ip, bind_port))

# 这是客户端处理线程
def handle_client(client_socket):

    # 打印出客户端发送得到内容
    request = client_socket.recv(1024)

    print("[*] Received: %s" % request)

    #返还一个数据包
    client_socket.send(b"ACK!")
    #client_socket.close()


while True:

    # socket.accept() 方法返回元组 (conn, address)，conn 是一个新的可发送接收数据的 socket 对象，address是连接另一端的地址及端口
    client, addr = server.accept()

    print("[*] Accepted connection from: %s:%d" % (addr[0], addr[1]))

    # handle_client(client)

    # handle_client 为回调函数（新的线程对象）
    client_handler = threading.Thread(target = handle_client, args = (client,))
    client_handler.start()
