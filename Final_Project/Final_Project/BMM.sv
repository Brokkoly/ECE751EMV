
module BMM(clk,rst_n,M,T,U,sel,RmM,O,done,start);

		localparam SIZETU = 4;
		localparam SIZEM = 8;
		localparam SIZEI = 3;
		localparam ZERO = 4'd0;
		localparam R2 = 16; //2^n (2^SIZETU)

		input [SIZEM-1:0] T,U;	//Need to keep these constants
		input [SIZEM-1:0] M;
		input [SIZETU-1:0] RmM;
		input clk,rst_n,start;
		input sel;
		output reg [SIZEM:0] O;
		output reg done;

		reg [SIZEM:0] Z;
		wire doneI,doneM;
		reg startI,startM;
		reg [SIZEM-1:0] Xhat,Yhat;
		wire [SIZEM:0] hat,Im;
		reg [SIZEM-1:0] b,d,x,y;
		reg [1:0] partialComp;


		interleaved inter(.clk(clk),.rst_n(rst_n),.b(b),.d(d),.M(M),.Z(hat),.done(doneI),.start(startI));
		montgomery mont(.clk(clk),.rst_n(rst_n),.xhat(x),.yhat(y),.M(M),.Z(Im),.done(doneM),.start(startM));

		typedef enum reg [3:0] {WAIT,BEGINI1,I1,BEGINI2,I2,BEGINA,MID,ENDMID,I3,END} state_t;
		state_t state, nxt_state;

		always@(posedge clk, negedge rst_n)
			if(!rst_n)begin
				state <= WAIT;
				done <= 0;
				startI <= 0;
			end
			else if(start) begin
				state <= BEGINI1;
				done <= 0;
			end
			else begin
				state <= nxt_state;
				if(state == BEGINI1)begin
					startI <= 1;
					b <= T;
					d <= R2;
				end
				else if(state == I1)begin
					startI <= 0;
					if(doneI)begin
						Xhat <= hat;
						Yhat <= U;
					end
				end
				else if(state == BEGINI2)begin
					startI <= 1;
					b <= U;
					d <= R2;
				end
				else if(state == I2)begin
					startI <= 0;
					if(doneI)begin
						Yhat <= hat[SIZEM-1:0];
					end
				end
				else if(state == BEGINA)begin
					b <= Xhat;
					d <= {ZERO,Yhat[SIZEM-1:(SIZEM/2)]}; //Yh
					x <= Xhat;
					y <= {ZERO,Yhat[(SIZEM/2)-1:0]}; //Yl
					startI <= 1;
					startM <= 1;
					partialComp <= 0;
				end
				else if(state == MID)begin
					startI <= 0;
					startM <= 0;
					if(doneI)begin
						partialComp = partialComp + 1;
					end
					if(doneM)begin
						partialComp = partialComp + 1;
					end
				end
				else if(state == ENDMID)begin
					b <= Z;
					d <= 1;
					startI <= 1;
				end
				else if(state == I3)begin
					startI <= 0;
					if(doneI)begin
						O <= hat;
					end
				end
				else if(state == END)begin
					done <= 1;
				end
				else begin
					done <= 0;
				end
			end

		always@(*)begin
			Z = Z;
			case(state)
				WAIT:begin
					Z = Z;
					nxt_state = WAIT;
					
				end
				BEGINI1:begin
					Z = 0;
					nxt_state = I1;
				end
				I1:begin
					nxt_state = I1;
					if(doneI)begin
						if(!sel)begin
							nxt_state = BEGINI2;
						end
						else begin
							nxt_state = BEGINA;

						end
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
					Z = 0;
					nxt_state = MID;

				end
				MID:begin
					nxt_state = MID;
					if(partialComp == 2)begin
						nxt_state = ENDMID;
					end
				end
				ENDMID:begin
					Z = hat + Im;
					nxt_state <= I3;
				end
				I3:begin
					nxt_state = I3;
					if(doneI)begin
						nxt_state = END;
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