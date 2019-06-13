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
F 2 "MountingHole:MountingHole_2.7mm_M2.5" H 6150 6800 50  0001 C CNN
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
F 2 "MountingHole:MountingHole_2.7mm_M2.5" H 6150 7000 50  0001 C CNN
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
F 2 "MountingHole:MountingHole_2.7mm_M2.5" H 6150 7200 50  0001 C CNN
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
F 2 "MountingHole:MountingHole_2.7mm_M2.5" H 6150 7400 50  0001 C CNN
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
P 8700 2150
F 0 "Y1" H 8700 2300 50  0000 C CNN
F 1 "32768 - 6pF" H 8700 2000 50  0000 C CNN
F 2 "humidity:Crystal LFXTAL016178" H 8700 2150 50  0001 C CNN
F 3 "https://www.tme.eu/Document/1590aad5e7e715d4e1ddba2015ebdc85/LFXTAL016178Reel.pdf" H 8700 2150 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/32.768k-85smxr/smd-quartz-crystals/iqd-frequency-products/lfxtal016178reel/" H 8700 2150 50  0001 C CNN "TME Link"
	1    8700 2150
	-1   0    0    1   
$EndComp
$Comp
L Timer:MCP7940N-xSN U2
U 1 1 5CEF9BB0
P 7750 2250
F 0 "U2" H 7850 1900 50  0000 C CNN
F 1 "MCP7940N-xSN" H 7300 1850 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 7750 2250 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/20005010F.pdf" H 7750 2250 50  0001 C CNN
	1    7750 2250
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT1
U 1 1 5CF7BB91
P 8600 1300
F 0 "BT1" V 8450 1300 50  0000 L CNN
F 1 "KEYS3000" V 8800 1300 50  0000 C CNN
F 2 "humidity:CR1216_Keystone_3000" V 8600 1360 50  0001 C CNN
F 3 "~" V 8600 1360 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/keys3000/batteries-holders/keystone/3000/" V 8600 1300 50  0001 C CNN "TME Link"
	1    8600 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R15
U 1 1 5CF7BDA8
P 7850 1400
F 0 "R15" V 7950 1400 50  0000 C CNN
F 1 "1k" V 7850 1400 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7780 1400 50  0001 C CNN
F 3 "~" H 7850 1400 50  0001 C CNN
	1    7850 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 1550 7850 1800
Wire Wire Line
	8600 1100 8600 900 
$Comp
L power:GND #PWR025
U 1 1 5CF7C329
P 8600 1450
F 0 "#PWR025" H 8600 1200 50  0001 C CNN
F 1 "GND" H 8605 1277 50  0000 C CNN
F 2 "" H 8600 1450 50  0001 C CNN
F 3 "" H 8600 1450 50  0001 C CNN
	1    8600 1450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR023
U 1 1 5CF7C3FA
P 7750 2750
F 0 "#PWR023" H 7750 2500 50  0001 C CNN
F 1 "GND" H 7755 2577 50  0000 C CNN
F 2 "" H 7750 2750 50  0001 C CNN
F 3 "" H 7750 2750 50  0001 C CNN
	1    7750 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 2650 7750 2750
$Comp
L Device:C C5
U 1 1 5CF7C57B
P 8950 2600
F 0 "C5" H 9065 2646 50  0000 L CNN
F 1 "C" H 9065 2555 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8988 2450 50  0001 C CNN
F 3 "~" H 8950 2600 50  0001 C CNN
	1    8950 2600
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 5CF7C5FA
P 8450 2600
F 0 "C4" H 8565 2646 50  0000 L CNN
F 1 "C" H 8565 2555 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8488 2450 50  0001 C CNN
F 3 "~" H 8450 2600 50  0001 C CNN
	1    8450 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8150 2350 8950 2350
Wire Wire Line
	8950 2350 8950 2150
Wire Wire Line
	8950 2150 8850 2150
Wire Wire Line
	8450 2450 8450 2150
Wire Wire Line
	8150 2150 8450 2150
Connection ~ 8450 2150
Wire Wire Line
	8450 2150 8550 2150
Wire Wire Line
	8950 2450 8950 2350
