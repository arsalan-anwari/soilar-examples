# Endnode Tranceiver

In this test we use a single rfm95w as a tranceiver. It has two states, RX_MODE and TX_MODE. The tranceiver first starts in RX mode where i received data from a gateway (see test `gateway-tranceiver`). After receiving data 10 times, it goes into TX mode where it send data for ever to a gateway. 

This is to test if the switch from TX and RX is fluid. 
