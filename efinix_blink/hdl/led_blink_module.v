module led_blink_module
(
    input  clk_i,
    output led_o
);

    reg [23:0] counter;
    reg        polarity;

    always@(posedge clk_i) begin
        counter <= counter + 1'b1;

        if (counter == 24'hFFFFF)
            polarity <= ~polarity;
    end

    assign led_o = polarity;

endmodule
