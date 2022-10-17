module efinity_osc_top
(
    input  osc_clk,
    output led_o
);

    led_blink_module led_blink_module_inst
    (
        .clk_i ( osc_clk ),
        .led_o ( led_o   )
    );

endmodule