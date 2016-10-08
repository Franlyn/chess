# chess
Chess Game

Overall Design:
- Class Game will take user inputs, start the game, and print all the outputs. It contains myBoard (class Board) and a vector of players (class Player).
- Class Player has subclasses Human and Computer (Level1, Level2, and Level3).
- In Class Human, inputs from a human player will be taken to move the chess piece from its starting position to the target position. The validity of each movement will be checked
by passing the positions to the public method valid(int r1, char c1, int r2,
char c2, char co) in class Board.
- Class Computer (contains 3 levels) will get the number of possible choices for a starting
move point by calling fromSize(char colour, int level) in class Board. Then, it will choose a random number within the range and pass it to toSize(int choose, int level) in class Board to get the number of possible choices of the end move points. After that, it will choose a random number within the range, and pass it to computerMove(int choose, int level) in class Board, so that a move is generated.
- Class Board creates a board. As the board is being initialized, each square on the board will be initialized by the public methods setPiece(har type, char co, vector<vector <Square>> &theBoard) in class Square.
- Class Square has a pointer of chess piece (class ChessPiece). Class ChessPiece has subclasses for all six types of chess. It can generate possible moves and possible attacks for each chess piece based on the type. a
- Class Square, TextDisplay, and GraphicsDisplay are three subclasses of class Observer. They are attached to each other and will be notified if any chess is moved.
Design patterns:
- Observer pattern:
- Square, TextDisplay and GraphicsDisplay are observers of Square.
- Each Square object has a vector of pointers to its observers, and a public method
notifyAll().
- Class Observer provides a virtual public method notify(Square &s,
vector<vector<Square>> &theBoard) to its subclasses. Therefore, each Square object, TextDisplay object and GraphicsDisplay object has a virtual public method notify(Square &s, vector<vector<Square>> &theBoard).
- Every time a Square object is updated, notifyAll() is called. This calls the notify(Square &s, vector<vector<Square>> &theBoard) method of all its observers to let them know the changes.
 
- Factory method pattern:
Player gives factory methods moveFrom(), moveTo() and cMove(Board &b) to Human and Computer. Human and computer players of different levels have different implementations, depending their specified rules.
- Decorator:
King, Queen, Bishop, Rook, Knight and Pawn are decorators of ChessPiece. Each one of them has a private method canCheck(const int r, const int c) and a virtual public methods update(vector<vector<Square>> &theBoard) provided by ChessPiece. In addition, each one of them add their own functionalities corresponding the rules for the chess piece type.

Player:
Class Player contains private fields playerType, indicating whether the player is a human or a computer player, and colour, indicating whether the player owns white or black chess pieces. Player has four subclasses: Human, Level1, Level2 and Level3. Human has virtual public methods moveFrom(), which takes input from a player to indicate which chess piece he/she wants to move, and moveTo(), which takes input from the player to indicate where the chess piece will be moved. Level1, Level2 and Level3 are different computer levels, each level has a virtual public method cMove(), which generates a move according to the rules specified by the corresponding level.

Game:
Class Game has private fields players, which is a vector of game players, and scores, which is a vector of scores corresponding to each player in players. Game has public methods setUp(Xwindow &w), new_game(Xwindow &w), play(Xwindow &w), humPlay(int np, Xwindow &w), comPlay(int np, Xwindow &w), displayInvalid(), displayCheck(char co), displayWon(char co, Xwindow &w, bool isresign), displayCurrentScore(), and displayFinalScore().
Once the program is running, the command setup can be optionally entered to begin setup mode before a chess game starts. In setup mode, setUp() is called to initialize board configurations using specified language. Then, "game white-player black player" should be entered to start a new game. new_game(Xwindow &w) is called to decide the type and sequence of players (with a total of two players. Type can be 'H' or 'C'). For each computer player, a level (1-3) is chosen. By default, Player 1 of the game uses black chess pieces, while player 2 uses white chess pieces. Then, play(Xwindow &w)
is called, players take turns to move their chess pieces by entering move, followed by the move coordinates. In this process, each player's corresponding move method is called to move chess pieces on the board. With every move made, the board is redisplayed. If one of the players is in check, displayCheck(char co) is called to determine the colour of the player who is in check and prints the information on screen. If the game has a winner, the field scores will be updated to award the winner a point, and displayWon(char co, Xwindow &w, bool isresign) is called to determine the colour of the winning player and prints the information on screen. If a player runs out of legal moves (draw), 0.5 points will be awarded to each player, and "Stalemate!" will be displayed. In addition, if a player entered "resign" to concede the game, displayWon(char co, Xwindow &w, bool isresign) will terminate the game and print each player's score on screen.

