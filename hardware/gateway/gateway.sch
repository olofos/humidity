EESchema Schematic File Version 4
LIBS:gateway-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Mechanical:MountingHole H1
U 1 1 5CEEFE01
P 6150 6800
F 0 "H1" H 6250 6846 50  0000 L CNN
F 1 "MountingHole" H 6250 6755 50  0000 L CNN
F 2 "humidity:MountingHole_2.7mm_M2.5" H 6150 6800 50  0001 C CNN
F 3 "~" H 6150 6800 50  0001 C CNN
	1    6150 6800
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 5CEEFFB2
P 6150 7000
F 0 "H2" H 6250 7046 50  0000 L CNN
F 1 "MountingHole" H 6250 6955 50  0000 L CNN
F 2 "humidity:MountingHole_2.7mm_M2.5" H 6150 7000 50  0001 C CNN
F 3 "~" H 6150 7000 50  0001 C CNN
	1    6150 7000
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 5CEEFFCA
P 6150 7200
F 0 "H3" H 6250 7246 50  0000 L CNN
F 1 "MountingHole" H 6250 7155 50  0000 L CNN
F 2 "humidity:MountingHole_2.7mm_M2.5" H 6150 7200 50  0001 C CNN
F 3 "~" H 6150 7200 50  0001 C CNN
	1    6150 7200
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 5CEEFFE4
P 6150 7400
F 0 "H4" H 6250 7446 50  0000 L CNN
F 1 "MountingHole" H 6250 7355 50  0000 L CNN
F 2 "humidity:MountingHole_2.7mm_M2.5" H 6150 7400 50  0001 C CNN
F 3 "~" H 6150 7400 50  0001 C CNN
	1    6150 7400
	1    0    0    -1  
$EndComp
$Comp
L Connector:Raspberry_Pi_2_3 J3
U 1 1 5CEF00C6
P 4400 2650
F 0 "J3" H 3700 1350 50  0000 C CNN
F 1 "Raspberry_Pi_2_3" V 3600 1550 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x20_P2.54mm_Vertical_SMD" H 4400 2650 50  0001 C CNN
F 3 "https://www.raspberrypi.org/documentation/hardware/raspberrypi/schematics/rpi_SCH_3bplus_1p0_reduced.pdf" H 4400 2650 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/zl264-40dg/pin-headers/ninigi/" H 0   0   50  0001 C CNN "TME Link"
F 5 "24.27" H 4400 2650 50  0001 C CNN "TME Price"
	1    4400 2650
	1    0    0    -1  
$EndComp
$Comp
L humidity:RFM69HW U1
U 1 1 5CEF0CB1
P 8050 4700
F 0 "U1" H 7700 4100 50  0000 C CNN
F 1 "RFM69HW" V 8050 4650 50  0000 C CNN
F 2 "humidity:RFM69HW" H 4750 6350 50  0001 C CNN
F 3 "" H 4750 6350 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/rfm69hw-433s2/rf-modules/hope-microelectronics/" H 0   0   50  0001 C CNN "TME Link"
F 5 "29.94" H 0   0   50  0001 C CNN "TME Price"
	1    8050 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 2050 5600 2150
Wire Wire Line
	5600 2150 5200 2150
Wire Wire Line
	5200 2050 5500 2050
Wire Wire Line
	5500 2050 5500 1950
Wire Wire Line
	5500 1950 5700 1950
Wire Wire Line
	5700 1950 5700 2150
$Comp
L Device:Crystal Y1
U 1 1 5CF7B659
P 6950 2400
F 0 "Y1" H 6950 2550 50  0000 C CNN
F 1 "32768 " H 6950 2250 50  0000 C CNN
F 2 "Crystal:Crystal_C26-LF_D2.1mm_L6.5mm_Horizontal" H 6950 2400 50  0001 C CNN
F 3 "" H 6950 2400 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/26-hx5f-32.768k/tht-quartz-crystals/ilsi/26-hx5f12-5-32-768khz/" H 6950 2400 50  0001 C CNN "TME Link"
F 5 "1.52097" H -1750 250 50  0001 C CNN "TME Price"
	1    6950 2400
	0    1    1    0   
