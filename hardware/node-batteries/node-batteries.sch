EESchema Schematic File Version 4
LIBS:node-batteries-cache
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
L Device:Battery_Cell BT1
U 1 1 5CF4D46F
P 2600 3150
F 0 "BT1" H 2718 3246 50  0000 L CNN
F 1 "Battery_Cell" H 2718 3155 50  0000 L CNN
F 2 "humidity:AA_Battery_Holder" V 2600 3210 50  0001 C CNN
F 3 "https://www.tme.eu/se/en/details/bh-311-1p/batteries-holders/comf/" V 2600 3210 50  0001 C CNN
	1    2600 3150
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT2
U 1 1 5CF4D50A
P 2600 3550
F 0 "BT2" H 2718 3646 50  0000 L CNN
F 1 "Battery_Cell" H 2718 3555 50  0000 L CNN
F 2 "humidity:AA_Battery_Holder" V 2600 3610 50  0001 C CNN
F 3 "https://www.tme.eu/se/en/details/bh-311-1p/batteries-holders/comf/" V 2600 3610 50  0001 C CNN
	1    2600 3550
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Male J1
U 1 1 5CF4D605
P 3950 3300
F 0 "J1" H 3923 3230 50  0000 R CNN
F 1 "Conn_01x03_Male" H 3923 3321 50  0000 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 3950 3300 50  0001 C CNN
F 3 "~" H 3950 3300 50  0001 C CNN
	1    3950 3300
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2600 2950 2600 2850
Wire Wire Line
	2600 2850 3500 2850
Wire Wire Line
	3500 2850 3500 3200
Wire Wire Line
	3500 3200 3750 3200
Wire Wire Line
	3750 3400 3500 3400
Wire Wire Line
	3500 3400 3500 3700
Wire Wire Line
	3500 3700 2600 3700
Wire Wire Line
	2600 3700 2600 3650
Wire Wire Line
	2600 3250 2600 3300
Wire Wire Line
	2600 3300 3750 3300
Connection ~ 2600 3300
Wire Wire Line
	2600 3300 2600 3350
$Comp
L Mechanical:MountingHole MH1
U 1 1 5CF4DA0D
P 5650 3250
F 0 "MH1" H 5750 3296 50  0000 L CNN
F 1 "MountingHole M3" H 5750 3205 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 5650 3250 50  0001 C CNN
F 3 "~" H 5650 3250 50  0001 C CNN
	1    5650 3250
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole MH2
U 1 1 5CF4DA9E
P 5650 3450
F 0 "MH2" H 5750 3496 50  0000 L CNN
F 1 "MountingHole M3" H 5750 3405 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 5650 3450 50  0001 C CNN
F 3 "~" H 5650 3450 50  0001 C CNN
	1    5650 3450
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole MH3
U 1 1 5CF4DABE
P 5650 3650
F 0 "MH3" H 5750 3696 50  0000 L CNN
F 1 "MountingHole M3" H 5750 3605 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 5650 3650 50  0001 C CNN
F 3 "~" H 5650 3650 50  0001 C CNN
	1    5650 3650
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole MH4
U 1 1 5CF4DAE2
P 5650 3850
F 0 "MH4" H 5750 3896 50  0000 L CNN
F 1 "MountingHole M3" H 5750 3805 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 5650 3850 50  0001 C CNN
F 3 "~" H 5650 3850 50  0001 C CNN
	1    5650 3850
	1    0    0    -1  
$EndComp
Text Label 2750 2850 0    50   ~ 0
V_BAT
Text Label 2750 3300 0    50   ~ 0
V_MID
Text Label 2750 3700 0    50   ~ 0
GND
$Comp
L Mechanical:MountingHole MH5
U 1 1 5CF45294
P 5650 4050
F 0 "MH5" H 5750 4096 50  0000 L CNN
F 1 "MountingHole M3" H 5750 4005 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 5650 4050 50  0001 C CNN
F 3 "~" H 5650 4050 50  0001 C CNN
	1    5650 4050
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole MH6
U 1 1 5CF452BC
P 5650 4250
F 0 "MH6" H 5750 4296 50  0000 L CNN
F 1 "MountingHole M3" H 5750 4205 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3" H 5650 4250 50  0001 C CNN
F 3 "~" H 5650 4250 50  0001 C CNN
	1    5650 4250
	1    0    0    -1  
$EndComp
$EndSCHEMATC
