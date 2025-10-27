## ±8 Gauss, High Performance 3-axis Magnetic Sensor

# MMC5983MA

**FEATURES**

-  **Fully integrated 3-axis magnetic sensor and**
**electronic circuits requiring fewer external**
**components**

-  **Superior dynamic range and accuracy:**
 **±8G FSR**
 **18bits operation**
 **0.4mG total RMS noise**
 **Enables heading accuracy of**  **0.5º**

-  **Max output data rate of 1000Hz**

-  **Industrial standard low profile package**
**3.0mm x 3.0mm x 1.0mm**

-  **Degaussing with built-in SET/RESET function**
 **Eliminates thermal variation induced offset**
**error (Null field output)**
 **Clears the residual magnetization resulting**
**from strong external fields**

-  **On-chip sensitivity compensation**

-  **On-chip temperature sensor**

-  **Data_Ready Interrupt**

-  **Low power consumption**

-  1µ **A power down current**

-  **I** **2** **C Slave, FAST(≤400KHz) mode**

-  **3.0V single low power supply**

-  **SPI interface available**

-  **RoHS compliant**

**APPLICATIONS**

-  **Electronic Compass & Navigation**

-  **Position Sensing**

-  **General Purpose Magnetic Field**
**Measurements**

**DESCRIPTION**
The MMC5983MA is an AEC-Q100 qualified complete
3-axis magnetic sensor with on-chip signal processing
and integrated I 2 C/SPI bus suitable for use in
automotive applications. The device can be connected
directly to a microprocessor, eliminating the need for
A/D converters or timing resources.

Information furnished by MEMSIC is believed to be accurate and reliable.
However, no responsibility is assumed by MEMSIC for its use, or for any
infringements of patents or other rights of third parties which may result from

**FUNCTIONAL BLOCK DIAGRAM**

It can measure magnetic fields within the full scale
range of  8 Gauss (G), with 0.25mG/0.0625mG per
LSB resolution at 16bits/18bits operation mode and 0.4
mG total RMS noise level, enabling heading accuracy
of  0.5º in electronic compass applications.
An integrated SET/RESET function provides for the
elimination of error due to Null Field output change with
temperature. Temperature information from the
integrated temperature sensor is available over the I 2 C
Interface. The SET/RESET function can be performed
for each measurement, periodically, or when the
temperature changes by a predetermined amount as
the specific application requires.
In addition, the SET/RESET function clears the sensors
of any residual magnetic polarization resulting from
exposure to strong external magnets.
The MMC5983MA is packaged in a low profile LGA
package and an operating temperature range from 40  C to +105  C.
The MMC5983MA provides an I 2 C digital output with
400 KHz, fast mode operation, and a 10MHz SPI digital
output.

its use. No license is granted by implication or otherwise under any patent or
patent rights of MEMSIC.

MEMSIC MMC5983MA Rev A Page 1 of 20 Formal release date: 4/3/2019

-----

**www.memsic.com**

 **MEMSIC, Inc.**
**One Technology Drive, Suite 325, Andover, MA01810, USA**
**Tel: +1 978 738 0900** **Fax: +1 978 738 0196**

### SPECIFICATIONS (Measurements @ 25  C, unless otherwise noted; V DD =3.0V unless otherwise specified)