$EndComp
$Comp
L Device:Battery_Cell BT1
U 1 1 5CF7BB91
P 8150 1350
F 0 "BT1" V 8000 1350 50  0000 L CNN
F 1 "KEYS3000" V 8300 1400 50  0000 C CNN
F 2 "humidity:CR1216_Keystone_3000" V 8150 1410 50  0001 C CNN
F 3 "~" V 8150 1410 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/keys3000/batteries-holders/keystone/3000/" V 8150 1350 50  0001 C CNN "TME Link"
F 5 "4.2504" H -450 50  50  0001 C CNN "TME Price"
	1    8150 1350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR025
U 1 1 5CF7C329
P 8150 1650
F 0 "#PWR025" H 8150 1400 50  0001 C CNN
F 1 "GND" H 8155 1477 50  0000 C CNN
F 2 "" H 8150 1650 50  0001 C CNN
F 3 "" H 8150 1650 50  0001 C CNN
	1    8150 1650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR023
U 1 1 5CF7C3FA
P 7850 2750
F 0 "#PWR023" H 7850 2500 50  0001 C CNN
F 1 "GND" H 7855 2577 50  0000 C CNN
F 2 "" H 7850 2750 50  0001 C CNN
F 3 "" H 7850 2750 50  0001 C CNN
	1    7850 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	11000 2100 11000 1900
Wire Wire Line
	11000 1900 10900 1900
Wire Wire Line
	7750 750  7750 900 
$Comp
L Device:C C3
U 1 1 5CF7DB01
P 7450 1400
F 0 "C3" H 7500 1300 50  0000 L CNN
F 1 "100n" V 7300 1400 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 7488 1250 50  0001 C CNN
F 3 "~" H 7450 1400 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/cl10b104ko8nnnc/0603-mlcc-smd-capacitors/samsung/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.13310" H 0   0   50  0001 C CNN "TME Price"
	1    7450 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 900  7450 900 
Wire Wire Line
	7450 900  7450 1250
Connection ~ 7750 900 
Wire Wire Line
	7750 900  7750 1850
$Comp
L power:GND #PWR021
U 1 1 5CF7DF5B
P 7450 1650
F 0 "#PWR021" H 7450 1400 50  0001 C CNN
F 1 "GND" H 7455 1477 50  0000 C CNN
F 2 "" H 7450 1650 50  0001 C CNN
F 3 "" H 7450 1650 50  0001 C CNN
	1    7450 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 1650 7450 1550
Wire Wire Line
	6900 4600 7550 4600
Wire Wire Line
	7000 4500 7550 4500
Wire Wire Line
	7100 4400 7550 4400
Wire Wire Line
	6800 4700 7550 4700
NoConn ~ 5200 2750
NoConn ~ 8550 4600
NoConn ~ 8550 4700
NoConn ~ 8550 4800
NoConn ~ 8550 4900
NoConn ~ 8550 5000
$Comp
L Connector:Conn_01x06_Male J1
U 1 1 5CF84B33
P 1100 1300
F 0 "J1" H 1200 1600 50  0000 R CNN
F 1 "FTDI" H 1300 900 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Horizontal" H 1100 1300 50  0001 C CNN
F 3 "~" H 1100 1300 50  0001 C CNN
	1    1100 1300
	1    0    0    1   
$EndComp
Text Notes 1050 1500 2    50   ~ 0
GND
Text Notes 1050 1400 2    50   ~ 0
CTS
Text Notes 1050 1300 2    50   ~ 0
VCC
Text Notes 1050 1200 2    50   ~ 0
TXD
Text Notes 1050 1100 2    50   ~ 0
RXD
Text Notes 1050 1000 2    50   ~ 0
DTR/RTS
NoConn ~ 1300 1000
NoConn ~ 1300 1300
NoConn ~ 1300 1400
$Comp
L power:GND #PWR01
U 1 1 5CF87188
P 1400 1600
F 0 "#PWR01" H 1400 1350 50  0001 C CNN
F 1 "GND" H 1405 1427 50  0000 C CNN
F 2 "" H 1400 1600 50  0001 C CNN
F 3 "" H 1400 1600 50  0001 C CNN
	1    1400 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 1600 1400 1500
Wire Wire Line
	1400 1500 1300 1500
