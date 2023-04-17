LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY custom_swap IS
	PORT(
		--signal clk : IN STD_LOGIC; -- CPU's master-input clk <required for multi-cycle>
		--signal reset : IN STD_LOGIC; -- CPU's master asynchronous reset <required for multi-cycle>
		--signal clk_en: IN STD_LOGIC; -- Clock-qualifier <required for multi-cycle>
		--signal start: IN STD_LOGIC; -- True when this instr. issues <required for multi-cycle>
			dataa: IN STD_LOGIC_VECTOR (31 DOWNTO 0); -- operand A <always required>
		--signal datab: IN STD_LOGIC_VECTOR (31 DOWNTO 0); -- operand B <optional>
		--signal prefix: IN STD_LOGIC_VECTOR (10 DOWNTO 0); -- prefix <optional>
			result : OUT STD_LOGIC_VECTOR (31 DOWNTO 0) -- result <always required>
);
END custom_swap;
ARCHITECTURE arch OF custom_swap IS
	--signal clk: IN STD_LOGIC;
	--signal reset : IN STD_LOGIC;
	--signal clk_en: IN STD_LOGIC;
	--signal start: IN STD_LOGIC;
	signal dataa: STD_LOGIC_VECTOR (31 DOWNTO 0);
	--signal datab: IN STD_LOGIC_VECTOR (31 DOWNTO 0);
	--signal prefix: IN STD_LOGIC_VECTOR (10 DOWNTO 0);
	signal result : STD_LOGIC_VECTOR (31 DOWNTO 0);
BEGIN
	result(7 downto 0) <= dataa(31 downto 24);
	result(31 downto 24) <= dataa(7 downto 0);
	for i in dataa(24 downto 7)'range generate
		result(i) <= dataa(24 downto 7)(i)  
	end generate;
END custom_swap;