#!/bin/bash
sudo socat PTY,link=/dev/ttyS10 PTY,link=/dev/ttyS11 &
sleep 1
sudo stty -F /dev/ttyS10 -onlcr && stty -F /dev/ttyS11 -onlcr
chown stadnik /dev/ttyS10 && chown stadnik /dev/ttyS11