#!/bin/bash

packets=$(cat)
rules=$1
filtered_packets=""

for line in $rules
do
    line="$(sed -e 's# *##g' $line)"
    A1="$(cut -d',' -f1 <<<"$line")"
    echo $A1
    A2="$(cut -d',' -f2 <<<"$line")"
    A3="$(cut -d',' -f3 <<<"$line")"
    A4="$(cut -d',' -f4 <<<"$line")"
    current_packets="$(echo $packets | ./firewall.exe $A1)"
    echo $current_packets
    # current_packets="$(echo $packets | ./firewall.exe $A1 | ./firewall.exe $A2 | ./firewall.exe $A3 | ./firewall.exe $A4)" 
    # filtered_packets="$current_packets$filtered_packets"
done





