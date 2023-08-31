## Configuring IP

```
PC1> ip 10.0.1.100 255.255.255.0 10.0.1.254
PC2> ip 10.0.1.101 255.255.255.240 10.0.1.102
PC3> ip 10.0.1.120 255.255.255.0 10.0.1.254
PC4> ip 10.0.1.121 255.255.255.240 10.0.1.122
```

## Ping commands

- PC1 to PC3 <br/> `PC1> ping 10.0.1.120 -c 3` <br/> 
Observation: Pings are successful 

- PC1 to PC2 <br/> `PC1> ping 10.0.1.101 -c 3` <br/> 
Observation: Pings are successful

- PC1 to PC4 <br/> `PC1> ping 10.0.1.121 -c 3` <br/>
Observation: Pings result in timeout. We can see through wireshark that the ping request is sent successfully from PC1.
A reply to the request is seen, but actually this reply should not occur. We can see ARP requests by PC4 to try to find
the default gateway (instead of trying to find PC1).
This is because 10.0.1.100/24 (PC1) is not considered to be on the same subnet by 10.0.1.121/28 (PC4). 
(For PC4, the valid IP range on its subnet is 10.0.1.112 to 10.0.1.127 (last 4 bits)).
Hence, PC4 tries to look for the default gateway (10.0.1.122), but since it has not been configured, it cannot find it, and results in ping timeout.

- PC4 to PC1 <br/> `PC4> ping 10.0.1.100 -c 3` <br/>
Observation: Error: host (10.0.1.122) not reachable
We can see ARP requests by PC4 to try to find the default gateway (instead of trying to find PC1).
This is because 10.0.1.100/24 (PC1) is not considered to be on the same subnet by 10.0.1.121/28 (PC4). 
(For PC4, the valid IP range on its subnet is 10.0.1.112 to 10.0.1.127 (last 4 bits)).
Hence, PC4 tries to look for the default gateway (10.0.1.122), but since it has not been configured, it cannot find it.

- PC2 to PC4 <br/> `PC2> ping 10.0.1.121 -c 3` <br/>
Observation: Pings are successful

- PC2 to PC3 <br/> `PC2> ping 10.0.1.120 -c 3` <br/>
Observation: host (10.0.1.102) not reachable
We can see ARP requests by PC2 to try to find the default gateway (instead of trying to find PC3).
This is because 10.0.1.120/24 (PC3) is not considered to be on the same subnet by 10.0.1.101/28 (PC2). 
(For PC2, the valid IP range on its subnet is 10.0.1.96 to 10.0.1.111 (last 4 bits)).
Hence, PC2 tries to look for the default gateway (10.0.1.102), but since it has not been configured, it cannot find it.