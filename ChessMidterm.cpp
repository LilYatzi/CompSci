#include<iostream>
#include<bitset>


using std::cout;
using std::cin;
using std::endl;

/*
Need a function to set up a clean board, needs an char[8][8]

*/
const char EMPTY_WHITE = 0b00000000;
const char EMPTY_BLACK = 0b10000000;
const char PAWN = 0b00000010;
const char ROOK = 0b00000100;
const char KNIGHT = 0b00001000;
const char BISHOP = 0b00010000;
const char QUEEN = 0b00100000;
const char KING = 0b01000000;
const char BLACK_PIECE = 0b00000001;
const char WHITE_PIECE = 0b11111110;
const char CLEAN = 0b01111110;
const char CLEAR_SPOT = 0b10000000;

char attempted_move[4];

char steps[5][9][2] = {
    {{ROOK,ROOK},{7,0},{-7,0},{0,7},{0,-7},{0,0},{0,0},{0,0},{0,0}},
    {{KNIGHT,KNIGHT},{2,1},{2,-1},{-2,1},{-2,-1},{1,2},{1,-2},{-1,2},{-1,-2}},
    {{BISHOP, BISHOP},{7,7},{7,-7},{-7,7},{-7,-7},{0,0},{0,0},{0,0},{0,0}},
    {{QUEEN, QUEEN},{7,7},{7,-7},{-7,7},{-7,-7},{7,0},{-7,0},{0,7},{0,-7}},
    {{KING, KING},{1,1},{1,-1},{-1,1},{-1,-1},{0,1},{0,-1},{1,0},{-1,0}}
};

char black_turn = 0b00000000;

char board[8][8];

char starting_peices[8] = {ROOK,KNIGHT,BISHOP,QUEEN,KING,BISHOP,KNIGHT,ROOK};

void set_board()
{
    bool black = 1;
    for(int y = 0; y <= 7; y++)
    {
        for(int x = 0; x <= 7; x++)
        {
            board[y][x] |= (black << 7);
            //sets the peices on the board and then sets their colors
            if(y==0)
            {
                board[y][x] |= starting_peices[x];
                board[y][x] |= BLACK_PIECE;
            }
            else if(y==1)
            {
                board[y][x] |= PAWN;
                board[y][x] |= BLACK_PIECE;
            }
            else if(y==6)
            {
                board[y][x] |= PAWN;
                board[y][x] &= WHITE_PIECE;
            }
            else if(y==7)
            {
                board[y][x] |= starting_peices[x];
                board[y][x] &= WHITE_PIECE;
            }
            black = !black;
        }
        black = !black;
    }
}

void print_board()
{
    //takes a char[4] do display the board, peice[0] and [3] are square color designators peice[1] is W or B for white and black peice[2] is the peice
    cout<< endl<< endl;
    char peice[4];
    for(int y = 0; y <= 7; y++)
    {
        for(int x = 0; x <= 7; x++)
        {
            //checks if square is empty, if it isn't it checks the color of the peice
            if((board[y][x] & CLEAN) == 0)
            {
                peice[1] = ' ';
                peice[2] = ' ';
            }
            else if(board[y][x] & (1 << 0))
            {
                peice[1] = 'b';
            }
            else
            {
                peice[1] = 'w';
            }
            //cout << (board[y][x] & CLEAN);
            switch ((board[y][x]&CLEAN))
            {
            case PAWN:
                peice[2] = 'P';
                break;
            case ROOK:
                peice[2] = 'R';
                break;
            case KNIGHT:
                peice[2] = 'N';
                break;
            case BISHOP:
                peice[2] = 'B';
                break;
            case QUEEN:
                peice[2] = 'Q';
                break;
            case KING:
                peice[2] = 'K';
                break;
            default:
                break;
            }
            //checks if square is black
            if(board[y][x] & (1 << 7))
            {
                peice[0] = '[';
                peice[3] = ']';
            }
            else
            {
                peice[0] = ' ';
                peice[3] = ' ';
            }
            cout << peice;
        }
        cout << endl;
    }
}

void move_peice(char fromy, char fromx, char toy, char tox)
{
    board[toy][tox] &= CLEAR_SPOT;
    board[toy][tox] |= (board[fromy][fromx] & ~(CLEAR_SPOT));
    board[fromy][fromx] &= CLEAR_SPOT;
}

int read_attempted_move(char move[])
{
    for(int i = 0; i < 4; i++)
    {
        attempted_move[i] = 0;
    }
    if(move[0] >= 65 && move[0] <=72)
    {
        attempted_move[0] = move[0]-65;
    }
    else
    {
        return 0;
    }
    if(move[1] >= 49 && move[1] <= 56)
    {
        attempted_move[1] = move[1]-49;
    }
    else
    {
        return 0;
    }
    if(move[2] >= 65 && move[2] <=72)
    {
        attempted_move[2] = move[2]-65;
    }
    else
    {
        return 0;
    }
    if(move[3] >= 49 && move[3] <= 56)
    {
        attempted_move[3] = move[3]-49;
    }
    else
    {
        return 0;
    }
    return 1;
}

bool valid_pawn_move()
{
    return false;
}

bool check_move_valid()
{
    char x1 = attempted_move[0];
    char y1 = attempted_move[1];
    char x2 = attempted_move[2];
    char y2 = attempted_move[3];
    /*for(int i = 0; i < 4; i++)
    {
        cout << int(attempted_move[i]) << endl;
    }*/
    //char peice = (board[y1][x1]&CLEAN);
    if (((board[y1][x1] & BLACK_PIECE) == black_turn))
    {
        cout << std::bitset<8>(board[y1][x1]) << endl;
        cout << std::bitset<8>((board[y1][x1] & BLACK_PIECE)) << endl;
        cout << std::bitset<8>(black_turn) << endl;
        cout << "Not your turn" << endl;
        return false;
    }
    
    char p_index;
    for(int i = 0; i < 6; i++)
    {
        if(steps[i][0][0] == peice)
        {
            p_index=i;
            i=6;
        }
        else if(i == 5)
        {
            if(peice == PAWN)
            {
                return valid_pawn_move();
            }
            cout << "No peice on that tile" << endl;
            return false;
        }
    }
    for(int i = 1; i < 9; i++)
    {
        //if()
    }
}



int main()
{
    set_board();
    print_board();
    cout << std::bitset<8>(steps[1][0][1]) << endl;
    for(int i = 0; i < 5; i++)
    {
        char c[4]= {0,0,0,0};
        cin.get(c, 5);
        cin.ignore();
        if(read_attempted_move(c))
        {
            cout<< "Good input" << endl;
            cout << check_move_valid() << endl;
        }
        else
        {
            cout<< "Bad input" << endl;
        }
    }
}