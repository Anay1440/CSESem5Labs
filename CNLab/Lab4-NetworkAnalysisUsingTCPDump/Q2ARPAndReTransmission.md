# Part 1: ARP

## How to run

Terminal 1:
$ sudo tcpdump -i enp2s0 -w Q2ARP

Terminal 2:
$ telnet 172.16.59.242

## Observation:

Open Q2ARP in Wireshark, and type arp in the filter. Find out the broadcasts from your machine by checking
the mac address. You will notice 4 total ARP attempts, each at 1 second from the previous. 

-- Note --
The ARP is shown only because the destination IP address given is within the same LAN (172.16.59.xxx). 

# Part 2: Retransmission

## How to run

Terminal 1:
$ sudo tcpdump -i enp2s0 -w Q2Retransmission

Terminal 2:
$ telnet 128.238.66.200

## Observation: 

Since the destination IP is outside the LAN, it is observed that the request is communicated to the main lab router.
It is noticed that the TCP Retransmissions follow the following pattern: The delay between 2 retransmissions 
increases by a factor of 2 after every attempt. (T2 - T1 = 1, T3 - T2 = 2, T4 - T3 = 4)