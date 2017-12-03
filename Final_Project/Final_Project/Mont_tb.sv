
module Mont_tb();
localparam SIZEBD = 4;
localparam SIZEM = 8;
localparam SIZEI = 3;

reg clk,rst_n,start;
reg [SIZEM-1:0] M;
reg [SIZEBD-1:0] yhat,xhat;
wire [SIZEM:0] Z;
wire done;

reg [SIZEI-1:0] j;

//interleaved iDUT(.clk(clk),.rst_n(rst_n),.b(b),.d(d),.M(M),.Z(Z),.done(done),.start(start));
montgomery iDUT(.clk(clk), .rst_n(rst_n), .xhat(xhat), .yhat(yhat), .M(M), .Z(Z), .done(done), .start(start));

initial begin
	
	clk = 0;
	rst_n = 0;
	start = 0;
	M = 0;
	xhat = 0;
	yhat = 0;
	repeat(5)@(posedge clk);
	@(negedge clk) rst_n = 1;
	@(posedge clk)
	M = 233;
	xhat = 5;
	yhat = 7;
	start = 1;
	@(posedge clk)
	start = 0;
	for(j = 0; j <= SIZEBD-1; j++)begin
		@(posedge clk);
	end
	@(posedge clk);
	$stop;

end

always
	#5 clk = ~clk;


endmodule