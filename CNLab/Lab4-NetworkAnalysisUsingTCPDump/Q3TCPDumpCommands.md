## 3a: tcpdump udp port 520
Ans: This will track all udp protocol packets where either the source or destination port is 520
which is reserved for Route Info Protocol (RIP)

## 3b: tcpdump -x -s 120 ip proto 89
Ans: This will show packet contents in hex and ascii format. The size of the capture will 
be at most 120 bytes. Only packets with ip protocol 89 (Open Shortest Path First (OSPF))

## 3c: tcpdump -x -s 70 host ip addr1 and (ip addr2 or ip addr3)
Ans: This will show packet contents in hex and ascii format. The size of the capture will
be at most 70 bytes. Only communication between addr1 and addr2 or addr1 and addr3 will be shown.

## 3d: tcpdump -x -s 70 host ip addr1 and not ip addr2
Ans: This will show packet contents in hex and ascii format. The size of the capture will
be at most 70 bytes. Only communication to and from addr1 excluding communication to addr2
will be shown.