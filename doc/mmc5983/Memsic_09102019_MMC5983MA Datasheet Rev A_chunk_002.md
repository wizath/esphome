**Register Details**
**Xout0, Xout1, XYZout2**

|Xout0|7|6|5|4|3|2|1|0|
|---|---|---|---|---|---|---|---|---|
|Addr: 00H|Xout[17:10]|Xout[17:10]|Xout[17:10]|Xout[17:10]|Xout[17:10]|Xout[17:10]|Xout[17:10]|Xout[17:10]|
|Mode|R|R|R|R|R|R|R|R|

|Xout1|7|6|5|4|3|2|1|0|
|---|---|---|---|---|---|---|---|---|
|Addr: 01H|Xout[9:2]|Xout[9:2]|Xout[9:2]|Xout[9:2]|Xout[9:2]|Xout[9:2]|Xout[9:2]|Xout[9:2]|
|Mode|R|R|R|R|R|R|R|R|

|XYZout2|7|6|5|4|3|2|1|0|
|---|---|---|---|---|---|---|---|---|
|Addr: 06H|Xout[1:0]|Xout[1:0]|Yout[1:0]|Yout[1:0]|Zout[1:0]|Zout[1:0]|0|0|
|Mode|R|R|R|R|R|R|R|R|

|X-axis output, unsigned format.|Col2|
|---|---|
|X-axis output|Data|
|16bits operation mode|Xout[17:2]|
|18bits operation mode|Xout[17:0]|

**Yout0, Yout1, XYZout2**

|Yout0|7|6|5|4|3|2|1|0|
|---|---|---|---|---|---|---|---|---|
|Addr: 02H|Yout[17:10]|Yout[17:10]|Yout[17:10]|Yout[17:10]|Yout[17:10]|Yout[17:10]|Yout[17:10]|Yout[17:10]|
|Mode|R|R|R|R|R|R|R|R|

|Yout1|7|6|5|4|3|2|1|0|
|---|---|---|---|---|---|---|---|---|
|Addr: 03H|Yout[9:2]|Yout[9:2]|Yout[9:2]|Yout[9:2]|Yout[9:2]|Yout[9:2]|Yout[9:2]|Yout[9:2]|
|Mode|R|R|R|R|R|R|R|R|

|XYZout2|7|6|5|4|3|2|1|0|
|---|---|---|---|---|---|---|---|---|
|Addr: 06H|Xout[1:0]|Xout[1:0]|Yout[1:0]|Yout[1:0]|Zout[1:0]|Zout[1:0]|0|0|
|Mode|R|R|R|R|R|R|R|R|

|Y-axis output, unsigned format.|Col2|
|---|---|
|Y-axis output|Data|
|16bits operation mode|Yout[17:2]|
|18bits operation mode|Yout[17:0]|

MEMSIC MMC5983MA Rev A Page 13 of 20 Formal release date: 4/3/2019

-----

**Zout0, Zout1, XYZout2**

|Zout0|7|6|5|4|3|2|1|0|
|---|---|---|---|---|---|---|---|---|
|Addr: 04H|Zout[17:10]|Zout[17:10]|Zout[17:10]|Zout[17:10]|Zout[17:10]|Zout[17:10]|Zout[17:10]|Zout[17:10]|
|Mode|R|R|R|R|R|R|R|R|

|Zout1|7|6|5|4|3|2|1|0|
|---|---|---|---|---|---|---|---|---|
|Addr: 05H|Zout[9:2]|Zout[9:2]|Zout[9:2]|Zout[9:2]|Zout[9:2]|Zout[9:2]|Zout[9:2]|Zout[9:2]|
|Mode|R|R|R|R|R|R|R|R|

|XYZout2|7|6|5|4|3|2|1|0|
|---|---|---|---|---|---|---|---|---|
|Addr: 06H|Xout[1:0]|Xout[1:0]|Yout[1:0]|Yout[1:0]|Zout[1:0]|Zout[1:0]|0|0|
|Mode|R|R|R|R|R|R|R|R|

|Z-axis output, unsigned format.|Col2|
|---|---|
|Z-axis output|Data|
|16bits operation mode|Zout[17:2]|
|18bits operation mode|Zout[17:0]|

**Tout**