Board:
Class Board has a private field theBoard, which is a vector of vector of squares, simulating the actual board. It also has private fields size, won, capture and check, which are states of the board, td and gd, which are pointers to the board's text display and graphical display respectively. Board has a private method clearBoard(), which is used to set the board to its original state when a game ends.
Board has public methods numPossibleMoves(int r, char c), numPossibleAttacks(int r, char c) and numPossibleChecks(int r, char c), which are used by players to decide what moves to make for the chess piece at row r, column c; setUp(), which is called by a game's setUp() method to set up the board; init(int s, Xwindow &w), which is called in a game to initialize the board (takes Xwindow); isWon(), isCheck() and isCapture(), which return the states of a game; computerMove(int rand, int level), which is called by a computer player to generate a move; move(int r1, char c1, int r2, char c2), which is called by a human player to move the chess piece at row r1, column c1 to row r2, column c2; valid(int r1, char c1, int r2, char c2, char co), which tells a player if it is legal to move the chess piece at row r1, column c1 to row r2, column c2.

Square:
Class Square has private fields observers, r, c, chess_type, colour and piece. observers is a vector of all of the square's observers, including all squares, text display and graphical display. r, c indicata the square's position on the board. If the square has a
chess piece on it, piece points to the chess piece. chess_type, colour are information about the chess piece. Otherwise, piece is a nullptr, and chess_type, colour are both 'X'.
Square has the public methods getRow(), getCol() and isEmpty(), which return informationaboutthesquare;setType(chartype)andsetColour(charco), which are called to change the chess piece on the square, getType() and getColour(), which return the chess piece's information; setCoords(int row, int col), which is called when a square is created to set its r, c fields; setPiece(char type, char co, vector<vector <Square>> &theBoard), which creates a chess piece of type type and colour co on the square; canMove(int r, int c), canAttack(int r, int c), getMoveCoord(int rand), sizeMove(), sizeAttack(), sizeCheck(), inCheck(int r, int c), firstMove(), move_piece(int r, int c, vector<vector <Square>> &theBoard) and attack_piece(int r, int c, vector<vector <Square>> &theBoard) are used to facilitate moves; attach(const shared_ptr<Observer>& o) and notifyAll() are used to add and notify observers, and notify(Square &, vector<vector<Square>> &theBoard) is called by other squares to notify the square.

ChessPiece:
- Standard moves & attacks
In the abstract class ChessPiece, there are 8 important members, which are the common properties for each specific type of chess piece:
1. char type -> the type of the current piece {K, Q, B, P, N, R}
2. char colour -> represents which player it belongs to {W, B}
3. int row -> the row position in theBoard (0 - 7)
4. int col -> the column position in theBoard (0 - 7)
5. pair<int, int> possibleMoves -> stores currently all possible move points
6. pair<int, int> possibleAttacks -> stores currently all possible attack points
7. pair<int, int> possibleChecks -> stores currently all possible move/attack points
that can put my opponent in check
8. void update(&theBoard) -> called by notify() and is used to update the
current piece’s possibleMoves, possibleAttacks, and possibleChecks.
When making move, we use the three vectors to check whether the move is legal/valid or not. After each move, the moved square will notify all its observers and to update their possibleMoves, possibleAttacks, and possibleChecks.

- en passant
1. When the update(&theBoard) was called after a Pawn’s normal move,
we check whether there is(are) would-be-attacked Pawn(s) that satisfy en
passant’s condition, then the Pawn will add the special second move points to
it(them).
2. When the update(&theBoard) was called after a soecial second move, then we
will add special attack points to the would-attacking Pawn(s).

- Castling
In King’s update(&theBoard), it will check conditions:
1. Whether the King is firstmove. If yes; then...
2. Whether there exists such firstmove Rook(s) at the corner(s). If yes, then...
3. Whether there is no piece in between them and non of the square can put the
King in check. If yes, then...
4. Add corresponding move point(s) to the King and Rook(s) who both satisfy
castling conditions.
Since castling will not happen if Rook and King has moved, setNotFirst() (method in class ChessPiece) will be called(in void Square::move_piece(int r, int c, vector<vector <Square>> &theBoard)) when King or Rook is moved for the first time, so that we know if castling will happen.

- Checkmate
In class King, there is a isInCheck(r, c), which can provide information for determining checkmate. Basically, checkmate is accomplished in theBoard, which can call the square that is occupied by a King, and then by calling public method inCheck() in class Square to get the information from isInCheck(r, c).
