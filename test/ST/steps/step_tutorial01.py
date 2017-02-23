# file:features/steps/step_tutorial01.py
# ----------------------------------------------------------------------------
# STEPS:
# ----------------------------------------------------------------------------
from behave import given, when, then
from framework.run_target import run_target
import serial
from framework.message_loop import MessageLoop
import time
import shutil
import logging
from framework.file_log import setup_logger
import os
import errno
#fo = open("target2.log", "w")


@given('we have behave installed')
def step_impl(context):
    if os.path.exists(os.path.dirname("../../artifacts/run.log")):
        shutil.rmtree("../../artifacts")
    if not os.path.exists(os.path.dirname("../../artifacts/run.log")):
        try:
            os.makedirs(os.path.dirname("../../artifacts/run.log"))
        except OSError as err:
            if err.errno != errno.EEXIST:
                raise
    setup_logger("TEST", True, logging.DEBUG, "../../artifacts/run.log")
    serial_connection = serial.Serial("/dev/ttyS11")
    msgLoop = MessageLoop(serial_connection)
    msgLoop.run()

    # fo.write(serialConnection.read(10))
    target, timer = run_target(5)
    time.sleep(4)
    msg = bytearray()
    msg.append(6)
    msg.append(8)
    msg.append(0x0b)
    msg.append('T')
    msg.append('S')
    msg.append('T')
    msg.append(0)
    serial_connection.write(msg)

    time.sleep(1)

    target.terminate()
    timer.cancel()
    pass


@when('we implement a test')
def step_impl(context):
    assert True is not False


@then('behave will test it for us!')
def step_impl(context):
    assert context.failed is False
