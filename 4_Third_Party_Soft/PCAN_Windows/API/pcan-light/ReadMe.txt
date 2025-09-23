===============================================================================
ReadMe.txt

PCAN-Light V2.xx
Copyright (c) 2015 PEAK-System Technik GmbH Darmstadt, Germany
All rights reserved.
===============================================================================

Maximize the Notepad Window to read this file more easily.


Contents:
---------
  * Introduction
  * Rights to use these files
  * System Requirements
  * Contents of this directory
  * Installation of PCAN hardware
  * How to contact PEAK-System Technik GmbH
  * LIFE SUPPORT APPLIANCES


Introduction
------------
The PCAN system of the company PEAK-System Technik GmbH consists of a
collection of Windows Device Drivers. These allow the Real-time connection of
Windows applications to all CAN busses that are physically connected to the PC
via a PCAN hardware.

PCAN-Light is a simple programming interface to the PCAN system. Via several
Interface DLLs it is possible to connect own applications to the Device drivers
and the PCAN hardware, to communicate with the CAN busses.

The provided drivers, the PCAN-Light API, and the PCAN-View CAN bus Monitor
software are the feature-reduced versions of the larger software packages
PCAN-Evaluation, PCAN-Developer, or PCAN-Explorer. These can be aquired
separately.


Rights to use these files
-------------------------
PEAK-System Technik GmbH grants the right to the customer to use the files in
this software package as long as this is done in connection with original
hardware by PEAK-System or OEM hardware coming from PEAK-System. It is NOT
allowed to use any of these files (even not parts) with third-party hardware.

If you are not sure whether you have acquired an appropriate license with the
used hardware, please contact our technical support team (support@peak-system.com).


System Requirements
-------------------
- Operating systems: Windows 7/Vista/XP
  (Driver for Linux could be download at www.peak-system.com/linux)


Contents of this directory
--------------------------
ReadMe.txt
    This text file.

LiesMich.txt
    The german translation of this file.

PCANLight_enu.chm
    The PCAN-Light documentation in English.

PCANLight_deu.chm
    The PCAN-Light documentation in German.

\Include
    The Header files for different programming languages and development environments.

\Win32
    The 32Bit Interface DLLs and the LIB files for the different CAN Interfaces.    
	
    pcan_dng.dll for use with:
      PCAN-Dongle 

    pcan_isa.dll & pcan_2isa.dll for use with:
      PCAN-PC/104
      PCAN-ISA
	
    pcan_pcc.dll & pcan_2pcc.dll for use with:
      PCAN-PC Card

    pcan_pci.dll & pcan_2pci.dll for use with:
      PCAN-cPCI
      PCAN-miniPCI
      PCAN-PC/104-Plus
      PCAN-PCI
      PCAN-PCI Express

    pcan_usb.dll & pcan_2usb.dll for use with:
      PCAN-USB
      PCAN-USB Hub
      PCAN-USB Pro
	
    \BB_LIB
        32Bit LIB Files for Borland Builder 

    \VC_LIB
        32Bit LIB Files for Visual C/C++

\x64
    The 64Bit Interface DLLs for the different CAN Interfaces.    
	
    pcan_pci.dll & pcan_2pci.dll for use with:
      PCAN-cPCI
      PCAN-miniPCI
      PCAN-PC/104-Plus
      PCAN-PCI
      PCAN-PCI Express

    pcan_usb.dll & pcan_2usb.dll for use with:
      PCAN-USB
      PCAN-USB Hub
      PCAN-USB Pro
		
\Samples
    Contains example files that demonstrate the use of the PCAN-Light API in
    different programming languages and development environments.


Installation of PCAN hardware
-----------------------------
For information about the installation of PCAN hardware, please refer to the
user manual of the respective hardware. The hardware user manuals are located
in the folder <Product CD>\Pdf.


How to contact PEAK-System Technik GmbH
---------------------------------------
If you have any questions concerning the installation of PCAN hardware, or
require information about other PEAK CAN products, then please contact us:

PEAK-System Technik GmbH
Otto-Roehm-Str. 69
D-64293 Darmstadt
Germany

Tel. +49 6151 / 8173-20
FAX  +49 6151 / 8173-29

support@peak-system.com
http://www.peak-system.com


LIFE SUPPORT APPLIANCES
-----------------------
These products are not designed for use in life support appliances, devices,
or systems where malfunction of these products can reasonably be expected to
result in personal injury. PEAK-System customers using or selling these
products for use in such applications do so at their own risk and agree to
fully indemnify PEAK-System for any damages resulting from such improper use
or sale.