|Tout|7|6|5|4|3|2|1|0|
|---|---|---|---|---|---|---|---|---|
|Addr: 07H|Tout[7:0]|Tout[7:0]|Tout[7:0]|Tout[7:0]|Tout[7:0]|Tout[7:0]|Tout[7:0]|Tout[7:0]|
|Mode|R|R|R|R|R|R|R|R|

Temperature output, unsigned format. The range is -75~125°C, about 0.8°C/LSB, 00000000 stands for -75°C

**Status**

|Device Status|7|6|5|4|3|2|1|0|
|---|---|---|---|---|---|---|---|---|
|Addr: 08H|Reserved|Reserved|Reserved|OTP_Re<br>ad_Done|Reserved|Reserved|Meas_T_<br>Done|Meas_M<br>_ Done|
|Reset Value|0|0|0|0|0|0|0|0|
|Mode|R/W|R/W|R/W|R/W|R/W|R/W|R/W|R/W|

|Bit Name|Description|
|---|---|
|Meas_M_Done|Indicates a measurement event of magnetic field is completed. This bit should be checked before<br>reading the output. When the new measurement command is occurred, this bit turns to “0”. When<br>the measurement is finished, this bit will remain “1” till next measurement. Writing 1 into this bit<br>will clear the corresponding interrupt.|
|Meas_T_Done|Indicates a measurement event of temperature is completed. When the new measurement<br>command is occurred, this bit turns to “0”. When the measurement is finished, this bit will remain<br>“1” till next measurement. Writing 1 into this bit will clear the corresponding interrupt.|
|OTP_Rd_Done|Indicates the chip was able to successfully read its memory.|

**Internal Control 0**

|Control<br>Register 0|7|6|5|4|3|2|1|0|
|---|---|---|---|---|---|---|---|---|
|Addr: 09H|Reserved|OTP<br>Read|Auto_SR<br>_en|Reset|Set|INT_mea<br>s_done_<br>en|TM_T|TM_M|
|Reset Value|0|0|0|0|0|0|0|0|
|Mode|W|W|W|W|W|W|W|W|

|Bit Name|Description|
|---|---|
|TM_M|Take magnetic field measurement, set ‘1’ will initiate measurement. This bit will be automatically<br>reset to 0 at the end of each measurement.|
|TM_T|Take Temperature measurement, set ‘1’ will initiate measurement. This bit will be automatically<br>reset to 0 at the end of each measurement. This bit and TM_M cannot be high at the same time.|

MEMSIC MMC5983MA Rev A Page 14 of 20 Formal release date: 4/3/2019

-----

|INT_meas_do<br>ne_en|Writing “1” will enable the interrupt for completed measurements. Once a measurement is finished,<br>either magnetic field or temperature, an interrupt will be sent to the host.|
|---|---|
|Set|Writing “1”will cause the chip to do the Set operation, which will allow large set current to flow<br>through the sensor coils for 500ns. This bit is self-cleared at the end of Set operation.|
|Reset|Writing “1” will cause the chip to do the Reset operation, which will allow large reset current to flow<br>through the sensor coils for 500ns. This bit is self-cleared at the end of Reset operation.|
|Auto_SR_en|Writing “1” will enable the feature of automatic set/reset.|
|OTP Read|Writing “1” will let the device to read the OTP data again. This bit will be automatically reset to 0<br>after the shadow registers for OTP are refreshed.|

**Internal Control 1**

|Control<br>Register 1|7|6|5|4|3|2|1|0|
|---|---|---|---|---|---|---|---|---|
|Addr: 0AH|SW_<br>RST|Reserved|Reserved|YZ-inhibit|YZ-inhibit|X-inhibit|BW1|BW0|
|Reset Value|0|0|0|0|0|0|0|0|
|Mode|W|W|W|W|W|W|W|W|

|BW1|BW0|Measurement Time|Bandwidth|
|---|---|---|---|
|0|0|8ms|100Hz|
|0|1|4ms|200Hz|
|1|0|2ms|400Hz|
|1|1|0.5ms|800Hz|

|Bit Name|Description|
|---|---|
|BW0&<br>BW1|Output resolution<br>BW1<br>BW0<br>Measurement Time<br>Bandwidth<br>0 <br>0 <br>8ms<br>100Hz<br>0 <br>1 <br>4ms<br>200Hz<br>1 <br>0 <br>2ms<br>400Hz<br>1 <br>1 <br>0.5ms<br>800Hz<br>Note: X/Y/Z channel measurements are taken in parallel.<br>These bandwidth selection bits adjust the length of the decimation filter. They control the duration<br>of each measurement.|
|<br>X-inhibit|Writing “1” will disable X channel.|
|<br>Y/Z-inhibit|Writing “1” to the two bits will disable Y and Z channel.|
|SW_RST|Writing “1”will cause the part to reset, similar to power-up. It will clear all registers and also re-<br>read OTP as part of its startup routine. The power on time is 10mS.|

