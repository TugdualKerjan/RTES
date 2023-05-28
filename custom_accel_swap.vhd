LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY custom_accel_swap IS
    PORT (
        -- Basic signals
        Clk : IN STD_LOGIC;
        nReset : IN STD_LOGIC;

        -- IRQ signal
        IRQ : OUT STD_LOGIC;
        -- Avalon master signals
        mAddress : OUT STD_LOGIC_VECTOR (31 DOWNTO 0);
        mRead : OUT STD_LOGIC;
        mReadData : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
        mWrite : OUT STD_LOGIC;
        mWriteData : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
        mWaitRequest : IN STD_LOGIC;

        -- Avalon slave signals
        sAddress : IN STD_LOGIC_VECTOR (1 DOWNTO 0);
        sChipSelect : IN STD_LOGIC;
        sRead : IN STD_LOGIC;
        sReadData : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
        sWrite : IN STD_LOGIC;
        sWriteData : IN STD_LOGIC_VECTOR(31 DOWNTO 0)
    );
END ENTITY custom_accel_swap;

ARCHITECTURE comp OF custom_accel_swap IS
    SIGNAL iSrcAddr : STD_LOGIC_VECTOR (31 DOWNTO 0);
    SIGNAL iDstAddr : STD_LOGIC_VECTOR (31 DOWNTO 0);
    SIGNAL iLen : unsigned (15 DOWNTO 0);
    SIGNAL iIRQEN : STD_LOGIC;
    SIGNAL iDone : STD_LOGIC;
    SIGNAL iClrDone : STD_LOGIC;
    SIGNAL iStart : STD_LOGIC;
    SIGNAL iIndex : unsigned(15 DOWNTO 0);
    SIGNAL iWordInput : STD_LOGIC_VECTOR(31 DOWNTO 0);
    SIGNAL iWordOutput : STD_LOGIC_VECTOR(31 DOWNTO 0);
    -- State machine
    TYPE SM IS(IDLE, READ_WD, WAITR, COMPUTE, WRITE_WD, WAITW, CHECK);
    SIGNAL StateM : SM;

BEGIN
    -- Write from slave
    SlaveWr :
    PROCESS (clk, nReset)
    BEGIN
        IF nReset = '0' THEN
            iSrcAddr <= (OTHERS => '0');
            iDstAddr <= (OTHERS => '0');
            iLen <= (OTHERS => '0');
            iStart <= '0';
            iIRQEN <= '0';
        ELSIF rising_edge(clk) THEN
            iStart <= '0';
            iClrDone <= '0';
            IF sChipSelect = '1' AND sWrite = '1' THEN
                CASE sAddress IS
                    WHEN "00" => iSrcAddr <= sWriteData;
                    WHEN "01" => iDstAddr <= sWriteData;
                    WHEN "10" => iLen <= unsigned(sWriteData (15 DOWNTO 0));
                    WHEN "11" => iStart <= sWriteData(0);
                        iIRQEN <= sWritedata(2);
                        iClrDone <= sWriteData(3);
                    WHEN OTHERS => NULL;
                END CASE;
            END IF;
        END IF;
    END PROCESS SlaveWr;

    -- Read from slave
    SlaveRd :
    PROCESS (clk)
    BEGIN
        IF rising_edge(clk) THEN
            IF sChipSelect = '1' AND sRead = '1' THEN
                sReadData <= (OTHERS => '0');
                CASE sAddress IS
                    WHEN "00" => sReadData <= iSrcAddr;
                    WHEN "01" => sReadData <= iDstAddr;
                    WHEN "10" => sReadData(15 DOWNTO 0) <= STD_LOGIC_VECTOR(iLen);
                    WHEN "11" => sReadData(0) <= iStart;
                        sReadData(1) <= iDone;
                        sReadData(2) <= iIRQEN;
                    WHEN OTHERS => NULL;
                END CASE;
            END IF;
        END IF;
    END PROCESS SlaveRd;

    -- DMA
    MasterWrRd :
    PROCESS (clk, nReset)
    BEGIN
        IF nReset = '0' THEN
            iWordInput <= (OTHERS => '0');
            iWordOutput <= (OTHERS => '0');
            iIndex <= (OTHERS => '0');
            iDone <= '0';
        ELSIF rising_edge(clk) THEN
            IF iClrDone = '1' THEN
                iDone <= '0';
            END IF;
            CASE StateM IS
                WHEN IDLE => -- wait command start
                    mAddress <= (OTHERS => '0');
                    mWrite <= '0';
                    mRead <= '0';
                    iIndex <= (OTHERS => '0');
                    IF iStart = '1' THEN
                        iDone <= '0';
                        StateM <= READ_WD;
                    END IF;
                WHEN READ_WD => -- read word from memory
                    mAddress <= STD_LOGIC_VECTOR(unsigned(iSrcAddr) + iIndex * 4);
                    mRead <= '1';
                    StateM <= WAITR;
                WHEN WAITR => -- wait for value
                    iWordInput <= (OTHERS => '0');
                    iWordOutput <= (OTHERS => '0');
                    IF mWaitRequest = '0' THEN
                        iWordInput <= mReadData;
                        mRead <= '0';
                        StateM <= COMPUTE;
                    END IF;
                WHEN COMPUTE => -- swap
                    iWordOutput(7 DOWNTO 0) <= iWordInput(31 DOWNTO 24);
                    iWordOutput(31 DOWNTO 24) <= iWordInput(7 DOWNTO 0);
                    swap_loop : FOR i IN 8 TO 24 LOOP
                        iWordOutput(i) <= iWordInput(31 - i);
                    END LOOP swap_loop;
                    StateM <= WRITE_WD;
                WHEN WRITE_WD => -- write output word
                    mWrite <= '1';
                    mAddress <= STD_LOGIC_VECTOR(unsigned(iDstAddr) + iIndex * 4);
                    mWriteData <= iWordOutput;
                    StateM <= WAITW;
                WHEN WAITW => -- wait for write to complete
                    IF mWaitRequest = '0' THEN
                        mWrite <= '0';
                        iIndex <= iIndex + 1;
                        StateM <= CHECK;
                    END IF;
                WHEN CHECK => -- check whether to continue or stop
                    IF iIndex < iLen THEN
                        StateM <= READ_WD;
                    ELSE
                        iDone <= '1';
                        StateM <= IDLE;
                    END IF;
                WHEN OTHERS => NULL;
            END CASE;
        END IF;
    END PROCESS MasterWrRd;

    IRQ <= '1' WHEN iDone = '1' AND iIRQEn = '1' ELSE
        '0';
END comp;