#!/bin/sh
TTY=/dev/ttyACM0
stty -F $TTY 115200
# keep tty open
cat <$TTY >/dev/null &
PID=$!
cat $* >$TTY
sleep 1
kill $PID