|Parameter|Conditions|Min|Typ|Max|Units|
|---|---|---|---|---|---|
|Field Range (Each Axis)|Total applied field||8||G|
|Supply Voltage|VDD|2.8|3.0|3.6|V|
|Supply Voltage|VDDIO(I2Cinterface and INT)|2.8|3.0|3.6|V|
|Supply Voltage Rise Time||||5.0|ms|
|Supply Current1,2 <br>(7 measurements/second)<br>|BW=00||450||µA|
|Supply Current1,2 <br>(7 measurements/second)<br>|BW=01||225||µA|
|Supply Current1,2 <br>(7 measurements/second)<br>|BW=10||112.5||µA|
|Supply Current1,2 <br>(7 measurements/second)<br>|BW=11||32||µA|
|Power Down Current2|||1.0||µA|
|Operating Temperature||-40||105|C|
|Storage Temperature||-55||125|C|
|Linearity Error2 <br>(Best fit straight line)|FS=±8G<br>Happlied=±4G||0.1||%FS|
|Hysteresis2|3 sweeps across ±8G||0.01||%FS|
|Repeatability Error2|3 sweeps across ±8G||0.1||%FS|
|Alignment Error|||1.0|3.0|Degrees|
|Transverse Sensitivity|||0.8||%|
|Total RMS Noise2|BW=00||0.4||mG|
|Total RMS Noise2|BW=01||0.6||mG|
|Total RMS Noise2|BW=10||0.8||mG|
|Total RMS Noise2|BW=11||1.2||mG|
|<br>Output Resolution|||18||Bits|
|Max Output data rate2|BW=00||50||Hz|
|Max Output data rate2|BW=01||100||Hz|
|Max Output data rate2|BW=10||225||Hz|
|Max Output data rate2|BW=11||580||Hz|
|Max Output data rate2|BW=11(CM_Freq=111)||1000||Hz|
|Heading Accuracy3|||1.0||Degrees|
|Sensitivity Accuracy4,5 <br>|8 G||5||%|
|Sensitivity Accuracy4,5 <br>|With16bits operation||4096||Counts/G|
|Sensitivity Accuracy4,5 <br>|With18bits operation||16384||Counts/G|
|Sensitivity Change Over<br>Temperature|-40~105C <br>Delta from 25C,8 G||5||%|
|Null Field Output5|||0.5||G|
|Null Field Output5|With16bits operation||32768||Counts|
|Null Field Output5|With18bits operation||131072||Counts|
|Null Field Output Change Over<br>Temperature using SET/RESET|-40~105C <br>Delta from 25C||3||mG|
|Temperature Sensor Output|||0.8||C/Count|
|Disturbing Field6|||10||G|
|Maximum Exposed Field||||10,000|G|
|SET/RESET Repeatability|||1||mG|

1. Supply current is proportional to how many measurements performed per second.
2. Based on 3lots characterization result.
3. MEMSIC product enables users to utilize heading accuracy to be 1.0 degree typical when using MEMSIC’s proprietary software or algorithm.
4. Sensitivity of the orthogonal axes is analytically derived from raw data and is subsequently processed by MEMSIC software drivers.
5. Based on shipment test result.
6. This is the magnitude of external field that can be tolerated without changing the sensor characteristics. If the disturbing field is exceeded, a SET/RESET
operation is required to restore proper sensor operation.

MEMSIC MMC5983MA Rev A Page 2 of 20 Formal release date: 4/3/2019

-----

**DIGITAL INTERFACE (VIO=3.0V)**

|Symbol|Parameter (Units)|Minimum|Typical|Maximum|
|---|---|---|---|---|
|VIH|High Level Input Voltage (Volts)|0.7*VIO|||
|VIL|Low Level Input Voltage (Volts)|||0.3*VIO|
|VHYS|Hysteresis of Schmitt Trigger Input (Volts)|0.2|||
|IIL|Input Leakage, All Inputs (uA)|-10||10|
|VOH|High Level Output Voltage (Volts)|0.8*VIO|||
|VOL|Low Level Output Voltage (Volts)|||0.2*VIO|

**I** **2** **C INTERFACE I/O CHARACTERISTICS (VIO=3.0V)**

