EESchema Schematic File Version 4
LIBS:node-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Humidity sensor node wih 433 MHz RFM69 tranceiver"
Date ""
Rev "A"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_ST_STM32L0:STM32L031K6Tx U4
U 1 1 5CD802CE
P 1650 2400
F 0 "U4" H 1900 1400 50  0000 C CNN
F 1 "STM32L031K6T6" V 1650 2400 50  0000 C CNN
F 2 "Package_QFP:LQFP-32_7x7mm_P0.8mm" H 1150 1500 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00140359.pdf" H 1650 2400 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/stm32l031k6t6/st-microcontrollers/st-microelectronics/" H 1650 2400 50  0001 C CNN "TME Link"
F 5 "20.98" H 1650 2400 50  0001 C CNN "TME Price"
	1    1650 2400
	1    0    0    -1  
$EndComp
$Comp
L humidity:SHTC3 U2
U 1 1 5CD805F1
P 7600 2050
F 0 "U2" H 7300 1750 50  0000 L CNN
F 1 "SHTC3" V 7800 2050 50  0000 C CNN
F 2 "humidity:SHTC3" H 7600 2050 50  0001 C CNN
F 3 "https://www.tme.eu/Document/de9a660213658e76095c62bf61d76ee0/HT_DS_SHTC3_D1.pdf" H 7600 2050 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/shtc3/humidity-sensors/sensirion/3-000-047/" H 0   0   50  0001 C CNN "TME Link"
F 5 "16.93" H 0   0   50  0001 C CNN "TME Price"
	1    7600 2050
	1    0    0    -1  
$EndComp
$Comp
L humidity:AT25DF512C U3
U 1 1 5CD80CB9
P 6250 2100
F 0 "U3" H 6350 1650 50  0000 L CNN
F 1 "AT25DF512C" V 6500 2100 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 6250 2100 50  0001 C CNN
F 3 "https://www.adestotech.com/wp-content/uploads/DS-AT25DF512C_030.pdf" H 6250 2100 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/at25df512c-sshngub/serial-flash-memories-integrated-circ/adesto/at25df512c-sshngu-b/" H 0   0   50  0001 C CNN "TME Link"
F 5 "4.54" H 0   0   50  0001 C CNN "TME Price"
	1    6250 2100
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR02
U 1 1 5CD80DE8
P 3900 750
F 0 "#PWR02" H 3900 600 50  0001 C CNN
F 1 "VCC" H 3917 923 50  0000 C CNN
F 2 "" H 3900 750 50  0001 C CNN
F 3 "" H 3900 750 50  0001 C CNN
	1    3900 750 
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR01
U 1 1 5CD80EC0
P 1550 750
F 0 "#PWR01" H 1550 600 50  0001 C CNN
F 1 "VCC" H 1567 923 50  0000 C CNN
F 2 "" H 1550 750 50  0001 C CNN
F 3 "" H 1550 750 50  0001 C CNN
	1    1550 750 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 1500 1650 1350
Wire Wire Line
	1650 1350 1550 1350
Connection ~ 1550 1350
Wire Wire Line
	1550 1350 1550 1500
Wire Wire Line
	1750 1500 1750 1350
Wire Wire Line
	1750 1350 1650 1350
Connection ~ 1650 1350
$Comp
L power:VCC #PWR03
U 1 1 5CD80F64
P 6250 750
F 0 "#PWR03" H 6250 600 50  0001 C CNN
F 1 "VCC" H 6267 923 50  0000 C CNN
F 2 "" H 6250 750 50  0001 C CNN
F 3 "" H 6250 750 50  0001 C CNN
	1    6250 750 
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 750  6250 950 
$Comp
L Device:C C14
U 1 1 5CD8102B
P 10300 2950
F 0 "C14" H 10185 2904 50  0000 R CNN
F 1 "100n" H 10185 2995 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 10338 2800 50  0001 C CNN
F 3 "~" H 10300 2950 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/cl10b104ko8nnnc/0603-mlcc-smd-capacitors/samsung/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.13310" H 0   0   50  0001 C CNN "TME Price"
	1    10300 2950
	1    0    0    1   
$EndComp
$Comp
L Device:C C6
U 1 1 5CD811AE
P 6050 1200
F 0 "C6" H 5935 1154 50  0000 R CNN
F 1 "100n" H 5935 1245 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 6088 1050 50  0001 C CNN
F 3 "~" H 6050 1200 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/cl10b104ko8nnnc/0603-mlcc-smd-capacitors/samsung/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.13310" H 0   0   50  0001 C CNN "TME Price"
	1    6050 1200
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR011
U 1 1 5CD812DF
P 6050 1450
F 0 "#PWR011" H 6050 1200 50  0001 C CNN
F 1 "GND" H 6055 1277 50  0000 C CNN
F 2 "" H 6050 1450 50  0001 C CNN
F 3 "" H 6050 1450 50  0001 C CNN
	1    6050 1450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 1350 6050 1450
Wire Wire Line
	6050 1050 6050 950 
Wire Wire Line
	6050 950  6250 950 
Wire Wire Line
	3900 750  3900 900 
Connection ~ 6250 950 
Wire Wire Line
	6250 950  6250 1600
$Comp
L power:VCC #PWR05
U 1 1 5CD81DC3
P 7600 800
F 0 "#PWR05" H 7600 650 50  0001 C CNN
F 1 "VCC" H 7617 973 50  0000 C CNN
F 2 "" H 7600 800 50  0001 C CNN
F 3 "" H 7600 800 50  0001 C CNN
	1    7600 800 
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 800  7600 1000
$Comp
L Device:C C7
U 1 1 5CD81DCA
P 7400 1250
F 0 "C7" H 7285 1204 50  0000 R CNN
F 1 "100n" H 7285 1295 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 7438 1100 50  0001 C CNN
F 3 "~" H 7400 1250 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/cl10b104ko8nnnc/0603-mlcc-smd-capacitors/samsung/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.13310" H 0   0   50  0001 C CNN "TME Price"
	1    7400 1250
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR012
U 1 1 5CD81DD0
P 7400 1500
F 0 "#PWR012" H 7400 1250 50  0001 C CNN
F 1 "GND" H 7405 1327 50  0000 C CNN
F 2 "" H 7400 1500 50  0001 C CNN
F 3 "" H 7400 1500 50  0001 C CNN
	1    7400 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 1400 7400 1500
Wire Wire Line
	7400 1100 7400 1000
Wire Wire Line
	7400 1000 7600 1000
Connection ~ 7600 1000
Wire Wire Line
	7600 1000 7600 1700
$Comp
L Device:C C4
U 1 1 5CD81F83
P 3700 1150
F 0 "C4" H 3650 1050 50  0000 R CNN
F 1 "100n" H 3650 1250 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 3738 1000 50  0001 C CNN
F 3 "~" H 3700 1150 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/cl10b104ko8nnnc/0603-mlcc-smd-capacitors/samsung/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.13310" H 0   0   50  0001 C CNN "TME Price"
	1    3700 1150
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR09
U 1 1 5CD81F8A
P 3700 1400
F 0 "#PWR09" H 3700 1150 50  0001 C CNN
F 1 "GND" H 3705 1227 50  0000 C CNN
F 2 "" H 3700 1400 50  0001 C CNN
F 3 "" H 3700 1400 50  0001 C CNN
	1    3700 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 1300 3700 1400
Wire Wire Line
	3700 1000 3700 900 
Wire Wire Line
	3700 900  3900 900 
$Comp
L Device:C C1
U 1 1 5CD821F6
P 2000 1100
F 0 "C1" H 1950 1000 50  0000 R CNN
F 1 "100n" H 1950 1200 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 2038 950 50  0001 C CNN
F 3 "~" H 2000 1100 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/cl10b104ko8nnnc/0603-mlcc-smd-capacitors/samsung/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.13310" H 0   0   50  0001 C CNN "TME Price"
	1    2000 1100
	1    0    0    1   
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5CD821FD
P 2000 1300
F 0 "#PWR06" H 2000 1050 50  0001 C CNN
F 1 "GND" H 2005 1127 50  0000 C CNN
F 2 "" H 2000 1300 50  0001 C CNN
F 3 "" H 2000 1300 50  0001 C CNN
	1    2000 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 1250 2000 1300
Wire Wire Line
	2000 950  2000 850 
Wire Wire Line
	2000 850  1550 850 
Connection ~ 3900 900 
Wire Wire Line
	3900 900  3900 1550
$Comp
L power:GND #PWR018
U 1 1 5CD82875
P 1650 3550
F 0 "#PWR018" H 1650 3300 50  0001 C CNN
F 1 "GND" H 1655 3377 50  0000 C CNN
F 2 "" H 1650 3550 50  0001 C CNN
F 3 "" H 1650 3550 50  0001 C CNN
	1    1650 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 3400 1550 3450
Wire Wire Line
	1550 3450 1650 3450
Wire Wire Line
	1650 3450 1650 3400
Wire Wire Line
	1650 3450 1650 3550
Connection ~ 1650 3450
$Comp
L power:GND #PWR016
U 1 1 5CD831AE
P 3900 2750
F 0 "#PWR016" H 3900 2500 50  0001 C CNN
F 1 "GND" H 3905 2577 50  0000 C CNN
F 2 "" H 3900 2750 50  0001 C CNN
F 3 "" H 3900 2750 50  0001 C CNN
	1    3900 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 2650 3800 2700
Wire Wire Line
	3800 2700 3900 2700
Wire Wire Line
	3900 2650 3900 2700
