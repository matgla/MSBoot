import threading
import time
import os


class MessageLoop:

    def __init__(self, serial_connection):
        self.serial = serial_connection
        self.log_file_name = "../../artifacts/target.log"

        if not os.path.exists(os.path.dirname(self.log_file_name)):
            try:
                os.makedirs(os.path.dirname(self.log_file_name))
            except OSError as err:
                # if err.errno != errno.EEXIST: TODO: fix it
                #    raise
                print "jakis error"

    def log(self, bytearray):
        with open(self.log_file_name, "a") as file:
            file.write(bytearray)

    def run(self):
        try:
            self.runner_thread = threading.Thread(
                target=self.loop)
            self.runner_thread.setDaemon(True)
            self.runner_thread.start()
        except Exception as err:
            print "Can't start thread for message handling" + str(err)

    def loop(self):
        while True:
            size = 0
            while size == 0:
                while self.serial.in_waiting != 0:
                    size = 0
                size = self.serial.read(1)
                log = "size to recv: " + str(size) + "!\n"
                self.log(log)
            received_bytes = 0
            payload = bytearray()
            while received_bytes < size:
                if self.serial.in_waiting != 0:
                    payload.append(self.serial.read(1))
                    received_bytes = received_bytes + 1
            # if payload[0] == 1:
            self.log(bytearray)
            size = 0
