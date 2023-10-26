```
(R1)
config terminal
interface s0/0
ip address 100.1.1.2 255.255.255.0
no shutdown
exit
interface s0/1
ip address 20.1.1.1 255.255.255.0
no shutdown
exit
router rip
version 2
network 20.1.1.0
network 100.1.1.0
end
```
```
(R2)
config terminal
interface f0/0
ip address 172.16.2.1 255.255.0.0
no shutdown
exit
interface s0/0
ip address 100.1.1.1 255.255.255.0
no shutdown
exit
router rip
version 2
network 172.16.0.0
network 100.1.1.0
end
```
```
(R3)
config terminal
interface s0/1
ip address 20.1.1.2 255.255.255.0
no shutdown
exit
interface f0/0
ip address 10.2.2.1 255.255.255.0
no shutdown
exit
router rip
version 2
network 10.2.2.0
network 20.1.1.0
end
```
```
PC1> ip 172.16.2.10 255.255.0.0 172.16.2.1
PC2> ip 10.2.2.20 255.255.255.0 10.2.2.1
```
Testing:
```
show ip route
show ip rip database
debug ip rip
```