$Comp
L power:GND #PWR015
U 1 1 5CD84390
P 6250 2650
F 0 "#PWR015" H 6250 2400 50  0001 C CNN
F 1 "GND" H 6255 2477 50  0000 C CNN
F 2 "" H 6250 2650 50  0001 C CNN
F 3 "" H 6250 2650 50  0001 C CNN
	1    6250 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6250 2650 6250 2600
$Comp
L power:GND #PWR014
U 1 1 5CD84ADF
P 7600 2550
F 0 "#PWR014" H 7600 2300 50  0001 C CNN
F 1 "GND" H 7605 2377 50  0000 C CNN
F 2 "" H 7600 2550 50  0001 C CNN
F 3 "" H 7600 2550 50  0001 C CNN
	1    7600 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	10400 2650 10300 2650
Wire Wire Line
	10300 2650 10300 2800
$Comp
L power:GND #PWR031
U 1 1 5CD8691F
P 10300 3150
F 0 "#PWR031" H 10300 2900 50  0001 C CNN
F 1 "GND" H 10305 2977 50  0000 C CNN
F 2 "" H 10300 3150 50  0001 C CNN
F 3 "" H 10300 3150 50  0001 C CNN
	1    10300 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	10300 3100 10300 3150
$Comp
L Device:Crystal Y1
U 1 1 5CD874E3
P 1000 4950
F 0 "Y1" H 1000 4800 50  0000 C CNN
F 1 "32.768K" H 1000 5100 50  0000 C CNN
F 2 "Crystal:Crystal_C26-LF_D2.1mm_L6.5mm_Horizontal" H 1000 4950 50  0001 C CNN
F 3 "" H 1000 4950 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/26-hx5f-32.768k/tht-quartz-crystals/ilsi/26-hx5f12-5-32-768khz/" H 1000 4950 50  0001 C CNN "TME Link"
F 5 "1.52097" H 1000 4950 50  0001 C CNN "TME Price"
	1    1000 4950
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C12
U 1 1 5CD87672
P 750 5200
F 0 "C12" H 700 5100 50  0000 R CNN
F 1 "18p" H 700 5300 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 788 5050 50  0001 C CNN
F 3 "~" H 750 5200 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/vj0603a180jxacw2bc/0603-mlcc-smd-capacitors/vishay/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.13033" H 0   0   50  0001 C CNN "TME Price"
	1    750  5200
	1    0    0    1   
$EndComp
$Comp
L Device:C C13
U 1 1 5CD878C7
P 1250 5200
F 0 "C13" H 1300 5300 50  0000 L CNN
F 1 "18p" H 1300 5100 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 1288 5050 50  0001 C CNN
F 3 "~" H 1250 5200 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/vj0603a180jxacw2bc/0603-mlcc-smd-capacitors/vishay/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.13033" H 0   0   50  0001 C CNN "TME Price"
	1    1250 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	850  4950 750  4950
Wire Wire Line
	750  4950 750  5050
Wire Wire Line
	1150 4950 1250 4950
Wire Wire Line
	1250 4950 1250 5050
$Comp
L power:GND #PWR030
U 1 1 5CD89821
P 1000 5450
F 0 "#PWR030" H 1000 5200 50  0001 C CNN
F 1 "GND" H 1005 5277 50  0000 C CNN
F 2 "" H 1000 5450 50  0001 C CNN
F 3 "" H 1000 5450 50  0001 C CNN
	1    1000 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	750  5350 750  5400
Wire Wire Line
	750  5400 1000 5400
Wire Wire Line
	1000 5400 1000 5450
Wire Wire Line
	1000 5400 1250 5400
Wire Wire Line
	1250 5400 1250 5350
Connection ~ 1000 5400
Wire Wire Line
	1050 2300 550  2300
Wire Wire Line
	1050 2400 550  2400
Text Label 550  2300 0    50   ~ 0
OSC32_IN
Text Label 550  2400 0    50   ~ 0
OSC32_OUT
Wire Wire Line
	750  4950 750  4400
Connection ~ 750  4950
Wire Wire Line
	1250 4950 1250 4400
Connection ~ 1250 4950
Text Label 750  4400 3    50   ~ 0
OSC32_IN
Text Label 1250 4400 3    50   ~ 0
OSC32_OUT
Wire Wire Line
	2150 1700 2750 1700
Wire Wire Line
	2150 1800 2750 1800
Text Label 2750 3200 2    50   ~ 0
LEDR
Wire Wire Line
	2150 1900 2750 1900
Text Label 2750 1900 2    50   ~ 0
USART2_TX
Wire Wire Line
	2150 2000 2750 2000
Text Label 2750 2000 2    50   ~ 0
USART2_RX
Wire Wire Line
	2150 2100 2750 2100
Text Label 2750 2500 2    50   ~ 0
RFM69_INT
Wire Wire Line
	2150 2200 2750 2200
Text Label 2750 2200 2    50   ~ 0
SPI1_SCK
Wire Wire Line
	2150 2300 2750 2300
Text Label 2750 2300 2    50   ~ 0
SPI1_MISO
Wire Wire Line
	2150 2400 2750 2400
Text Label 2750 2400 2    50   ~ 0
SPI1_MOSI
Wire Wire Line
	1050 2600 550  2600
Text Label 2750 2100 2    50   ~ 0
CS_RFM69
Wire Wire Line
	1050 2700 550  2700
Text Label 550  2600 0    50   ~ 0
CS_FLASH
Wire Wire Line
	2150 2600 2750 2600
Text Label 2750 2600 2    50   ~ 0
I2C1_SCL
Wire Wire Line
	2150 2700 2750 2700
Wire Wire Line
	2150 2900 2750 2900
Wire Wire Line
	2150 3000 2750 3000
Text Label 2750 3000 2    50   ~ 0
SWDIO
Wire Wire Line
	2150 3100 2750 3100
Text Label 2750 3100 2    50   ~ 0
SWCLK
Wire Wire Line
	1050 2800 550  2800
Wire Wire Line
	1050 2900 550  2900
Wire Wire Line
	1050 3000 550  3000
Wire Wire Line
	1050 3100 550  3100
Wire Wire Line
	1050 3200 550  3200
Text Label 550  2800 0    50   ~ 0
CONF0
Text Label 550  2900 0    50   ~ 0
CONF1
Text Label 550  3000 0    50   ~ 0
CONF2
Text Label 550  3100 0    50   ~ 0
CONF3
Text Label 550  3200 0    50   ~ 0
CONF4
Text Label 8000 850  0    50   ~ 0
CONF0
Text Label 8000 1100 0    50   ~ 0
CONF1
Text Label 8000 1350 0    50   ~ 0
CONF2
Text Label 8000 1600 0    50   ~ 0
CONF3
Text Label 8000 1850 0    50   ~ 0
CONF4
$Comp
L power:GND #PWR017
U 1 1 5CDBE2FB
P 9000 2050
F 0 "#PWR017" H 9000 1800 50  0001 C CNN
F 1 "GND" H 9005 1877 50  0000 C CNN
F 2 "" H 9000 2050 50  0001 C CNN
F 3 "" H 9000 2050 50  0001 C CNN
	1    9000 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 1750 2900 1750
Text Label 2900 1750 0    50   ~ 0
SPI1_SCK
Wire Wire Line
	3400 1850 2900 1850
Wire Wire Line
	3400 1950 2900 1950
Wire Wire Line
	3400 2050 2900 2050
Text Label 2900 1950 0    50   ~ 0
SPI1_MISO
Text Label 2900 1850 0    50   ~ 0
SPI1_MOSI
Text Label 2900 2050 0    50   ~ 0
CS_RFM69
Wire Wire Line
	4400 2450 4900 2450
Text Label 4900 2450 2    50   ~ 0
RFM69_INT
NoConn ~ 4400 1950
NoConn ~ 4400 2050
NoConn ~ 4400 2150
NoConn ~ 4400 2250
NoConn ~ 4400 2350
Text Label 550  2700 0    50   ~ 0
BAT_MID
Wire Wire Line
	2150 2500 2750 2500
Text Label 2750 1800 2    50   ~ 0
LEDG
Wire Wire Line
	5750 1800 5250 1800
Text Label 5250 1800 0    50   ~ 0
SPI1_SCK
Wire Wire Line
	5750 1900 5250 1900
Text Label 5250 2000 0    50   ~ 0
SPI1_MISO
Text Label 5250 1900 0    50   ~ 0
SPI1_MOSI
Wire Wire Line
	5750 2000 5250 2000
Wire Wire Line
	5750 2100 5250 2100
Text Label 5250 2100 0    50   ~ 0
CS_FLASH
Wire Wire Line
	1050 1700 550  1700
Text Label 550  1700 0    50   ~ 0
STM_RESET
Wire Wire Line
	1050 1900 550  1900
Text Label 550  1900 0    50   ~ 0
BOOT0
$Comp
L power:VCC #PWR037
U 1 1 5CE0883D
P 3400 6550
F 0 "#PWR037" H 3400 6400 50  0001 C CNN
F 1 "VCC" H 3417 6723 50  0000 C CNN
F 2 "" H 3400 6550 50  0001 C CNN
F 3 "" H 3400 6550 50  0001 C CNN
	1    3400 6550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR040
U 1 1 5CE0BAB4
P 3400 7500
F 0 "#PWR040" H 3400 7250 50  0001 C CNN
F 1 "GND" H 3405 7327 50  0000 C CNN
F 2 "" H 3400 7500 50  0001 C CNN
F 3 "" H 3400 7500 50  0001 C CNN
	1    3400 7500
	1    0    0    -1  
