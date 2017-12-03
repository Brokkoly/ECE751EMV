
module Inter_tb();
localparam SIZEBD = 4;
localparam SIZEM = 8;
localparam SIZEI = 3;

reg clk,rst_n,start;
reg [SIZEM-1:0] b,M;
reg [SIZEBD-1:0] d;
wire [SIZEM:0] Z;
wire done;

reg [SIZEI-1:0] j;

interleaved iDUT(.clk(clk),.rst_n(rst_n),.b(b),.d(d),.M(M),.Z(Z),.done(done),.start(start));
initial begin
	
	clk = 0;
	rst_n = 0;
	start = 0;
	M = 0;
	b = 0;
	d = 0;
	repeat(5)@(posedge clk);
	@(negedge clk) rst_n = 1;
	@(posedge clk)
	M = 233;
	b = 5;
	d = 7;
	start = 1;
	@(posedge clk)
	start = 0;
	for(j = SIZEM-1; j >= 1; j--)begin
		@(posedge clk);
	end
	@(posedge clk);
	$stop;

end

always
	#5 clk = ~clk;


endmodule