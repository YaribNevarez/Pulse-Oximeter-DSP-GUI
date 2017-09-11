vlib work
vlib msim

vlib msim/xil_defaultlib
vlib msim/xpm
vlib msim/processing_system7_bfm_v2_0_5
vlib msim/lib_cdc_v1_0_2
vlib msim/proc_sys_reset_v5_0_10
vlib msim/generic_baseblocks_v2_1_0
vlib msim/axi_infrastructure_v1_1_0
vlib msim/axi_register_slice_v2_1_10
vlib msim/fifo_generator_v13_1_2
vlib msim/axi_data_fifo_v2_1_9
vlib msim/axi_crossbar_v2_1_11
vlib msim/axi_protocol_converter_v2_1_10

vmap xil_defaultlib msim/xil_defaultlib
vmap xpm msim/xpm
vmap processing_system7_bfm_v2_0_5 msim/processing_system7_bfm_v2_0_5
vmap lib_cdc_v1_0_2 msim/lib_cdc_v1_0_2
vmap proc_sys_reset_v5_0_10 msim/proc_sys_reset_v5_0_10
vmap generic_baseblocks_v2_1_0 msim/generic_baseblocks_v2_1_0
vmap axi_infrastructure_v1_1_0 msim/axi_infrastructure_v1_1_0
vmap axi_register_slice_v2_1_10 msim/axi_register_slice_v2_1_10
vmap fifo_generator_v13_1_2 msim/fifo_generator_v13_1_2
vmap axi_data_fifo_v2_1_9 msim/axi_data_fifo_v2_1_9
vmap axi_crossbar_v2_1_11 msim/axi_crossbar_v2_1_11
vmap axi_protocol_converter_v2_1_10 msim/axi_protocol_converter_v2_1_10

vlog -work xil_defaultlib -64 -sv "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/2527/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/7e3a/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/2527/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/7e3a/hdl" \
"C:/Xilinx/Vivado/2016.3/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \

vcom -work xpm -64 -93 \
"C:/Xilinx/Vivado/2016.3/data/ip/xpm/xpm_VCOMP.vhd" \

vlog -work processing_system7_bfm_v2_0_5 -64 "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/2527/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/7e3a/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/2527/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/7e3a/hdl" \
"../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/2527/hdl/processing_system7_bfm_v2_0_vl_rfs.v" \

vlog -work xil_defaultlib -64 "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/2527/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/7e3a/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/2527/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/7e3a/hdl" \
"../../../bd/poxi_design/ip/poxi_design_processing_system7_0_0/sim/poxi_design_processing_system7_0_0.v" \

vcom -work xil_defaultlib -64 -93 \
"../../../bd/poxi_design/ipshared/28bc/src/spi.vhd" \
"../../../bd/poxi_design/ipshared/28bc/hdl/POXI_v1_0_S00_AXI.vhd" \
"../../../bd/poxi_design/ipshared/28bc/hdl/POXI_v1_0.vhd" \
"../../../bd/poxi_design/ip/poxi_design_POXI_0_0/sim/poxi_design_POXI_0_0.vhd" \

vcom -work lib_cdc_v1_0_2 -64 -93 \
"../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/52cb/hdl/lib_cdc_v1_0_rfs.vhd" \

vcom -work proc_sys_reset_v5_0_10 -64 -93 \
"../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/04b4/hdl/proc_sys_reset_v5_0_vh_rfs.vhd" \

vcom -work xil_defaultlib -64 -93 \
"../../../bd/poxi_design/ip/poxi_design_rst_ps7_0_100M_0/sim/poxi_design_rst_ps7_0_100M_0.vhd" \
"../../../bd/poxi_design/ipshared/e2ec/src/espi.vhd" \
"../../../bd/poxi_design/ipshared/e2ec/hdl/TFT_SPI_DISPLAY_240x320_v1_0_S00_AXI.vhd" \
"../../../bd/poxi_design/ipshared/e2ec/hdl/TFT_SPI_DISPLAY_240x320_v1_0.vhd" \
"../../../bd/poxi_design/ip/poxi_design_TFT_SPI_DISPLAY_240x320_0_0/sim/poxi_design_TFT_SPI_DISPLAY_240x320_0_0.vhd" \

vlog -work generic_baseblocks_v2_1_0 -64 "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/2527/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/7e3a/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/2527/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/7e3a/hdl" \
"../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/7ee0/hdl/generic_baseblocks_v2_1_vl_rfs.v" \

vlog -work axi_infrastructure_v1_1_0 -64 "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/2527/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/7e3a/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/2527/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/7e3a/hdl" \
"../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/7e3a/hdl/axi_infrastructure_v1_1_vl_rfs.v" \

vlog -work axi_register_slice_v2_1_10 -64 "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/2527/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/7e3a/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/2527/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/7e3a/hdl" \
"../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/7efe/hdl/axi_register_slice_v2_1_vl_rfs.v" \

vlog -work fifo_generator_v13_1_2 -64 "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/2527/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/7e3a/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/2527/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/7e3a/hdl" \
"../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/a807/simulation/fifo_generator_vlog_beh.v" \

vcom -work fifo_generator_v13_1_2 -64 -93 \
"../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/a807/hdl/fifo_generator_v13_1_rfs.vhd" \

vlog -work fifo_generator_v13_1_2 -64 "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/2527/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/7e3a/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/2527/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/7e3a/hdl" \
"../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/a807/hdl/fifo_generator_v13_1_rfs.v" \

vlog -work axi_data_fifo_v2_1_9 -64 "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/2527/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/7e3a/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/2527/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/7e3a/hdl" \
"../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/10b8/hdl/axi_data_fifo_v2_1_vl_rfs.v" \

vlog -work axi_crossbar_v2_1_11 -64 "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/2527/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/7e3a/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/2527/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/7e3a/hdl" \
"../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/d552/hdl/axi_crossbar_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib -64 "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/2527/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/7e3a/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/2527/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/7e3a/hdl" \
"../../../bd/poxi_design/ip/poxi_design_xbar_0/sim/poxi_design_xbar_0.v" \

vlog -work axi_protocol_converter_v2_1_10 -64 "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/2527/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/7e3a/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/2527/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/7e3a/hdl" \
"../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/4a8b/hdl/axi_protocol_converter_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib -64 "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/2527/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/7e3a/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/2527/hdl" "+incdir+../../../../poxi.srcs/sources_1/bd/poxi_design/ipshared/7e3a/hdl" \
"../../../bd/poxi_design/ip/poxi_design_auto_pc_0/sim/poxi_design_auto_pc_0.v" \

vcom -work xil_defaultlib -64 -93 \
"../../../bd/poxi_design/hdl/poxi_design.vhd" \

vlog -work xil_defaultlib "glbl.v"

