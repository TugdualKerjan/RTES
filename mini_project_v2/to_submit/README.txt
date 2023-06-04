# CS476 RTOS Mini-Project
## Authors
PELUSO Nathan - KERJAN Tugdual
## Description
Files written to implement the demo of our project.
## Content
```
.
├── C 						// All C files and related
│   ├── mini_project_v3
│   │   ├── calculs.h
│   │   ├── create-this-app
│   │   ├── Makefile				// Change C_SRC to switch between "test_and_profile.c" or "mini_project_with_fake_camera.c"
│   │   ├── mini_project_v3.elf
│   │   ├── mini_project_v3.map
│   │   ├── mini_project_v3.objdump
│   │   ├── mini_project_with_fake_camera.c	// Demo with emulated camera
│   │   ├── num_disp.h
│   │   └── test_and_profile.c			// Test & profiling
│   └── mini_project_v3_bsp			// System-generated BSP
│       ├── ...
│       └── system.h				// System-generated peripherals addresses etc
├── hdl
│   ├── accel_averager.vhd			// VHDL code for accelerator
│   └── DE1_SoC_top_level.vhd			// Top-level VHDL code
├── misc
│   ├── accel_average_hw.tcl			// Custom Qsys component for accelerator
│   ├── final_design.sof			// Final compiled design
│   ├── soc_system.qsys				// Final Qsys design
│   └── test.do					// Custom script used for RTL simulation and debug of Accelerator module
└── README.txt
```
