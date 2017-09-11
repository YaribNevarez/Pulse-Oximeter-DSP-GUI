--Copyright 1986-2016 Xilinx, Inc. All Rights Reserved.
----------------------------------------------------------------------------------
--Tool Version: Vivado v.2016.3 (win64) Build 1682563 Mon Oct 10 19:07:27 MDT 2016
--Date        : Mon Jan 09 11:42:59 2017
--Host        : Yarib running 64-bit major release  (build 9200)
--Command     : generate_target poxi_design_wrapper.bd
--Design      : poxi_design_wrapper
--Purpose     : IP block netlist
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity poxi_design_wrapper is
  port (
    DDR_addr : inout STD_LOGIC_VECTOR ( 14 downto 0 );
    DDR_ba : inout STD_LOGIC_VECTOR ( 2 downto 0 );
    DDR_cas_n : inout STD_LOGIC;
    DDR_ck_n : inout STD_LOGIC;
    DDR_ck_p : inout STD_LOGIC;
    DDR_cke : inout STD_LOGIC;
    DDR_cs_n : inout STD_LOGIC;
    DDR_dm : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dq : inout STD_LOGIC_VECTOR ( 31 downto 0 );
    DDR_dqs_n : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dqs_p : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_odt : inout STD_LOGIC;
    DDR_ras_n : inout STD_LOGIC;
    DDR_reset_n : inout STD_LOGIC;
    DDR_we_n : inout STD_LOGIC;
    FIXED_IO_ddr_vrn : inout STD_LOGIC;
    FIXED_IO_ddr_vrp : inout STD_LOGIC;
    FIXED_IO_mio : inout STD_LOGIC_VECTOR ( 53 downto 0 );
    FIXED_IO_ps_clk : inout STD_LOGIC;
    FIXED_IO_ps_porb : inout STD_LOGIC;
    FIXED_IO_ps_srstb : inout STD_LOGIC;
    UART_0_rxd : in STD_LOGIC;
    UART_0_txd : out STD_LOGIC;
    adccs : out STD_LOGIC;
    daccs : out STD_LOGIC;
    iron : out STD_LOGIC;
    pgacs : out STD_LOGIC;
    psclk : out STD_LOGIC;
    psmiso : in STD_LOGIC;
    psmosi : out STD_LOGIC;
    rdon : out STD_LOGIC;
    tft_cs : out STD_LOGIC;
    tft_dc : out STD_LOGIC;
    tft_mosi : out STD_LOGIC;
    tft_r : out STD_LOGIC;
    tft_sck : out STD_LOGIC;
    zLED : out STD_LOGIC_VECTOR ( 3 downto 0 );
    zPushB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    zSwitch : in STD_LOGIC_VECTOR ( 3 downto 0 )
  );
end poxi_design_wrapper;

architecture STRUCTURE of poxi_design_wrapper is
  component poxi_design is
  port (
    DDR_cas_n : inout STD_LOGIC;
    DDR_cke : inout STD_LOGIC;
    DDR_ck_n : inout STD_LOGIC;
    DDR_ck_p : inout STD_LOGIC;
    DDR_cs_n : inout STD_LOGIC;
    DDR_reset_n : inout STD_LOGIC;
    DDR_odt : inout STD_LOGIC;
    DDR_ras_n : inout STD_LOGIC;
    DDR_we_n : inout STD_LOGIC;
    DDR_ba : inout STD_LOGIC_VECTOR ( 2 downto 0 );
    DDR_addr : inout STD_LOGIC_VECTOR ( 14 downto 0 );
    DDR_dm : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dq : inout STD_LOGIC_VECTOR ( 31 downto 0 );
    DDR_dqs_n : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    DDR_dqs_p : inout STD_LOGIC_VECTOR ( 3 downto 0 );
    FIXED_IO_mio : inout STD_LOGIC_VECTOR ( 53 downto 0 );
    FIXED_IO_ddr_vrn : inout STD_LOGIC;
    FIXED_IO_ddr_vrp : inout STD_LOGIC;
    FIXED_IO_ps_srstb : inout STD_LOGIC;
    FIXED_IO_ps_clk : inout STD_LOGIC;
    FIXED_IO_ps_porb : inout STD_LOGIC;
    zSwitch : in STD_LOGIC_VECTOR ( 3 downto 0 );
    zPushB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    psmiso : in STD_LOGIC;
    zLED : out STD_LOGIC_VECTOR ( 3 downto 0 );
    psclk : out STD_LOGIC;
    adccs : out STD_LOGIC;
    rdon : out STD_LOGIC;
    iron : out STD_LOGIC;
    daccs : out STD_LOGIC;
    pgacs : out STD_LOGIC;
    psmosi : out STD_LOGIC;
    tft_dc : out STD_LOGIC;
    tft_r : out STD_LOGIC;
    tft_mosi : out STD_LOGIC;
    tft_sck : out STD_LOGIC;
    tft_cs : out STD_LOGIC;
    UART_0_txd : out STD_LOGIC;
    UART_0_rxd : in STD_LOGIC
  );
  end component poxi_design;
begin
poxi_design_i: component poxi_design
     port map (
      DDR_addr(14 downto 0) => DDR_addr(14 downto 0),
      DDR_ba(2 downto 0) => DDR_ba(2 downto 0),
      DDR_cas_n => DDR_cas_n,
      DDR_ck_n => DDR_ck_n,
      DDR_ck_p => DDR_ck_p,
      DDR_cke => DDR_cke,
      DDR_cs_n => DDR_cs_n,
      DDR_dm(3 downto 0) => DDR_dm(3 downto 0),
      DDR_dq(31 downto 0) => DDR_dq(31 downto 0),
      DDR_dqs_n(3 downto 0) => DDR_dqs_n(3 downto 0),
      DDR_dqs_p(3 downto 0) => DDR_dqs_p(3 downto 0),
      DDR_odt => DDR_odt,
      DDR_ras_n => DDR_ras_n,
      DDR_reset_n => DDR_reset_n,
      DDR_we_n => DDR_we_n,
      FIXED_IO_ddr_vrn => FIXED_IO_ddr_vrn,
      FIXED_IO_ddr_vrp => FIXED_IO_ddr_vrp,
      FIXED_IO_mio(53 downto 0) => FIXED_IO_mio(53 downto 0),
      FIXED_IO_ps_clk => FIXED_IO_ps_clk,
      FIXED_IO_ps_porb => FIXED_IO_ps_porb,
      FIXED_IO_ps_srstb => FIXED_IO_ps_srstb,
      UART_0_rxd => UART_0_rxd,
      UART_0_txd => UART_0_txd,
      adccs => adccs,
      daccs => daccs,
      iron => iron,
      pgacs => pgacs,
      psclk => psclk,
      psmiso => psmiso,
      psmosi => psmosi,
      rdon => rdon,
      tft_cs => tft_cs,
      tft_dc => tft_dc,
      tft_mosi => tft_mosi,
      tft_r => tft_r,
      tft_sck => tft_sck,
      zLED(3 downto 0) => zLED(3 downto 0),
      zPushB(3 downto 0) => zPushB(3 downto 0),
      zSwitch(3 downto 0) => zSwitch(3 downto 0)
    );
end STRUCTURE;