|Parameter|Symbol|Test Condition|Min.|Typ.|Max.|Unit|
|---|---|---|---|---|---|---|
|Logic Input Low Level|VIL||-0.5||0.3* VIO|V|
|Logic Input High Level|VIH||0.7*VIO||VIO|V|
|Hysteresis of Schmitt Input|Vhys||0.2|||V|
|Logic Output Low Level|VOL||||0.6|V|
|Input Leakage Current|Ii|0.1VIO<Vin<0.9VIO|-10||10|µA|
|SCL Clock Frequency|fSCL||0||400|kHz|
|START Hold Time|tHD;STA||0.6|||µS|
|START Setup Time|tSU;STA||0.6|||µS|
|LOW period of SCL|tLOW||1.3|||µS|
|HIGH period of SCL|tHIGH||0.6|||µS|
|Data Hold Time|tHD;DAT||0||0.9|µS|
|<br>Data Setup Time|tSU;DAT||0.1|||µS|
|Rise Time|tr|From VIL toVIH|||0.3|µS|
|Fall Time|tf|From VIH toVIL|||0.3|µS|
|Bus Free Time Between STOP and<br>START|tBUF||1.3|||µS|
|STOP Setup Time|tSU;STO||0.6|||µS|

SDA

SCL

t HD;DAT t HIGH

Sr

|A<br>t f tLOW t r tSU;DAT t f t HD;STA t SP t r tBUF<br>t HD;STA t SU;STA t SU;STO|Col2|
|---|---|
|||

**Timing Definition**

MEMSIC MMC5983MA Rev A Page 3 of 20 Formal release date: 4/3/2019

-----

**SPI INTERFACE I/O CHARACTERISTICS (VIO=3.0V)**

|Parameter|Symbol|Value 1|Col4|Col5|Unit|
|---|---|---|---|---|---|
|<br> <br>**Parameter**|<br>**Symbol**|**Min.**|**Typ.**|**Max.**||
|SPI clock cycle|tc(SCK)|100|||ns|
|SPI clock frequency|fc(SCK)|||10|MHz|
|CS setup time|tsu(CS)|6|||<br> <br> <br> <br> <br>ns|
|CS hold time|th(CS)|8||||
|SDI input setup time|tsu(SI)|5||||
|SDI input hold time|th(SI)|15||||
|SDO valid output time|tv(SO)|||50|50|
|SDO output hold time|th(SO)|9||||
|SDO output disable time|tdis(SO)|||50|50|

1. Values are guaranteed at 10 MHz clock frequency for SPI, based on characterization results, not tested in production.

**Timing Definition**

MEMSIC MMC5983MA Rev A Page 4 of 20 Formal release date: 4/3/2019

-----

**SPI Read and Write protocol**

CS (SPI_CS) is the serial port enable and it is controlled by the SPI master. It goes low at the start of the
transmission and goes back high at the end.

SCK (SPI_SCK) is the serial port clock and it is controlled by the SPI master. It is stopped high when CS is high (no
transmission).

SDI (SPI_SDI) and SDO (SPI_SDO) are respectively the serial port data input and output. Those lines are driven at
the falling edge of SCK and should be captured at the rising edge of SCK.

Both the Read Register and Write Register commands are completed in 16 clocks pulses or in multiple of 8 in case
of multiple byte read/write. Bit duration is the time between two falling edges of SCK. The first bit (bit 0) starts at the
first falling edge of SCK after the falling edge of CS while the last bit (bit 15, bit 23, ...) starts at the last falling edge
of SCK (SPI_CS) just before the rising edge of CS.

bit 0: RW bit. When 0, the data DI(7:0) is written into the device. When 1, the data DO(7:0) from the device is read.
In latter case, the chip will drive SDO at the start of bit 8.

bit 1: Don’t care.

bit 2-7: Address AD(5:0). This is the address field of the indexed register.

bit 8-15: Data DI(7:0) (write mode). This is the data that will be written into the device (MSB first) (MSB first). bit 815: data DO(7:0) (read mode). This is the data that will be read from the device (MSB first).

In multiple read/write commands further blocks of 8 clock periods will be added.

MEMSIC MMC5983MA Rev A Page 5 of 20 Formal release date: 4/3/2019

-----

**SPI Read**

The SPI Read command is performed with 16 clocks pulses. Multiple byte read command is performed adding blocks
of 8 clocks pulses at the previous one.

