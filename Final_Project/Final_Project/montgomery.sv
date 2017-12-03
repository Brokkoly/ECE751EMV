module montgomery(clk, rst_n, xhat, yhat, M, Z, done, start);

	localparam SIZEM = 8;
	localparam SIZEHAT = 4;
	localparam SIZEI = 3;

	input [SIZEM-1:0] xhat;
	input [SIZEM-1:0] yhat; //TODO: right size? and Reg because Vivado yelled at me
	input [SIZEM-1:0] M; 
	input clk, rst_n, start;
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
	else if (start) begin
		state <= BEGIN;
		i <= 0;
		done <= 0;		
	end
	else if (state != WAIT)begin
		i <= i+1;
		if(i==SIZEHAT-2)begin
			state <= END;
			done <=1;
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
		done<= 0;
	end

	always@(*)begin
		case(state)
		WAIT:begin
			Z = Z;
			nxt_state= WAIT;
		end
		BEGIN:begin
			Z = 0;
			Z = yhat[i] ? (Z+xhat) : Z;
			Z = Z[0] ? (Z+M) : Z;	//qm stuff: Add M if i bit is 1 TODO: CHECK
			Z = Z>>1; //Divide by 2
			if(Z >= M)begin
						Z = Z - M;
					end
			if(Z >= M)begin
						Z = Z - M;
			end
			nxt_state = MID;
		end
		MID:begin
			Z = yhat[i] ? (Z+xhat) : Z;
			Z = Z[0] ? (Z+M) : Z;	//qm stuff: Add M if i bit is 1 TODO: CHECK
			Z = Z>>1; //Divide by 2
			if(Z >= M)begin
						Z = Z - M;
					end
			if(Z >= M)begin
						Z = Z - M;
			end
			nxt_state = MID;
		end
		END:begin
			Z = yhat[i] ? (Z+xhat) : Z;
			Z = Z[0] ? (Z+M) : Z;	//qm stuff: Add M if i bit is 1 TODO: CHECK
			Z = Z>>1; //Divide by 2
			if(Z >= M)begin
						Z = Z - M;
					end
			if(Z >= M)begin
						Z = Z - M;
			end
			nxt_state = WAIT;
		end
		default:begin
			Z =0;
			nxt_state= WAIT;
		end
		endcase
	end

endmodule