$Comp
L Device:R R2
U 1 1 5CF885AD
P 2250 1050
F 0 "R2" V 2150 1050 50  0000 C CNN
F 1 "0" V 2250 1050 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 2180 1050 50  0001 C CNN
F 3 "~" H 2250 1050 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/smd0603-0r/0603-smd-resistors/royal-ohm/0603saj0000t5e/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.09735" H 0   0   50  0001 C CNN "TME Price"
	1    2250 1050
	0    1    1    0   
$EndComp
$Comp
L Device:R R3
U 1 1 5CF89270
P 2250 1250
F 0 "R3" V 2150 1250 50  0000 C CNN
F 1 "0" V 2250 1250 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 2180 1250 50  0001 C CNN
F 3 "~" H 2250 1250 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/smd0603-0r/0603-smd-resistors/royal-ohm/0603saj0000t5e/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.09735" H 0   0   50  0001 C CNN "TME Price"
	1    2250 1250
	0    1    1    0   
$EndComp
Wire Wire Line
	2000 1050 2100 1050
Wire Wire Line
	2000 1200 2000 1250
Wire Wire Line
	2000 1250 2100 1250
$Comp
L Device:R R1
U 1 1 5CF8A80D
P 2250 850
F 0 "R1" V 2150 850 50  0000 C CNN
F 1 "DNP" V 2250 850 50  0000 C CNN
F 2 "humidity:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder-DNP" V 2180 850 50  0001 C CNN
F 3 "~" H 2250 850 50  0001 C CNN
	1    2250 850 
	0    1    1    0   
$EndComp
$Comp
L Device:R R4
U 1 1 5CF8A8C6
P 2250 1450
F 0 "R4" V 2150 1450 50  0000 C CNN
F 1 "DNP" V 2250 1450 50  0000 C CNN
F 2 "humidity:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder-DNP" V 2180 1450 50  0001 C CNN
F 3 "~" H 2250 1450 50  0001 C CNN
	1    2250 1450
	0    1    1    0   
$EndComp
Wire Wire Line
	2000 1100 2000 1050
Wire Wire Line
	1300 1200 2000 1200
Wire Wire Line
	2000 1100 1300 1100
Wire Wire Line
	2000 1050 2000 850 
Wire Wire Line
	2000 850  2100 850 
Connection ~ 2000 1050
Wire Wire Line
	2000 1250 2000 1450
Wire Wire Line
	2000 1450 2100 1450
Connection ~ 2000 1250
Wire Wire Line
	2400 1050 2600 1050
Wire Wire Line
	2400 1250 2500 1250
Wire Wire Line
	2400 850  2500 850 
Wire Wire Line
	2400 1450 2600 1450
$Comp
L power:GND #PWR012
U 1 1 5CF91659
P 4000 4100
F 0 "#PWR012" H 4000 3850 50  0001 C CNN
F 1 "GND" H 4005 3927 50  0000 C CNN
F 2 "" H 4000 4100 50  0001 C CNN
F 3 "" H 4000 4100 50  0001 C CNN
	1    4000 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 3950 4000 4050
Wire Wire Line
	4700 4050 4700 3950
Wire Wire Line
	4000 4050 4000 4100
Wire Wire Line
	4600 3950 4600 4050
Wire Wire Line
	4500 4050 4500 3950
Wire Wire Line
	4400 3950 4400 4050
Wire Wire Line
	4300 4050 4300 3950
Wire Wire Line
	4200 3950 4200 4050
Wire Wire Line
	4100 4050 4100 3950
$Comp
L Device:C C2
U 1 1 5CFC2266
P 8300 3800
F 0 "C2" H 8415 3846 50  0000 L CNN
F 1 "100n" H 8415 3755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 8338 3650 50  0001 C CNN
F 3 "~" H 8300 3800 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/cl10b104ko8nnnc/0603-mlcc-smd-capacitors/samsung/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.13310" H 0   0   50  0001 C CNN "TME Price"
	1    8300 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8300 3650 8300 3500
Wire Wire Line
	8300 3500 8050 3500
Wire Wire Line
	8050 3500 8050 4200
$Comp
L power:GND #PWR05
U 1 1 5CFC6FB2
P 8300 4000
F 0 "#PWR05" H 8300 3750 50  0001 C CNN
F 1 "GND" H 8305 3827 50  0000 C CNN
F 2 "" H 8300 4000 50  0001 C CNN
F 3 "" H 8300 4000 50  0001 C CNN
	1    8300 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	8300 4000 8300 3950
