#!/bin/sh
TTY=/dev/ttyACM0
# keep tty open
cat <$TTY >/dev/null &
PID=$!
cat $* >$TTY
sleep 1
kill $PID