$EndComp
Text Label 2250 7050 2    50   ~ 0
BAT_MID
$Comp
L Device:CP1 C15
U 1 1 5CE1224B
P 3100 7050
F 0 "C15" H 3150 7150 50  0000 L CNN
F 1 "22u" H 3150 6950 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_5x5.3" H 3100 7050 50  0001 C CNN
F 3 "~" H 3100 7050 50  0001 C CNN
F 4 "" H 3100 7050 50  0001 C CNN "Part"
F 5 "https://www.tme.eu/se/en/details/sc1e226m05005vr/85degc-smd-electrolytic-capacitors/samwha/" H 0   0   50  0001 C CNN "TME Link"
F 6 "0.36794" H 0   0   50  0001 C CNN "TME Price"
	1    3100 7050
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6750 2000 7200 2000
Text Label 6750 2000 0    50   ~ 0
I2C1_SCL
Text Label 6750 2100 0    50   ~ 0
I2C1_SDA
Wire Wire Line
	6750 2100 7200 2100
Text Label 9550 2650 0    50   ~ 0
STM_RESET
Wire Wire Line
	9550 2650 10300 2650
Connection ~ 10300 2650
$Comp
L power:GND #PWR032
U 1 1 5CE4C513
P 11000 3050
F 0 "#PWR032" H 11000 2800 50  0001 C CNN
F 1 "GND" H 11005 2877 50  0000 C CNN
F 2 "" H 11000 3050 50  0001 C CNN
F 3 "" H 11000 3050 50  0001 C CNN
	1    11000 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	11000 2750 11000 3050
$Comp
L Device:LED D2
U 1 1 5CE64770
P 5250 7250
F 0 "D2" H 5450 7200 50  0000 R CNN
F 1 "KP-2012LSGC" H 5300 7350 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5250 7250 50  0001 C CNN
F 3 "~" H 5250 7250 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/kp-2012lsgc/smd-colour-leds/kingbright-electronic/" H 0   0   50  0001 C CNN "TME Link"
F 5 "1.0520" H 0   0   50  0001 C CNN "TME Price"
	1    5250 7250
	-1   0    0    1   
$EndComp
$Comp
L Device:R R31
U 1 1 5CE64A71
P 4750 7250
F 0 "R31" V 4650 7250 50  0000 C CNN
F 1 "240" V 4750 7250 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 4680 7250 50  0001 C CNN
F 3 "~" H 4750 7250 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/smd0603-240r-1%25/0603-smd-resistors/royal-ohm/0603saf0241t5e/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.11531" H 0   0   50  0001 C CNN "TME Price"
	1    4750 7250
	0    1    1    0   
$EndComp
Text Label 4300 7250 0    50   ~ 0
LEDG
$Comp
L Device:LED D1
U 1 1 5CE7A4C1
P 5250 6800
F 0 "D1" H 5450 6750 50  0000 R CNN
F 1 "KP-2012LSURCK" H 5300 6900 50  0000 C CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5250 6800 50  0001 C CNN
F 3 "~" H 5250 6800 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/kp-2012lsurck/smd-colour-leds/kingbright-electronic/" H 0   0   50  0001 C CNN "TME Link"
F 5 "1.0254" H 0   0   50  0001 C CNN "TME Price"
	1    5250 6800
	-1   0    0    1   
$EndComp
$Comp
L Device:R R30
U 1 1 5CE7A4C7
P 4750 6800
F 0 "R30" V 4850 6800 50  0000 C CNN
F 1 "330" V 4750 6800 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 4680 6800 50  0001 C CNN
F 3 "~" H 4750 6800 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/smd0603-330r-1%25/0603-smd-resistors/royal-ohm/0603saf3300t5e/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.11531" H 0   0   50  0001 C CNN "TME Price"
	1    4750 6800
	0    -1   -1   0   
$EndComp
Text Label 4300 6800 0    50   ~ 0
LEDR
$Comp
L power:GND #PWR022
U 1 1 5CE99F9C
P 10300 1650
F 0 "#PWR022" H 10300 1400 50  0001 C CNN
F 1 "GND" H 10305 1477 50  0000 C CNN
F 2 "" H 10300 1650 50  0001 C CNN
F 3 "" H 10300 1650 50  0001 C CNN
	1    10300 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	10300 1250 9550 1250
Text Label 9550 1250 0    50   ~ 0
BOOT0
$Comp
L power:VCC #PWR019
U 1 1 5CEAC8F0
P 10300 1050
F 0 "#PWR019" H 10300 900 50  0001 C CNN
F 1 "VCC" H 10317 1223 50  0000 C CNN
F 2 "" H 10300 1050 50  0001 C CNN
F 3 "" H 10300 1050 50  0001 C CNN
	1    10300 1050
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR013
U 1 1 5CEDD223
P 5100 2200
F 0 "#PWR013" H 5100 2050 50  0001 C CNN
F 1 "VCC" H 5117 2373 50  0000 C CNN
F 2 "" H 5100 2200 50  0001 C CNN
F 3 "" H 5100 2200 50  0001 C CNN
	1    5100 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5100 2200 5100 2300
Wire Wire Line
	5100 2300 5750 2300
Wire Wire Line
	5750 2400 5100 2400
Wire Wire Line
	5100 2400 5100 2300
Connection ~ 5100 2300
$Comp
L Connector:Conn_01x06_Male J2
U 1 1 5CEF1C88
P 4600 4800
F 0 "J2" H 4700 5100 50  0000 R CNN
F 1 "FTDI" H 4700 4350 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Horizontal" H 4600 4800 50  0001 C CNN
F 3 "~" H 4600 4800 50  0001 C CNN
	1    4600 4800
	1    0    0    1   
$EndComp
Text Notes 4550 5050 2    50   ~ 0
GND
Text Notes 4550 4950 2    50   ~ 0
CTS
Text Notes 4550 4850 2    50   ~ 0
VCC
Text Notes 4550 4750 2    50   ~ 0
TXD
Text Notes 4550 4650 2    50   ~ 0
RXD
Text Notes 4550 4550 2    50   ~ 0
DTR/RTS
$Comp
L Device:R R14
U 1 1 5CEF79DC
P 5650 4600
F 0 "R14" V 5550 4600 50  0000 C CNN
F 1 "330" V 5650 4600 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 5580 4600 50  0001 C CNN
F 3 "~" H 5650 4600 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/smd0603-330r-1%25/0603-smd-resistors/royal-ohm/0603saf3300t5e/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.11531" H 0   0   50  0001 C CNN "TME Price"
	1    5650 4600
	0    -1   1    0   
$EndComp
$Comp
L Device:R R16
U 1 1 5CF072C0
P 5650 4700
F 0 "R16" V 5550 4700 50  0000 C CNN
F 1 "330" V 5650 4700 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 5580 4700 50  0001 C CNN
F 3 "~" H 5650 4700 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/smd0603-330r-1%25/0603-smd-resistors/royal-ohm/0603saf3300t5e/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.11531" H 0   0   50  0001 C CNN "TME Price"
	1    5650 4700
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4800 4700 5350 4700
Wire Wire Line
	4750 4600 4800 4600
$Comp
L Device:R R11
U 1 1 5CF1C5B8
P 5650 4150
F 0 "R11" V 5550 4150 50  0000 C CNN
F 1 "DNP" V 5650 4150 50  0000 C CNN
F 2 "humidity:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder-DNP" V 5580 4150 50  0001 C CNN
F 3 "~" H 5650 4150 50  0001 C CNN
F 4 "330" V 5650 4150 50  0001 C CNN "DNPValue"
F 5 "-" H 0   0   50  0001 C CNN "TME Link"
	1    5650 4150
	0    -1   1    0   
$EndComp
$Comp
L Device:R R12
U 1 1 5CF1C5BF
P 5650 4250
F 0 "R12" V 5550 4250 50  0000 C CNN
F 1 "DNP" V 5650 4250 50  0000 C CNN
F 2 "humidity:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder-DNP" V 5580 4250 50  0001 C CNN
F 3 "~" H 5650 4250 50  0001 C CNN
F 4 "330" V 5650 4250 50  0001 C CNN "DNPValue"
F 5 "-" H 0   0   50  0001 C CNN "TME Link"
	1    5650 4250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5500 4250 5450 4250
Wire Wire Line
	5450 4250 5450 4600
Connection ~ 5450 4600
Wire Wire Line
	5450 4600 5500 4600
Wire Wire Line
	5500 4150 5350 4150
Wire Wire Line
	5350 4150 5350 4700
Connection ~ 5350 4700
Wire Wire Line
	5350 4700 5500 4700
Wire Wire Line
	5800 4600 5950 4600
Wire Wire Line
	5950 4600 5950 4150
Wire Wire Line
	5950 4150 5800 4150
Wire Wire Line
	5800 4250 5850 4250
Wire Wire Line
	5850 4250 5850 4700
Wire Wire Line
	5850 4700 5800 4700
Wire Wire Line
	5950 4600 6450 4600
Connection ~ 5950 4600
Wire Wire Line
	5850 4700 6450 4700
Connection ~ 5850 4700
Text Notes 5350 5100 0    50   ~ 0
Populate only\none set of \nresistors
$Comp
L power:GND #PWR029
U 1 1 5CF5D50D
P 4900 5350
F 0 "#PWR029" H 4900 5100 50  0001 C CNN
F 1 "GND" H 4905 5177 50  0000 C CNN
F 2 "" H 4900 5350 50  0001 C CNN
F 3 "" H 4900 5350 50  0001 C CNN
	1    4900 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 5000 4800 5000
