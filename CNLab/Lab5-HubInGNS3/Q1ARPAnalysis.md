## Configuring IP

```
PC1> ip 10.0.1.11 255.255.255.0 10.0.1.254
PC2> ip 10.0.1.12 255.255.255.0 10.0.1.254
PC3> ip 10.0.1.13 255.255.255.0 10.0.1.254
PC4> ip 10.0.1.14 255.255.255.0 10.0.1.254
```

## Analysing ARP

- Destination MAC address: ff:ff:ff:ff:ff:ff
- Source MAC address: 00:50:79:66:68:00
- Type field in packet headers: ARP (0x0806)

Another type field seen in the packets is IPv4 (0x0800).<br/>
This type field is seen for the ICMP packets.