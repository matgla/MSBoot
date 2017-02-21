# file:features/steps/step_tutorial01.py
# ----------------------------------------------------------------------------
# STEPS:
# ----------------------------------------------------------------------------
from behave import given, when, then
from framework.run_target import run_target
import serial
from framework.message_loop import MessageLoop
import time
#fo = open("target2.log", "w")


@given('we have behave installed')
def step_impl(context):
    serial_connection = serial.Serial("/dev/ttyS11")
    msgLoop = MessageLoop(serial_connection)
    msgLoop.run()
    # fo.write(serialConnection.read(10))
    target, timer = run_target(5)
    time.sleep(2)

    target.terminate()
    timer.cancel()
    pass


@when('we implement a test')
def step_impl(context):
    assert True is not False


@then('behave will test it for us!')
def step_impl(context):
    assert context.failed is False