$Comp
L Connector:Conn_01x04_Male J5
U 1 1 5CF6A4AC
P 6400 7300
F 0 "J5" H 6500 7450 50  0000 R CNN
F 1 "SWD" H 6500 7000 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Horizontal" H 6400 7300 50  0001 C CNN
F 3 "~" H 6400 7300 50  0001 C CNN
	1    6400 7300
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR041
U 1 1 5CF7DCC7
P 6100 7500
F 0 "#PWR041" H 6100 7250 50  0001 C CNN
F 1 "GND" H 6105 7327 50  0000 C CNN
F 2 "" H 6100 7500 50  0001 C CNN
F 3 "" H 6100 7500 50  0001 C CNN
	1    6100 7500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 7400 6100 7400
Wire Wire Line
	6100 7400 6100 7500
$Comp
L power:VCC #PWR038
U 1 1 5CF84561
P 6100 7000
F 0 "#PWR038" H 6100 6850 50  0001 C CNN
F 1 "VCC" H 6117 7173 50  0000 C CNN
F 2 "" H 6100 7000 50  0001 C CNN
F 3 "" H 6100 7000 50  0001 C CNN
	1    6100 7000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 7000 6100 7100
Wire Wire Line
	6100 7100 6200 7100
Text Label 5750 7200 0    50   ~ 0
SWDIO
Text Label 5750 7300 0    50   ~ 0
SWCLK
Wire Wire Line
	6200 7200 5750 7200
Wire Wire Line
	5750 7300 6200 7300
Text Label 1950 5150 2    50   ~ 0
I2C1_SCL
Wire Wire Line
	1950 5150 2100 5150
Text Label 1950 5250 2    50   ~ 0
I2C1_SDA
Wire Wire Line
	1950 5250 2300 5250
Text Label 1950 5450 2    50   ~ 0
CS_RFM69
Text Label 1950 5550 2    50   ~ 0
CS_FLASH
$Comp
L Device:R R18
U 1 1 5CFD71E1
P 2100 4950
F 0 "R18" V 2200 4950 50  0000 C CNN
F 1 "4k7" V 2100 4950 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 2030 4950 50  0001 C CNN
F 3 "~" H 2100 4950 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/smd0603-4k7-1%25/0603-smd-resistors/royal-ohm/0603saf4701t5e/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.115131" H 0   0   50  0001 C CNN "TME Price"
	1    2100 4950
	-1   0    0    1   
$EndComp
$Comp
L Device:R R19
U 1 1 5CFD74C7
P 2300 4950
F 0 "R19" V 2400 4950 50  0000 C CNN
F 1 "4k7" V 2300 4950 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 2230 4950 50  0001 C CNN
F 3 "~" H 2300 4950 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/smd0603-4k7-1%25/0603-smd-resistors/royal-ohm/0603saf4701t5e/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.115131" H 0   0   50  0001 C CNN "TME Price"
	1    2300 4950
	-1   0    0    1   
$EndComp
$Comp
L Device:R R20
U 1 1 5CFD7525
P 2500 4950
F 0 "R20" V 2600 4950 50  0000 C CNN
F 1 "100k" V 2500 4950 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 2430 4950 50  0001 C CNN
F 3 "~" H 2500 4950 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/cq0603-100k-1%25/0603-smd-resistors/royal-ohm/cq03saf1003t5e/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.18525" H 0   0   50  0001 C CNN "TME Price"
	1    2500 4950
	-1   0    0    1   
$EndComp
$Comp
L Device:R R21
U 1 1 5CFD7585
P 2700 4950
F 0 "R21" V 2800 4950 50  0000 C CNN
F 1 "100k" V 2700 4950 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 2630 4950 50  0001 C CNN
F 3 "~" H 2700 4950 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/cq0603-100k-1%25/0603-smd-resistors/royal-ohm/cq03saf1003t5e/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.18525" H 0   0   50  0001 C CNN "TME Price"
	1    2700 4950
	-1   0    0    1   
$EndComp
Wire Wire Line
	2950 5450 2500 5450
Wire Wire Line
	1950 5550 2700 5550
Wire Wire Line
	2100 5100 2100 5150
Connection ~ 2100 5150
Wire Wire Line
	2100 5150 2950 5150
Wire Wire Line
	2300 5100 2300 5250
Connection ~ 2300 5250
Wire Wire Line
	2300 5250 2950 5250
Wire Wire Line
	2500 5100 2500 5450
Connection ~ 2500 5450
Wire Wire Line
	2500 5450 1950 5450
Wire Wire Line
	2700 5100 2700 5550
Connection ~ 2700 5550
Wire Wire Line
	2700 5550 2950 5550
$Comp
L power:VCC #PWR023
U 1 1 5D0129B6
P 2100 4700
F 0 "#PWR023" H 2100 4550 50  0001 C CNN
F 1 "VCC" H 2117 4873 50  0000 C CNN
F 2 "" H 2100 4700 50  0001 C CNN
F 3 "" H 2100 4700 50  0001 C CNN
	1    2100 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 4700 2100 4750
Wire Wire Line
	2100 4750 2300 4750
Wire Wire Line
	2300 4750 2300 4800
Connection ~ 2100 4750
Wire Wire Line
	2100 4750 2100 4800
Wire Wire Line
	2300 4750 2500 4750
Wire Wire Line
	2500 4750 2500 4800
Connection ~ 2300 4750
Wire Wire Line
	2500 4750 2700 4750
Wire Wire Line
	2700 4750 2700 4800
Connection ~ 2500 4750
Wire Notes Line
	500  5700 1500 5700
Wire Notes Line
	1500 5700 1500 4200
Wire Notes Line
	1500 4200 500  4200
Wire Notes Line
	500  4200 500  5700
Text Notes 550  4350 0    75   Italic 15
RTC Crystal
Text Notes 550  6350 0    75   Italic 15
Power
Text Notes 8000 650  0    75   Italic 15
Configuration
Text Notes 1600 4350 0    75   Italic 15
SPI/I2C pull-ups
Text Notes 5750 6850 0    75   Italic 15
SWD
Text Notes 4200 3900 0    75   Italic 15
FTDI
Text Notes 9500 800  0    75   Italic 15
Boot mode\nand reset
Text Notes 4100 6650 0    75   Italic 15
LEDs
Wire Notes Line
	4000 7750 4000 6200
Wire Notes Line
	4000 6200 500  6200
Wire Notes Line
	500  6200 500  7750
Wire Notes Line
	500  7750 4000 7750
Wire Notes Line
	7950 2300 7950 500 
Wire Notes Line
	7950 500  9150 500 
Wire Notes Line
	9150 500  9150 2300
Wire Notes Line
	9150 2300 7950 2300
Wire Notes Line
	5700 6700 6450 6700
Wire Notes Line
	6450 6700 6450 7750
Wire Notes Line
	6450 7750 5700 7750
Wire Notes Line
	5700 7750 5700 6700
Wire Notes Line
	3000 4200 3000 5650
Wire Notes Line
	3000 5650 1550 5650
Wire Notes Line
	1550 5650 1550 4200
Wire Notes Line
	1550 4200 3000 4200
Wire Notes Line
	4200 3750 7100 3750
Wire Notes Line
	7100 3750 7100 5600
Wire Notes Line
	7100 5600 4200 5600
Wire Notes Line
	4200 3750 4200 5600
Wire Notes Line
	4050 6500 5650 6500
Wire Notes Line
	5650 6500 5650 7750
Wire Notes Line
	5650 7750 4050 7750
Wire Notes Line
	9450 500  11200 500 
Text Notes 6700 650  0    75   Italic 15
SHTC3
Text Notes 6700 1050 0    75   ~ 0
Humidity and\ntemperature\nsensor
Text Notes 6700 2650 0    75   ~ 0
I2C address:\n0x70
Wire Notes Line
	7900 2800 6650 2800
Wire Notes Line
	6650 2800 6650 500 
Wire Notes Line
	6650 500  7900 500 
Wire Notes Line
	7900 500  7900 2800
Text Notes 5050 650  0    75   Italic 15
SPI Flash
Wire Notes Line
	5000 2900 5000 500 
Wire Notes Line
	5000 500  6600 500 
Wire Notes Line
	6600 500  6600 2900
Wire Notes Line
	5000 2900 6600 2900
Text Notes 2900 650  0    75   Italic 15
RFM69
Text Notes 2900 950  0    75   ~ 0
433 MHz\ntranciever
Wire Wire Line
	4400 1750 4900 1750
Wire Notes Line
	2850 500  4950 500 
Wire Notes Line
	4950 500  4950 3100
Wire Notes Line
	4950 3100 2850 3100
Wire Notes Line
	2850 500  2850 3100
Text Notes 600  750  0    75   Italic 15
STM32L031
Wire Notes Line
	2800 500  2800 3800
Wire Notes Line
	2800 3800 500  3800
Wire Notes Line
	500  3800 500  500 
Wire Notes Line
	500  500  2800 500 
NoConn ~ 4800 4500
NoConn ~ 4800 4900
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5D147A7D
P 3800 6550
F 0 "#FLG01" H 3800 6625 50  0001 C CNN
F 1 "PWR_FLAG" H 3800 6724 50  0000 C CNN
F 2 "" H 3800 6550 50  0001 C CNN
F 3 "~" H 3800 6550 50  0001 C CNN
	1    3800 6550
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG02
U 1 1 5D151979
P 3800 7500
F 0 "#FLG02" H 3800 7575 50  0001 C CNN
F 1 "PWR_FLAG" H 3800 7673 50  0000 C CNN
F 2 "" H 3800 7500 50  0001 C CNN
F 3 "~" H 3800 7500 50  0001 C CNN
	1    3800 7500
	-1   0    0    1   
