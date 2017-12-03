

module montgomery(clk, rst_n, xhat, yhat, M, Z, done, start);

	localparam SIZEM = 8;
	localparam SIZEHAT = 4;
	localparam SIZEI = 3;

	input [SIZEHAT-1:0] xhat;
	input [SIZEM-1:0] yhat,M; //I think this is wasteful TODO:Check
	input clk, rst_n, start;
	output reg [sizeM:0] Z;
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
		i <= SIZEM-1;
		done <= 0;		
	end
	else begin
		i <= i-1;
		if(i==1)begin
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

	always@(*)begin
		case(state)
		WAIT:begin
			Z = Z;
			nxt_state= WAIT;
		end
		BEGIN:begin
			Z = 0;
			Z = y[i] ? (Z+xhat) : Z;
			Z = Z[i] ? (Z+M) : Z	//qm stuff: Add M if i bit is 1 TODO: CHECK
			Z = Z>>1; //Divide by 2
			if(Z >= M)begin
						Z = Z - M;
					end
			if(Z >= M)begin
						Z = Z - M;
			end
			yhat = yhat>>1; //why does this seem weird to me
			nxt_state = MID;
		end
		MID:begin
			Z = y[i] ? (Z+xhat) : Z;
			Z = Z[i] ? (Z+M) : Z	//qm stuff: Add M if i bit is 1 TODO: CHECK
			Z = Z>>1; //Divide by 2
			if(Z >= M)begin
						Z = Z - M;
					end
			if(Z >= M)begin
						Z = Z - M;
			end
			yhat = yhat>>1; //why does this seem weird to me
			nxt_state = MID;
		end
		END:begin
			Z = y[i] ? (Z+xhat) : Z;
			Z = Z[i] ? (Z+M) : Z	//qm stuff: Add M if i bit is 1 TODO: CHECK
			Z = Z>>1; //Divide by 2
			if(Z >= M)begin
						Z = Z - M;
					end
			if(Z >= M)begin
						Z = Z - M;
			end
			yhat = yhat>>1; //why does this seem weird to me
			nxt_state = WAIT;
		end
		default:begin
			Z =0;
			nxt_state= WAIT;
		end
		endcase
	end

endmodule