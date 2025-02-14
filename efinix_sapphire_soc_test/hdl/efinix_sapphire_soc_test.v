// author      : siarhei baldzenka
// data        : 10.02.2025
// e-mail      : venera.electronica@gmail.com
// description : sapphire risc-v soc test


module efinix_sapphire_soc_test
(
    // system signals
    input  wire       i_sys_areset,
    input  wire       pll_clk_50,
    input  wire       pll_clk_soc,
    input  wire       pll_locked,
    // leds
    output wire       o_led,
    output wire [2:0] gpio_wr_en,
    output wire [2:0] gpio_wr,
    input  wire [2:0] gpio_rd,
    // jtag
    input  wire       jtag_enable,
    input  wire       jtag_tdi,
    input  wire       jtag_capture,
    input  wire       jtag_shift,
    input  wire       jtag_update,
    input  wire       jtag_reset,
    output wire       jtag_tdo,
    input  wire       jtag_tck

);

    wire resetn;
    wire reset;
    wire soc_periph_reset;

    assign resetn = pll_locked & i_sys_areset;
    assign reset  = ~(pll_locked & i_sys_areset);

    assign gpio_wr_en[0] = 1'b1;
    assign gpio_wr[0]    = 1'b0;

    led_blink_module led_blink_module_inst
    (
        .i_clk    ( pll_clk_50 ),
        .i_resetn ( resetn     ),
        .o_led    ( o_led      )
    );

    sapphire_mcu sapphire_mcu_inst
    (
        .io_systemClk                 ( pll_clk_soc      ),
        .io_asyncReset                ( reset            ),
        .io_systemReset               ( soc_periph_reset ),

        .system_gpio_0_io_writeEnable ( gpio_wr_en[2:1]  ),
        .system_gpio_0_io_write       ( gpio_wr[2:1]     ),
        .system_gpio_0_io_read        ( gpio_rd[2:1]     ),

        .jtagCtrl_enable              ( jtag_enable      ),
        .jtagCtrl_tdi                 ( jtag_tdi         ),
        .jtagCtrl_capture             ( jtag_capture     ),
        .jtagCtrl_shift               ( jtag_shift       ),
        .jtagCtrl_update              ( jtag_update      ),
        .jtagCtrl_reset               ( jtag_reset       ),
        .jtagCtrl_tdo                 ( jtag_tdo         ),
        .jtagCtrl_tck                 ( jtag_tck         )
    );


endmodule