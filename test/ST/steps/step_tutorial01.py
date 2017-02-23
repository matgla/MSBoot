# file:features/steps/step_tutorial01.py
# ----------------------------------------------------------------------------
# STEPS:
# ----------------------------------------------------------------------------
from behave import given, when, then
import time
from framework.test_utils import TestFramework


@given('we have behave installed')
def step_impl(context):
    tf = TestFramework()
    tf.init_framework()

    connection = tf.get_connection()

    time.sleep(4)
    msg = bytearray()
    msg.append(6)
    msg.append(8)
    msg.append(0x0b)
    msg.append('T')
    msg.append('S')
    msg.append('T')
    msg.append(0)

    connection.write(msg)

    time.sleep(1)

    tf.teardown()
    pass


@when('we implement a test')
def step_impl(context):
    assert True is not False


@then('behave will test it for us!')
def step_impl(context):
    assert context.failed is False
