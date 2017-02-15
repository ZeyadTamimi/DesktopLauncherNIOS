`timescale 1ps / 1ps
module PWM_Controller (
	PWM_CW,               // Ports declared
	PWM_out,					         
	clk
	);
	
	input clk;            //Port type declared
	input [15:0] PWM_CW;
	
	output reg PWM_out; // 1 bit PWM output
	wire [15:0] counter_out;

	always @ (posedge clk)
	begin
			
			if (PWM_CW > counter_out)
				PWM_out <= 1;
				
			else 
				PWM_out <= 0;
	end
		
	
	counter counter_inst(
	
		.clk (clk),
		.counter_out (counter_out)
		);
	
endmodule


`timescale 1ps / 1ps
module counter (
	clk,				//Counter clock
	counter_out   			 // 8 bit output from the counter
);

	input clk;			// clock declared as an input port
	output reg [15:0] counter_out;  // counter_out declared as an 8 bit output register
	
	always @(posedge clk)
		begin
			if (counter_out == 16'd62500) counter_out = 16'b0;
			else counter_out <= counter_out + 16'b1;
		end
		
endmodule				// identifies the end of the module