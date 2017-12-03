
module expmod(A,e,M,start,done,clk,rst_n,C);
	localparam SIZEA = 8;
	localparam SIZEM = 8;
	localparam SIZEE = 3;
	localparam R2 = 16; //2^n (2^(SIZEM/2))
	localparam SIZEI = 2;


	input [SIZEA-1:0] A;
	input [SIZEM-1:0] M;
	input [SIZEE-1:0] e;
	input start,clk,rst_n;

	output reg done;
	output reg [SIZEM-1:0] C;
	
	wire doneI,doneM,doneB;
	reg startI,startM,startB;
	wire [SIZEM:0] hat,Im,Z;
	reg [SIZEM-1:0] b,d,x,y,T,U;
	reg [SIZEM-1:0] RmM;
	reg [SIZEM-1:0] Ahat;
	reg [SIZEI-1:0] i;
	reg [SIZEM:0] temp;
	reg sel;

	interleaved inter(.clk(clk),.rst_n(rst_n),.b(b),.d(d),.M(M),.Z(hat),.done(doneI),.start(startI));
	montgomery mont(.clk(clk),.rst_n(rst_n),.xhat(x),.yhat(y),.M(M),.Z(Im),.done(doneM),.start(startM));
	BMM bmm(.clk(clk),.rst_n(rst_n),.M(M),.T(T),.U(U),.sel(sel),.RmM(RmM),.O(Z),.done(doneB),.start(startB));

	typedef enum reg [3:0] {WAIT,BEGINI1,I1,BEGINI2,I2,BEGINA,BMM1,BEGINMT1,MT1,BEGINBMM2,BMM2,BEGINMT2,MT2,END} state_t;
	state_t state, nxt_state;
	always@(posedge clk, negedge rst_n)	
		if(!rst_n)begin
			C <= 1;
			done <= 0;
		end
		else if(state != WAIT)begin
			state <= nxt_state;
			case(state)
				BEGINI1:begin
					startI <= 1;
					b <= R2;
					d <= R2;
					C <= 1;
				end
				I1:begin
					startI <= 0;
					if(doneI)begin
						RmM <= hat;
					end
				end
				BEGINI2:begin
					startI <= 1;
					b <= A;
					d <= R2;
				end
				I2:begin
					startI <= 0;
					i <= SIZEE;
					if(doneI)begin
						Ahat <= hat;
					end
				end
				BEGINA:begin
					i <= i -1;
					if(i == 0)begin //check for off by 1
						state <= END;
					end
					startB <= 1;
					T <= C;
					U <= C;
					sel <= 0;
				end
				BMM1:begin
					startB <= 0;
					if(doneB)begin
						temp <= Z;
					end
				end
				BEGINMT1:begin
					startM <= 1;
					x <= temp;
					y <= 1;
				end
				MT1:begin
					startM <= 0;
					if(doneM)begin
						C <= Im;
						if(e[i])begin
							state <= BEGINBMM2;
						end
						else begin
							state <= BEGINA;
						end
					end	
				end
				BEGINBMM2:begin
					 startB <= 1;
					 T <= C;
					 U <= Ahat;
					 sel <= 1;
				end
				BMM2:begin
					startB <= 0;
					if(doneB)begin
						temp <= Z;
					end
				end
				BEGINMT2:begin
					startM <= 1;
					x <= temp;
					y <= 1;
				end
				MT2:begin
					startM <= 0;
					if(doneM)begin
						C <= Im;
					end
				end
				END:begin
					done <= 1;
				end
				default:begin
					done <= 0;
					state <= WAIT;
				end
			endcase
		end
		else begin
			done <= 0;
			if(start)begin
				state <= BEGINI1;
			end
		end

	always@(*)begin
		case(state)
			WAIT:begin
				nxt_state = WAIT;
			end
			BEGINI1:begin
				nxt_state = I1;
			end
			I1:begin
				nxt_state = I1;
				if(doneI)begin
					nxt_state = BEGINI2;
				end
			end
			BEGINI2:begin
				nxt_state = I2;
			end
			I2:begin
				nxt_state = I2;
				if(doneI)begin
					nxt_state = BEGINA;
				end
			end
			BEGINA:begin
				nxt_state = BMM1;
			end
			BMM1:begin
				nxt_state = BMM1;
				if(doneB)begin
					nxt_state = BEGINMT1;
				end
			end
			BEGINMT1:begin
				nxt_state = MT1;
			end
			MT1:begin
				nxt_state = MT1;
				if(doneM)begin
					nxt_state = BEGINBMM2;
				end
			end
			BEGINBMM2:begin
				nxt_state = BMM2;
			end
			BMM2:begin
				nxt_state = BMM2;
				if(doneB)begin
					nxt_state = BEGINMT2;
				end
			end
			BEGINMT2:begin
				nxt_state = MT2;
			end
			MT2:begin
				nxt_state = MT2;
				if(doneM)begin
					nxt_state = BEGINA;
				end
			end
			END:begin
				nxt_state = WAIT;
			end
			default:begin
				nxt_state = WAIT;
			end
		endcase
	end

endmodule