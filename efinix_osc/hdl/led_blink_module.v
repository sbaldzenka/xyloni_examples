module led_blink_module
(
    input  clk_i,
    output led_o
);

    reg [9:0] counter;
    reg        polarity;

    always@(posedge clk_i) begin
        counter <= counter + 1'b1;

        if (counter == 10'h3FF)
            polarity <= ~polarity;
    end

    assign led_o = polarity;

endmodule
