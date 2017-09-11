# Zybo xdc for PMOD ADCs and DACs

############################
# On-board leds            #
############################
##IO_L23P_T3_35
set_property PACKAGE_PIN M14 [get_ports zLED[0]]
set_property IOSTANDARD LVCMOS33 [get_ports zLED[0]]

##IO_L23N_T3_35
set_property PACKAGE_PIN M15 [get_ports zLED[1]]
set_property IOSTANDARD LVCMOS33 [get_ports zLED[1]]

##IO_0_35
set_property PACKAGE_PIN G14 [get_ports zLED[2]]
set_property IOSTANDARD LVCMOS33 [get_ports zLED[2]]

##IO_L3N_T0_DQS_AD1N_35
set_property PACKAGE_PIN D18 [get_ports zLED[3]]
set_property IOSTANDARD LVCMOS33 [get_ports zLED[3]]

############################
# On-board switches        #
############################
##IO_L19N_T3_VREF_35
set_property PACKAGE_PIN G15 [get_ports zSwitch[0]]
set_property IOSTANDARD LVCMOS33 [get_ports zSwitch[0]]

##IO_L24P_T3_34
set_property PACKAGE_PIN P15 [get_ports zSwitch[1]]
set_property IOSTANDARD LVCMOS33 [get_ports zSwitch[1]]

##IO_L4N_T0_34
set_property PACKAGE_PIN W13 [get_ports zSwitch[2]]
set_property IOSTANDARD LVCMOS33 [get_ports zSwitch[2]]

##IO_L9P_T1_DQS_34
set_property PACKAGE_PIN T16 [get_ports zSwitch[3]]
set_property IOSTANDARD LVCMOS33 [get_ports zSwitch[3]]

############################
# On-board pushbuttons     #
############################
##IO_L20N_T3_34
set_property PACKAGE_PIN R18 [get_ports zPushB[0]]
set_property IOSTANDARD LVCMOS33 [get_ports zPushB[0]]

##IO_L24N_T3_34
set_property PACKAGE_PIN P16 [get_ports zPushB[1]]
set_property IOSTANDARD LVCMOS33 [get_ports zPushB[1]]

##IO_L18P_T2_34
set_property PACKAGE_PIN V16 [get_ports zPushB[2]]
set_property IOSTANDARD LVCMOS33 [get_ports zPushB[2]]

##IO_L7P_T1_34
set_property PACKAGE_PIN Y16 [get_ports zPushB[3]]
set_property IOSTANDARD LVCMOS33 [get_ports zPushB[3]]


# PMOD JE
############################
# POXI2-Pmod               #
############################
#NET JE1         LOC = V12   | IOSTANDARD=LVCMOS33; # SPI serial clock
#NET JE2         LOC = W16   | IOSTANDARD=LVCMOS33; # ADC CS (active high!)
#NET JE3         LOC = J15   | IOSTANDARD=LVCMOS33; # LED red on
#NET JE4         LOC = H15   | IOSTANDARD=LVCMOS33; # LED ifrared on
#NET JE5         LOC = V13   | IOSTANDARD=LVCMOS33; # PGA CS (active high!)
#NET JE6         LOC = U17   | IOSTANDARD=LVCMOS33; # DAC CS (active high!)
#NET JE7         LOC = T17   | IOSTANDARD=LVCMOS33; # SPI mosi
#NET JE8         LOC = Y17   | IOSTANDARD=LVCMOS33; # SPI miso (ADC only)
set_property PACKAGE_PIN V12 [get_ports psclk]
set_property IOSTANDARD LVCMOS33 [get_ports psclk]
set_property PACKAGE_PIN W16 [get_ports adccs]
set_property IOSTANDARD LVCMOS33 [get_ports adccs]
set_property PACKAGE_PIN J15 [get_ports rdon]
set_property IOSTANDARD LVCMOS33 [get_ports rdon]
set_property PACKAGE_PIN H15 [get_ports iron]
set_property IOSTANDARD LVCMOS33 [get_ports iron]
set_property PACKAGE_PIN V13 [get_ports pgacs]
set_property IOSTANDARD LVCMOS33 [get_ports pgacs]
set_property PACKAGE_PIN U17 [get_ports daccs]
set_property IOSTANDARD LVCMOS33 [get_ports daccs]
set_property PACKAGE_PIN T17 [get_ports psmosi]
set_property IOSTANDARD LVCMOS33 [get_ports psmosi]
set_property PACKAGE_PIN Y17 [get_ports psmiso]
set_property IOSTANDARD LVCMOS33 [get_ports psmiso]

#Pmod Header JB
############################
# TFT Display              #
############################
#IO_L15P_T2_DQS_34
#JB1
set_property PACKAGE_PIN T20 [get_ports {tft_mosi}]
set_property IOSTANDARD LVCMOS33 [get_ports {tft_mosi}]

#IO_L15N_T2_DQS_34
#JB2
set_property PACKAGE_PIN U20 [get_ports {tft_dc}]
set_property IOSTANDARD LVCMOS33 [get_ports {tft_dc}]

#IO_L16P_T2_34
#JB3
set_property PACKAGE_PIN V20 [get_ports {tft_r}]
set_property IOSTANDARD LVCMOS33 [get_ports {tft_r}]

#IO_L16N_T2_34
#JB4
set_property PACKAGE_PIN W20 [get_ports {tft_cs}]
set_property IOSTANDARD LVCMOS33 [get_ports {tft_cs}]

#IO_L17P_T2_34
#JB7
set_property PACKAGE_PIN Y18 [get_ports {tft_sck}]
set_property IOSTANDARD LVCMOS33 [get_ports {tft_sck}]

#IO_L17N_T2_34
#JB8
set_property PACKAGE_PIN Y19 [get_ports {UART_0_txd}]
set_property IOSTANDARD LVCMOS33 [get_ports {UART_0_txd}]

#IO_L22P_T3_34
#JB9
set_property PACKAGE_PIN W18 [get_ports {UART_0_rxd}]
set_property IOSTANDARD LVCMOS33 [get_ports {UART_0_rxd}]

##IO_L22N_T3_34
#JB10
#set_property PACKAGE_PIN W19 [get_ports {jb_n[3]}]
#set_property IOSTANDARD LVCMOS33 [get_ports {jb_n[3]}]

