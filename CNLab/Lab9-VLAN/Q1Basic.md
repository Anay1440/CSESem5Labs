```
(R1)
config t
interface f0/0
no shutdown
ip address 192.168.10.1 255.255.255.240
exit
interface f0/0.2
encapsulation dot1q 2
ip address 192.168.1.65 255.255.255.192
exit
interface f0/0.10
encapsulation dot1q 10
ip address 192.168.1.129 255.255.255.224
end
```
```
PC1> ip 192.168.1.66 255.255.255.192 192.168.1.65
PC2> ip 192.168.1.67 255.255.255.192 192.168.1.65
PC3> ip 192.168.1.130 255.255.255.224 192.168.1.129
```
Testing
```
PC1> ping 192.168.1.67
PC1> ping 192.168.1.130
```