#include<iostream>
#include<bitset>
#include<limits>

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


bool black_king_moved = false;
bool black_krook_moved = false;
bool black_qrook_moved = false;
bool white_king_moved = false;
bool white_krook_moved = false;
bool white_qrook_moved = false;
bool castling = false;

char last_move_double_pawn_move[3] = {0,0,0};

char attempted_move[4];

char checking_p[2];
char checked_king[2];
bool checking_for_mate = false;

char steps[5][9][2] = {
    {{ROOK,ROOK},{7,0},{-7,0},{0,7},{0,-7},{0,0},{0,0},{0,0},{0,0}},
    {{KNIGHT,KNIGHT},{2,1},{2,-1},{-2,1},{-2,-1},{1,2},{1,-2},{-1,2},{-1,-2}},
    {{BISHOP, BISHOP},{7,7},{7,-7},{-7,7},{-7,-7},{0,0},{0,0},{0,0},{0,0}},
    {{QUEEN, QUEEN},{7,7},{7,-7},{-7,7},{-7,-7},{7,0},{-7,0},{0,7},{0,-7}},
    {{KING, KING},{1,1},{1,-1},{-1,1},{-1,-1},{0,1},{0,-1},{1,0},{-1,0}}
};

char white_turn = 0b00000001;

char board[8][8];

char starting_peices[8] = {ROOK,KNIGHT,BISHOP,QUEEN,KING,BISHOP,KNIGHT,ROOK};

void set_board()
{
    bool black = 0;
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
        cout << 8 - y;
        cout << "   ";
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
    cout << "      A   B   C   D   E   F   G   H" << endl;
}

void move_peice(char fromx, char fromy, char tox, char toy)
{
    if((board[fromx][fromy]&CLEAN) == KING)
    {
        if(!white_turn)
        {
            black_king_moved = true;
        }
        else
        {
            white_king_moved = true;
        }
    }
    if((board[fromx][fromy]&CLEAN) == ROOK)
    {
        if(fromx == 0)
        {
            if(!white_turn)
            {
                black_qrook_moved = true;
            }
            else
            {
                white_qrook_moved = true;
            }
        }
        if(fromx == 7)
        {
            if(!white_turn)
            {
                black_krook_moved = true;
            }
            else
            {
                white_krook_moved = true;
            }
        }
    }
    board[toy][tox] &= CLEAR_SPOT;
    board[toy][tox] |= (board[fromy][fromx] & ~(CLEAR_SPOT));
    board[fromy][fromx] &= CLEAR_SPOT;
}

bool try_castle(bool white_black, bool long_short)
{
    if(white_black)
    {
        if(long_short)
        {
            if(!white_king_moved && !white_qrook_moved)
            {
                if(board[7][0] == ROOK && (board[7][1]&CLEAN) == 0 && (board[7][2]&CLEAN) == 0 && (board[7][3]&CLEAN) == 0)
                {
                    move_peice(0,7,2,7);
                    move_peice(4,7,1,7);
                    return true;
                }
            }
        }
        else
        {
            if(!white_king_moved && !white_krook_moved)
            {
                if((board[7][7]&~(EMPTY_BLACK)) == ROOK && (board[7][6]&CLEAN) == 0 && (board[7][5]&CLEAN) == 0)
                {
                    move_peice(7,7,5,7);
                    move_peice(4,7,6,7);
                    return true;
                }
            }
        }
    }
    else
    {
        if(long_short)
        {
            if(!black_king_moved && !black_qrook_moved)
            {
                if((board[0][0]&~(EMPTY_BLACK)) == (ROOK|BLACK_PIECE) && (board[0][1]&CLEAN) == 0 && (board[0][2]&CLEAN) == 0 && (board[0][3]&CLEAN) == 0)
                {
                    move_peice(0,0,2,0);
                    move_peice(4,0,1,0);
                    return true;
                }
            }
        }
        else
        {
            if(!black_king_moved && !black_krook_moved)
            {
                if((board[0][7]&~(CLEAR_SPOT)) == (ROOK|BLACK_PIECE) && (board[0][6]&CLEAN) == 0 && (board[0][5]&CLEAN) == 0)
                {
                    move_peice(7,0,5,0);
                    move_peice(4,0,6,0);
                    return true;
                }
            }
        }
    }
    return false;
}

