```
(R1)
config t
ip dhcp pool pool1
network 9.0.0.0 255.255.255.0
default-router 9.0.0.1
exit
ip dhcp pool pool2
network 19.0.0.0 255.255.255.0
default-router 19.0.0.1
exit
interface f0/0
no shutdown
ip address 10.0.0.1 255.255.255.0
exit
interface f0/1
no shutdown
ip address 20.0.0.1 255.255.255.0
exit
ip route 9.0.0.0 255.255.255.0 10.0.0.2
ip route 19.0.0.0 255.255.255.0 20.0.0.2
end
```
```
(R2)
config t
interface f0/0
no shutdown
ip address 10.0.0.2 255.255.255.0
exit
interface f0/1
no shutdown
ip address 9.0.0.1 255.255.255.0
ip helper-address 10.0.0.1
end
```
```
(R3)
config t
interface f0/1
no shutdown
ip address 20.0.0.2 255.255.255.0
exit
interface f0/0
no shutdown
ip address 19.0.0.1 255.255.255.0
ip helper-address 20.0.0.1
end
```
Testing
```
PC1> dhcp
PC3> dhcp
```