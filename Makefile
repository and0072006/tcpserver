ROOT = .

ROOT=$(shell pwd)

tcpserver: libs
	$(MAKE) -C tcpserver

all: tcpserver

testrunner: libs
	$(MAKE) -C test/testrunner

libs: log tcpclient conf

log:
	$(MAKE) -C log
tcpclient:
	$(MAKE) -C tcpclient
conf:
	$(MAKE) -C conf


.PHONY: tcpserver log tcpclient conf