$EndComp
Text Notes 500  3950 0    75   ~ 0
Check that bootloader works on UART2 on PA2/PA3
Text Notes 500  4050 0    75   ~ 0
Connect unused IO with a pull-up/down
$Comp
L Device:Q_PMOS_GSD Q1
U 1 1 5CE46C28
P 2650 6750
F 0 "Q1" V 2993 6750 50  0000 C CNN
F 1 "Si2323DDS" V 2902 6750 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23_Handsoldering" H 2850 6850 50  0001 C CNN
F 3 "~" H 2650 6750 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/si2323dds-t1-ge3/smd-p-channel-transistors/vishay/" H 0   0   50  0001 C CNN "TME Link"
F 5 "3.34344" H 0   0   50  0001 C CNN "TME Price"
	1    2650 6750
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2650 6950 2650 7450
Wire Wire Line
	2850 6650 3100 6650
Wire Wire Line
	3100 6650 3100 6900
Wire Wire Line
	3100 7200 3100 7450
Wire Wire Line
	3100 7450 2650 7450
Connection ~ 2650 7450
Wire Wire Line
	3400 6650 3400 6550
Connection ~ 3100 6650
Wire Wire Line
	3400 6650 3800 6650
Wire Wire Line
	3800 6650 3800 6550
Connection ~ 3400 6650
Wire Wire Line
	3400 7500 3400 7450
Wire Wire Line
	3400 7450 3100 7450
Connection ~ 3100 7450
Wire Wire Line
	3400 7450 3800 7450
Wire Wire Line
	3800 7450 3800 7500
Connection ~ 3400 7450
Text Notes 2600 7400 1    50   ~ 0
or DMP2045U\nor DMG3415U-7
Text Notes 2750 7400 1    35   ~ 0
|Vgs(th)| <= 1V
Wire Wire Line
	2150 3200 2750 3200
Text Label 2750 1700 2    50   ~ 0
SW
$Comp
L power:GND #PWR028
U 1 1 5CF2CE2C
P 4000 5200
F 0 "#PWR028" H 4000 4950 50  0001 C CNN
F 1 "GND" H 4005 5027 50  0000 C CNN
F 2 "" H 4000 5200 50  0001 C CNN
F 3 "" H 4000 5200 50  0001 C CNN
	1    4000 5200
	1    0    0    -1  
$EndComp
Text Notes 4350 2750 0    40   ~ 0
RX: PayloadReady \n    (Mapping 01)\nTX: PacketSent\n    (Mapping 00)
$Comp
L Connector:Conn_Coaxial J3
U 1 1 5CF38B55
P 4850 5950
F 0 "J3" H 4949 5926 50  0000 L CNN
F 1 "SMA Female" H 4949 5835 50  0000 L CNN
F 2 "humidity:Adam_Tech_SMA_Female_RF2-19A" H 4850 5950 50  0001 C CNN
F 3 "https://www.tme.eu/Document/bd1bc003b249b3f9362db618e35fe545/RF2-19A-T-00-50-G.pdf" H 4850 5950 50  0001 C CNN
F 4 "RF2-03E-T-00-50-G" H 5000 6100 50  0000 C BNN "Part"
F 5 "https://www.tme.eu/se/en/details/rf2-03e-t-00-50-g/sma-smb-smc-connectors/adam-tech/" H 0   0   50  0001 C CNN "TME Link"
F 6 "12.76" H 0   0   50  0001 C CNN "TME Price"
	1    4850 5950
	1    0    0    -1  
$EndComp
Text Label 4900 1750 2    50   ~ 0
ANT
Text Label 4100 5950 0    50   ~ 0
ANT
Wire Wire Line
	4100 5950 4650 5950
$Comp
L power:GND #PWR036
U 1 1 5CF705CB
P 4850 6200
F 0 "#PWR036" H 4850 5950 50  0001 C CNN
F 1 "GND" H 4855 6027 50  0000 C CNN
F 2 "" H 4850 6200 50  0001 C CNN
F 3 "" H 4850 6200 50  0001 C CNN
	1    4850 6200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 6150 4850 6200
Text Notes 4100 5800 0    75   Italic 15
Antenna
Wire Notes Line
	4050 5650 5450 5650
Wire Notes Line
	5450 5650 5450 6450
Wire Notes Line
	5450 6450 4050 6450
Wire Notes Line
	4050 6450 4050 5650
Text Notes 3100 4350 0    75   Italic 15
Unused Pins
Wire Notes Line
	3050 4200 4150 4200
Wire Notes Line
	4150 5450 3050 5450
Wire Notes Line
	3050 5450 3050 4200
Text Label 1300 6650 0    50   ~ 0
V_BAT
Text Notes 2900 1600 0    40   ~ 0
CPOL=0\nCPHA=0\nCS active low
Text Notes 5100 1600 0    40   ~ 0
CPOL=0  or  CPOL=1\nCPHA=0      CPHA=1\nCS active low
$Comp
L power:GND #PWR010
U 1 1 5D1BEC46
P 4100 1400
F 0 "#PWR010" H 4100 1150 50  0001 C CNN
F 1 "GND" H 4105 1227 50  0000 C CNN
F 2 "" H 4100 1400 50  0001 C CNN
F 3 "" H 4100 1400 50  0001 C CNN
	1    4100 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 1400 4100 1300
Wire Wire Line
	4100 1000 4100 900 
Wire Wire Line
	4100 900  3900 900 
Wire Wire Line
	2250 7050 1750 7050
Wire Wire Line
	1750 7100 1750 7050
Connection ~ 1750 7050
Wire Wire Line
	1750 7050 1600 7050
Wire Wire Line
	1750 7400 1750 7450
Connection ~ 1750 7450
Wire Wire Line
	1750 7450 2650 7450
$Comp
L Device:R R32
U 1 1 5D265FEC
P 1450 7050
F 0 "R32" V 1550 7050 50  0000 C CNN
F 1 "10k" V 1450 7050 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 1380 7050 50  0001 C CNN
F 3 "~" H 1450 7050 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/crcw060310k0fktabc/0603-smd-resistors/vishay/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.12458" H 0   0   50  0001 C CNN "TME Price"
	1    1450 7050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1550 750  1550 850 
Connection ~ 1550 850 
Wire Wire Line
	1550 850  1550 1350
$Comp
L Device:C C2
U 1 1 5D2A1EAF
P 2300 1100
F 0 "C2" H 2250 1000 50  0000 R CNN
F 1 "100n" H 2250 1200 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 2338 950 50  0001 C CNN
F 3 "~" H 2300 1100 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/cl10b104ko8nnnc/0603-mlcc-smd-capacitors/samsung/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.13310" H 0   0   50  0001 C CNN "TME Price"
	1    2300 1100
	1    0    0    1   
$EndComp
$Comp
L Device:C C3
U 1 1 5D2A1F2B
P 2600 1100
F 0 "C3" H 2550 1000 50  0000 R CNN
F 1 "100n" H 2550 1200 50  0000 R CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 2638 950 50  0001 C CNN
F 3 "~" H 2600 1100 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/cl10b104ko8nnnc/0603-mlcc-smd-capacitors/samsung/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.13310" H 0   0   50  0001 C CNN "TME Price"
	1    2600 1100
	1    0    0    1   
$EndComp
Wire Wire Line
	2000 850  2300 850 
Wire Wire Line
	2300 850  2300 950 
Connection ~ 2000 850 
Wire Wire Line
	2300 850  2600 850 
Wire Wire Line
	2600 850  2600 950 
Connection ~ 2300 850 
$Comp
L power:GND #PWR07
U 1 1 5D2C0293
P 2300 1300
F 0 "#PWR07" H 2300 1050 50  0001 C CNN
F 1 "GND" H 2305 1127 50  0000 C CNN
F 2 "" H 2300 1300 50  0001 C CNN
F 3 "" H 2300 1300 50  0001 C CNN
	1    2300 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5D2C0304
P 2600 1300
F 0 "#PWR08" H 2600 1050 50  0001 C CNN
F 1 "GND" H 2605 1127 50  0000 C CNN
F 2 "" H 2600 1300 50  0001 C CNN
F 3 "" H 2600 1300 50  0001 C CNN
	1    2600 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 1300 2600 1250
Wire Wire Line
	2300 1250 2300 1300
Wire Wire Line
	2150 2800 2750 2800
Text Label 2750 2900 2    50   ~ 0
PA12
Text Label 3100 4850 0    50   ~ 0
PA12
Wire Wire Line
	4600 6800 4300 6800
Wire Wire Line
	5100 6800 4900 6800
Wire Wire Line
	5100 7250 4900 7250
Wire Wire Line
	4600 7250 4300 7250
$Comp
L power:GND #PWR039
U 1 1 5CE94230
P 5550 7400
F 0 "#PWR039" H 5550 7150 50  0001 C CNN
F 1 "GND" H 5555 7227 50  0000 C CNN
F 2 "" H 5550 7400 50  0001 C CNN
F 3 "" H 5550 7400 50  0001 C CNN
	1    5550 7400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 7250 5550 7250
Wire Wire Line
	5550 7250 5550 7400
Wire Wire Line
	5400 6800 5550 6800
Text Notes 4300 7000 0    40   ~ 0
TIM2_CH1\nVf=1.75V\nIf(2.4V)=1.97mA
Text Notes 4300 7450 0    40   ~ 0
TIM2_CH2\nVf=1.9V\nIf(2.4V)=2.08mA
Wire Wire Line
	5550 6800 5550 7250
