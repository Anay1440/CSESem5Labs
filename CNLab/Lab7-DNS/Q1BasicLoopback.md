```
(R1)
configure terminal
hostname R1
interface f0/0
ip address 10.10.10.1 255.255.255.0
no shutdown
do wr
end
```
```
(R2)
configure terminal
hostname R2
interface f0/0
ip address 10.10.10.2 255.255.255.0
no shutdown
do wr
end
```
Setting up R2 as DNS Server
```
(R2)
configure terminal
ip dns server
ip host loopback.R2.com 2.2.2.2
end
```
Creating loopback interface
```
(R2)
configure terminal
interface loopback 1
ip address 2.2.2.2 255.255.255.255
end
```
Setting up R1 to resolve hostnames using R2:
```
(R1)
configure terminal
ip domain lookup
ip name-server 10.10.10.2
end
```
Setting R2 as default gateway for R1. This tells R1 that if it needs to reach a network not in its routing table, then it should hop to R2. 
```
(R1)
configure terminal
ip route 0.0.0.0 0.0.0.0 10.10.10.2
end
```
Testing
```
(R1)
ping loopback.R2.com repeat 3
```