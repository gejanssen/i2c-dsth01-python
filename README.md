# De i2c humidity sensor DSTH01

Hoe de **DSTH01** humdity sensor te gebruiken in de raspberry pi met Python.

### Download

Even downloaden

	gej@rpib3:~ $ git clone https://github.com/gejanssen/i2c-dsth01-python.git
	Cloning into 'i2c-dsth01-python'...
	remote: Counting objects: 14, done.
	remote: Compressing objects: 100% (11/11), done.
	remote: Total 14 (delta 0), reused 14 (delta 0), pack-reused 0
	Unpacking objects: 100% (14/14), done.
	Checking connectivity... done.
	gej@rpib3:~ $ 

### Install i2c tools

Installatie I2c tools.

	gej@rpib3:~/i2c-dsth01-python $ sudo apt-get install i2c-tools
	Reading package lists... Done
	Building dependency tree       


### Welk i2c adres te gebruiken

Op welk I2C adres zit de DSTH01?

	gej@rpib3:~/i2c-dsth01-python $ i2cdetect -y 1
	Error: Could not open file `/dev/i2c-1': Permission denied
	Run as root?
	gej@rpib3:~/i2c-dsth01-python $ sudo i2cdetect -y 1
	     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
	00:          -- -- -- -- -- -- -- -- -- -- -- -- -- 
	10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
	20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
	30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
	40: 40 -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
	50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
	60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
	70: -- -- -- -- -- -- -- --                         
	gej@rpib3:~/i2c-dsth01-python $ 

Ah, adres 40.

### Wat is de luchtvochtigheid?

	gej@rpi-a:~/i2c-dsth01-python $ sudo python DSTH0.py
	Temperature:  23.4375 C
	Humidity:  34.8125 %
	gej@rpi-a:~/i2c-dsth01-python $

## Compile the C code

	gej@rpi-a:~/i2c-dsth01-python $ gcc si7005_rpi.c -o si7005_rpi
	gej@rpi-a:~/i2c-dsth01-python $ ls -l
	total 32
	drwxr-xr-x 2 gej gej 4096 Mar 15 11:20 Datasheet
	-rw-r--r-- 1 gej gej 1522 Mar 15 11:20 DSTH0.py
	-rw-r--r-- 1 gej gej 1614 Mar 15 11:22 README.md
	-rwxr-xr-x 1 gej gej 8256 Mar 15 11:23 si7005_rpi
	-rw-r--r-- 1 gej gej 3672 Mar 15 11:20 si7005_rpi.c
	drwxr-xr-x 2 gej gej 4096 Mar 15 11:20 Sources
	gej@rpi-a:~/i2c-dsth01-python $

En de code uitvoeren

	gej@rpi-a:~/i2c-dsth01-python $ ./si7005_rpi
	can't open i2c : /dev/i2c-1
	gej@rpi-a:~/i2c-dsth01-python $

Oh oh, root rechten nodig....

	gej@rpi-a:~/i2c-dsth01-python $ sudo ./si7005_rpi
	Start read temp
	Temperature Result : 23.47 C
	Start read humi
	Humidity Result : 30.46 RH
	gej@rpi-a:~/i2c-dsth01-python $


## Aansluitschema

Hoe de i2c bus aan te sluiten:


[![badge](https://raw.githubusercontent.com/gejanssen/i2c-dsth01-python/master/Raspberry-Pi-GPIO-Layout-Re-300x149.gif)](https://raw.githubusercontent.com/gejanssen/i2c-dsth01-python/master/Raspberry-Pi-GPIO-Layout-Re-300x149.gif)