bit 0: READ bit. The value is 1.

bit 1: don’t care.

bit 2-7: address AD(5:0). This is the address field of the indexed register.

bit 8-15: data DO(7:0) (read mode). This is the data that will be read from the device (MSB first).

bit 16-... : data DO(...-8). Further data in multiple byte reading.

MEMSIC MMC5983MA Rev A Page 6 of 20 Formal release date: 4/3/2019

-----

**SPI Write**

The SPI Write command is performed with 16 clocks pulses. Multiple byte write command is performed adding blocks
of 8 clocks pulses at the previous one.

bit 0: WRITE bit. The value is 0.

bit 1: don’t care

bit 2 -7: address AD(5:0). This is the address field of the indexed register.

bit 8-15: data DI(7:0) (write mode). This is the data that will be written inside the device (MSB first).

bit 16-... : data DI(...-8). Further data in multiple byte writing.

MEMSIC MMC5983MA Rev A Page 7 of 20 Formal release date: 4/3/2019

-----

**SPI Read in 3-wires mode**

The part can be configured as 3-wires SPI read mode, by write “1” to Internal Control Register 3 (0CH), bit 6 before
reading command.

The SPI Read command is performed with 16 clocks pulses:

bit 0: READ bit. The value is 1.

bit 1: don’t care.

bit 2-7: address AD(5:0). This is the address field of the indexed register.

bit 8-15: data DO(7:0) (read mode). This is the data that will be read from the device (MSB first). Multiple write
command is also available in 3-wires mode.

MEMSIC MMC5983MA Rev A Page 8 of 20 Formal release date: 4/3/2019

-----

**ABSOLUTE MAXIMUM RATINGS***
Supply Voltage -0.5 to +3.6V
Storage Temperature -55  C to +125  C
Maximum Exposed Field 10000 G

***Note:** Stresses above those listed under Absolute Maximum
Ratings may cause permanent damage to the device. This is
a stress rating only; the functional operation of the device at
these or any other conditions above those indicated in the
operational sections of this specification is not implied.
Exposure to absolute maximum rating conditions for
extended periods may affect the device’s reliability.

**Pin Description: LGA Package**

**Ordering Guide:**

MMC5983MA
Package type:

Code Type

LGA16
A
RoHS compliant

Performance Grade:

Code Performance Grade
M Industrial Grade

I 2 C address

Code 7bits address
3 0110000

**Marking illustration:**

**Note:** Coordinates shown above indicate polarity after
a SET operation.

The black dot on top-right marks the location of pin one
(1). The 1 st line represents the device’s Name. The 2 nd
line represents the device’s Lot Number.

|Pin|Name|Description|I/O|
|---|---|---|---|
|1|SCL/SPI_SCK|Serial Clock Line for<br>I2C/SPI bus|I|
|2|VDD|Power Supply|P|
|3|NC|Not Connected|NC|
|4|SPI_CS|Chip Select line for<br>SPI (active low). Tie<br>to VDDIO for I²C<br>Interface|I|
|5|SPI_SDO|SPI Serial Data Out|O|
|6|NC|<br>Not Connected|NC|
|7|NC|Not Connected|NC|
|8|NC|Not Connected|NC|
|9|GND|Connect to Ground|P|
|10|CAP|Connect a 10uF<br>capacitor for<br>SET/RESET|P|
|11|GND|Connect to Ground|P|
|12|NC|Not Connected|NC|
|13|VDDIO|Power supply for I2C <br>and INT|P|
|14|NC|Not Connected|NC|
|15|INT|Interrupt Output|O|
|16|SDA/SPI_SDI|Serial Data Line for<br>I2C/SPI bus|I/O|

All parts are shipped in tape and reel packaging with
5000pcs per 13” reel.

**Caution:**
This is an Electro-Static Discharge (ESD) sensitive
device.

MEMSIC MMC5983MA Rev A Page 9 of 20 Formal release date: 4/3/2019

