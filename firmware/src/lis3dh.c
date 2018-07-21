/* ***********************************************************************
    Shaki firmware
    Copyright (C) 2016-2018 Marco Fagiolini <mfx@amdx.de>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
* ***********************************************************************/

#include "i2cmaster.h"

#include "lis3dh_regs.h"
#include "lis3dh.h"


void lis3dh_write(uint8_t address, uint8_t data)
{
    i2c_start_wait(LIS3DH_DEFAULT_ADDRESS << 1 | I2C_WRITE);
    i2c_write(address);
    i2c_write(data);
    i2c_stop();
}

void lis3dh_read(uint8_t address, uint8_t *buffer, uint8_t length)
{
    i2c_start((LIS3DH_DEFAULT_ADDRESS << 1) + I2C_WRITE);
    i2c_write(address);

    i2c_rep_start((LIS3DH_DEFAULT_ADDRESS << 1) + I2C_READ);
    for (uint8_t i = 0 ; i < length - 1 ; ++i) {
        buffer[i] = i2c_readAck();
    }
    buffer[length - 1] = i2c_readNak();
    i2c_stop();
}

uint8_t lis3dh_read_single(uint8_t address)
{
    uint8_t value;

    i2c_start((LIS3DH_DEFAULT_ADDRESS << 1) + I2C_WRITE);
    i2c_write(address);

    i2c_rep_start((LIS3DH_DEFAULT_ADDRESS << 1) + I2C_READ);
    value = i2c_readNak();
    i2c_stop();

    return value;
}

int8_t lis3dh_init()
{
    i2c_init();

    if (lis3dh_read_single(LIS3DH_REG_WHOAMI) != 0x33) {
        return -1;
    }

    // Enable all axes, 1600Hz, low power mode
    lis3dh_write(LIS3DH_REG_CTRL1, LIS3DH_FLAG_CTRL1_XEN |
                                   LIS3DH_FLAG_CTRL1_YEN |
                                   LIS3DH_FLAG_CTRL1_ZEN |
                                   LIS3DH_FLAG_CTRL1_LPEN |
                                   LIS3DH_FLAG_CTRL1_ODR3);

    // Enable interrupt on xyz data ready
    lis3dh_write(LIS3DH_REG_CTRL3, LIS3DH_FLAG_CTRL3_I1_ZYXDA);

#ifdef LIS3DH_SENSITIVITY_4G
    // +/- 4g sensitivity
    lis3dh_write(LIS3DH_REG_CTRL4, 1 << 4);
#endif

    return 0;
}

int8_t lis3dh_update(AccelVec *accel_vec)
{
    uint8_t buffer[6];
    lis3dh_read(LIS3DH_REG_OUT_X_L | LIS3DH_AUTOINCREMENT_FLAG, buffer, 6);

    accel_vec->x = buffer[1];
    accel_vec->y = buffer[3];
    accel_vec->z = buffer[5];

    return 0;
}
