// Represents a device controlling access to 3 requesting devices where r_0 has
// the highest priority and r_2 has the lowest priority
module arbiter (
    input clk,
    input resetn,       // active-low sync reset
    input [3:1] r,      // request
    output reg [3:1] g  // grant
);

// Internal
reg [1:0] state;

parameter A = 2'b00, B = 2'b01, C = 2'b10, D = 2'b11;

// Next state logic
always @(posedge clk) begin;    
    if (resetn == 1'b0) begin
        state <= A;
    end else begin
        case (state)
            A: 
                if (r[1] == 1'b1) begin
                    state <= B;            
                end else if (r[2] == 1'b1) begin
                    state <= C;
                end else if (r[3] == 1'b1) begin
                    state <= D;
                end
            B:
                if (r[1] == 1'b1) begin
                    state <= B;
                end else begin
                    state <= A;
                end
            C:
                if (r[2] == 1'b1) begin
                    state <= C;
                end else begin
                    state <= A;
                end
            D:
                if (r[3] == 1'b1) begin
                    state <= D;
                end else begin
                    state <= A;
                end    
        endcase
    end
end

// Output logic

always @(*) begin
    case (state)
        A: g = 3'b000;
        B: g = 3'b001;
        C: g = 3'b010;
        D: g = 3'b100;
    endcase
end


endmodule
