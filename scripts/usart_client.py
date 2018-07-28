#!/usr/bin/env python

import socket
import signal
import sys
import getopt


class UsartClient:
    port = 0
    address = ""

    def __init__(self, address, port):
        self.address = address
        self.port = port
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def run(self):
        server_address = (self.address, self.port)
        print("connecting to {} port {}".format(*server_address))
        self.socket.connect(server_address)

        try:
            while (1):
                data = self.socket.recv(16)
                print("received: {!r}".format(data))
        finally:
            self.socket.close()

    def stop(self):
        self.socket.close()


def main(argv):
    port = 0

    try:
        opts, args = getopt.getopt(argv, "p:", ["port="])
    except:
        getopt.GetoptError
        print("usart_client.py -p <port>")
        sys.exit(2)

    for opt, arg in opts:
        if opt in ("-h", "--help"):
            print("usart_config.py -p <port>")
            sys.exit()
        elif opt in ("-p", "--port"):
            port = int(arg)

    print("Configuration: port = {}".format(port))

    client = UsartClient("localhost", port)

    try:
        client.run()
    except KeyboardInterrupt:
        print("Interrupt received, stopping...")
    finally:
        client.stop()


if __name__ == "__main__":
    main(sys.argv[1:])
