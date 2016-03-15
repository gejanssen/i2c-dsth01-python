# De i2c humidity sensor DSTH01

Hoe de DSTH01 humdity sensor te gebruiken in de raspberry pi met Python.

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
	40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
	50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
	60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
	70: -- -- -- -- -- -- -- --                         
	gej@rpib3:~/i2c-dsth01-python $ 

Ah, adres 40.

### Wat is de luchtvochtigheid?

	gej@rpib3:~/i2c-dsth01-python $ sudo python DSTH0.py 
