// author      : siarhei baldzenka
// data        : 10.02.2025
// e-mail      : venera.electronica@gmail.com
// description : led blink

module led_blink_module
(
    input  wire i_clk,
    input  wire i_resetn,
    output wire o_led
);

    reg [23:0] counter;
    reg        polarity;

    always@(posedge i_clk, negedge i_resetn) begin
        if (!i_resetn) begin
            counter <= 24'b0;
         end else begin
            counter <= counter + 1'b1;
        end
    end

    always@(posedge i_clk) begin
        if (counter == 24'h8FFFFF) begin
            polarity <= ~polarity;
        end
    end

    assign o_led = polarity;

endmodule