-----

**THEORY OF OPERATION**
The Anisotropic Magneto-Resistive (AMR) sensors are
special resistors made of permalloy thin film deposited
on a silicon wafer. During manufacturing, a strong
magnetic field is applied to the film to orient its magnetic
domains in the same direction, establishing a
magnetization vector. Subsequently, an external
magnetic field applied perpendicularly to the sides of
the film causes the magnetization to rotate and change
angle. This effect causes the film’s resistance to vary
with the intensity of the applied magnetic field. The
MEMSIC AMR sensor is incorporated into a
Wheatstone bridge configuration to maximize Signal to
Noise ratio. A change in magnetic field produces a
proportional change in differential voltage across the
Wheatstone bridge.

However, the influence of a strong magnetic field (more
than 10 G) in any direction could upset, or flip, the
polarity of the film, thus changing the sensor
characteristics. A strong restoring magnetic field must
be applied momentarily to restore, or set, the sensor
characteristics. The MEMSIC magnetic sensor has an
on-chip magnetically coupled strap: a SET/RESET
strap pulsed with a high current, to provide the restoring
magnetic field

**EXTERNAL CIRCUITRY CONNECTION**

The MMC5983MA was designed for flexible power
connections to support existing and new designs. It can
operate from a single 2.8V to 3.6V supply or from dual
supplies using a 2.8V to 3.6V VDD supply and a 2.8V
to 3.6V VDDIO supply. The circuit connection diagrams
below illustrate power supply connection options.

2.7K

SCL/SPI_SCK

2.7K

16 15 14 13

12

11

NC

GND

CAP

Power
2.8~3.6V

10uF
1uF

10

GND

9

VIO
2.8~3.6V

SPI_CS

|VDD|Col2|
|---|---|
|NC|NC|
|NC|4|

**<Top View>**
**I** **2** **C Single Supply Connection**

16 15 14 13

12

11

NC

GND

CAP

SCL/SPI_SCK

Power
2.8~3.6V

VDD

VIO
2.8~3.6V

10uF
1uF

NC

10

GND

2.7K

SPI_CS

16 15 14 13

12

11

NC

GND

10uF

10

CAP

GND

**<Top View>**
**SPI Dual Supply Connection**

|2.7K<br>SCL/SPI_SCK<br>Power VDD|Col2|Col3|Col4|
|---|---|---|---|
|VDD<br>Power<br><br>2.7K<br>SCL/SPI_SCK||||
|VDD<br>Power<br><br>2.7K<br>SCL/SPI_SCK|||2|
|VDD<br>Power<br><br>2.7K<br>SCL/SPI_SCK||NC|NC|
|VDD<br>Power<br><br>2.7K<br>SCL/SPI_SCK||NC|4|

**<Top View>**
**I** **2** **C Dual Supply Connection**

MEMSIC MMC5983MA Rev A Page 10 of 20 Formal release date: 4/3/2019

-----

**PIN DESCRIPTIONS**
**CAP** – This is the supply input for SET/RESET coil.
MEMSIC recommends a minimum 10 uF low ESR
capacitor placed in close proximity to the CAP pin.
**GND** – This is the ground pin for the magnetic sensor.
**SDA/SPI_SDI** – This pin is the I 2 C/SPI serial data line,
and operates in I 2 C FAST (400 KHz)/SPI mode .
**SCL/SPI_SCK** – This pin is the I 2 C/SPI serial clock line,
and operates in FAST (400 KHz)/SPI mode.
**SPI_CS** – This pin is chip select line for SPI (active
low). Tie to VDDIO for I²C Interface.
**SPI_SDO** – This pin the SPI serial data out line.
**VDD** – This pin is the power supply of the ASIC.
**VDDIO** – This pin is the power supply of the digital
interface of the ASIC.
**INT** – This pin is Interrupt output. Active High. It is held
as hi-Z until an interrupt function is enabled.
Note: VDD and CAP pins are shorted together inside
the device.

