<h2>Software "Heating table"</h2>

<div id="badges" align="center">
    <img alt="Static Badge" src="https://img.shields.io/badge/Version%20-0.2%20-violet">
    <img alt="Static Badge" src="https://img.shields.io/badge/CPU%20-ATMega328p%20-blue">
    <img alt="Static Badge" src="https://img.shields.io/badge/License%20-MIT%20-red">
</div>
Easy controller for Heating table.
		

<details><summary><b>Environment and Tools</b></summary>
<div>Programmer: USBASP or AVRISP</div>
<div>Toolchain: WinAVR-20100110</div>
<div>Compiler: AVR-GCC</div>
<div>Download: AVRDuDe 7.0</div>
</details>

<details><summary><b>Settings in main.h</b></summary>

</details>

<b>Building:</b>
Makefile is used for compilation and firmware (for help enter: >>make help).
Assemble the project using the "make" instructions.

<b>Download:</b>
Disconnect the MAX6675 from the SPI (open jumper). Connect the "USB ASP" programmer to the ISP connector on the controller board and to a free USB port on the computer.
Use the "make flash" instruction to load the software into the controller's memory. 
Return the jumpers to their place.