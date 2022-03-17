obj-m += simple.o
obj-m += hello.o
obj-m += asmt1.o
obj-m += asmt2.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