Connection ~ 5550 7250
Wire Notes Line
	4150 4200 4150 5450
Wire Notes Line
	4050 6500 4050 7750
$Comp
L Connector:Conn_01x02_Male J1
U 1 1 5D574B6A
P 10650 1250
F 0 "J1" H 10750 1350 50  0000 R CNN
F 1 "BOOT0_Jumper" V 10550 1200 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 10650 1250 50  0001 C CNN
F 3 "~" H 10650 1250 50  0001 C CNN
	1    10650 1250
	-1   0    0    1   
$EndComp
$Comp
L Device:R R13
U 1 1 5D5753D0
P 10300 1450
F 0 "R13" V 10200 1450 50  0000 C CNN
F 1 "10k" V 10300 1450 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 10230 1450 50  0001 C CNN
F 3 "~" H 10300 1450 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/crcw060310k0fktabc/0603-smd-resistors/vishay/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.12458" H 0   0   50  0001 C CNN "TME Price"
	1    10300 1450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	10300 1650 10300 1600
Wire Wire Line
	10300 1250 10300 1300
Wire Wire Line
	10450 1250 10300 1250
Connection ~ 10300 1250
Wire Wire Line
	10300 1050 10300 1150
Wire Wire Line
	10300 1150 10450 1150
$Comp
L Device:R R17
U 1 1 5D5F18B0
P 3800 4850
F 0 "R17" V 3700 4850 50  0000 C CNN
F 1 "100k" V 3800 4850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 3730 4850 50  0001 C CNN
F 3 "~" H 3800 4850 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/cq0603-100k-1%25/0603-smd-resistors/royal-ohm/cq03saf1003t5e/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.18525" H 0   0   50  0001 C CNN "TME Price"
	1    3800 4850
	0    1    1    0   
$EndComp
Wire Wire Line
	3650 4850 3100 4850
Wire Wire Line
	3950 4850 4000 4850
Wire Wire Line
	8800 850  9000 850 
Wire Wire Line
	8500 1350 8000 1350
Wire Wire Line
	8500 1600 8000 1600
Wire Wire Line
	8500 1850 8000 1850
$Comp
L Device:R R1
U 1 1 5D9745BE
P 8650 850
F 0 "R1" V 8750 850 50  0000 C CNN
F 1 "0" V 8650 850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 8580 850 50  0001 C CNN
F 3 "~" H 8650 850 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/smd0603-0r/0603-smd-resistors/royal-ohm/0603saj0000t5e/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.09735" H 0   0   50  0001 C CNN "TME Price"
	1    8650 850 
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R2
U 1 1 5D9746CD
P 8650 1100
F 0 "R2" V 8750 1100 50  0000 C CNN
F 1 "0" V 8650 1100 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 8580 1100 50  0001 C CNN
F 3 "~" H 8650 1100 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/smd0603-0r/0603-smd-resistors/royal-ohm/0603saj0000t5e/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.09735" H 0   0   50  0001 C CNN "TME Price"
	1    8650 1100
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R3
U 1 1 5D97474D
P 8650 1350
F 0 "R3" V 8750 1350 50  0000 C CNN
F 1 "0" V 8650 1350 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 8580 1350 50  0001 C CNN
F 3 "~" H 8650 1350 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/smd0603-0r/0603-smd-resistors/royal-ohm/0603saj0000t5e/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.09735" H 0   0   50  0001 C CNN "TME Price"
	1    8650 1350
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R4
U 1 1 5D9747CF
P 8650 1600
F 0 "R4" V 8750 1600 50  0000 C CNN
F 1 "0" V 8650 1600 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 8580 1600 50  0001 C CNN
F 3 "~" H 8650 1600 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/smd0603-0r/0603-smd-resistors/royal-ohm/0603saj0000t5e/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.09735" H 0   0   50  0001 C CNN "TME Price"
	1    8650 1600
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R5
U 1 1 5D974853
P 8650 1850
F 0 "R5" V 8750 1850 50  0000 C CNN
F 1 "0" V 8650 1850 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 8580 1850 50  0001 C CNN
F 3 "~" H 8650 1850 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/smd0603-0r/0603-smd-resistors/royal-ohm/0603saj0000t5e/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.09735" H 0   0   50  0001 C CNN "TME Price"
	1    8650 1850
	0    -1   -1   0   
$EndComp
Text Notes 6050 5050 0    40   ~ 0
PA3 (USART2_RX) is 5V tolerant\nso it should be safe to connect\nit directly to 3.3V FTDI cable
Text Notes 6050 4400 0    40   ~ 0
FT232R (used in FTDI cable)\nhas a input switching voltage \nof max 1.5V so it should be \nfine to drive it directly at \neg 2.4 V
$Comp
L Device:R R34
U 1 1 5DCECCD3
P 3100 2450
F 0 "R34" V 3000 2450 50  0000 C CNN
F 1 "100k" V 3100 2450 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 3030 2450 50  0001 C CNN
F 3 "~" H 3100 2450 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/cq0603-100k-1%25/0603-smd-resistors/royal-ohm/cq03saf1003t5e/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.18525" H 0   0   50  0001 C CNN "TME Price"
	1    3100 2450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3400 2250 3100 2250
Wire Wire Line
	3100 2250 3100 2300
$Comp
L power:GND #PWR043
U 1 1 5DD046B2
P 3100 2700
F 0 "#PWR043" H 3100 2450 50  0001 C CNN
F 1 "GND" H 3105 2527 50  0000 C CNN
F 2 "" H 3100 2700 50  0001 C CNN
F 3 "" H 3100 2700 50  0001 C CNN
	1    3100 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3100 2600 3100 2700
Text Notes 2900 3050 0    40   ~ 0
It seems like the reset \npin can be left floating
$Comp
L Device:R R33
U 1 1 5DDC161F
P 10300 2400
F 0 "R33" V 10400 2400 50  0000 C CNN
F 1 "10k" V 10300 2400 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 10230 2400 50  0001 C CNN
F 3 "~" H 10300 2400 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/crcw060310k0fktabc/0603-smd-resistors/vishay/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.12458" H 0   0   50  0001 C CNN "TME Price"
	1    10300 2400
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR042
U 1 1 5DE37299
P 10300 2200
F 0 "#PWR042" H 10300 2050 50  0001 C CNN
F 1 "VCC" H 10317 2373 50  0000 C CNN
F 2 "" H 10300 2200 50  0001 C CNN
F 3 "" H 10300 2200 50  0001 C CNN
	1    10300 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	10300 2200 10300 2250
Wire Wire Line
	10300 2550 10300 2650
$Comp
L Device:CP1 C5
U 1 1 5DEC8EEA
P 4100 1150
F 0 "C5" H 4150 1250 50  0000 L CNN
F 1 "22u" H 4150 1050 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_5x5.3" H 4100 1150 50  0001 C CNN
F 3 "~" H 4100 1150 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/sc1e226m05005vr/85degc-smd-electrolytic-capacitors/samwha/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.36794" H 0   0   50  0001 C CNN "TME Price"
	1    4100 1150
	1    0    0    -1  
$EndComp
$Comp
L humidity:SW_Push_4pin SW1
U 1 1 5DEFB807
P 10650 2650
F 0 "SW1" H 10750 2800 40  0000 C CNN
F 1 "DTSM-65R-V-B" H 10650 2450 40  0000 C CNN
F 2 "humidity:SW_SPST_DTSM-6" H 10650 2650 40  0001 C CNN
F 3 "https://www.tme.eu/se/en/details/dtsm-65r-v-b/microswitches-tact/diptronics/" H 10650 2650 40  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/dtsm-65r-v-b/microswitches-tact/diptronics/" H 0   100 50  0001 C CNN "TME Link"
F 5 "1.8894" H 0   100 50  0001 C CNN "TME Price"
	1    10650 2650
	1    0    0    -1  
$EndComp
NoConn ~ 10900 2650
NoConn ~ 10400 2750
Text Notes 4100 7700 0    40   ~ 0
Vary duty cycle linearly  depending\non VCC to get constant luminosity
$Comp
L Diode:1N4148W D3
U 1 1 5DF5C846
P 1750 7250
F 0 "D3" V 1704 7330 50  0000 L CNN
F 1 "1N4148W" V 1795 7330 50  0000 L CNN
F 2 "Diode_SMD:D_SOD-123" H 1750 7075 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 1750 7250 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/1n4148w-7-f/smd-universal-diodes/diodes-incorporated/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.2481" H 0   0   50  0001 C CNN "TME Price"
	1    1750 7250
	0    1    1    0   
$EndComp
Text Label 6450 4700 2    50   ~ 0
USART2_RX
Text Label 6450 4600 2    50   ~ 0
USART2_TX
Wire Wire Line
	4900 5000 4900 5350
NoConn ~ 4800 4800
Text Notes 11150 3700 2    40   ~ 0
"The recommended value of\n100 nF for the [reset] capacitor \ncan be reduced to 10 nF to limit \npower consumption." (AN4467)
Wire Notes Line
	9450 3750 11200 3750
Wire Notes Line
	11200 500  11200 3750
Wire Notes Line
	9450 3750 9450 500 