bool read_attempted_move(char move[])
{
    for(int i = 0; i < 4; i++)
    {
        attempted_move[i] = 0;
    }
    if(move[0] == 'O' && move[1] == 'O')
    {
        if(move[2] == 'O')
        {
            if(try_castle(white_turn, 1))
            {
                castling = true;
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if(try_castle(white_turn, 0))
            {
                castling = true;
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    if(move[0] >= 65 && move[0] <=72)
    {
        attempted_move[0] = (move[0]-65);
    }
    else
    {
        return 0;
    }
    if(move[1] >= 49 && move[1] <= 56)
    {
        attempted_move[1] = 7-(move[1]-49);
    }
    else
    {
        return 0;
    }
    if(move[2] >= 65 && move[2] <=72)
    {
        attempted_move[2] = (move[2]-65);
    }
    else
    {
        return 0;
    }
    if(move[3] >= 49 && move[3] <= 56)
    {
        attempted_move[3] = 7-(move[3]-49);
    }
    else
    {
        return 0;
    }

    return 1;
}

bool valid_pawn_move(int x1, int y1, int x2, int y2)
{
    bool forwardmove = false;
    bool kill = false;
    bool can_double = false;
    if(y1 == 6 && (board[y1][x1] & BLACK_PIECE) != BLACK_PIECE)
    {
        can_double = true;
    }
    if(y1 == 1 && (board[y1][x1] & BLACK_PIECE) == BLACK_PIECE)
    {
        can_double = true;
    }
    if(x1 == x2)
    {
        forwardmove = true;
    }
    else if(abs(y2-y1) == 1 && abs(x1-x2) == 1)
    {
        kill = true;
    }
    else
    {
        return false;
    }
    if(forwardmove)
    {
        int viable_move = ((board[y1][x1] & BLACK_PIECE) == BLACK_PIECE) ? 1 : -1;
        if(y2-y1 == viable_move && (board[y2][x2]&CLEAN) == 0)
        {
            return true;
        }
        else if(y2-y1 == viable_move*(2*can_double) && (board[y2][x2]&CLEAN) == 0 && (board[y1+viable_move][x1]&CLEAN) == 0)
        {
            last_move_double_pawn_move[0] = y2;
            last_move_double_pawn_move[1] = x2;
            last_move_double_pawn_move[2] = white_turn;
            return true;
        }
        else
        {
            return false;
        }
    }

    if(kill)
    {
        int viable_move = ((board[y1][x1] & BLACK_PIECE) == BLACK_PIECE) ? 1 : -1;
        if(y2-y1 == viable_move && (board[y2][x2]&CLEAN) != 0 && (board[y1][x1] & BLACK_PIECE) != (board[y2][x2] & BLACK_PIECE))
        {
            return true;
        }
        else if(last_move_double_pawn_move[0] != 0)
        {
            if(y2-y1 == viable_move && x2 == last_move_double_pawn_move[1] && (board[y1][x1] & BLACK_PIECE) != (board[last_move_double_pawn_move[0]][last_move_double_pawn_move[1]] & BLACK_PIECE) && y1 == last_move_double_pawn_move[0])
            {
                board[last_move_double_pawn_move[0]][last_move_double_pawn_move[1]] &= CLEAR_SPOT;
                return true;
            }
        }
    }
    return false;
}

bool check_move_valid(char x1, char y1, char x2, char y2)
{
    if(x1 == x2 && y1 == y2)
    {
        cout << "Moving to the same square?" << endl;
        return false;
    }

    //checks if the peice color matches the players turn
    if (((board[y1][x1] & BLACK_PIECE) == white_turn) && !checking_for_mate)
    {
        cout << "Not your turn" << endl;
        return false;
    }


    char peice = static_cast<char>(board[y1][x1] & CLEAN);
    char p_index;

    //iterates through steps array to find the right piece, pawn moves done in a different method because they are a pain
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
                return valid_pawn_move(x1,y1,x2,y2);
            }
            cout << "No peice on that tile" << endl;
            return false;
        }
    }

    //in the for loop, we will iterate over every 'step' in the step array, and iterate over each square that it would encompass, if it's blocked or out of bounds, we move on to the next step. The function returns true if x1+step*i == x2(same for y).
    for(int i = 1; i < 9; i++)
    {
        for(int n = 1; n <= abs(abs(steps[p_index][i][0])+abs(steps[p_index][i][1])); n++)
        {
            int xmove;
            int ymove;
            //need to step by one, but needed to include range in steps[], so a range of 7 in one direction would be [7,0], to turn this into one or 0 for the formula x1+step*n we static cast a bool into an int. if the step is 0 it remains 0 otherwise it becomes 1
            if(peice != KNIGHT)
            {
                xmove = (steps[p_index][i][0] < 0) ? -static_cast<int>(steps[p_index][i][0] != 0) : static_cast<int>(steps[p_index][i][0] != 0);
                ymove = (steps[p_index][i][1] < 0) ? -static_cast<int>(steps[p_index][i][1] != 0) : static_cast<int>(steps[p_index][i][1] != 0);
            }
            else
            {
                xmove=steps[p_index][i][0];
                ymove=steps[p_index][i][1];
            }
            int newx = x1+xmove*n;
            int newy = y1+ymove*n;
            if(newx == x2 && newy == y2)
            {
                if((board[y2][x2]&CLEAN) == 0)
                {
                    return true;
                }
                else if((board[y2][x2]&BLACK_PIECE) != (board[y1][x1]&BLACK_PIECE))
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            if(peice == KNIGHT)
            {
                break;
            }
            if(newx < 0 || newx > 7)
            {
                break;
            }
            if(newy < 0 || newy > 7)
            {
                break;
            }
            if((board[newy][newx]&CLEAN) != 0)
            {
                break;
            }
        }
    }
   return false;
}

void check_promotion()
{
    if(attempted_move[3] == 0 || attempted_move[3] == 7)
    {
        if((board[attempted_move[3]][attempted_move[2]]&CLEAN) == PAWN)
        {
            char peice;
            for(;;)
            {
                char c;
                cin >> c;
                switch(c)
                {
                    case 'N':
                    peice = KNIGHT;
                    break;
                    case 'R':
                    peice = ROOK;
                    break;
                    case 'Q':
                    peice = QUEEN;
                    break;
                    case 'B':
                    peice = BISHOP;
                    break;
                    default:
                    continue;
                }
                break;
            }
            board[attempted_move[3]][attempted_move[2]] &= ~(CLEAN);
            board[attempted_move[3]][attempted_move[2]] |= peice;
        }
    }
}

bool peice_can_see(char board[8], char peice, char px, char py, char kx, char ky)
{
    char p = (peice&CLEAN);
    switch(p)
    {
        case KING:

            {if(abs(py - ky) <=1 && abs(px - kx) <= 1)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;}


        case QUEEN:

            {if(abs(py - ky) == abs(px-kx))
            {
                char xmove = (kx-px) ? (kx-px)/abs(px-kx) : 0;
                char ymove = (ky-py) ? (ky-py)/abs(py-ky) : 0;
                for(int i = 1; i < abs(py-ky); i++)
                {
                    if((board[py+ymove*i]&(1 << 7-(px+xmove*i))))
                    {
                        return false;
                    }
                }
                return true;
            }
            else if(abs(py-ky) == 0 || abs(px-kx) == 0)
            {
                char xmove = abs(kx-px) ? (kx-px)/abs(kx-px) : 0;
                char ymove = abs(ky-py) ? (ky-py)/abs(ky-py) : 0;

                for(int i = 0; i < abs(py-ky)+abs(px-kx); i++)
                {
                    if(board[py+(ymove*i)]&(1 <<(7-(px+xmove*i))))
                    {
                        return false;
                    }
                }
                return true;
            }
            else
            {
                return false;
            }
            break;}


        case ROOK:

            {if(abs(py-ky) == 0 || abs(px-kx) == 0)
            {
                char xmove = abs(kx-px) ? (kx-px)/abs(kx-px) : 0;
                char ymove = abs(ky-py) ? (ky-py)/abs(ky-py) : 0;

                for(int i = 0; i < abs(py-ky)+abs(px-kx); i++)
                {
                    if(board[py+(ymove*i)]&(1 <<(7-(px+xmove*i))))
                    {
                        return false;
                    }
                }
                return true;
            }
            else
            {
                return false;
            }
            break;}


        case KNIGHT:

            {if(abs(py-ky) + abs(px-kx) == 3 && abs(abs(py-ky) - abs(px-kx)) == 1)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;}


        case BISHOP:
            {if(abs(py - ky) == abs(px - kx))
            {
                char xmove = (kx-px) ? (kx-px)/abs(px-kx) : 0;
                char ymove = (ky-py) ? (ky-py)/abs(py-ky) : 0;
                for(int i = 1; i < abs(py-ky); i++)
                {
                    if((board[py+ymove*i]&(1 << 7-(px+xmove*i))))
                    {
                        return false;
                    }
                }
                return true;
            }
            else
            {
                return false;
            }

        break;}


        case PAWN:
            {char color = (peice&BLACK_PIECE) ? -1 : 1;
            if((ky-py) == color and abs(px-kx) == 1)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;}
            
    }
    cout << "NOT A PEICE? SOMETHING BIG WRONG" << endl;
    return false;

}

bool check4check(char color_to_check, char sim_board[8][8])
{
    char simple_board[8] = {0,0,0,0,0,0,0,0};
    char king_loc[2];
    for(int y = 0; y < 8; y++)
    {
        for(int x = 0; x < 8; x++)
        {
            char peice = (sim_board[y][x]);
            if((peice&BLACK_PIECE) == color_to_check && (peice&CLEAN) != 0)
            {
                simple_board[y] |= (1 << 7-x);
                if((peice&CLEAN) == KING)
                {
                    king_loc[0] = x;
                    king_loc[1] = y;
                }
            }
        }
    }
    /*for(int i  = 0; i < 8; i++)
    {
        cout << std::bitset<8>(simple_board[i]) << endl;
    }*/
    for(int y = 0; y < 8; y++)
    {
        for(int x = 0; x < 8; x++)
        {
            char peice = (sim_board[y][x]);
            if((peice&BLACK_PIECE) != color_to_check && (peice&CLEAN) != 0)
            {
                if(peice_can_see(simple_board, peice, x, y, king_loc[0], king_loc[1]))
                {
                    checking_p[0] = x;
                    checking_p[1] = y;
                    checked_king[0] = king_loc[0];
                    checked_king[1] = king_loc[1];
                    return true;
                }
            }
        }
    }
    return false;
}

bool would_check(char who_turn, char x1, char y1, char x2, char y2)
{
    char board_copy[8][8];
    for(int y = 0; y < 8; y++)
    {
        for(int x = 0; x < 8; x++)
        {
            board_copy[y][x] = board[y][x];
        }
    }
    board_copy[y2][x2] &= CLEAR_SPOT;
    board_copy[y2][x2] |= (board_copy[y1][x1]&~(CLEAR_SPOT));
    board_copy[y1][x1] &= CLEAR_SPOT;
    return check4check(who_turn, board_copy);
}

bool check4checkmate(char color_to_check)
{
    //king move?
    for(int n = 1; n < 10; n++)
    {
        if(check_move_valid(checked_king[0],checked_king[1],steps[4][n][0],steps[4][n][1]) && !would_check(color_to_check,checked_king[0],checked_king[1],steps[4][n][0],steps[4][n][1]))
        {
            return false;
        }
    }
    //can kill?
    for(int y = 0; y < 7; y++)
    {
        for(int x = 0; x < 7; x++)
        {
            if((board[y][x]&BLACK_PIECE) == color_to_check)
            {
                if(check_move_valid(x,y,checking_p[0],checking_p[1]) && !would_check(color_to_check,x,y,checking_p[0],checking_p[1]))
                {
                    return false;
                }
            }
        }
    }
    //can block?
    char step[2];
    char num_steps;
    if(abs(checking_p[0] - checked_king[0]) == abs(checking_p[0] - checked_king[0]) && abs(checking_p[0] - checked_king[0]) > 1)
    {
        step[0] = (checked_king[0]-checking_p[0])/abs(checked_king[0]-checking_p[0]);
        step[1] = (checked_king[1]-checking_p[1])/abs(checked_king[1]-checking_p[0]);
        num_steps = abs(checking_p[0] - checked_king[0]);
    }
    else if(abs(checking_p[0]-checked_king[0])== 0 || abs(checking_p[1]-checked_king[1]) == 0 && abs(checking_p[0]-checked_king[0])+abs(checking_p[1]-checked_king[1]) > 1)
    {
        step[0] = (abs(checking_p[0]-checked_king[0]) != 0) ? (checked_king[0]-checking_p[0])/abs(checked_king[0]-checking_p[0]) : 0;
        step[1] = (abs(checking_p[1]-checked_king[1]) != 0) ? (checked_king[1]-checking_p[1])/abs(checked_king[1]-checking_p[1]) : 0;
        num_steps = abs(checking_p[0]-checked_king[0])+abs(checking_p[1]-checked_king[1]);
    }
    else
    {
        return true;
    }
    for(int i = 0; i < num_steps; i++)
    {
        for(int y = 0; y < 7; y++)
        {
            for(int x = 0; x < 7; x++)
            {
                if((board[y][x]&BLACK_PIECE) == color_to_check)
                {
                    if(check_move_valid(x, y, (checking_p[0] + step[0]*i), (checking_p[1] + step[1]*i)) && !would_check(color_to_check,x, y, (checking_p[0] + step[0]*i), (checking_p[1] + step[1]*i)))
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

void handle_moves()
{
    for(;;)
    {
        print_board();
        char c[5]= {0,0,0,0,0};
        cin.get(c, 5);
        cin.ignore();
        if(read_attempted_move(c))
        {
            cout<< "Good input" << endl;
            if(castling)
            {
                castling = false;
                white_turn ^= (1 << 0);
                continue;
            }
            bool m = check_move_valid(attempted_move[0],attempted_move[1],attempted_move[2],attempted_move[3]);
            if(m && !would_check(((~(white_turn))&BLACK_PIECE),attempted_move[0],attempted_move[1],attempted_move[2],attempted_move[3]))
            {
                cout << "VALID MOVE DETECTED" << endl;
                move_peice(attempted_move[0],attempted_move[1],attempted_move[2],attempted_move[3]);
                check_promotion();
                if(check4check(white_turn,board))
                {
                    cout << "CHECK";
                    checking_for_mate = true;
                    if(check4checkmate(white_turn))
                    {
                        cout << "CHECKMATE! GAME OVER!";
                    }
                    checking_for_mate = false;
                }
                white_turn ^= (1 << 0);
                if(last_move_double_pawn_move[2] == white_turn)
                {
                    last_move_double_pawn_move[0] == 0;
                    last_move_double_pawn_move[1] == 0;
                }
            }
            else
            {
                cout << "MOVE NOT VALID" << endl;
            }
            //cout << m << endl;
        }
        else
        {
            cout<< "Bad input" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}


int main()
{
    set_board();
    print_board();
    for(;;)
    {
        handle_moves();
    }
}