$Comp
L Device:CP1 C1
U 1 1 5CFCC218
P 2400 4150
F 0 "C1" H 2515 4196 50  0000 L CNN
F 1 "22u" H 2515 4105 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_5x5.3" H 2400 4150 50  0001 C CNN
F 3 "~" H 2400 4150 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/sc1e226m05005vr/85degc-smd-electrolytic-capacitors/samwha/" H 2400 4150 50  0001 C CNN "TME Link"
F 5 "0.36794" H 2400 4150 50  0001 C CNN "TME Price"
	1    2400 4150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 5CFDF95F
P 7950 5400
F 0 "#PWR03" H 7950 5150 50  0001 C CNN
F 1 "GND" H 7955 5227 50  0000 C CNN
F 2 "" H 7950 5400 50  0001 C CNN
F 3 "" H 7950 5400 50  0001 C CNN
	1    7950 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7950 5300 7950 5350
Wire Wire Line
	7950 5350 8050 5350
Wire Wire Line
	8050 5350 8050 5300
Wire Wire Line
	7950 5350 7950 5400
$Comp
L Connector:Conn_Coaxial J2
U 1 1 5CFE5EE4
P 9100 4400
F 0 "J2" H 9199 4376 50  0000 L CNN
F 1 "Conn_Coaxial" H 9199 4285 50  0000 L CNN
F 2 "humidity:Adam_Tech_SMA_Female_RF2-19A" H 9100 4400 50  0001 C CNN
F 3 " ~" H 9100 4400 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/rf2-19a-t-00-50-g/sma-smb-smc-connectors/adam-tech/" H 0   0   50  0001 C CNN "TME Link"
F 5 "10.86" H 0   0   50  0001 C CNN "TME Price"
	1    9100 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 4400 8550 4400
Wire Wire Line
	4000 4050 4100 4050
Wire Wire Line
	5600 2050 6200 2050
Wire Wire Line
	7350 2150 6450 2150
Connection ~ 4000 4050
Connection ~ 4100 4050
Wire Wire Line
	4100 4050 4200 4050
Connection ~ 4200 4050
Wire Wire Line
	4200 4050 4300 4050
Connection ~ 4300 4050
Wire Wire Line
	4300 4050 4400 4050
Connection ~ 4400 4050
Wire Wire Line
	4400 4050 4500 4050
Connection ~ 4500 4050
Wire Wire Line
	4500 4050 4600 4050
Connection ~ 4600 4050
Wire Wire Line
	4600 4050 4700 4050
Wire Wire Line
	3400 1100 3400 1750
Wire Wire Line
	3400 1750 3600 1750
Wire Wire Line
	3600 1850 3300 1850
Wire Wire Line
	3300 1850 3300 1200
Connection ~ 7950 5350
NoConn ~ 5200 1750
NoConn ~ 5200 1850
$Comp
L power:GND #PWR07
U 1 1 5D20A08B
P 9100 4700
F 0 "#PWR07" H 9100 4450 50  0001 C CNN
F 1 "GND" H 9105 4527 50  0000 C CNN
F 2 "" H 9100 4700 50  0001 C CNN
F 3 "" H 9100 4700 50  0001 C CNN
	1    9100 4700
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 4600 9100 4700
$Comp
L power:PWR_FLAG #FLG02
U 1 1 5D21CD29
P 4700 4100
F 0 "#FLG02" H 4700 4175 50  0001 C CNN
F 1 "PWR_FLAG" H 4700 4273 50  0000 C CNN
F 2 "" H 4700 4100 50  0001 C CNN
F 3 "~" H 4700 4100 50  0001 C CNN
	1    4700 4100
	-1   0    0    1   
$EndComp
Wire Wire Line
	4700 4050 4700 4100
Connection ~ 4700 4050
$Comp
L power:PWR_FLAG #FLG04
U 1 1 5D226779
P 8150 650
F 0 "#FLG04" H 8150 725 50  0001 C CNN
F 1 "PWR_FLAG" H 8150 550 50  0000 C CNN
F 2 "" H 8150 650 50  0001 C CNN
F 3 "~" H 8150 650 50  0001 C CNN
	1    8150 650 
	1    0    0    -1  