Connection ~ 8950 2350
$Comp
L power:GND #PWR024
U 1 1 5CF7CD47
P 8450 2800
F 0 "#PWR024" H 8450 2550 50  0001 C CNN
F 1 "GND" H 8455 2627 50  0000 C CNN
F 2 "" H 8450 2800 50  0001 C CNN
F 3 "" H 8450 2800 50  0001 C CNN
	1    8450 2800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR026
U 1 1 5CF7CD6C
P 8950 2800
F 0 "#PWR026" H 8950 2550 50  0001 C CNN
F 1 "GND" H 8955 2627 50  0000 C CNN
F 2 "" H 8950 2800 50  0001 C CNN
F 3 "" H 8950 2800 50  0001 C CNN
	1    8950 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8950 2750 8950 2800
Wire Wire Line
	8450 2750 8450 2800
$Comp
L power:+3.3V #PWR014
U 1 1 5CF7D1A9
P 4600 1150
F 0 "#PWR014" H 4600 1000 50  0001 C CNN
F 1 "+3.3V" H 4615 1323 50  0000 C CNN
F 2 "" H 4600 1150 50  0001 C CNN
F 3 "" H 4600 1150 50  0001 C CNN
	1    4600 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 1150 4600 1250
Wire Wire Line
	4500 1350 4500 1250
Wire Wire Line
	4500 1250 4600 1250
Connection ~ 4600 1250
Wire Wire Line
	4600 1250 4600 1350
$Comp
L power:+3.3V #PWR022
U 1 1 5CF7D765
P 7750 750
F 0 "#PWR022" H 7750 600 50  0001 C CNN
F 1 "+3.3V" H 7765 923 50  0000 C CNN
F 2 "" H 7750 750 50  0001 C CNN
F 3 "" H 7750 750 50  0001 C CNN
	1    7750 750 
	1    0    0    -1  
$EndComp
Wire Wire Line
	7750 750  7750 900 
$Comp
L Device:C C3
U 1 1 5CF7DB01
P 7450 1400
F 0 "C3" H 7500 1300 50  0000 L CNN
F 1 "100n" V 7300 1400 50  0000 C CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7488 1250 50  0001 C CNN
F 3 "~" H 7450 1400 50  0001 C CNN
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
NoConn ~ 7350 2350
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
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2180 1050 50  0001 C CNN
F 3 "~" H 2250 1050 50  0001 C CNN
	1    2250 1050
	0    1    1    0   
$EndComp
$Comp
L Device:R R3
U 1 1 5CF89270
P 2250 1250
F 0 "R3" V 2150 1250 50  0000 C CNN
F 1 "0" V 2250 1250 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2180 1250 50  0001 C CNN
F 3 "~" H 2250 1250 50  0001 C CNN
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
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2180 850 50  0001 C CNN
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
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 2180 1450 50  0001 C CNN
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
L power:+3.3V #PWR04
U 1 1 5CFAB772
P 8050 3350
F 0 "#PWR04" H 8050 3200 50  0001 C CNN
F 1 "+3.3V" H 8065 3523 50  0000 C CNN
F 2 "" H 8050 3350 50  0001 C CNN
F 3 "" H 8050 3350 50  0001 C CNN
	1    8050 3350
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5CFC2266
P 8300 3800
F 0 "C2" H 8415 3846 50  0000 L CNN
F 1 "100n" H 8415 3755 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8338 3650 50  0001 C CNN
F 3 "~" H 8300 3800 50  0001 C CNN
	1    8300 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 3350 8050 3500
Wire Wire Line
	8300 3650 8300 3500
Wire Wire Line
	8300 3500 8050 3500
Connection ~ 8050 3500
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
P 7800 3800
F 0 "C1" H 7915 3846 50  0000 L CNN
F 1 "100u" H 7915 3755 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_6.3x5.7" H 7800 3800 50  0001 C CNN
F 3 "~" H 7800 3800 50  0001 C CNN
	1    7800 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 3500 7800 3500
Wire Wire Line
	7800 3500 7800 3650
