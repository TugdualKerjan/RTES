LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY AtomicCounter IS
	PORT (
		Clk : IN STD_LOGIC;
		nReset : IN STD_LOGIC;
		Address : IN STD_LOGIC;
		ChipSelect : IN STD_LOGIC;

		Read : IN STD_LOGIC;
		Write : IN STD_LOGIC;

		ReadData : OUT STD_LOGIC_VECTOR (31 DOWNTO 0);
		WriteData : IN STD_LOGIC_VECTOR (31 DOWNTO 0)
	);
END AtomicCounter;

ARCHITECTURE comp OF AtomicCounter IS
	SIGNAL iCounter : unsigned(31 DOWNTO 0);
BEGIN
	pRegWr :
	PROCESS (Clk, nReset)
	BEGIN
		IF nReset = '0' THEN
			iCounter <= X"0000_0000";
		ELSIF rising_edge(Clk) THEN
			IF ChipSelect = '1' AND Write = '1' THEN
				CASE Address IS
					WHEN '0' => iCounter <= unsigned(WriteData(31 DOWNTO 0));
					WHEN '1' => iCounter <= iCounter + 1;
				END CASE;
			END IF;
		END IF;
	END PROCESS pRegWr;
	pRegRd :
	PROCESS (Clk)
	BEGIN
		IF rising_edge(Clk) THEN
			ReadData <= (OTHERS => '0');
			IF ChipSelect = '1' AND Read = '1' THEN
				CASE Address IS
					WHEN '0' => ReadData <= STD_LOGIC_VECTOR(iCounter);
					WHEN '1' => NULL;
				END CASE;
			END IF;
		END IF;
	END PROCESS pRegRd;
END comp;
