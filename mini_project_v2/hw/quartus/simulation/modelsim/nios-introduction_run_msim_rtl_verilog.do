transcript on
if ![file isdirectory verilog_libs] {
	file mkdir verilog_libs
}

vlib verilog_libs/altera_ver
vmap altera_ver ./verilog_libs/altera_ver
vlog -vlog01compat -work altera_ver {/opt/intelFPGA/18.1/quartus/eda/sim_lib/altera_primitives.v}

vlib verilog_libs/lpm_ver
vmap lpm_ver ./verilog_libs/lpm_ver
vlog -vlog01compat -work lpm_ver {/opt/intelFPGA/18.1/quartus/eda/sim_lib/220model.v}

vlib verilog_libs/sgate_ver
vmap sgate_ver ./verilog_libs/sgate_ver
vlog -vlog01compat -work sgate_ver {/opt/intelFPGA/18.1/quartus/eda/sim_lib/sgate.v}

vlib verilog_libs/altera_mf_ver
vmap altera_mf_ver ./verilog_libs/altera_mf_ver
vlog -vlog01compat -work altera_mf_ver {/opt/intelFPGA/18.1/quartus/eda/sim_lib/altera_mf.v}

vlib verilog_libs/altera_lnsim_ver
vmap altera_lnsim_ver ./verilog_libs/altera_lnsim_ver
vlog -sv -work altera_lnsim_ver {/opt/intelFPGA/18.1/quartus/eda/sim_lib/altera_lnsim.sv}

vlib verilog_libs/cyclonev_ver
vmap cyclonev_ver ./verilog_libs/cyclonev_ver
vlog -vlog01compat -work cyclonev_ver {/opt/intelFPGA/18.1/quartus/eda/sim_lib/mentor/cyclonev_atoms_ncrypt.v}
vlog -vlog01compat -work cyclonev_ver {/opt/intelFPGA/18.1/quartus/eda/sim_lib/mentor/cyclonev_hmi_atoms_ncrypt.v}
vlog -vlog01compat -work cyclonev_ver {/opt/intelFPGA/18.1/quartus/eda/sim_lib/cyclonev_atoms.v}

vlib verilog_libs/cyclonev_hssi_ver
vmap cyclonev_hssi_ver ./verilog_libs/cyclonev_hssi_ver
vlog -vlog01compat -work cyclonev_hssi_ver {/opt/intelFPGA/18.1/quartus/eda/sim_lib/mentor/cyclonev_hssi_atoms_ncrypt.v}
vlog -vlog01compat -work cyclonev_hssi_ver {/opt/intelFPGA/18.1/quartus/eda/sim_lib/cyclonev_hssi_atoms.v}

vlib verilog_libs/cyclonev_pcie_hip_ver
vmap cyclonev_pcie_hip_ver ./verilog_libs/cyclonev_pcie_hip_ver
vlog -vlog01compat -work cyclonev_pcie_hip_ver {/opt/intelFPGA/18.1/quartus/eda/sim_lib/mentor/cyclonev_pcie_hip_atoms_ncrypt.v}
vlog -vlog01compat -work cyclonev_pcie_hip_ver {/opt/intelFPGA/18.1/quartus/eda/sim_lib/cyclonev_pcie_hip_atoms.v}

if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlib soc_system
vmap soc_system soc_system
vlog -vlog01compat -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/soc_system.v}
vlog -vlog01compat -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/altera_avalon_sc_fifo.v}
vlog -vlog01compat -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/altera_reset_controller.v}
vlog -vlog01compat -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/altera_reset_synchronizer.v}
vlog -vlog01compat -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/soc_system_jtag_uart_0.v}
vlog -vlog01compat -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/soc_system_mm_interconnect_0.v}
vlog -vlog01compat -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/soc_system_mm_interconnect_0_avalon_st_adapter.v}
vlog -vlog01compat -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/soc_system_mm_interconnect_0_avalon_st_adapter_001.v}
vlog -vlog01compat -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/soc_system_nios2_gen2_0.v}
vlog -vlog01compat -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/soc_system_nios_hex_0.v}
vlog -vlog01compat -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/soc_system_nios_leds.v}
vlog -vlog01compat -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/soc_system_nios_switches.v}
vlog -vlog01compat -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/soc_system_performance_counter_0.v}
vlog -vlog01compat -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/soc_system_pll_0.v}
vlog -vlog01compat -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/soc_system_sdram_controller_0.v}
vlog -vlog01compat -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/soc_system_sysid.v}
vlog -vlog01compat -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/altera_avalon_st_clock_crosser.v}
vlog -vlog01compat -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/altera_avalon_st_handshake_clock_crosser.v}
vlog -sv -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/altera_merlin_arbitrator.sv}
vlog -sv -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/altera_merlin_burst_adapter.sv}
vlog -sv -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/altera_merlin_burst_adapter_uncmpr.sv}
vlog -sv -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/altera_merlin_burst_uncompressor.sv}
vlog -sv -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/altera_merlin_master_agent.sv}
vlog -sv -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/altera_merlin_master_translator.sv}
vlog -sv -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/altera_merlin_slave_agent.sv}
vlog -sv -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/altera_merlin_slave_translator.sv}
vlog -sv -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/altera_merlin_width_adapter.sv}
vlog -vlog01compat -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/altera_std_synchronizer_nocut.v}
vlog -sv -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/soc_system_irq_mapper.sv}
vlog -sv -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/soc_system_mm_interconnect_0_avalon_st_adapter_001_error_adapter_0.sv}
vlog -sv -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/soc_system_mm_interconnect_0_avalon_st_adapter_error_adapter_0.sv}
vlog -sv -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/soc_system_mm_interconnect_0_cmd_demux.sv}
vlog -sv -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/soc_system_mm_interconnect_0_cmd_demux_001.sv}
vlog -sv -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/soc_system_mm_interconnect_0_cmd_demux_002.sv}
vlog -sv -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/soc_system_mm_interconnect_0_cmd_mux.sv}
vlog -sv -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/soc_system_mm_interconnect_0_cmd_mux_001.sv}
vlog -sv -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/soc_system_mm_interconnect_0_cmd_mux_002.sv}
vlog -sv -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/soc_system_mm_interconnect_0_router.sv}
vlog -sv -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/soc_system_mm_interconnect_0_router_001.sv}
vlog -sv -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/soc_system_mm_interconnect_0_router_002.sv}
vlog -sv -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/soc_system_mm_interconnect_0_router_003.sv}
vlog -sv -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/soc_system_mm_interconnect_0_router_004.sv}
vlog -sv -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/soc_system_mm_interconnect_0_router_005.sv}
vlog -sv -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/soc_system_mm_interconnect_0_rsp_demux.sv}
vlog -sv -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/soc_system_mm_interconnect_0_rsp_mux.sv}
vlog -sv -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/soc_system_mm_interconnect_0_rsp_mux_001.sv}
vlog -sv -work soc_system +incdir+/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/soc_system_mm_interconnect_0_rsp_mux_002.sv}
vcom -93 -work work {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/hdl/DE1_SoC_top_level.vhd}
vcom -93 -work soc_system {/home/nathan/Documents/Cours/EPFL_RTES_CS476/Code/mini_project_v2/hw/quartus/db/ip/soc_system/submodules/accel_averager.vhd}

