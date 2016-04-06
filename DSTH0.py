import smbus
import time
from time import sleep

# DSTH01 default address.
DSTH01_I2CADDR = 0x40

bus = smbus.SMBus(1)

# Main
if __name__ == '__main__':

            bus.write_byte_data(DSTH01_I2CADDR, 0x03, 0x11)
            time.sleep(0.1)
           
            while True:
                status = bus.read_i2c_block_data(DSTH01_I2CADDR, 0x00, 1)
                print status
                if status[0] == 0:
                    break
                time.sleep(0.1)
       
            status = bus.read_i2c_block_data(DSTH01_I2CADDR, 0x00, 4)
            temperature = (status[1] << 8) + status[2];
            temperature = temperature >> 2;
            temperature = temperature / 32.0;
            temperature -= 50;         
            print 'Temperature: ', temperature, 'C'
       
            bus.write_byte_data(DSTH01_I2CADDR, 0x03, 0x01)
            time.sleep(0.1)
           
            status = bus.read_i2c_block_data(DSTH01_I2CADDR, 0x00, 1)
            time.sleep(0.1)
            while status[0] != 0:
                status = bus.read_i2c_block_data(DSTH01_I2CADDR, 0x00, 1)
                print status
                time.sleep(0.1)
       
            status = bus.read_i2c_block_data(DSTH01_I2CADDR, 0x00, 4)
            humidity = (status[1] << 8) + status[2];
            humidity = humidity >> 4;
            humidity = humidity / 16.0;
            humidity -= 24;
            print 'Humidity: ', humidity, '%'
            time.sleep(1)