**Internal Control 2**

|Control<br>Register 2|7|6|5|4|3|2|1|0|
|---|---|---|---|---|---|---|---|---|
|Addr: 0BH|En_prd_s<br>et|Prd_set[2:0]|Prd_set[2:0]|Prd_set[2:0]|Cmm_en|Cm_freq[2:0]|Cm_freq[2:0]|Cm_freq[2:0]|
|Reset Value|0|0|0|0|0|0|0|0|
|Mode|W|W|W|W|W|W|W|W|

MEMSIC MMC5983MA Rev A Page 15 of 20 Formal release date: 4/3/2019

-----

|CM_Freq [2:0]|Frequency (Typical)|
|---|---|
|000|Continuous Measurement Mode is off.|
|001|1Hz|
|010|10 Hz|
|011|20Hz|
|100|50 Hz|
|101|100 Hz|
|110 (BW=01)|200Hz|
|111 (BW=11)|1000 Hz|

|Prd_set [2:0]|Times of measurement|
|---|---|
|000|1|
|001|25|
|010|75|
|011|100|
|100|250|
|101|500|
|110|1000|
|111|2000|

|Bit Name|Description|
|---|---|
|CM_Freq[2:0]|These bits determine how often the chip will take measurements in Continuous<br>Measurement Mode. The frequency is based on the assumption that BW[1:0] = 00.<br> <br> <br> <br> <br> <br>CM_Freq [2:0]<br>Frequency (Typical)<br>000<br>Continuous Measurement Mode is off.<br>001<br>1Hz<br>010<br>10 Hz<br>011<br>20Hz<br>100<br>50 Hz<br>101<br>100 Hz<br>110 (BW=01)<br>200Hz<br>111 (BW=11)<br>1000 Hz|
|Cmm_en|Writing “1” will enable the continuous mode. In order to enter the continuous mode,<br>CM_Freq[2:0] cannot be 000.|
|Prd_set[2:0]|These bits determine how often the chip will do a set operation. The device will perform a<br>SET automatically per the setting in below table.<br> <br> <br> <br> <br> <br> <br> <br> <br> <br> <br> <br>Prd_set [2:0]<br>Times of measurement<br>000<br>1 <br>001<br>25<br>010<br>75<br>011<br>100<br>100<br>250<br>101<br>500<br>110<br>1000<br>111<br>2000|
|En_prd_set|Writing “1” will enable the feature of periodic set. This feature needs to work with both<br>Auto_SR_en and Cmm_en bits set to 1.|

**Internal Control 3**

|Control<br>Register 3|7|6|5|4|3|2|1|0|
|---|---|---|---|---|---|---|---|---|
|Addr: 0CH|reserved|Spi_3w|reserved|reserved|reserved|St_enm|St_enp|reserved|
|Reset Value|0|0|0|0|0|0|0|0|
|Mode|W|W|W|W|W|W|W|W|

|Bit Name|Description|
|---|---|
|St_enp|Writing “1” will apply an extra current flowing from the positive end to the negative end of an<br>internal coil and result in an extra magnetic field. This feature can be used to check whether the<br>sensor has been saturated.<br>|
|St_enm|Writing “1” will apply an extra current flowing from the negative end to the positive end of an<br>internal coil and result in an extra magnetic field. This feature can be used to check whether the<br>sensor has been saturated.<br>|
|Spi_3w|Writing a 1 into this location will put the device into 3-wire SPI mode.|

|Product ID1|Col2|Col3|Col4|Col5|Col6|Col7|Col8|Col9|
|---|---|---|---|---|---|---|---|---|
|Product ID 1|7|6|5|4|3|2|1|0|
|Addr: 2FH|Product ID1[7:0]|Product ID1[7:0]|Product ID1[7:0]|Product ID1[7:0]|Product ID1[7:0]|Product ID1[7:0]|Product ID1[7:0]|Product ID1[7:0]|
|Reset Value|0|0|1|1|0|0|0|0|
|Mode|R|R|R|R|R|R|R|R|

