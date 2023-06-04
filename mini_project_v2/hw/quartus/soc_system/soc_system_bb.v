
module soc_system (
	clk_clk,
	nios_hex_0_external_connection_export,
	nios_hex_1_external_connection_export,
	nios_hex_2_external_connection_export,
	nios_hex_3_external_connection_export,
	nios_hex_4_external_connection_export,
	nios_hex_5_external_connection_export,
	nios_leds_external_connection_export,
	nios_switches_external_connection_export,
	pll_0_sdram_clk,
	reset_reset_n,
	sdram_controller_0_wire_addr,
	sdram_controller_0_wire_ba,
	sdram_controller_0_wire_cas_n,
	sdram_controller_0_wire_cke,
	sdram_controller_0_wire_cs_n,
	sdram_controller_0_wire_dq,
	sdram_controller_0_wire_dqm,
	sdram_controller_0_wire_ras_n,
	sdram_controller_0_wire_we_n);	

	input		clk_clk;
	output	[6:0]	nios_hex_0_external_connection_export;
	output	[6:0]	nios_hex_1_external_connection_export;
	output	[6:0]	nios_hex_2_external_connection_export;
	output	[6:0]	nios_hex_3_external_connection_export;
	output	[6:0]	nios_hex_4_external_connection_export;
	output	[6:0]	nios_hex_5_external_connection_export;
	output	[9:0]	nios_leds_external_connection_export;
	input	[9:0]	nios_switches_external_connection_export;
	output		pll_0_sdram_clk;
	input		reset_reset_n;
	output	[12:0]	sdram_controller_0_wire_addr;
	output	[1:0]	sdram_controller_0_wire_ba;
	output		sdram_controller_0_wire_cas_n;
	output		sdram_controller_0_wire_cke;
	output		sdram_controller_0_wire_cs_n;
	inout	[15:0]	sdram_controller_0_wire_dq;
	output	[1:0]	sdram_controller_0_wire_dqm;
	output		sdram_controller_0_wire_ras_n;
	output		sdram_controller_0_wire_we_n;
endmodule
