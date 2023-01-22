#!/bin/bash

echo "Processes currently running (ps):"
ps
echo "------------"

echo "Displaying current directory (pwd): "
pwd
echo "------------"

echo "Displays the accumulated user and system times for processes run from the shell (times):"
times
echo "------------"

echo "Disk usage (df):"
df -h
echo "------------"

echo "Memory usage (free):"
free -m