MEMSIC MMC5983MA Rev A Page 16 of 20 Formal release date: 4/3/2019

-----

**4** **th** **cycle** : The Master device sends a START command
followed by the MEMSIC device’s seven bit address,
and finally the eighth bit set low to indicate a WRITE.
An Acknowledge should be send by the MEMSIC
device in response.

**5** **th** **cycle** : The Master device sends the MEMSIC
device’s Status Register [00001000] as the address to
read.

**6** **th** **cycle** : The Master device sends a START command
followed by the MEMSIC device’s seven bit address,
and finally the eighth bit set high to indicate a
READ. An Acknowledge should be send by the
MEMSIC device in response.

**7** **th** **cycle** : The Master device cycles the SCL line. This
causes the Status Register data to appear on SDA line.
Continuously read the Status Register until the
Meas_M_Done bit (bit 0) is set to ‘1’.or check INT pin
status. This indicates that data for the x, y, and z
sensors is available to be read.

**8** **th** **cycle** : The Master device sends a START command
followed by the MEMSIC device’s seven bit address,
and finally the eighth bit set low to indicate a WRITE.
An Acknowledge should be send by the MEMSIC
device in response.

**9** **th** **cycle** : The Master device sends a [00000000] (Xout
LSB register address) as the register address to read.

**10** **th** **cycle** : The Master device calls the MEMSIC
device’s address with a READ (8 th SCL cycle SDA line
high). An Acknowledge should be send by the MEMSIC
device in response.

**11** **th** **cycle** : Master device continues to cycle the SCL
line, and each consecutive byte of data from the X, Y
and Z registers should appear on the SDA line. The
internal memory address pointer automatically moves
to the next byte. The Master device acknowledges
each. Thus:

**12** **th** **cycle** : Xout[17:10].

**13** **th** **cycle** : Xout[9:2].

**14** **th** **cycle** : Yout[17:10].

**15** **th** **cycle** : Yout[9:2].

**16** **th** **cycle** : Zout[17:10].

**17** **th** **cycle** : Zout[9:2].

**18** **th** **cycle** : Xout[1:0], Yout[1:0], Zout[1:0] for 18bits
mode.

Master ends communications by NOT sending an
‘Acknowledge’ and also follows with a ‘STOP’
command.

**DATA TRANSFER**

A data transfer is started with a “START” condition and
ended with a “STOP” condition. A “START” condition is
defined by a HIGH to LOW transition on the SDA line
while SCL line is HIGH. A “STOP” condition is defined
by a LOW to HIGH transition on the SDA line while the
SCL line is held HIGH. All data transfer in I 2 C system
are 8-bits long. Each byte has to be followed by an
acknowledge bit. Each data transfer involves a total of
9 clock cycles. Data is transferred starting with the most
significant bit (MSB).

After a START condition, the Master device calls a
specific slave device by sending its 7-bit address with
the 8 th bit (LSB) indicating that either a READ or WRITE
operation will follow, [1] for READ and [0] for WRITE.
The MEMSIC device 7-bit device address is [ **0110000]** .

The initial addressing of the slave is always followed by
the master writing the number of the slave register to
be read or written, so this initial addressing always
indicates a WRITE operation by sending **[01100000]** .
After being addressed, the MEMSIC device being
called should respond by an “Acknowledge” signal by
pulling SDA line LOW. Subsequent communication
bytes can either be
**a)** The data to be written to the device register, or

**b)** Another START condition followed by the device
address indicating a READ operation **[01100001]** ,
and then the master reads the register data.

Multiple data bytes can be written or read to numerically
sequential registers without the need of another START
condition. Data transfer is terminated by a STOP
condition or another START condition.  Two detailed
examples of communicating with the MEMSIC device
are listed below for the actions of acquiring a magnetic
field measurement and magnetizing the sensor.

**EXAMPLE MEASUREMENT**

**1** **st** **cycle** : A START condition is established by the
Master device followed by a call to the slave address

[0110000] with the eighth bit held low to indicate a
WRITE request.

**2** **nd** **cycle** : After an acknowledge signal is received by
the Master device (MEMSIC device pulls SDA line low
during 9 th SCL pulse), the Master device sends the
address of Control Register 0 or [00001001] as the
target register to be written. The MEMSIC device
should acknowledge receipt of the address (9 th SCL
pulse, SDA pulled low).

