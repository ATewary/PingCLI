# PingCLI
A simple implementation of Ping, written in C++.
May or may not be working, kind of maade it 'headless'-ly as I didn't have superuser acceess to the Linux server I was writing this in.


1. Run with sudo (as opening a RAW socket requires privilege)
2. Enter an IPv4 addr or a hostname (google.com)
3. Watch as this program send's ICMP Echo Requests and receives ICMP Echo Replies with simple statistics
4. Runs infinitely until CLI is closed/terminated. 
