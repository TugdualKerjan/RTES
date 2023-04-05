LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY ParallelPort IS
	PORT (
		-- Avalon interfaces signals
		Clk : IN STD_LOGIC;
		nReset : IN STD_LOGIC;
		Address : IN STD_LOGIC_VECTOR (2 DOWNTO 0);
		ChipSelect : IN STD_LOGIC;
		Read : IN STD_LOGIC;
		Write : IN STD_LOGIC;
		ReadData : OUT STD_LOGIC_VECTOR (7 DOWNTO 0);
		WriteData : IN STD_LOGIC_VECTOR (7 DOWNTO 0);
		-- Parallel Port external interface
		ParPort : INOUT STD_LOGIC_VECTOR (7 DOWNTO 0);

		IRQ : OUT STD_LOGIC
	);
END ParallelPort;

ARCHITECTURE comp OF ParallelPort IS
	SIGNAL iRegDir : STD_LOGIC_VECTOR (7 DOWNTO 0);
	SIGNAL iRegPort : STD_LOGIC_VECTOR (7 DOWNTO 0);
	SIGNAL iRegPin : STD_LOGIC_VECTOR (7 DOWNTO 0);
	SIGNAL iEOT : STD_LOGIC;
	SIGNAL iClrEOT : STD_LOGIC;
	SIGNAL iIRQEN : STD_LOGIC;
BEGIN
	-- Parallel Port output value
	pPort :
	PROCESS (iRegDir, iRegPort)
	BEGIN
		FOR i IN 0 TO 7 LOOP
			IF iRegDir(i) = '1' THEN
				ParPort(i) <= iRegPort(i);
			ELSE
				ParPort(i) <= 'Z';
			END IF;
		END LOOP;
	END PROCESS pPort;

	pRegWr :
	PROCESS (Clk, nReset)
	BEGIN
		IF nReset = '0' THEN
			iRegDir <= (OTHERS => '0'); -- Input by default
			iIRQEn <= '0';
		ELSIF rising_edge(Clk) THEN
			iClrEOT <= '0';
			IF ChipSelect = '1' AND Write = '1' THEN -- Write cycle
				CASE Address(2 DOWNTO 0) IS
					WHEN "000" => iRegDir <= WriteData;
					WHEN "010" => iRegPort <= WriteData;
					WHEN "011" => iRegPort <= iRegPort OR WriteData;
					WHEN "100" => iRegPort <= iRegPort AND NOT WriteData;
					WHEN "101" => iIRQEN <= WriteData(0);
					WHEN "110" => iClrEOT <= WriteData(0);
					WHEN OTHERS => NULL;
				END CASE;
			END IF;
		END IF;
	END PROCESS pRegWr;

	pRegRd :
	PROCESS (Clk)
	BEGIN
		IF rising_edge(Clk) THEN
			ReadData <= (OTHERS => '0'); -- default value
			IF ChipSelect = '1' AND Read = '1' THEN -- Read cycle
				CASE Address(2 DOWNTO 0) IS
					WHEN "000" => ReadData <= iRegDir;
					WHEN "001" => ReadData <= iRegPin;
					WHEN "010" => ReadData <= iRegPort;
					WHEN "101" => ReadData(0) <= iIRQEn;
					WHEN "110" => ReadData(0) <= iEOT;
					WHEN OTHERS => NULL;
				END CASE;
			END IF;
		END IF;
	END PROCESS pRegRd;

	pInterrupt :
	PROCESS (Clk)
	BEGIN
		IF nReset = '0' THEN
			iEOT <= '0';
		ELSIF rising_edge(Clk) THEN
			IF iClrEOT = '1' THEN
				iEOT <= '0';
			END IF;
			IF ChipSelect = '1' AND Write = '1' THEN -- Write cycle
				CASE Address(2 DOWNTO 0) IS
					WHEN "010" => iEOT <= '1';
					WHEN "011" => iEOT <= '1';
					WHEN "100" => iEOT <= '1';
					WHEN OTHERS => NULL;
				END CASE;
			END IF;
		END IF;
	END PROCESS pInterrupt;

	IRQ <= '1' WHEN iEOT = '1' AND iIRQEn = '1' ELSE
		'0';
	-- Parallel Port Input value
	iRegPin <= ParPort;
END comp;