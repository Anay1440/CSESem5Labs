```
(R1)
config t
ip dhcp pool lab8
network 192.168.3.0 255.255.255.0
default-router 192.168.3.1
exit
interface f0/0
no shutdown
ip address 192.168.3.1 255.255.255.0
exit
```
Testing
```
PC1> dhcp
PC2> dhcp
```