.PHONY: default
default: modules

obj-m = driver.o

.PHONY: modules
modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
