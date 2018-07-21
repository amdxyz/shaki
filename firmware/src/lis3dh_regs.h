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

#ifndef LIS3DH_REGS_H_
#define LIS3DH_REGS_H_


#define LIS3DH_DEFAULT_ADDRESS          0x18
#define LIS3DH_AUTOINCREMENT_FLAG       0x80

#define LIS3DH_REG_STATUS1              0x07
#define LIS3DH_REG_OUTADC1_L            0x08
#define LIS3DH_REG_OUTADC1_H            0x09
#define LIS3DH_REG_OUTADC2_L            0x0A
#define LIS3DH_REG_OUTADC2_H            0x0B
#define LIS3DH_REG_OUTADC3_L            0x0C
#define LIS3DH_REG_OUTADC3_H            0x0D
#define LIS3DH_REG_INTCOUNT             0x0E
#define LIS3DH_REG_WHOAMI               0x0F
#define LIS3DH_REG_TEMPCFG              0x1F
#define LIS3DH_REG_CTRL1                0x20
#define LIS3DH_REG_CTRL2                0x21
#define LIS3DH_REG_CTRL3                0x22
#define LIS3DH_REG_CTRL4                0x23
#define LIS3DH_REG_CTRL5                0x24
#define LIS3DH_REG_CTRL6                0x25
#define LIS3DH_REG_REFERENCE            0x26
#define LIS3DH_REG_STATUS2              0x27
#define LIS3DH_REG_OUT_X_L              0x28
#define LIS3DH_REG_OUT_X_H              0x29
#define LIS3DH_REG_OUT_Y_L              0x2A
#define LIS3DH_REG_OUT_Y_H              0x2B
#define LIS3DH_REG_OUT_Z_L              0x2C
#define LIS3DH_REG_OUT_Z_H              0x2D
#define LIS3DH_REG_FIFOCTRL             0x2E
#define LIS3DH_REG_FIFOSRC              0x2F
#define LIS3DH_REG_INT1CFG              0x30
#define LIS3DH_REG_INT1SRC              0x31
#define LIS3DH_REG_INT1THS              0x32
#define LIS3DH_REG_INT1DUR              0x33
#define LIS3DH_REG_CLICKCFG             0x38
#define LIS3DH_REG_CLICKSRC             0x39
#define LIS3DH_REG_CLICKTHS             0x3A
#define LIS3DH_REG_TIMELIMIT            0x3B
#define LIS3DH_REG_TIMELATENCY          0x3C
#define LIS3DH_REG_TIMEWINDOW           0x3D
#define LIS3DH_REG_ACTTHS               0x3E
#define LIS3DH_REG_ACTDUR               0x3F

#define LIS3DH_FLAG_CTRL1_XEN           1 << 0
#define LIS3DH_FLAG_CTRL1_YEN           1 << 1
#define LIS3DH_FLAG_CTRL1_ZEN           1 << 2
#define LIS3DH_FLAG_CTRL1_LPEN          1 << 3
#define LIS3DH_FLAG_CTRL1_ODR0          1 << 4
#define LIS3DH_FLAG_CTRL1_ODR1          1 << 5
#define LIS3DH_FLAG_CTRL1_ODR2          1 << 6
#define LIS3DH_FLAG_CTRL1_ODR3          1 << 7

#define LIS3DH_FLAG_CTRL2_HP_IA1        1 << 0
#define LIS3DH_FLAG_CTRL2_HP_IA2        1 << 1
#define LIS3DH_FLAG_CTRL2_HPCLICK       1 << 2
#define LIS3DH_FLAG_CTRL2_FDS           1 << 3
#define LIS3DH_FLAG_CTRL2_HPCF1         1 << 4
#define LIS3DH_FLAG_CTRL2_HPCF2         1 << 5
#define LIS3DH_FLAG_CTRL2_HPM0          1 << 6
#define LIS3DH_FLAG_CTRL2_HPM1          1 << 7

#define LIS3DH_FLAG_CTRL3_I1_OVERRUN    1 << 1
#define LIS3DH_FLAG_CTRL3_I1_WTM        1 << 2
#define LIS3DH_FLAG_CTRL3_I1_321DA      1 << 3
#define LIS3DH_FLAG_CTRL3_I1_ZYXDA      1 << 4
#define LIS3DH_FLAG_CTRL3_I1_IA2        1 << 5
#define LIS3DH_FLAG_CTRL3_I1_IA1        1 << 6
#define LIS3DH_FLAG_CTRL3_I1_CLICK      1 << 7


#endif /* LIS3DH_REGS_H_ */