16 15 14 13

12

11

NC

GND

CAP

Power
2.8~3.6V

SCL/SPI_SCK

VDD

10uF
1uF

NC

10

SPI_CS

GND

**<Top View>**
**SPI Single Supply Connection**

MEMSIC MMC5983MA Rev A Page 11 of 20 Formal release date: 4/3/2019

-----

**HARDWARE DESIGN CONSIDERATIONS**
 Provide adequate separation distance to devices
that contain permanent magnets or generate
magnetic fields (e.g. speakers, coils, inductors)
The combined magnetic field to be measured and
interference magnetic field should be less than the
full scale range of the MMC5983MA.
 Provide adequate separation distance to current
carrying traces. Do not route current carrying
traces under the sensor or on the other side of the
PCB opposite to the device.
 Do not cover the sensor with magnetized material
or materials that may become magnetized, (e.g.,
shield box, LCD, battery, iron bearing materials).
 Do not place the device opposite to magnetized
materials or materials that may become
magnetized located on the other side of the PCB.
Please refer to MEMSIC magnetic sensor layout
guideline.

**POWER CONSUMPTION**
The power consumed by the device is proportional to
the number of measurements taken per second. For
example, when BW<1:0> = 00, which is 16-bit mode
with 10ms per measurement, MMC5983MA consumes
450 µA (typical) at 3.0 V with 7 measurements per
second. If only 2 measurements are performed per
second, the current will be 450 * 2 / 7 = 128 µA.

**I** **2** **C INTERFACE DESCRIPTION**
A slave mode I 2 C circuit has been implemented into the
MEMSIC magnetic sensor as a standard interface for
customer applications. The A/D converter functionality
has been added to the MEMSIC sensor, thereby
increasing ease-of-use, and lowering power
consumption, footprint and total solution cost.

The I 2
C (or Inter IC bus) is an industry standard bidirectional two-wire interface bus. A master I 2 C device
can operate READ/WRITE and control up to 128
devices by device addressing. The MEMSIC magnetic
sensor operates only in a slave mode, i.e. only
responding to calls by a Master device to its address.

**I** **2** **C BUS CHARACTERISTICS**

VDD

Rp Rp

SDA (Serial Data Line)

SCL (Serial Clock Line)

DEVICE 1 DEVICE 2

The two wires in the I 2 C bus are called SDA (serial data
line) and SCL (serial clock line). In order for a data
transfer to start, the bus has to be free, which is defined
by both wires in a HIGH output state. Due to the opendrain / pull-up resistor structure and wired Boolean
“AND” operation, any device on the bus can pull lines
low and overwrite a HIGH signal. The data on the SDA
line has to be stable during the HIGH period of the SCL
line. In other words, valid data can only change when
the SCL line is LOW.

Note: Rp selection guide: 2.7K ohm for an I 2 C bus less
than 10 cm length, and 10K ohm for a bus length less
than 5 cm.

VDD

Rp Rp

SDA (Serial Data Line)

SCL (Serial Clock Line)

DEVICE 1

DEVICE 2

MEMSIC MMC5983MA Rev A Page 12 of 20 Formal release date: 4/3/2019

-----

**REGISTER MAP**

|Register Name|Address|Description|
|---|---|---|
|Xout0|00H|Xout [17:10]|
|Xout1|01H|Xout [9:2]|
|Yout0|02H|Yout [17:10]|
|Yout1|03H|Yout [9:2]|
|Zout0|04H|Zout [17:10]|
|Zout1|05H|Zout [9:2]|
|XYZout2|06H|Xout[1:0], Yout[1:0], Zout[1:0]|
|Tout|07H|Temperature output|
|Status|08H|Device status|
|Internal control 0|09H|Control register 0|
|Internal control 1|0AH|Control register 1|
|Internal control 2|0BH|Control register 2|
|Internal control 3|0CH|Control register 3|
|Product ID 1|2FH|Product ID|
