module BMM_tb();
localparam SIZEBD = 4;
localparam SIZEM = 8;
localparam SIZEI = 3;

reg clk,rst_n,start;
reg [SIZEM-1:0] M;
reg [SIZEBD-1:0] RmM;
reg [SIZEM-1:0] T,U;
reg sel;
wire [SIZEM:0] Z;
wire done;

reg [SIZEI-1:0] j;

//interleaved iDUT(.clk(clk),.rst_n(rst_n),.b(b),.d(d),.M(M),.Z(Z),.done(done),.start(start));
BMM iDUT(.clk(clk),.rst_n(rst_n),.M(M),.T(T),.U(U),.sel(sel),.RmM(RmM),.O(Z),.done(done),.start(start));
initial begin
	
	clk = 0;
	rst_n = 0;
	start = 0;
	M = 0;
	T = 0;
	U= 0;
	RmM = 0;
	sel = 0;
	repeat(5)@(posedge clk);
	@(negedge clk) rst_n = 1;
	@(posedge clk)
	M = 233;
	T = 5;
	U = 7;
	start = 1;
	sel = 0;
	@(posedge clk)
	start = 0;
	while(!done)begin
		@(posedge clk);
	end
	@(posedge clk);
	sel = 1;
	start = 1;
	@(posedge clk);
	start = 0;
	while(!done)begin
		@(posedge clk);
	end
	@(posedge clk);
	$stop;

end

always
	#5 clk = ~clk;


endmodule