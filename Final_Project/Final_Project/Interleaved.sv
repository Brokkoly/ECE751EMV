

module interleaved(clk,rst_n,b,d,M,Z,done,start);

		localparam SIZEBD = 4;
		localparam SIZEM = 8;
		localparam SIZEI = 3;
		localparam ZERO = 4'd0;// SIZEM-SIZEBD;
		
		input [SIZEM-1:0] d,b;
		input [SIZEM-1:0] M;
		input clk,rst_n,start;
		output reg [SIZEM:0] Z;
		output reg done;

		reg [SIZEI-1:0] i;

		typedef enum reg [2:0] {WAIT,BEGIN,MID,END} state_t;
		state_t state, nxt_state;

		always@(posedge clk, negedge rst_n)
			if(!rst_n)begin
				state <= WAIT;
				done <= 0;
			end
			else if(start) begin
				state <= BEGIN;
				i <= SIZEM-1;
				done <= 0;
			end
			else if(state != WAIT)begin
				i <= i - 1;
				if(i == 1)begin
					state <= END;
					done <= 1;
				end
				else begin
					state <= nxt_state;
					done <= 0;
				end
				if(state == END)begin
					done <= 0;
				end

			end
			else begin
				done <= 0;
			end

		
		always@(*)begin
			Z = Z;
			case(state)
				WAIT:begin
					Z = Z;
					nxt_state = WAIT;	
				end
				BEGIN:begin
					Z = 0;
					
					Z = Z<<1;
					
					Z = b[i] ? (Z+d) : Z;
					
					if(Z >= M)begin
						Z = Z - M;
					end
					if(Z >= M)begin
						Z = Z - M;
					end
					nxt_state = MID;	
				end
				MID:begin
					Z = Z<<1;
					
					Z = b[i] ? (Z+d) : Z;
					
					if(Z >= M)begin
						Z = Z - M;
					end
					if(Z >= M)begin
						Z = Z - M;
					end
					nxt_state = MID;
				end
				END:begin
					Z = Z<<1;
					
					Z = b[i] ? (Z+d) : Z;
					
					if(Z >= M)begin
						Z = Z - M;
					end
					if(Z >= M)begin
						Z = Z - M;
					end
					nxt_state = WAIT;
				end
				default:begin
					Z = 0;
					nxt_state = WAIT;
				end
			endcase
		end

endmodule 

