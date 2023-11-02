```
(R1)
config terminal
ip nat inside source static 192.168.0.10 10.0.0.1
interface f0/0
ip address 10.0.0.1 255.255.255.0
ip nat outside
no shutdown
exit
interface f0/1
ip address 192.168.0.1 255.255.255.0
ip nat inside
no shutdown
end
```
```
(R2)
config terminal
interface f0/0
ip address 10.0.0.2 255.255.255.0
no shutdown
end
```
```
PC1> ip 192.168.0.10 255.255.255.0 192.168.0.1
```
Testing
```
R1# show ip nat translations

PC1> ping 10.0.0.2 -c 5
```