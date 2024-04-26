<h2>Software "Heating table"</h2>

<div id="badges" align="center">
    <img alt="Static Badge" src="https://img.shields.io/badge/Version%20-1.0%20-violet">
    <img alt="Static Badge" src="https://img.shields.io/badge/CPU%20-ATMega328p%20-blue">
    <img alt="Static Badge" src="https://img.shields.io/badge/License%20-MIT%20-red">
</div>
Easy controller for Heating table.
		

<details><summary><b>Tools and Shema</b></summary>
<div>Programmer: USBASP or AVRISP</div>
<div>Toolchain: WinAVR-20100110</div>
<div>Compiler: AVR-GCC</div>
<div>Download: AVRDuDe 7.0</div>

 <div>Control: Key (PB0)</div>
 <div>TIARC: MOC3021 -> BCA16-600 (OC1A: PB1)</div>
 <div>Sensor: max6675 (MOSI: PB3, MISO: PB4, SCK: PB5, SS: PB2)</div>
 <div>UART: not use (Rx: PD0, Tx: PD1)</div>
 <div>Zero crossing: PC814 <- 2W10 (INT0: PD2)</div>
 <div>Control: Encoder (DW: PD3, CLK: PD4)</div>
 <div>Display: 7H x3 BC12-GWA (Katode(GND): PD5-PD7, Anode(VCC): 74H595N Q0-Q7)</div>
 <div>Register: 74H595N (Q0-Q7: Anode Display, SH_CP/CLK: PC3, ST_CP/SET: PC2, DS/DATA: PC1)</div>
</details>

<details><summary><b>Settings in main.h</b></summary>
<div>//PID settings</div>
<div>Kp  5</div>
<div>USER_PID_PERIOD 1000 ms</div>
<div>MAX_OUTPUT_PID 535 - system parameter</div>
<div>MAX_TIM1 545 - system parameter</div>

<div>Display settings
<div>USER_DISPLAY_FREQUENCY 300 max 300HZ</div>
<div>USER_DELAY_AUTOOUT 3000 ms</div>

<div>Encoder settings</div>
<div>USER_ENCODER_PERIOD 100 ms</div>

<div>Measurement settings </div>
<div>START_TEMP 250</div>
<div>MAX_TEMP 400</div>
</details>

<b>Building:</b>
Makefile is used for compilation and firmware (for help enter: >>make help).
Assemble the project using the "make" instructions.

<b>Download:</b>
Disconnect the MAX6675 from the SPI (open jumper). Connect the "USB ASP" programmer to the ISP connector on the controller board and to a free USB port on the computer.
Use the "make flash" instruction to load the software into the controller's memory. 
Return the jumpers to their place.