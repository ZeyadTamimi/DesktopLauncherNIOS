`timescale 1ps / 1ps
module PWM_Controller (
	PWM_CW,               // Ports declared
	PWM_out,					         
	clk
	);
	
	input clk;            //Port type declared
	input [7:0] PWM_CW;   // 8 bit PWM input
	
	output reg PWM_out; // 1 bit PWM output
	wire [7:0] counter_out;  // 8 bit counter output

	

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
	output reg [7:0] counter_out;  // counter_out declared as an 8 bit output register
	
	always @(posedge clk)
		begin
			counter_out <= #1 counter_out + 1'b1;
		end
		
endmodule				// identifies the end of the module