**3** **rd** **cycle** : The Master device writes to the Internal
Control Register 0 the code [00000001] (TM_M high) to
initiate data acquisition. The MEMSIC device should
send an Acknowledge and internally initiate a
measurement (collect x, y and z data). A STOP
condition indicates the end of the write operation.

MEMSIC MMC5983MA Rev A Page 17 of 20 Formal release date: 4/3/2019

-----

**EXAMPLE OF SET**

**1** **st** **cycle** : A START condition is established by the
Master Device followed by a call to the slave address

[0110000] with the eighth bit held low to indicate a
WRITE request.

**2** **nd** **cycle** : After an acknowledge signal is received by
the Master device (The MEMSIC device pulls the SDA
line low during the 9 th SCL pulse), the Master device
sends [00001001] as the target address (Internal
Control Register 0). The MEMSIC device should
acknowledge receipt of the address (9 th SCL pulse).

**3** **rd** **cycle** : The Master device writes to the MEMSIC
device’s Internal Control 0 register the code [00001000]
(SET bit) to initiate a SET action. The MEMSIC device
should send an Acknowledge.

**EXAMPLE OF RESET**

**1** **st** **cycle** : A START condition is established by the
Master device followed by a call to the slave address

[0110000] with the eighth bit held low to indicate a
WRITE request

**2** **nd** **cycle** : After an acknowledge signal is received by
the Master device (The MEMSIC device pulls the SDA
line low during the 9 th SCL pulse), the Master device
sends [00001001] as the target address (Internal
Control Register 0). The MEMSIC device should
acknowledge receipt of the address (9 th SCL pulse).

**3** **rd** **cycle** : The Master device writes to the MEMSIC
device’s Internal Control 0 register the code [00010000]
(RESET bit) to initiate a RESET action. The MEMSIC
device should send an Acknowledge.

At this point, the MEMSIC AMR sensors have been
conditioned for optimum performance and data
measurements can commence.

**Note:** The RESET action can be skipped for most
applications

**USING SET AND RESET TO REMOVE BRIDGE**
**OFFSET**

The integrated SET and RESET functions of the
MMC5893VA enables the user to remove the error
associated with bridge Offset change as a function of
temperature, thereby enabling more precise heading
measurements over a wider temperature than
competitive technologies. The SET and RESET
functions effectively alternately flip the magnetic
sensing polarity of the sensing elements of the device.

**1)** The most accurate magnetic field measurements
can be obtained by using the protocol described
as follows: Perform SET. This sets the internal
magnetization of the sensing resistors in the
direction of the SET field.

**2)** Perform MEASUREMENT. This measurement
will contain not only the sensors response to the
external magnetic field, H, but also the Offset; in
other words,

**Output1 = +H + Offset.**

**3)** Perform RESET. This resets the internal
magnetization of the sensing resistors in the
direction of the RESET field, which is opposite to
the SET field (180 o opposed).

**4)** Perform MEASUREMENT. This measurement
will contain both the sensors response to the
external field and also the Offset. In other words,
**Output2 = -H + Offset.**

**5)** Finally, calculate H by subtracting the two
measurements and dividing by 2. This procedure
effectively eliminates the Offset from the
measurement and therefore any changes in the
Offset over temperature.

**Note:** To calculate and store the offset; add the two
measurements and divide by 2. This calculated offset
value can be subtracted from subsequent
measurements to obtain H directly from each
measurement.

MEMSIC MMC5983MA Rev A Page 18 of 20 Formal release date: 4/3/2019

-----

**SOLDERING RECOMMENDATIONS**
MEMSIC magnetic sensor is capable of withstanding an MSL3 / 260ºC solder reflow. Following is the reflow profile:
**Note:**

###  This is the reflow profile for Pb free process
  The peak temperature on the sensor surface should be limited under 260 ℃ for no more than 10 seconds.
  Reflow conditions recommended by solder paste should be followed to get the best SMT quality.
  Maximum 3 SMT cycles
  Second and third reflow cycle should be applied after device has cooled down to 25 ℃ (room temperature)
  If the part is mounted manually, please ensure the temperature does not exceed 260 ℃ for 10 seconds.

MEMSIC MMC5983MA Rev A Page 19 of 20 Formal release date: 4/3/2019

-----

### PACKAGE DRAWING (LGA package)

**LAND PATTERN**

MEMSIC MMC5983MA Rev A Page 20 of 20 Formal release date: 4/3/2019

-----