$EndComp
Text Label 1400 1100 0    50   ~ 0
FTDI_RX
Text Label 1400 1200 0    50   ~ 0
FTDI_TX
Text Label 2750 1100 0    50   ~ 0
PI_TX
Text Label 2750 1200 0    50   ~ 0
PI_RX
$Comp
L Device:LED D2
U 1 1 5D38D843
P 5500 4450
F 0 "D2" H 5500 4550 50  0000 R CNN
F 1 "KP-2012LSGC" V 5447 4333 50  0001 R CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5500 4450 50  0001 C CNN
F 3 "~" H 5500 4450 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/kp-2012lsgc/smd-colour-leds/kingbright-electronic/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.24810" H 0   0   50  0001 C CNN "TME Price"
	1    5500 4450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5200 3350 5500 3350
Wire Wire Line
	5500 3350 5500 3900
$Comp
L Device:R R11
U 1 1 5D395686
P 5500 4050
F 0 "R11" V 5400 4000 50  0000 L CNN
F 1 "330R" V 5500 4050 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 5430 4050 50  0001 C CNN
F 3 "~" H 5500 4050 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/smd0603-330r-1%25/0603-smd-resistors/royal-ohm/0603saf3300t5e/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.11531" H 0   0   50  0001 C CNN "TME Price"
	1    5500 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 4200 5500 4300
$Comp
L power:GND #PWR016
U 1 1 5D39D66E
P 5500 4800
F 0 "#PWR016" H 5500 4550 50  0001 C CNN
F 1 "GND" H 5505 4627 50  0000 C CNN
F 2 "" H 5500 4800 50  0001 C CNN
F 3 "" H 5500 4800 50  0001 C CNN
	1    5500 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5500 4800 5500 4600
NoConn ~ 3600 2150
NoConn ~ 3600 2250
NoConn ~ 3600 3250
NoConn ~ 3600 3350
Text Label 5800 2150 0    50   ~ 0
SDA
Text Label 5800 2050 0    50   ~ 0
SCL
$Comp
L Device:R R12
U 1 1 5D5915E6
P 6200 1800
F 0 "R12" V 6100 1800 50  0000 C CNN
F 1 "DNP" V 6200 1800 50  0000 C CNN
F 2 "humidity:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder-DNP" V 6130 1800 50  0001 C CNN
F 3 "~" H 6200 1800 50  0001 C CNN
	1    6200 1800
	-1   0    0    1   
$EndComp
$Comp
L Device:R R13
U 1 1 5D5916C9
P 6450 1800
F 0 "R13" V 6350 1800 50  0000 C CNN
F 1 "DNP" V 6450 1800 50  0000 C CNN
F 2 "humidity:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder-DNP" V 6380 1800 50  0001 C CNN
F 3 "~" H 6450 1800 50  0001 C CNN
	1    6450 1800
	-1   0    0    1   
$EndComp
Wire Wire Line
	6200 1550 6200 1600
Wire Wire Line
	6200 1600 6450 1600
Wire Wire Line
	6450 1600 6450 1650
Connection ~ 6200 1600
Wire Wire Line
	6200 1600 6200 1650
Wire Wire Line
	6200 1950 6200 2050
Connection ~ 6200 2050
Wire Wire Line
	6200 2050 7350 2050
Wire Wire Line
	6450 1950 6450 2150
Connection ~ 6450 2150
Wire Wire Line
	6450 2150 5700 2150
Text Notes 5700 1250 0    50   ~ 0
DNP: The PI already has I2C pullups
Text Label 3100 3050 0    50   ~ 0
RFM_RESET
Text Label 3100 2950 0    50   ~ 0
RFM_INT
Text Label 5500 3500 3    50   ~ 0
LED0
$Comp
L Device:LED D1
U 1 1 5D657D8C
P 5250 4450
F 0 "D1" H 5250 4550 50  0000 R CNN
F 1 "KP-2012LSURCK" V 5197 4333 50  0001 R CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5250 4450 50  0001 C CNN
F 3 "~" H 5250 4450 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/kp-2012lsurck/smd-colour-leds/kingbright-electronic/" H 0   0   50  0001 C CNN "TME Link"
F 5 "1.052" H 0   0   50  0001 C CNN "TME Price"
	1    5250 4450
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R8
U 1 1 5D657D92
P 5250 4050
F 0 "R8" V 5150 4000 50  0000 L CNN
F 1 "330R" V 5250 4050 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 5180 4050 50  0001 C CNN
F 3 "~" H 5250 4050 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/smd0603-330r-1%25/0603-smd-resistors/royal-ohm/0603saf3300t5e/" H 0   0   50  0001 C CNN "TME Link"
F 5 "0.11531" H 0   0   50  0001 C CNN "TME Price"
	1    5250 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 4200 5250 4300
