module efinix_blink_top
(
    input  wire       system_clk_i,
    output wire [3:0] leds
);

    led_blink_module led_blink_module_0_inst
    (
        .clk_i ( system_clk_i ),
        .led_o ( leds[0]      )
    );

    led_blink_module led_blink_module_1_inst
    (
        .clk_i ( system_clk_i ),
        .led_o ( leds[1]      )
    );

    led_blink_module led_blink_module_2_inst
    (
        .clk_i ( system_clk_i ),
        .led_o ( leds[2]      )
    );    
    
    led_blink_module led_blink_module_3_inst
    (
        .clk_i ( system_clk_i ),
        .led_o ( leds[3]      )
    );    
    
endmodule