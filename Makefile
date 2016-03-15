all: si7005_rpi

si7005_rpi:
	gcc si7005_rpi.c -o si7005_rpi

clean:
	rm si7005_rpi

