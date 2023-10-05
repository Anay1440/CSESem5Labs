```
(R1)
configure terminal
hostname R1
interface f0/0
ip address 10.10.10.1 255.255.255.0
no shutdown
do wr
interface f0/1
ip address 9.10.10.1 255.255.255.0
no shutdown
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
interface f0/1
ip address 30.10.10.1 255.255.255.0
no shutdown
end
```
```
(R3)
configure terminal
hostname R3
interface f0/0
ip address 20.10.10.1 255.255.255.0
no shutdown
do wr
interface f0/1
ip address 30.10.10.2 255.255.255.0
no shutdown
end
```
```
PC1> ip 9.10.10.3 255.255.255.0 9.10.10.1
PC1> ip dns 30.10.10.2
PC2> ip 20.10.10.2 255.255.255.0 20.10.10.1
```
Setting up R3 as DNS Server
```
(R3)
configure terminal
ip dns server
ip host www.mycsemit.com 20.10.10.2
end
```
Setting up R1 to resolve hostnames using R3:
```
(R1)
configure terminal
ip domain lookup
ip name-server 30.10.10.2
end
```
Setting R2 as default gateway for R1. This tells R1 that if it needs to reach a network not in its routing table, then it should hop to R2.
```
(R1)
configure terminal
ip route 0.0.0.0 0.0.0.0 10.10.10.2
end
```
Setting up R2 to resolve hostnames using R3:
```
(R2)
configure terminal
ip domain lookup
ip name-server 30.10.10.2
end
```
Setting R3 as default gateway for R2. This tells R2 that if it needs to reach a network not in its routing table, then it should hop to R3.
And setting R1 as gateway for net id: 10.10.10.0/24 and 9.10.10.0/24
```
(R2)
configure terminal
ip route 0.0.0.0 0.0.0.0 30.10.10.2
ip route 10.10.10.0 255.255.255.0 10.10.10.1
ip route 9.10.10.0 255.255.255.0 10.10.10.1
end
```
Setting R2 as default gateway for R3. This tells R3 that if it needs to reach a network not in its routing table, then it should hop to R2.
```
(R3)
configure terminal
ip route 0.0.0.0 0.0.0.0 30.10.10.1
end
```
Testing
```
PC1> ping www.mycsemit.com repeat 3
```