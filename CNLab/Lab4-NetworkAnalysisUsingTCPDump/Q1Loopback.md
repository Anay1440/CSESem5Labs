## How to run

Terminal 1:
$ sudo tcpdump -i lo host localhost

Terminal 2:
$ ping localhost

## Observation:

ICMP echo requests and replys are seen in the dump. 

-- Note --

If interface is set to ethernet ( $ sudo tcpdump -i enp2s0 host localhost ), and then ping, then no 
ICMP messages are seen. This is because you are creating a loopback, but listening on the hardware
level. If the interface is set to ethernet, then you will only see those packets which cross the physical
ethernet interface. The loopback interface (lo) is a logical interface, and you can only see loopback
messages when using this interface.
