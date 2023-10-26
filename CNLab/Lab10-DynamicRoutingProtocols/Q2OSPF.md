```
(R1)
config terminal
interface s0/0
ip address 192.168.1.1 255.255.255.0
no shutdown
exit
interface f0/0
ip address 10.0.0.1 255.0.0.0
no shutdown
exit
router ospf 200
network 10.0.0.0 0.255.255.255 area 0
network 192.168.1.0 0.0.0.255 area 0
end
```
```
(R2)
config terminal
interface s0/0
ip address 192.168.1.2 255.255.255.0
no shutdown
exit
interface f0/0
ip address 20.0.0.1 255.0.0.0
no shutdown
exit
interface f0/1
ip address 150.150.150.1 255.255.255.0
no shutdown
router ospf 200
network 20.0.0.0 0.255.255.255 area 0
network 192.168.1.0 0.0.0.255 area 0
network 150.150.150.0 0.0.0.255 area 1
end
```
```
(R3)
config terminal
interface f0/0
ip address 150.150.150.2 255.255.255.0
no shutdown
router ospf 200
network 150.150.150.0 0.0.0.255 area 1
end
```
```
PC1> ip 10.0.0.2 255.0.0.0 10.0.0.1
PC2> ip 10.0.0.3 255.0.0.0 10.0.0.1
PC3> ip 20.0.0.2 255.0.0.0 20.0.0.1
PC4> ip 20.0.0.3 255.0.0.0 20.0.0.1
```
Testing:
```
show ip route
show ip ospf neighbor
show ip ospf database
```