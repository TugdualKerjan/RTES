	component soc_system is
		port (
			clk_clk                             : in    std_logic                     := 'X';             -- clk
			pll_0_outclk2_clk                   : out   std_logic;                                        -- clk
			reset_reset_n                       : in    std_logic                     := 'X';             -- reset_n
			sdram_controller_0_wire_addr        : out   std_logic_vector(12 downto 0);                    -- addr
			sdram_controller_0_wire_ba          : out   std_logic_vector(1 downto 0);                     -- ba
			sdram_controller_0_wire_cas_n       : out   std_logic;                                        -- cas_n
			sdram_controller_0_wire_cke         : out   std_logic;                                        -- cke
			sdram_controller_0_wire_cs_n        : out   std_logic;                                        -- cs_n
			sdram_controller_0_wire_dq          : inout std_logic_vector(15 downto 0) := (others => 'X'); -- dq
			sdram_controller_0_wire_dqm         : out   std_logic_vector(1 downto 0);                     -- dqm
			sdram_controller_0_wire_ras_n       : out   std_logic;                                        -- ras_n
			sdram_controller_0_wire_we_n        : out   std_logic;                                        -- we_n
			i2c_0_i2c_scl                       : inout std_logic                     := 'X';             -- scl
			i2c_0_i2c_sda                       : inout std_logic                     := 'X';             -- sda
			switches_external_connection_export : in    std_logic_vector(9 downto 0)  := (others => 'X'); -- export
			leds_external_connection_export     : out   std_logic_vector(9 downto 0)                      -- export
		);
	end component soc_system;

	u0 : component soc_system
		port map (
			clk_clk                             => CONNECTED_TO_clk_clk,                             --                          clk.clk
			pll_0_outclk2_clk                   => CONNECTED_TO_pll_0_outclk2_clk,                   --                pll_0_outclk2.clk
			reset_reset_n                       => CONNECTED_TO_reset_reset_n,                       --                        reset.reset_n
			sdram_controller_0_wire_addr        => CONNECTED_TO_sdram_controller_0_wire_addr,        --      sdram_controller_0_wire.addr
			sdram_controller_0_wire_ba          => CONNECTED_TO_sdram_controller_0_wire_ba,          --                             .ba
			sdram_controller_0_wire_cas_n       => CONNECTED_TO_sdram_controller_0_wire_cas_n,       --                             .cas_n
			sdram_controller_0_wire_cke         => CONNECTED_TO_sdram_controller_0_wire_cke,         --                             .cke
			sdram_controller_0_wire_cs_n        => CONNECTED_TO_sdram_controller_0_wire_cs_n,        --                             .cs_n
			sdram_controller_0_wire_dq          => CONNECTED_TO_sdram_controller_0_wire_dq,          --                             .dq
			sdram_controller_0_wire_dqm         => CONNECTED_TO_sdram_controller_0_wire_dqm,         --                             .dqm
			sdram_controller_0_wire_ras_n       => CONNECTED_TO_sdram_controller_0_wire_ras_n,       --                             .ras_n
			sdram_controller_0_wire_we_n        => CONNECTED_TO_sdram_controller_0_wire_we_n,        --                             .we_n
			i2c_0_i2c_scl                       => CONNECTED_TO_i2c_0_i2c_scl,                       --                    i2c_0_i2c.scl
			i2c_0_i2c_sda                       => CONNECTED_TO_i2c_0_i2c_sda,                       --                             .sda
			switches_external_connection_export => CONNECTED_TO_switches_external_connection_export, -- switches_external_connection.export
			leds_external_connection_export     => CONNECTED_TO_leds_external_connection_export      --     leds_external_connection.export
		);

