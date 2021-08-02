from socket import *
import math
import os


BUFSIZE = 16384
# class back-end client
class Client:
    __instance = None

    #kiểm tra client
    @staticmethod
    def get_instance():
        if Client.__instance is None:
            Client()
        return Client.__instance
    #khởi tạo class Client
    def __init__(self):
        if Client.__instance is not None:
            raise Exception('Client is singleton class')
        else:
            Client.__instance = self
            self.__client = socket(AF_INET, SOCK_STREAM)
    # Hàm tạo kết nối đến server
    def connect(self, ip_address: str):
        try:
            self.__client.connect((ip_address, 3000))
        except ConnectionRefusedError:
            return False
        except OSError:
            return False
        return True

    # Hàm gửi dữ liệu cho server
    def send(self, data: str):
        try:
            self.__client.send(data.encode())
        except ConnectionResetError:
            return False
        return True

    # Hàm nhận dữ liệu từ server
    def recv(self):
        try:
            return self.__client.recv(BUFSIZE).decode()
        except ConnectionAbortedError:
            return 'Error ConnectionAbortedError'

    # Hàm lưu file từ server gửi
    def save_file(self, file_name: str, file_size: int, file_path: str):
        fo = open(os.path.join(file_path, file_name), 'wb')
        n = math.ceil(file_size / BUFSIZE)
        for i in range(n):
            fo.write(self.__client.recv(BUFSIZE))
        fo.close()

client = Client.get_instance()
