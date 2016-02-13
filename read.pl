#!/usr/bin/perl

use Device::SerialPort;

my $port = Device::SerialPort->new("/dev/ttyUSB0");
$port->databits(8);
$port->baudrate(19200);
$port->parity("none");
$port->stopbits(1);

while(1) {
  my $byte=$port->read(1);
  print "$byte";
}!perl