$Comp
L power:GND #PWR015
U 1 1 5D657D99
P 5250 4800
F 0 "#PWR015" H 5250 4550 50  0001 C CNN
F 1 "GND" H 5255 4627 50  0000 C CNN
F 2 "" H 5250 4800 50  0001 C CNN
F 3 "" H 5250 4800 50  0001 C CNN
	1    5250 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 4800 5250 4600
Wire Wire Line
	5200 3450 5250 3450
Wire Wire Line
	5250 3450 5250 3900
Text Label 5250 3500 3    50   ~ 0
LED1
Wire Wire Line
	2600 1050 2600 1100
Wire Wire Line
	2500 850  2500 1200
Wire Wire Line
	3400 1100 2600 1100
Wire Wire Line
	5200 2850 6800 2850
Wire Wire Line
	6800 2850 6800 4700
Wire Wire Line
	6900 4600 6900 2950
Wire Wire Line
	6900 2950 5200 2950
Wire Wire Line
	7000 4500 7000 3050
Wire Wire Line
	7000 3050 5200 3050
Wire Wire Line
	7100 4400 7100 3150
Wire Wire Line
	7100 3150 5200 3150
Wire Wire Line
	6700 4900 7550 4900
Wire Wire Line
	8550 5100 8650 5100
Wire Wire Line
	8650 5100 8650 5700
Wire Wire Line
	8650 5700 6600 5700
NoConn ~ 3600 2850
NoConn ~ 3600 3150
NoConn ~ 3600 2050
NoConn ~ 3600 2450
NoConn ~ 3600 2550
NoConn ~ 3600 2650
Wire Wire Line
	2600 1100 2600 1450
Connection ~ 2600 1100
Wire Wire Line
	3300 1200 2500 1200
Connection ~ 2500 1200
Wire Wire Line
	2500 1200 2500 1250
Wire Wire Line
	3600 2950 3100 2950
Wire Wire Line
	3600 3050 3100 3050
NoConn ~ 5200 2450
NoConn ~ 5200 2550
Text Label 6700 4900 0    50   ~ 0
RFM_RESET
Text Label 6600 5700 0    50   ~ 0
RFM_INT
Text Label 7850 1750 1    50   ~ 0
VBAT
Text Label 8650 4400 0    50   ~ 0
ANT
Text Label 7100 2250 0    50   ~ 0
X1
Text Label 7100 2550 0    50   ~ 0
X2
$Comp
L humidity:AP130-xxY U3
U 1 1 5D035730
P 1950 4000
F 0 "U3" H 1950 4365 50  0000 C CNN
F 1 "AP130-xxY" H 1950 4274 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-89-3_Handsoldering" H 1950 4000 50  0001 C CNN
F 3 "https://www.tme.eu/Document/a40bcc82e08605be7c628bfb79d62f46/AP130.pdf" H 1950 4000 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/ap130-33yg-13/ldo-unregulated-voltage-regulators/diodes-incorporated/" H 1950 4000 50  0001 C CNN "TME Link"
F 5 "2.47293" H 1950 4000 50  0001 C CNN "TME Price"
	1    1950 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 4000 2400 3900
Wire Wire Line
	2400 3900 2250 3900
$Comp
L power:GND #PWR0101
U 1 1 5D03A725
P 1950 4400
F 0 "#PWR0101" H 1950 4150 50  0001 C CNN
F 1 "GND" H 1955 4227 50  0000 C CNN
F 2 "" H 1950 4400 50  0001 C CNN
F 3 "" H 1950 4400 50  0001 C CNN
	1    1950 4400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 5D03A7C1
P 2400 4400
F 0 "#PWR0102" H 2400 4150 50  0001 C CNN
F 1 "GND" H 2405 4227 50  0000 C CNN
F 2 "" H 2400 4400 50  0001 C CNN
F 3 "" H 2400 4400 50  0001 C CNN
	1    2400 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 4300 2400 4400
