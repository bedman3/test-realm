import socket
import ctypes
import sys

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


if __name__ == "__main__":
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        buf = (ctypes.c_char * 1024)()
        exitFlag = False
        s.connect((HOST, PORT))
        print(f"connected to host {HOST} and port {PORT}")

        try:
            while not exitFlag:
                inputStr = input("Input a string to send to server, (type exit to quit shell): ")

                if len(inputStr) > MAX_MESSAGE_STRING_SIZE:
                    print(f"Input string greater than maximum size of {MAX_MESSAGE_STRING_SIZE}, please retry", file=sys.stderr)
                    continue

                if inputStr == "exit":
                    exitFlag = True
                    continue

                chatMsg = chatMessage()
                chatMsg.header_.length_ = ctypes.sizeof(chatMsg) - ctypes.sizeof(messageHeader)
                chatMsg.header_.messageType_ = 1000
                chatMsg.message_ = inputStr.encode('utf8')

                print(f'checking message {chatMsg.header_.length_} {chatMsg.header_.messageType_} {chatMsg.message_}')
                sendBytes = bytes((ctypes.c_char * ctypes.sizeof(chatMsg)).from_buffer_copy(chatMsg))
                # print(f'sending {sendBytes}')

                s.sendall(sendBytes)
        except KeyboardInterrupt:
            pass
        finally:
            s.close()
