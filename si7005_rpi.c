/*
 * si7005_rpi.c
 * Example code for interface between Raspberry PI and I2C-HUTMP (SI-7005)
 * 
 * contact : connect@deaware.com
 *
 */ 
 
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>

#include <linux/i2c-dev.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>

// --------------- Configuration file for Linux system ------------- //
#define I2C_DEVICE_NAME     "/dev/i2c-1"
#define I2C_HUTMP_ERROR     -1
#define I2C_HUTMP_SUCCESS   0

// --------------- Private data type ------------------------------- //
struct i2c_hutmp_t {
    int i2c_number;         // store i2c device number
    uint16_t temperature;   // collect and return temperature to user
    uint16_t humidity;      // collect and return humidity to user
};
typedef struct i2c_hutmp_t i2c_hutmp_t;

// --------------- Application Implement -------------------------- //
void i2c_hutmp_open(i2c_hutmp_t* p_ht) {
    p_ht->i2c_number = open(I2C_DEVICE_NAME, O_RDWR);
    if(p_ht->i2c_number < 0) {
        printf("can't open i2c : %s\n", I2C_DEVICE_NAME);
        exit(1);
    }
}

void i2c_hutmp_close(i2c_hutmp_t* p_ht) {
    close(p_ht->i2c_number);
}

void i2c_hutmp_set_addr(i2c_hutmp_t* p_ht, int i2c_address) {
    if (ioctl(p_ht->i2c_number, I2C_SLAVE, i2c_address) < 0) {
        perror("i2c set address false\n");
        exit(1);
    }
}

void i2c_hump_temp_start(i2c_hutmp_t* p_ht) {
    uint8_t data[3];
    data[0] = 0x03; 
    data[1] = 0x11;
    write(p_ht->i2c_number, data, 2);
}

int32_t i2c_hump_temp_read(i2c_hutmp_t* p_ht) {
    uint8_t data[5];
    uint16_t temp_result;
    data[0] = 0;

    write(p_ht->i2c_number, data, 1);
    if(read(p_ht->i2c_number, data, 3) != 3) {
        return I2C_HUTMP_ERROR;
    }
    
    temp_result = data[1] << 8;
    temp_result |=  data[2];
    temp_result = temp_result >> 2;

    p_ht->temperature = temp_result;
    return I2C_HUTMP_SUCCESS;
}

void i2c_hump_humi_start(i2c_hutmp_t* p_ht) {
    uint8_t data[3];
    data[0] = 0x03; 
    data[1] = 0x01;
    write(p_ht->i2c_number, data, 2);
}

int32_t i2c_hump_humi_read(i2c_hutmp_t* p_ht) {
    uint8_t data[5];
    uint16_t humi_result;
    data[0] = 0;

    write(p_ht->i2c_number, data, 1);
    if(read(p_ht->i2c_number, data, 3) != 3) {
        return I2C_HUTMP_ERROR;
    }
    
    humi_result = data[1] << 8;
    humi_result |=  data[2];
    humi_result = humi_result >> 4;

    p_ht->humidity = humi_result;
    return I2C_HUTMP_SUCCESS;
}


float i2c_hutmp_tmp_reg_to_celcius(i2c_hutmp_t* p_ht) {
    float temp_celcius;
    return temp_celcius = ((float)p_ht->temperature / 32) - 50;
}

float i2c_hutmp_humi_reg_to_rh(i2c_hutmp_t* p_ht) {
    float humi_rh;
    float humi_lin;
    // calculate 
    humi_rh = ((float)p_ht->humidity / 16) - 24;
    // linear
    humi_lin = humi_rh - ((humi_rh * humi_rh) * - 0.00393 + humi_rh * 0.4008 - 4.7844 );
    return humi_lin; 
}   


int main(void) {

    // Initial i2c-humtemp
    i2c_hutmp_t ht;
    i2c_hutmp_open(&ht);
    i2c_hutmp_set_addr(&ht, 0x40);

    // Example for read temperature 
    printf("Start read temp\n");
    i2c_hump_temp_start(&ht);
    sleep(1);
    i2c_hump_temp_read(&ht);
    printf("Temperature Result : %.2f C\n", i2c_hutmp_tmp_reg_to_celcius(&ht));

    // Example for read humidity
    printf("Start read humi\n");
    i2c_hump_humi_start(&ht);
    sleep(1);
    i2c_hump_humi_read(&ht);
    printf("Humidity Result : %.2f RH\n", i2c_hutmp_humi_reg_to_rh(&ht));

    return 0;
}