Wire Wire Line
	1950 4300 1950 4400
Wire Wire Line
	1650 3900 1500 3900
Wire Wire Line
	1500 3900 1500 3800
$Comp
L Device:C C6
U 1 1 5D049711
P 1500 4150
F 0 "C6" H 1615 4196 50  0000 L CNN
F 1 "1u" H 1615 4105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1538 4000 50  0001 C CNN
F 3 "~" H 1500 4150 50  0001 C CNN
	1    1500 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 3900 1500 4000
Connection ~ 1500 3900
$Comp
L power:GND #PWR0103
U 1 1 5D053DF6
P 1500 4400
F 0 "#PWR0103" H 1500 4150 50  0001 C CNN
F 1 "GND" H 1505 4227 50  0000 C CNN
F 2 "" H 1500 4400 50  0001 C CNN
F 3 "" H 1500 4400 50  0001 C CNN
	1    1500 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 4300 1500 4400
Wire Wire Line
	4200 1150 4200 1250
Wire Wire Line
	4300 1350 4300 1250
Wire Wire Line
	4300 1250 4200 1250
Connection ~ 4200 1250
Wire Wire Line
	4200 1250 4200 1350
NoConn ~ 4600 1350
$Comp
L humidity:+5V_PI #PWR0104
U 1 1 5D0A28CD
P 4200 1150
F 0 "#PWR0104" H 4200 1000 50  0001 C CNN
F 1 "+5V_PI" H 4215 1323 50  0000 C CNN
F 2 "" H 4200 1150 50  0001 C CNN
F 3 "" H 4200 1150 50  0001 C CNN
	1    4200 1150
	1    0    0    -1  
$EndComp
$Comp
L humidity:+5V_PI #PWR0105
U 1 1 5D0ADF6D
P 1500 3800
F 0 "#PWR0105" H 1500 3650 50  0001 C CNN
F 1 "+5V_PI" H 1515 3973 50  0000 C CNN
F 2 "" H 1500 3800 50  0001 C CNN
F 3 "" H 1500 3800 50  0001 C CNN
	1    1500 3800
	1    0    0    -1  
$EndComp
$Comp
L humidity:+3V3_PI #PWR0106
U 1 1 5D0AE289
P 4500 1150
F 0 "#PWR0106" H 4500 1000 50  0001 C CNN
F 1 "+3V3_PI" H 4515 1323 50  0000 C CNN
F 2 "" H 4500 1150 50  0001 C CNN
F 3 "" H 4500 1150 50  0001 C CNN
	1    4500 1150
	1    0    0    -1  
$EndComp
$Comp
L humidity:+3V3_PI #PWR0107
U 1 1 5D0B9906
P 6200 1550
F 0 "#PWR0107" H 6200 1400 50  0001 C CNN
F 1 "+3V3_PI" H 6215 1723 50  0000 C CNN
F 2 "" H 6200 1550 50  0001 C CNN
F 3 "" H 6200 1550 50  0001 C CNN
	1    6200 1550
	1    0    0    -1  
$EndComp
$Comp
L humidity:+3V3_REG #PWR0109
U 1 1 5D0BA502
P 8050 3350
F 0 "#PWR0109" H 8050 3200 50  0001 C CNN
F 1 "+3V3_REG" H 8065 3523 50  0000 C CNN
F 2 "" H 8050 3350 50  0001 C CNN
F 3 "" H 8050 3350 50  0001 C CNN
	1    8050 3350
	1    0    0    -1  
$EndComp
Connection ~ 8050 3500
Wire Wire Line
	8050 3350 8050 3500
$Comp
L humidity:+3V3_REG #PWR0110
U 1 1 5D0BA60F
P 2400 3800
F 0 "#PWR0110" H 2400 3650 50  0001 C CNN
F 1 "+3V3_REG" H 2415 3973 50  0000 C CNN
F 2 "" H 2400 3800 50  0001 C CNN
F 3 "" H 2400 3800 50  0001 C CNN
	1    2400 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 3800 2400 3900
Connection ~ 2400 3900
Wire Wire Line
	4500 1150 4500 1200
