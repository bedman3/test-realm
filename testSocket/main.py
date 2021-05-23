import socket
import ctypes
import struct

HOST = '127.0.0.1'  # The server's hostname or IP address
PORT = 7000        # The port used by the server
MAX_MESSAGE_STRING_SIZE = 1000

class messageHeader(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ("length_", ctypes.c_size_t),
        ("messageType_", ctypes.c_uint32)
    ]

class chatMessage(ctypes.Structure):
    _pack_ = 1
    _fields_ = [
        ("header_", messageHeader),
        ("message_", ctypes.c_char * MAX_MESSAGE_STRING_SIZE)
    ]

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    buf = (ctypes.c_char * 1024)()
    fmt = "<NL1000s"

    messageStr = "Testing sending message to a server"

    anotherMessageStr = "Haha just testing"

    # header = messageHeader(length_=len(anotherMessageStr), messageType_=1000)
    # chatMsg = chatMessage(header_=header, message_=anotherMessageStr)
    chatMsg = chatMessage()
    chatMsg.header_.length_ = len(anotherMessageStr)
    chatMsg.header_.messageType_ = 1000
    chatMsg.message_ = anotherMessageStr.encode('utf8')

    print(f'checking message {chatMsg.header_.length_} {chatMsg.header_.messageType_} {chatMsg.message_}')
    sendBytes = bytes((ctypes.c_char * ctypes.sizeof(chatMsg)).from_buffer_copy(chatMsg))
    print(f'sending {sendBytes}')

    s.connect((HOST, PORT))
    print(f"connected to host {HOST} and port {PORT}")
    s.send(sendBytes)






