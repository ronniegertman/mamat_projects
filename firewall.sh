
#!/bin/bash

packets=$(cat)
rules=$1
filtered_packets=""
# Read the rules line by line
while IFS= read -r line; do
    
    # Remove spaces from the line
    line="$(sed -e 's# *##g' <<<"$line")"
    line="$(sed -e 's/#.*//g' <<<"$line")"
    # Ignore empty lines
    [[ -z "$line" ]] && continue
    # Extract fields from the line
    A1="$(cut -d',' -f1 <<<"$line")"
    A2="$(cut -d',' -f2 <<<"$line")"
    A3="$(cut -d',' -f3 <<<"$line")"
    A4="$(cut -d',' -f4 <<<"$line")"
    # Process the packets through the firewall
    current_packets="$(echo "$packets" | ./firewall.exe "$A1" | ./firewall.exe "$A2" | ./firewall.exe "$A3" | ./firewall.exe "$A4")"
    #Append the result to filtered_packets
    tmp=$(echo "$current_packets" | sed $'s#src-ip#\\nsrc-ip#g')
    # echo $current_packets
    filtered_packets+="$tmp"
 
done < "$rules"
printf "%s\n" "$filtered_packets" | sort -n | uniq | sed 's# ##g' | sed '1{/^$/d}'

 