Connection ~ 8150 900 
Wire Wire Line
	8150 900  7850 900 
Wire Wire Line
	8150 650  8150 900 
Wire Wire Line
	7850 900  7850 1850
$Comp
L Device:R R5
U 1 1 5D093C3A
P 8500 2000
F 0 "R5" V 8400 1950 50  0000 L CNN
F 1 "10k" V 8500 2000 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 8430 2000 50  0001 C CNN
F 3 "~" H 8500 2000 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/crcw060310k0fktabc/0603-smd-resistors/vishay/" H 1550 200 50  0001 C CNN "TME Link"
F 5 "0.12458" H 1550 200 50  0001 C CNN "TME Price"
	1    8500 2000
	1    0    0    -1  
$EndComp
$Comp
L humidity:+3V3_PI #PWR02
U 1 1 5D0991BC
P 8500 1750
F 0 "#PWR02" H 8500 1600 50  0001 C CNN
F 1 "+3V3_PI" H 8515 1923 50  0000 C CNN
F 2 "" H 8500 1750 50  0001 C CNN
F 3 "" H 8500 1750 50  0001 C CNN
	1    8500 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 1750 8500 1850
Text Label 5800 2350 0    50   ~ 0
RTC_SQ_OUT
Text Label 6550 2850 0    50   ~ 0
CS
Text Label 6550 2950 0    50   ~ 0
MISO
Text Label 6550 3050 0    50   ~ 0
MOSI
Text Label 6550 3150 0    50   ~ 0
SCK
$Comp
L Timer_RTC:DS1307Z+ U2
U 1 1 5D124767
P 7850 2250
F 0 "U2" H 7500 1900 50  0000 L CNN
F 1 "DS1307Z+" H 7950 1900 50  0000 L CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 7850 1750 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/DS1307.pdf" H 7850 2250 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/ds1307z+/rtc-circuits/maxim-integrated/" H 7850 2250 50  0001 C CNN "TME Link"
F 5 "15.02" H 7850 2250 50  0001 C CNN "TME Price"
	1    7850 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 900  8150 1150
Wire Wire Line
	8150 1650 8150 1450
Wire Wire Line
	7850 2650 7850 2750
Wire Wire Line
	6950 2250 7200 2250
Wire Wire Line
	7200 2250 7200 2350
Wire Wire Line
	7200 2350 7350 2350
Wire Wire Line
	6950 2550 7200 2550
Wire Wire Line
	7200 2550 7200 2450
Wire Wire Line
	7200 2450 7350 2450
$Comp
L humidity:+5V_PI #PWR0108
U 1 1 5D1533CB
P 7750 750
F 0 "#PWR0108" H 7750 600 50  0001 C CNN
F 1 "+5V_PI" H 7765 923 50  0000 C CNN
F 2 "" H 7750 750 50  0001 C CNN
F 3 "" H 7750 750 50  0001 C CNN
	1    7750 750 
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 2150 8500 2250
Wire Wire Line
	8500 2250 8350 2250
Wire Wire Line
	6650 2350 6650 2700
Wire Wire Line
	6650 2700 7550 2700
Wire Wire Line
	7550 2700 7550 3000
Wire Wire Line
	7550 3000 8500 3000
Wire Wire Line
	8500 3000 8500 2250
Wire Wire Line
	5200 2350 6650 2350
Connection ~ 8500 2250
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5D15D37F
P 4800 1050
F 0 "#FLG0101" H 4800 1125 50  0001 C CNN
F 1 "PWR_FLAG" H 4800 1250 50  0000 C CNN
F 2 "" H 4800 1050 50  0001 C CNN
F 3 "~" H 4800 1050 50  0001 C CNN
	1    4800 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 1050 4800 1200
Wire Wire Line
	4800 1200 4500 1200
Connection ~ 4500 1200
Wire Wire Line
	4500 1200 4500 1350
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5D1628EE
P 3950 1050
F 0 "#FLG0102" H 3950 1125 50  0001 C CNN
F 1 "PWR_FLAG" H 3950 1250 50  0000 C CNN
F 2 "" H 3950 1050 50  0001 C CNN
F 3 "~" H 3950 1050 50  0001 C CNN
	1    3950 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 1050 3950 1250
Wire Wire Line
	3950 1250 4200 1250
$EndSCHEMATC
