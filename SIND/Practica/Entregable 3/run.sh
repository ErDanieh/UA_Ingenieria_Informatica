#!/bin/bash
set -e

for file in "mqtt" "devices" "averages"; do
  [ -f /config/${file}.ini ] && cp -f /config/${file}.ini /usr/src/app/
done
exec "python3" "./data-read.py"
