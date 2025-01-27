#!/bin/bash

packets=$(cat)
rules=$1
filtered_packets=""

# Read the rules line by line
while IFS= read -r line; do
    # Remove spaces and comments, and ignore empty lines
    line=${line// /}       # Remove spaces (Bash parameter expansion)
    line=${line%%#*}       # Remove comments
    [[ -z "$line" ]] && continue

    # Extract fields from the line using Bash built-ins
    IFS=',' read -r A1 A2 A3 A4 <<< "$line"

    # Process the packets through the firewall
    current_packets=$(echo "$packets" | ./firewall.exe "$A1" | ./firewall.exe "$A2" | ./firewall.exe "$A3" | ./firewall.exe "$A4")

    # Append the result to filtered_packets with src-ip replaced
    filtered_packets+=$'\n'"${current_packets//src-ip/$'\n'src-ip}"
done < "$rules"

# Remove duplicates, sort, and clean up
printf "%s\n" "$filtered_packets" | awk 'NF' | sort -u | tr -d ' '
