import socket
import os

def server_program():
    # get the hostname
    host = socket.gethostname()
    port = 9999  # initiate port no above 1024
    server_socket = socket.socket()  # get instance
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    # look closely. The bind() function takes tuple as argument
    server_socket.bind((host, port))  # bind host address and port together

    try:

        # configure how many client the server can listen simultaneously
        server_socket.listen(1)
        conn, address = server_socket.accept()  # accept new connection

        print("Receive data from " + str(address))
        # receive data stream. it won't accept data packet greater than 1024 bytes
        data = conn.recv(4096)

        if not data:
            # if data is not received break
            return

        f = open("test/rec.bin", "wb")
        f.write(data)
        conn.send(b"got_it")
        conn.close()  # close the connection

    finally:
        server_socket.shutdown(socket.SHUT_RDWR)
        server_socket.close()

if __name__ == '__main__':
    input("Press enter to receive the program...")
    server_program()
    os.system("./ppt8e test/rec.bin")
    print("Process finished.")
    exit(0)
