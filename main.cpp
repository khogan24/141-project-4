//game
//line_n + line_len = line_n+1
//

/*Board 0 with par 4 is:
 *
    0 1 2 3 4 5 6 7 8 9
  -----------------------
A | . . . . . . . . . . | A
B | . . . . . . . . . . | B
C | . . . @ &     . . . | C
D | . . . . .     . . . | D
E | . . .         . . . | E
F | . . . &     @ . . . | F
G | . . . . & @ . . . . | G
H | . . . . . . . . . . | H
  -----------------------
    0 1 2 3 4 5 6 7 8 9   0->9 = 10
 *
 *
 *
 *
 *
 * H|..........|H <--- line
 *  each line is 10 chars
 *  plus 2 borders* and 2 column indices*
 * *not garunteed, probable
 *
 *
 *
 */


//check if any blocks remain.



//funtion destroyBlocks() >> is itself a part of  Boards class
//check all adjacent blocks, destroy those destroyable
// line.at(currPos+9) = next line at same position
//line.at(currPos - 9) = previos line at same postion
//check if line is top/bottom


// function 'isValidMove'\
// check if move is valid. move if possible, or have the main() move
// par++
// call destoryBlocks()
bool isValidMove(board, currentBoard, int startPosition, int destination)
{
    //board is a 9x8 grid
    if((currentBoard.line.at(startPosition) == '.') // actual block?
        && (currentBoard.line.at(startPosition) != ' ')// not empty space
        && (currentBoard.line.at(destination) != ' ' )//if move is wrong direction of empty start it fails
    {
        return false;
    }
    else return true;

}


// function playerMove actually makes the move.
void playerMove(board, currentBoard, int startPosition, int destination)
{
    if(isValidMove)
    {
        makeMove(currentBoard, startPosition, destination);
    }
    //check if valid move
}