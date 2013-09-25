#include "MPU9150.h"

void setup_mpu9150()
{
i2c_write_register(MPU_device,MPU9150_RA_PWR_MGMT_1,0x01);
i2c_write_register(MPU_device,MPU9150_RA_SMPLRT_DIV,0x07);
i2c_write_register(MPU_device,MPU9150_RA_CONFIG,0x00);
i2c_write_register(MPU_device,MPU9150_RA_GYRO_CONFIG,0x08);
i2c_write_register(MPU_device,MPU9150_RA_ACCEL_CONFIG,0x00);
i2c_write_register(MPU_device,MPU9150_RA_FF_THR,0x00);
i2c_write_register(MPU_device,MPU9150_RA_FF_DUR,0x00);
i2c_write_register(MPU_device,MPU9150_RA_MOT_THR,0x00);
i2c_write_register(MPU_device,MPU9150_RA_MOT_DUR,0x00);
i2c_write_register(MPU_device,MPU9150_RA_ZRMOT_THR,0x00);
i2c_write_register(MPU_device,MPU9150_RA_ZRMOT_DUR,0x00);
i2c_write_register(MPU_device,MPU9150_RA_FIFO_EN,0x00);
i2c_write_register(MPU_device,MPU9150_RA_I2C_MST_CTRL,0x00);
i2c_write_register(MPU_device,MPU9150_RA_I2C_SLV0_ADDR,0x00);
i2c_write_register(MPU_device,MPU9150_RA_I2C_SLV0_REG,0x00);
i2c_write_register(MPU_device,MPU9150_RA_I2C_SLV0_CTRL,0x00);
i2c_write_register(MPU_device,MPU9150_RA_I2C_SLV1_ADDR,0x00);
i2c_write_register(MPU_device,MPU9150_RA_I2C_SLV1_REG,0x00);
i2c_write_register(MPU_device,MPU9150_RA_I2C_SLV1_CTRL,0x00);
i2c_write_register(MPU_device,MPU9150_RA_I2C_SLV2_ADDR,0x00);
i2c_write_register(MPU_device,MPU9150_RA_I2C_SLV2_REG,0x00);
i2c_write_register(MPU_device,MPU9150_RA_I2C_SLV2_CTRL,0x00);
i2c_write_register(MPU_device,MPU9150_RA_I2C_SLV3_ADDR,0x00);
i2c_write_register(MPU_device,MPU9150_RA_I2C_SLV3_REG,0x00);
i2c_write_register(MPU_device,MPU9150_RA_I2C_SLV3_CTRL,0x00);
i2c_write_register(MPU_device,MPU9150_RA_I2C_SLV4_ADDR,0x00);
i2c_write_register(MPU_device,MPU9150_RA_I2C_SLV4_REG,0x00);
i2c_write_register(MPU_device,MPU9150_RA_I2C_SLV4_DO,0x00);
i2c_write_register(MPU_device,MPU9150_RA_I2C_SLV4_CTRL,0x00);
i2c_write_register(MPU_device,MPU9150_RA_I2C_SLV4_DI,0x00);
i2c_write_register(MPU_device,MPU9150_RA_INT_PIN_CFG,0x02);
i2c_write_register(MPU_device,MPU9150_RA_INT_ENABLE,0x00);
i2c_write_register(MPU_device,MPU9150_RA_I2C_SLV0_DO,0x00);
i2c_write_register(MPU_device,MPU9150_RA_I2C_SLV1_DO,0x00);
i2c_write_register(MPU_device,MPU9150_RA_I2C_SLV2_DO,0x00);
i2c_write_register(MPU_device,MPU9150_RA_I2C_SLV3_DO,0x00);
i2c_write_register(MPU_device,MPU9150_RA_I2C_MST_DELAY_CTRL,0x00);
i2c_write_register(MPU_device,MPU9150_RA_SIGNAL_PATH_RESET,0x00);
i2c_write_register(MPU_device,MPU9150_RA_MOT_DETECT_CTRL,0x00);
i2c_write_register(MPU_device,MPU9150_RA_USER_CTRL,0x00);
i2c_write_register(MPU_device,MPU9150_RA_PWR_MGMT_2,0x00);
i2c_write_register(MPU_device,MPU9150_RA_FIFO_R_W,0x00);

i2c_write_register(MPU_magnet, MPU9150_MG_CNTL, 0x01);
}

void MPU9150_sleep()
{
i2c_write_register(MPU_device,MPU9150_RA_PWR_MGMT_1,0x41);
}

void MPU9150_wake_up()
{
i2c_write_register(MPU_device,MPU9150_RA_PWR_MGMT_1,0x01);
}

void get_IMU_accel(uint8_t* buffer)
{
i2c_read_registers(MPU_device,MPU9150_RA_ACCEL_XOUT_H,6,buffer);
}

void get_IMU_gyro(uint8_t* buffer)
{
i2c_read_registers(MPU_device,MPU9150_RA_TEMP_OUT_H,6,buffer);
}
void get_IMU_temp(uint8_t* buffer)
{
i2c_read_registers(MPU_device,MPU9150_RA_GYRO_XOUT_H,6,buffer);
}

void set_IMU_magnet()
{
i2c_write_register(MPU_magnet, MPU9150_MG_CNTL, 0x01);
}

void get_IMU_all(uint8_t* buffer)
{
i2c_read_registers(MPU_device,MPU9150_RA_ACCEL_XOUT_H,14,buffer);
}