$Comp
L power:GND #PWR02
U 1 1 5CFCECA5
P 7800 4000
F 0 "#PWR02" H 7800 3750 50  0001 C CNN
F 1 "GND" H 7805 3827 50  0000 C CNN
F 2 "" H 7800 4000 50  0001 C CNN
F 3 "" H 7800 4000 50  0001 C CNN
	1    7800 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 4000 7800 3950
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
NoConn ~ 5200 2350
$Comp
L power:PWR_FLAG #FLG03
U 1 1 5D1EE31E
P 5050 1150
F 0 "#FLG03" H 5050 1225 50  0001 C CNN
F 1 "PWR_FLAG" H 5050 1324 50  0000 C CNN
F 2 "" H 5050 1150 50  0001 C CNN
F 3 "~" H 5050 1150 50  0001 C CNN
	1    5050 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 1150 5050 1250
Wire Wire Line
	5050 1250 4600 1250
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
P 8250 1750
F 0 "#FLG04" H 8250 1825 50  0001 C CNN
F 1 "PWR_FLAG" H 8250 1650 50  0000 C CNN
F 2 "" H 8250 1750 50  0001 C CNN
F 3 "~" H 8250 1750 50  0001 C CNN
	1    8250 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7850 1800 8250 1800
Wire Wire Line
	8250 1800 8250 1750
Connection ~ 7850 1800
Wire Wire Line
	7850 1800 7850 1850
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
F 1 "LED" V 5447 4333 50  0001 R CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5500 4450 50  0001 C CNN
F 3 "~" H 5500 4450 50  0001 C CNN
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
F 1 "470" V 5500 4050 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5430 4050 50  0001 C CNN
F 3 "~" H 5500 4050 50  0001 C CNN
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
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 6130 1800 50  0001 C CNN
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
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 6380 1800 50  0001 C CNN
F 3 "~" H 6450 1800 50  0001 C CNN
	1    6450 1800
	-1   0    0    1   
$EndComp
$Comp
L power:+3.3V #PWR017
U 1 1 5D59172D
P 6200 1550
F 0 "#PWR017" H 6200 1400 50  0001 C CNN
F 1 "+3.3V" H 6215 1723 50  0000 C CNN
F 2 "" H 6200 1550 50  0001 C CNN
F 3 "" H 6200 1550 50  0001 C CNN
	1    6200 1550
	1    0    0    -1  
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
F 1 "LED" V 5197 4333 50  0001 R CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5250 4450 50  0001 C CNN
F 3 "~" H 5250 4450 50  0001 C CNN
	1    5250 4450
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R8
U 1 1 5D657D92
P 5250 4050
F 0 "R8" V 5150 4000 50  0000 L CNN
F 1 "470" V 5250 4050 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5180 4050 50  0001 C CNN
F 3 "~" H 5250 4050 50  0001 C CNN
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
$Comp
L humidity:D_Schottky_AncK D3
U 1 1 5D01B3AF
P 8250 900
F 0 "D3" H 8250 1000 50  0000 R CNN
F 1 "BAT54.215 " H 8250 800 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 8250 900 50  0001 C CNN
F 3 "https://www.tme.eu/Document/2c1c71bcfe5aad5e582fdc49c2dc275f/BAT54.215.pdf" H 8250 900 50  0001 C CNN
F 4 "https://www.tme.eu/se/en/details/bat54.215/smd-schottky-diodes/nexperia/" V 8250 900 50  0001 C CNN "TME Link"
	1    8250 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	8600 900  8400 900 
Wire Wire Line
	7850 900  8100 900 
Wire Wire Line
	7850 900  7850 1250
Wire Wire Line
	8600 1400 8600 1450
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
Text Notes 5400 2850 0    50   ~ 0
CS
Text Notes 5400 2950 0    50   ~ 0
MISO
Text Notes 5400 3050 0    50   ~ 0
MOSI
Text Notes 5400 3150 0    50   ~ 0
SCK
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
NoConn ~ 4300 1350
NoConn ~ 4200 1350
Text Label 8450 900  0    50   ~ 0
VBAT_IN
Text Label 7850 1150 1    50   ~ 0
VBAT_D
Text Label 7850 1750 1    50   ~ 0
VBAT
Text Label 8650 4400 0    50   ~ 0
ANT
Text Label 8250 2150 0    50   ~ 0
X1
Text Label 8250 2350 0    50   ~ 0
X2
$EndSCHEMATC
