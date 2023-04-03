library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity Counter is 
	port(
		Clk : IN std_logic;
		nReset : IN std_logic;
		Address : IN std_logic_vector(2 downto 0);
		ChipSelect : IN std_logic;
		
		Read: IN std_logic;
		Write: IN std_logic;
		
		ReadData: OUT std_logic_vector (31 downto 0	);
		WriteData: IN std_logic_vector (31 downto 0);
		
		IRQ: OUT std_logic
	);
End Counter;

Architecture comp of Counter is
		signal iCounter : unsigned(31 downto 0);
		signal iEn : std_logic;
		signal iRz : std_logic;
		signal iEOT : std_logic;
		signal iClrEOT : std_logic;
		signal iIRQEn : std_logic;
		signal iCounterMax: unsigned(31 downto 0);
	BEGIN
		pCounter:
			process(Clk)
			begin
				if rising_edge(Clk) then
					if iRz = '1' then
						iCounter <= (others => '0');
					elsif iEn = '1' then
						iCounter <= iCounter+1;
					end if;
				end if;
		end process pCounter;
		pRegWr:
			process(Clk, nReset)
			begin
				if nReset = '0' then
					iEn <= '0';
					iRz <= '0';
					iIRQEn <= '0';
					iCounterMax <= X"ffff_ffff";
				elsif rising_edge(Clk) then
					iRz <= '0';
					iClrEOT <= '0';
					if ChipSelect = '1' and Write ='1' then
						case Address(2 downto 0) is
							when "000" => null;
							when "001" => iRz <= '1';
							when "010" => iEn <= '1';
							when "011" => iEn <= '0';
							when "100" => iIRQEn <= WriteData(0);
							when "101" => iClrEOT <= WriteData(0);
							when "110" => iCounterMax <= unsigned(WriteData(31 downto 0)); 
							when others => null;
						end case;
					end if;
				end if;
			end process pRegWr;
		pRegRd:
			process(Clk)
			begin
				if rising_edge(Clk) then
					ReadData <= (others => '0');
					if ChipSelect = '1' and Read = '1' then
						case Address(2 downto 0) is
							when "000" => ReadData <= std_logic_vector(iCounter);
							when "100" => ReadData(0) <= iIRQEn;
							when "101" => ReadData(0) <= iEOT;
											  ReadData(1) <= iEn;
							when "110" => ReadData <= std_logic_vector(iCounterMax);
							when others => null;
						end case;
					end if;
				end if;
			end process pRegRd;
		pInterrupt:
			process(Clk)
			begin
			 if nReset = '0' then
				iEOT <= '0';
			 elsif rising_edge(Clk) then
					if iCounter = iCounterMax then
						iEOT <= '1';
					elsif iClrEOT = '1' then
						iEOT <= '0';
					end if;
				end if;
			end process pInterrupt;
		IRQ <= '1' when iEOT='1' and iIRQEn='1' and iEn='1' else '0';
							
END comp;