
*NOT WORKING. The ip nat inside command is causing CPU HOG error.*

```
(R1)
config terminal
access-list 1 permit 192.168.0.0 0.0.0.15
ip nat pool NATPool 10.0.0.2 10.0.0.10 netmask 255.255.255.0
ip nat inside source list 1 pool NATPool
interface f0/1
ip address 192.168.0.1 255.255.255.0
ip nat inside
no shutdown
exit
interface f0/0
ip nat outside
no shutdown
end
```
```
(R2)
config terminal
interface f0/0
ip address 10.0.0.1 255.255.255.0
no shutdown
end
```
```
PC1> ip 192.168.0.2 255.255.255.0 192.168.0.1
PC2> ip 192.168.0.3 255.255.255.0 192.168.0.1
```
Testing
```
R1# show ip nat translations

PC1> ping 10.0.0.2 -c 5
```