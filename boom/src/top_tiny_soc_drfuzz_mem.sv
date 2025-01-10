// Copyright 2022 Flavien Solt, ETH Zurich.
// Licensed under the General Public License, Version 3.0, see LICENSE for details.
// SPDX-License-Identifier: GPL-3.0-only

// Toplevel module with taints.

module top_tiny_soc #(
    parameter int unsigned NumTaints = 1,

    parameter int unsigned NumWords = 1 << 20,
    parameter int unsigned AddrWidth = 32,
    parameter int unsigned DataWidth = 64,

    parameter int unsigned StrbWidth = DataWidth >> 3,
    localparam type addr_t = logic [AddrWidth-1:0],
    localparam type data_t = logic [DataWidth-1:0],
    localparam type strb_t = logic [StrbWidth-1:0]
) (
  input logic clk_i,
  input logic rst_ni,

  // DrFUZZ signals
  // input logic meta_rst_ni,
  // input logic meta_rst_ni_t0,
  // output logic [5715:0] auto_cover_out_t0,
  // output logic [5715:0] auto_cover_out,
  // output logic [39:0] pc_probe_t0,
  // input logic intercept_mem_en,
  // input data_t intercept_mem_rdata,


  // MMIO interface
  output logic  mmio_req_o,
  output addr_t mmio_addr_o,
  output data_t mmio_wdata_o,
  output strb_t mmio_strb_o,
  output logic  mmio_we_o,
  input  data_t mmio_rdata_i,

  output logic  mmio_req_o_t0,
  output addr_t mmio_addr_o_t0,
  output data_t mmio_wdata_o_t0,
  output strb_t mmio_strb_o_t0,
  output logic  mmio_we_o_t0,
  input  data_t mmio_rdata_i_t0,

  // Mem interface
  output logic  mem_req_o,
  output addr_t mem_addr_o,
  output data_t mem_wdata_o,
  output strb_t mem_strb_o,
  output logic  mem_we_o,
  output data_t mem_rdata_o,

  output logic  mem_req_o_t0,
  output addr_t mem_addr_o_t0,
  output data_t mem_wdata_o_t0,
  output strb_t mem_strb_o_t0,
  output logic  mem_we_o_t0,
  output data_t mem_rdata_o_t0
);

  boom_mem_top i_mem_top (
    .clock(clk_i),
    .reset_wire_reset(~rst_ni),

    .mmio_req_o(mmio_req_o),
    .mmio_we_o(mmio_we_o),
    .mmio_addr_o(mmio_addr_o),
    .mmio_strb_o(mmio_strb_o),
    .mmio_data_o(mmio_wdata_o),
    .mmio_data_i(mmio_rdata_i),
    .mem_req_o(mem_req_o),
    .mem_we_o(mem_we_o),
    .mem_addr_o(mem_addr_o),
    .mem_strb_o(mem_strb_o),
    .mem_data_o(mem_wdata_o),
    .mem_data_i(mem_rdata_o),
    // Taint signals
    .mmio_req_o_t0(mmio_req_o_t0),
    .mmio_we_o_t0(mmio_we_o_t0),
    .mmio_addr_o_t0(mmio_addr_o_t0),
    .mmio_strb_o_t0(mmio_strb_o_t0),
    .mmio_data_o_t0(mmio_wdata_o_t0),
    .mmio_data_i_t0(mmio_rdata_i_t0),
    .mem_req_o_t0(mem_req_o_t0),
    .mem_we_o_t0(mem_we_o_t0),
    .mem_addr_o_t0(mem_addr_o_t0),
    .mem_strb_o_t0(mem_strb_o_t0),
    .mem_data_o_t0(mem_wdata_o_t0),
    .mem_data_i_t0(mem_rdata_o_t0)

    // .meta_reset(~meta_rst_ni),
    // .meta_reset_t0(~meta_rst_ni_t0),
    // .auto_cover_out(auto_cover_out),
    // .auto_cover_out_t0(auto_cover_out_t0),
    // .pc_probe_t0(pc_probe_t0)
  );

  ///////////////////////////////
  // Instruction SRAM instance //
  ///////////////////////////////

  ift_sram_mem #(
    .Width(DataWidth),
    .Depth(NumWords),
    .NumTaints(NumTaints),
    .RelocateRequestUp(64'h10000000) // 80000000 >> 3
  ) i_sram (
    .clk_i,
    .rst_ni,

    .req_i(mem_req_o),
    .write_i(mem_we_o),
    .addr_i(mem_addr_o >> 3), // 64-bit words
    .wdata_i(mem_wdata_o),
    .wmask_i({{8{mem_strb_o[7]}}, {8{mem_strb_o[6]}}, {8{mem_strb_o[5]}}, {8{mem_strb_o[4]}}, {8{mem_strb_o[3]}}, {8{mem_strb_o[2]}}, {8{mem_strb_o[1]}}, {8{mem_strb_o[0]}}}),
    .rdata_o(mem_rdata_o),

    .req_i_taint(mem_req_o_t0),
    .write_i_taint(mem_we_o_t0),
    .addr_i_taint(mem_addr_o_t0 >> 3), // 64-bit words
    .wdata_i_taint(mem_wdata_o_t0),
    .wmask_i_taint({{8{mem_strb_o_t0[7]}}, {8{mem_strb_o_t0[6]}}, {8{mem_strb_o_t0[5]}}, {8{mem_strb_o_t0[4]}}, {8{mem_strb_o_t0[3]}}, {8{mem_strb_o_t0[2]}}, {8{mem_strb_o_t0[1]}}, {8{mem_strb_o_t0[0]}}}),
    .rdata_o_taint(mem_rdata_o_t0)
  );

endmodule