$Comp
L Mechanical:MountingHole H1
U 1 1 5E031363
P 10400 4100
F 0 "H1" H 10500 4146 50  0000 L CNN
F 1 "MountingHole M3" H 10500 4055 50  0000 L CNN
F 2 "humidity:MountingHole_3.2mm_M3" H 10400 4100 50  0001 C CNN
F 3 "~" H 10400 4100 50  0001 C CNN
F 4 "-" H 0   0   50  0001 C CNN "TME Link"
	1    10400 4100
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 5E031864
P 10400 4300
F 0 "H2" H 10500 4346 50  0000 L CNN
F 1 "MountingHole M3" H 10500 4255 50  0000 L CNN
F 2 "humidity:MountingHole_3.2mm_M3" H 10400 4300 50  0001 C CNN
F 3 "~" H 10400 4300 50  0001 C CNN
F 4 "-" H 0   0   50  0001 C CNN "TME Link"
	1    10400 4300
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 5E0318E6
P 10400 4500
F 0 "H3" H 10500 4546 50  0000 L CNN
F 1 "MountingHole M3" H 10500 4455 50  0000 L CNN
F 2 "humidity:MountingHole_3.2mm_M3" H 10400 4500 50  0001 C CNN
F 3 "~" H 10400 4500 50  0001 C CNN
F 4 "-" H 0   0   50  0001 C CNN "TME Link"
	1    10400 4500
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 5E03196A
P 10400 4700
F 0 "H4" H 10500 4746 50  0000 L CNN
F 1 "MountingHole M3" H 10500 4655 50  0000 L CNN
F 2 "humidity:MountingHole_3.2mm_M3" H 10400 4700 50  0001 C CNN
F 3 "~" H 10400 4700 50  0001 C CNN
F 4 "-" H 0   0   50  0001 C CNN "TME Link"
	1    10400 4700
	1    0    0    -1  
$EndComp
Text Notes 10300 3950 0    75   Italic 15
Mechanical
Wire Notes Line
	10300 3800 11200 3800
Wire Notes Line
	11200 3800 11200 4800
Wire Notes Line
	11200 4800 10300 4800
Wire Notes Line
	10300 4800 10300 3800
Wire Wire Line
	850  6650 2450 6650
Wire Wire Line
	850  7450 1750 7450
Text Label 850  7050 0    50   ~ 0
V_BAT_MID
Text Label 4950 4600 0    50   ~ 0
FTDI_RX
Text Label 4950 4700 0    50   ~ 0
FTDI_TX
Connection ~ 4800 4600
Wire Wire Line
	4800 4600 5450 4600
$Comp
L Connector:Conn_01x03_Male J4
U 1 1 5CEF0263
P 550 7050
F 0 "J4" H 650 7250 50  0000 C CNN
F 1 "2 x AA" H 650 6900 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 550 7050 50  0001 C CNN
F 3 "~" H 550 7050 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/zl262-3sg/pin-headers/connfly/ds1023-1-3s21/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.60822" H 0   0   50  0001 C CNN "TME Price"
	1    550  7050
	1    0    0    -1  
$EndComp
Wire Wire Line
	850  6650 850  6950
Wire Wire Line
	850  6950 750  6950
Wire Wire Line
	850  7450 850  7150
Wire Wire Line
	850  7150 750  7150
Wire Wire Line
	7600 2400 7600 2550
NoConn ~ 7700 2400
Wire Wire Line
	850  7450 850  7500
Connection ~ 850  7450
$Comp
L Connector:TestPoint TP4
U 1 1 5D044718
P 9800 5900
F 0 "TP4" V 9800 6100 50  0000 L CNN
F 1 "TestPoint" H 9858 5929 50  0001 L CNN
F 2 "TestPoint:TestPoint_THTPad_D1.5mm_Drill0.7mm" H 10000 5900 50  0001 C CNN
F 3 "~" H 10000 5900 50  0001 C CNN
F 4 "-" H 1400 150 50  0001 C CNN "TME Link"
	1    9800 5900
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5D0688FF
P 9050 6100
F 0 "#PWR0101" H 9050 5850 50  0001 C CNN
F 1 "GND" H 9055 5927 50  0000 C CNN
F 2 "" H 9050 6100 50  0001 C CNN
F 3 "" H 9050 6100 50  0001 C CNN
	1    9050 6100
	1    0    0    -1  
$EndComp
Wire Wire Line
	9050 6050 9050 6100
Wire Wire Line
	9050 6050 9700 6050
$Comp
L power:VCC #PWR0102
U 1 1 5D0D4995
P 9050 5800
F 0 "#PWR0102" H 9050 5650 50  0001 C CNN
F 1 "VCC" H 9067 5973 50  0000 C CNN
F 2 "" H 9050 5800 50  0001 C CNN
F 3 "" H 9050 5800 50  0001 C CNN
	1    9050 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	9800 5900 9050 5900
Wire Wire Line
	9050 5900 9050 5800
Wire Wire Line
	750  7050 1300 7050
Wire Wire Line
	3100 6650 3400 6650
Text Label 9200 4650 0    50   ~ 0
I2C1_SCL
Text Label 9200 4800 0    50   ~ 0
I2C1_SDA
$Comp
L Connector:TestPoint TP5
U 1 1 5D186BB9
P 9800 4650
F 0 "TP5" V 9800 4850 50  0000 L CNN
F 1 "TestPoint" H 9858 4679 50  0001 L CNN
F 2 "TestPoint:TestPoint_THTPad_D1.5mm_Drill0.7mm" H 10000 4650 50  0001 C CNN
F 3 "~" H 10000 4650 50  0001 C CNN
F 4 "-" H 1400 150 50  0001 C CNN "TME Link"
	1    9800 4650
	0    1    1    0   
$EndComp
$Comp
L Connector:TestPoint TP6
U 1 1 5D186C47
P 9800 4800
F 0 "TP6" V 9800 5000 50  0000 L CNN
F 1 "TestPoint" H 9858 4829 50  0001 L CNN
F 2 "TestPoint:TestPoint_THTPad_D1.5mm_Drill0.7mm" H 10000 4800 50  0001 C CNN
F 3 "~" H 10000 4800 50  0001 C CNN
F 4 "-" H 1400 150 50  0001 C CNN "TME Link"
	1    9800 4800
	0    1    1    0   
$EndComp
Wire Wire Line
	9800 4800 9200 4800
Wire Wire Line
	9200 4650 9800 4650
Text Label 9200 4950 0    50   ~ 0
SPI1_SCK
Text Label 9200 5100 0    50   ~ 0
SPI1_MOSI
Text Label 9200 5250 0    50   ~ 0
SPI1_MISO
$Comp
L Connector:TestPoint TP7
U 1 1 5D1BC03F
P 9800 4950
F 0 "TP7" V 9800 5150 50  0000 L CNN
F 1 "TestPoint" H 9858 4979 50  0001 L CNN
F 2 "TestPoint:TestPoint_THTPad_D1.5mm_Drill0.7mm" H 10000 4950 50  0001 C CNN
F 3 "~" H 10000 4950 50  0001 C CNN
F 4 "-" H 1400 150 50  0001 C CNN "TME Link"
	1    9800 4950
	0    1    1    0   
$EndComp
$Comp
L Connector:TestPoint TP8
U 1 1 5D1BC0D1
P 9800 5100
F 0 "TP8" V 9800 5300 50  0000 L CNN
F 1 "TestPoint" H 9858 5129 50  0001 L CNN
F 2 "TestPoint:TestPoint_THTPad_D1.5mm_Drill0.7mm" H 10000 5100 50  0001 C CNN
F 3 "~" H 10000 5100 50  0001 C CNN
F 4 "-" H 1400 150 50  0001 C CNN "TME Link"
	1    9800 5100
	0    1    1    0   
$EndComp
$Comp
L Connector:TestPoint TP9
U 1 1 5D1BC165
P 9800 5250
F 0 "TP9" V 9800 5450 50  0000 L CNN
F 1 "TestPoint" H 9858 5279 50  0001 L CNN
F 2 "TestPoint:TestPoint_THTPad_D1.5mm_Drill0.7mm" H 10000 5250 50  0001 C CNN
F 3 "~" H 10000 5250 50  0001 C CNN
F 4 "-" H 1400 150 50  0001 C CNN "TME Link"
	1    9800 5250
	0    1    1    0   
$EndComp
Wire Wire Line
	9800 5250 9200 5250
Wire Wire Line
	9200 5100 9800 5100
Wire Wire Line
	9800 4950 9200 4950
Text Label 9200 5400 0    50   ~ 0
CS_RFM69
Text Label 9200 5550 0    50   ~ 0
CS_FLASH
$Comp
L Connector:TestPoint TP10
U 1 1 5D20457A
P 9800 5400
F 0 "TP10" V 9800 5600 50  0000 L CNN
F 1 "TestPoint" H 9858 5429 50  0001 L CNN
F 2 "TestPoint:TestPoint_THTPad_D1.5mm_Drill0.7mm" H 10000 5400 50  0001 C CNN
F 3 "~" H 10000 5400 50  0001 C CNN
F 4 "-" H 1400 150 50  0001 C CNN "TME Link"
	1    9800 5400
	0    1    1    0   
$EndComp
$Comp
L Connector:TestPoint TP11
U 1 1 5D204612
P 9800 5550
F 0 "TP11" V 9800 5750 50  0000 L CNN
F 1 "TestPoint" H 9858 5579 50  0001 L CNN
F 2 "TestPoint:TestPoint_THTPad_D1.5mm_Drill0.7mm" H 10000 5550 50  0001 C CNN
F 3 "~" H 10000 5550 50  0001 C CNN
F 4 "-" H 1400 150 50  0001 C CNN "TME Link"
	1    9800 5550
	0    1    1    0   
$EndComp
Wire Wire Line
	9800 5550 9200 5550
Wire Wire Line
	9200 5400 9800 5400
