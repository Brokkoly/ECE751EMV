
module expmod_tb();

localparam SIZEA = 8;
localparam SIZEM = 8;
localparam SIZEE = 3;
localparam R2 = 16; //2^n (2^(SIZEM/2))
localparam SIZEI = 2;

reg [SIZEA-1:0] A;
reg [SIZEM-1:0] M;
reg [SIZEE-1:0] e;
reg start,clk,rst_n;

wire done;
wire [SIZEM-1:0] C;

expmod iDUT(.A(A),.e(e),.M(M),.start(start),.done(done),.clk(clk),.rst_n(rst_n),.C(C));

initial begin
	clk = 0;
	rst_n = 0;
	start = 0;
	M = 0;
	e =0;
	A = 0;
	repeat(5)@(posedge clk);
	@(negedge clk) rst_n = 1;
	@(posedge clk)
	M = 233;
	A = 5;
	e = 6;
	start = 1;
	while(!done)begin
		@(posedge clk);
	end
	@(posedge clk);
	$stop;
end

always
	#5 clk = ~clk;
endmodule