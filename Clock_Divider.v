//The Clock Divider module
module Clock_Divider(input inclk, output reg outclk);

 wire[31:0]div_clk_count = 32'd1953; // 1953.125 
 reg [31:0] counter;

 always@(posedge inclk)begin

	if(counter == div_clk_count)// if counter equal to the divider
		begin
		outclk = ~outclk;// reverse the output clock
		counter[31:0] = 32'b0;// then reset the counter
		end
	else if(counter < div_clk_count)// if counter is still less
		begin
		counter[31:0] = counter + 1;// increment counter by 1
		end
		
	else
		begin
		counter[31:0] = 32'b0;// in any other condition, reset the counter
		end

 end

endmodule