$Comp
L Connector:TestPoint TP12
U 1 1 5D229E6E
P 9800 6050
F 0 "TP12" V 9800 6250 50  0000 L CNN
F 1 "TestPoint" H 9858 6079 50  0001 L CNN
F 2 "TestPoint:TestPoint_THTPad_1.5x1.5mm_Drill0.7mm" H 10000 6050 50  0001 C CNN
F 3 "~" H 10000 6050 50  0001 C CNN
F 4 "-" H 1400 50  50  0001 C CNN "TME Link"
	1    9800 6050
	0    1    1    0   
$EndComp
$Comp
L Connector:TestPoint TP13
U 1 1 5D229F08
P 9800 6150
F 0 "TP13" V 9800 6350 50  0000 L CNN
F 1 "TestPoint" H 9858 6179 50  0001 L CNN
F 2 "TestPoint:TestPoint_THTPad_1.5x1.5mm_Drill0.7mm" H 10000 6150 50  0001 C CNN
F 3 "~" H 10000 6150 50  0001 C CNN
F 4 "-" H 1400 50  50  0001 C CNN "TME Link"
	1    9800 6150
	0    1    1    0   
$EndComp
Wire Wire Line
	9800 6150 9700 6150
Wire Wire Line
	9700 6150 9700 6050
Connection ~ 9700 6050
Wire Wire Line
	9700 6050 9800 6050
Text Label 2900 2250 0    50   ~ 0
RFM69_RST
Wire Wire Line
	3100 2250 2900 2250
Connection ~ 3100 2250
Text Label 2750 2700 2    50   ~ 0
I2C1_SDA
Text Label 2750 2800 2    50   ~ 0
RFM69_RST
$Comp
L humidity:RFM69HW U1
U 1 1 5CD803DB
P 3900 2050
F 0 "U1" H 4150 1450 50  0000 C CNN
F 1 "RFM69HW" H 3500 1450 50  0000 C CNN
F 2 "humidity:RFM69HW" H 600 3700 50  0001 C CNN
F 3 "http://www.hoperf.com/upload/rf/RFM69HCW-V1.1.pdf" H 600 3700 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/rfm69hw-433s2/rf-modules/hope-microelectronics/" H 0   0   50  0001 C CNN "TME Link"
F 5 "29.96" H 0   0   50  0001 C CNN "TME Price"
	1    3900 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 2750 3900 2700
Connection ~ 3900 2700
Text Notes 1600 6950 0    50   ~ 0
BAT_MID on ADC_IN9
Text Notes 9000 4200 0    75   Italic 15
Test points
Wire Notes Line
	10250 6350 10250 4050
Wire Notes Line
	10250 4050 8950 4050
Wire Notes Line
	8950 4050 8950 6350
Wire Notes Line
	8950 6350 10250 6350
Wire Wire Line
	8000 850  8500 850 
Wire Wire Line
	8000 1100 8500 1100
Wire Wire Line
	9000 850  9000 1100
Wire Wire Line
	8800 1100 9000 1100
Connection ~ 9000 1100
Wire Wire Line
	9000 1100 9000 1350
Wire Wire Line
	8800 1350 9000 1350
Connection ~ 9000 1350
Wire Wire Line
	9000 1350 9000 1600
Wire Wire Line
	8800 1600 9000 1600
Connection ~ 9000 1600
Wire Wire Line
	9000 1600 9000 1850
Wire Wire Line
	8800 1850 9000 1850
Connection ~ 9000 1850
Wire Wire Line
	9000 1850 9000 2050
$Comp
L Device:C C8
U 1 1 5D148847
P 4400 1150
F 0 "C8" H 4515 1196 50  0000 L CNN
F 1 "1u" H 4515 1105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4438 1000 50  0001 C CNN
F 3 "~" H 4400 1150 50  0001 C CNN
	1    4400 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 900  4400 900 
Wire Wire Line
	4400 900  4400 1000
Connection ~ 4100 900 
$Comp
L power:GND #PWR04
U 1 1 5D157DE7
P 4400 1400
F 0 "#PWR04" H 4400 1150 50  0001 C CNN
F 1 "GND" H 4405 1227 50  0000 C CNN
F 2 "" H 4400 1400 50  0001 C CNN
F 3 "" H 4400 1400 50  0001 C CNN
	1    4400 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 1300 4400 1400
$Comp
L Device:C C10
U 1 1 5D167AF0
P 1300 1100
F 0 "C10" H 1350 1200 50  0000 L CNN
F 1 "1u" H 1350 1000 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1338 950 50  0001 C CNN
F 3 "~" H 1300 1100 50  0001 C CNN
	1    1300 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1550 850  1300 850 
Wire Wire Line
	1300 850  1300 950 
$Comp
L power:GND #PWR021
U 1 1 5D1777ED
P 1300 1300
F 0 "#PWR021" H 1300 1050 50  0001 C CNN
F 1 "GND" H 1305 1127 50  0000 C CNN
F 2 "" H 1300 1300 50  0001 C CNN
F 3 "" H 1300 1300 50  0001 C CNN
	1    1300 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 1250 1300 1300
$Comp
L Device:C C9
U 1 1 5D1878AF
P 1000 1100
F 0 "C9" H 1050 1200 50  0000 L CNN
F 1 "1u" H 1050 1000 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1038 950 50  0001 C CNN
F 3 "~" H 1000 1100 50  0001 C CNN
	1    1000 1100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR020
U 1 1 5D1880F3
P 1000 1300
F 0 "#PWR020" H 1000 1050 50  0001 C CNN
F 1 "GND" H 1005 1127 50  0000 C CNN
F 2 "" H 1000 1300 50  0001 C CNN
F 3 "" H 1000 1300 50  0001 C CNN
	1    1000 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 1250 1000 1300
Wire Wire Line
	1300 850  1000 850 
Wire Wire Line
	1000 850  1000 950 
Connection ~ 1300 850 
$Comp
L Device:C C11
U 1 1 5D20A2C9
P 700 1100
F 0 "C11" H 750 1200 50  0000 L CNN
F 1 "1u" H 750 1000 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 738 950 50  0001 C CNN
F 3 "~" H 700 1100 50  0001 C CNN
	1    700  1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 850  700  850 
Wire Wire Line
	700  850  700  950 
Connection ~ 1000 850 
$Comp
L power:GND #PWR024
U 1 1 5D21AE99
P 700 1300
F 0 "#PWR024" H 700 1050 50  0001 C CNN
F 1 "GND" H 705 1127 50  0000 C CNN
F 2 "" H 700 1300 50  0001 C CNN
F 3 "" H 700 1300 50  0001 C CNN
	1    700  1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	700  1250 700  1300
Wire Wire Line
	4000 4850 4000 5200
$Comp
L humidity:SW_Push_4pin SW2
U 1 1 5D4CC3C1
P 8600 2700
F 0 "SW2" H 8700 2850 40  0000 C CNN
F 1 "DTSM-65R-V-B" H 8600 2500 40  0000 C CNN
F 2 "humidity:SW_SPST_DTSM-6" H 8600 2700 40  0001 C CNN
F 3 "https://www.tme.eu/se/en/details/dtsm-65r-v-b/microswitches-tact/diptronics/" H 8600 2700 40  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/dtsm-65r-v-b/microswitches-tact/diptronics/" H -2050 150 50  0001 C CNN "TME Link"
F 5 "1.8894" H -2050 150 50  0001 C CNN "TME Price"
	1    8600 2700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 5D4DD0C9
P 8200 3100
F 0 "#PWR0103" H 8200 2850 50  0001 C CNN
F 1 "GND" H 8205 2927 50  0000 C CNN
F 2 "" H 8200 3100 50  0001 C CNN
F 3 "" H 8200 3100 50  0001 C CNN
	1    8200 3100
	1    0    0    -1  
$EndComp
NoConn ~ 8850 2700
NoConn ~ 8350 2800
Text Label 8000 2700 0    50   ~ 0
SW
Wire Wire Line
	11000 2750 10900 2750
Text Notes 8000 2500 0    75   Italic 15
Button
Wire Notes Line
	7950 2350 9150 2350
Wire Notes Line
	9150 2350 9150 3350
Wire Notes Line
	9150 3350 7950 3350
Wire Notes Line
	7950 2350 7950 3350
Wire Wire Line
	8350 2700 8200 2700
Wire Wire Line
	9050 2800 8850 2800
$Comp
L power:VCC #PWR0104
U 1 1 5D5C76F0
P 9050 2600
F 0 "#PWR0104" H 9050 2450 50  0001 C CNN
F 1 "VCC" H 9067 2773 50  0000 C CNN
F 2 "" H 9050 2600 50  0001 C CNN
F 3 "" H 9050 2600 50  0001 C CNN
	1    9050 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9050 2600 9050 2800
Wire Wire Line
	8200 2750 8200 2700
Connection ~ 8200 2700
Wire Wire Line
	8200 2700 8000 2700
Wire Wire Line
	8200 3100 8200 3050
$Comp
L Device:R R6
U 1 1 5D6B13F6
P 8200 2900
F 0 "R6" V 8100 2900 50  0000 C CNN
F 1 "100k" V 8200 2900 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 8130 2900 50  0001 C CNN
F 3 "~" H 8200 2900 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/cq0603-100k-1%25/0603-smd-resistors/royal-ohm/cq03saf1003t5e/" H 4400 -1950 50  0001 C CNN "TME Link"
F 5 "0.18525" H 4400 -1950 50  0001 C CNN "TME Price"
	1    8200 2900
	1    0    0    -1  
$EndComp
$EndSCHEMATC
