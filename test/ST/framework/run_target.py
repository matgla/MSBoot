from subprocess import Popen, PIPE 
from functools import partial
from threading import Timer
from time import sleep
from signal import SIGINT
from os import kill
import os
import asbasqwa

fo = open("target.log", "w")

def kill_target(program):
    program.kill()

def run_target(timeout):
    with open("stdout.txt","wb") as out, open("stderr.txt","wb") as err:
        fo.write(os.environ["STM_QEMU_PATH"] + "/bin/qemu-system-gnuarmeclipse")
        pipes = Popen([os.environ["STM_QEMU_PATH"] + "/bin/qemu-system-gnuarmeclipse", "-nographic", "-board", "STM32F4-Discovery", "-verbose", "--verbose", "--verbose", "--semihosting-config", "enable=on,target=native", "-d", "unimp,guest_errors", "-image", "../../bin/stm32BootLoader.bin", "-serial", "/dev/ttyS10"], stdout=out, stderr=err, stdin=PIPE)
    t = Timer(timeout, partial(kill_target, pipes))
    t.start()  # after 30 seconds, "hello, world" will be printed
    return pipes, t


