/* ----------------------------------------------------------- 
    Program 1: Basic Calculator with + - / * 
    
    Class: CS 141, Fall 2019.  Tues 10 am lab
    System: Codio
    Author: Vishvak Kumaran and Kevin Hogan

         -----------------------------------------------------------
  */
#include <iomanip>
#include <vector>
#include <iostream>   // For cin, cout
#include <fstream>    // For file input
#include <chrono>     // Used in pausing for some milliseconds using sleep_for(...)
#include <thread>     // Used in pausing for some milliseconds using sleep_for(...)
using namespace std;
// Global constants
const int MaxNumberOfBoards = 118;
const int BoardRows = 8;
const int BoardColumns = 10;
const int NumberOfPresetBoardParValues = 60;    // After the first 60 par values, the default par value is 15
const char FileName[] = "boards.txt";
const int SleepAmount = 150;                    // Length of time to pause, in milliseconds

char switchNumToChar( int num) //A switch case that switches the board numbers to the gamee pieces. 
{
	switch(num)
	{
		case 0:
			return ' '; //0 becomes a blank space
		case 1:
			return '&';// 1 becomes a ampersand
		case 2:
			return '@'; // 2 becomes the @ sign
		case 3:
			return'+'; // 3 becomes a +
		case 4:
			return '%'; //4 becomes a percent sign
		case 5:
			return'^'; //5 becomes the carrot
		case 6:
			return '#'; //6 becomes the hashtag
		case 7:
			return '='; // 7 becomes the equal sign. 
		case 8:
			return '*'; // 8 becomes the star
		case 9:
			return'.'; // 9 becomes the period. 
	}
}

class Board //This class is for one board. 
{ 
    public: 
    Board() = default; //Default constructor
	Board(int level, int arrayIndex[80], int par) 
	{
		int boardLevelNumber = level; //A variable for the board level number 
		parVal = par; //A variable for the par value
		for(int i = 0; i<BoardColumns*BoardColumns; i++) //A loop that places the board values within a array
			thisBoard[i] = arrayIndex[i];
	}
	void setLevel( int levelNum) //A set function for the level number 
	{
		this->boardLevelNumber = levelNum; // sets boardLevelNumber to levelNum
	}
	int pieceAt( int location )//this will return the board element at a given location
	{
		return thisBoard[location]; // 0-79
	}
	void setPieceAt( int index, int piece) //A set function for the piecee
	{
		this->thisBoard[index] = piece; //A pointer to the piece.
	}
	void displayBoard()  //A function to display the eboard. 
	{
		char rowLetter = 65; //'A'
		cout<<"\n     Board "<<boardLevelNumber<<" par "<< parVal; //the statement that prints before each board indicating board number and the par value.
		cout<<"\n       0 1 2 3 4 5 6 7 8 9  "<<setw(19)<<"\n     -----------------------";
		for(int index = 0; index < BoardRows * BoardColumns; index++) // A loop to print out the frame of the board
		{
			if(index % 10 == 0) // at each new line,
			{
				if (index !=0)// case for the first line
				{
					cout << " | " << rowLetter++;// at the end of each line, print out the |'LETTER'
				}
				cout <<endl;
				cout<< "   "<< rowLetter <<" |" ;// at the beginning of each line print out the 'LETTER'|
			}
			cout<<setw(2) << switchNumToChar(thisBoard[index]); // alignment
			
		} 
		cout << " | " << rowLetter;
		cout <<"\n     -----------------------"<<"\n       0 1 2 3 4 5 6 7 8 9  " << endl;
    }
	void setPar(int par) //A function that sets the par value 
	{
		this->parVal = par; //A pointer to the par value
	}
	int getPar() //A get function for the par value
	{
		return this->parVal; //Returns the pointer to the par value
	}
    void getMove(){ //Function that accounts for the moves made by the user in main
        while(true){
            string userInput; //A string input for the user
            cout<<"Your move: " << endl; //Allows the user to know when the move should be entered
            cin>>userInput;  //Gives the user the input option
        }
    }
	int *getBoardArray() //A function that returns the pointer to the current board
	{
		return this-> thisBoard; //Returns a pointer to the current board
	}
    private:
		int boardLevelNumber; //A integer variable
		int parVal;
		int *boardArrayIndex;
        int levelNum;
		int thisBoard[80];	
};  // end class Board
//------------------------------------------------------------------------------------------------------------------
// Class used to read in and store all game boards
class AllBoards // don't touch
{
    public:
        //------------------------------------------------------------------------------------------------------------------
        // Constructor that reads in data from the data file.
        AllBoards();    // Declaration.  See the definition outside the class, below.
    
        // Get and Set member functions.
        //------------------------------------------------------------------------------------------------------------------
        // Find and return a particular board.
        Board getBoard( int boardIndex)
        {
            // Validate board index number
            if( boardIndex < 0 || boardIndex > MaxNumberOfBoards) {
                cout << "In getBoard() inside AllBoards class, boardIndex "
                     << boardIndex << " is out of range. Exiting..." << endl;
                exit( -1);
            }
            // Construct a Board from one of all the boards
            Board newBoard( boardIndex, allBoards[ boardIndex], levelParValues[ boardIndex]);
            return newBoard;
        }
        //------------------------------------------------------------------------------------------------------------------
        // gets the par value
        int getParValue( int boardIndex) {
            int theParValue = 15;   // default
            if( boardIndex < NumberOfPresetBoardParValues) {
                theParValue = levelParValues[ boardIndex];
            }
            return theParValue;
        } // end getParValue()
    private:
        int par = 0;             // The number of moves it should take to solve this level
        int currentLevel = -1;   // Which board we're on
        int allBoards[ 118][ BoardRows * BoardColumns];   // Array to store all 118 8x10 boards
    
        // Par values for levels 0 through 59.  Default is 15 after that.
        const int levelParValues[ NumberOfPresetBoardParValues] =
            // 0   1   2   3   4   5   6   7   8   9
            { 4,  3, 14,  5,  6,  4,  4, 14,  5, 25,  //  0 -  9
             12, 17, 17,  8,  4, 12,  9,  8, 12,  8,  // 10 - 19
             10, 10, 16, 13, 20, 14, 10,  9, 12, 14,  // 20 - 29
             15, 13, 20,  8, 15, 10, 10, 11,  7, 23,  // 30 - 39
              8, 11, 16, 14, 12, 13, 13,  3, 35, 18,  // 40 - 49
             26, 10, 13, 18, 26, 12, 15,  5, 22, 15}; // 50 - 59
}; //end class allBoards
//This switch case will allow us to view the uppercase characters for each row as integer values
int rowCharToRowNum( char rowChar)
{
	
	switch( toupper(rowChar))
	{
		case 'A': //A switches to the 0 row
			return 0;
			break;			
		case 'B': //B switches to the 1 row
			return 1; 
			break;			
		case 'C': //C switches to the 2 row
			return 2;
			break;	
		case 'D': //D switches to the 3 row
			return 3;
			break;			
		case 'E': //E switches to the 4 row
			return 4;
			break;			
		case 'F': //F switches to the 5 row
			return 5;
			break;		
		case 'G': //G switches to the 6 row
			return 6;
			break;		
		case 'H': //H switches to the 7 row
			return 7;
			break;
	}
}
//------------------------------------------------------------------------------------------------------------------
//This function will acount for all the moves made by the user and adjust accordingly. 
//The parameters required include 3 variables to account for the board, the class, and two vectors used to store 
//and account for the integer indexes of the pieces. 
bool makemove(char row, //A character variable for the row
              int column,  //A integer variable to keep track of the column
              char directionChar, //A character variable that keeps track of the direction the character moves
              Board & theBoard, //The board class
              vector<int> &toDrop, //A vector that accounts for pieces that need be dropped
              vector<int> &toDestroy) //A vector that accounts for all the pieces that need to be destroyed
{
	int rowNum =  rowCharToRowNum(row); //A integer variable for the row number
	int columnNum = column; //A integer variable for the column
    bool returnVal = false; //A boolean that is initialized to false; this will be used for a variety of checks
	int direction = 0; //A direction variable 
	toDestroy.clear(); //Clears the vector prior to use
	int thePiece = 10*rowNum+columnNum; //Algebra that keeps track of the piece position 
	if(directionChar == 'r') 
	{
		direction = 1; //Sets the direction and movement of the piece based on user input. 
	}
	if(directionChar == 'l')
	{
		direction = -1; //Sets the direction and movement of the piece based on user input. 
	} 
	if(int(row) > 104) //Error checks that trigger to the user based on different errors. 
	{
		cout <<"Move value is out of bounds.  Please retry." << endl;
		returnVal = false;
	}
	else if(!direction) //Error checks that trigger to the user based on different errors. 
	{
		cout << "Invalid move direction.  Please retry." <<endl;
		returnVal = false; // return false if move is not possible
	}
	else if ((theBoard.pieceAt(thePiece) == 9) || (theBoard.pieceAt(thePiece) == 0)) // wall or empty space?
	{
		if(direction !=10)cout << "Attempting to move an invalid character.  Please retry."<<endl;// so it doesnt yell for 'gravity' moves
		returnVal = false; // return false if move is not possible
	}
	else if (theBoard.pieceAt((thePiece) + direction) != 0) // destination is not empty
	{
		 if(direction !=10)cout <<"Attempting to move into a non-empty space.  Please retry."<<endl;// so it doesnt yell for 'gravity' moves
		returnVal = false; // return false if move is not possible
	}
	else
	{	
		toDrop.push_back(thePiece+ direction); //Update the true drop vector 
        int indAbove = 10*rowNum+columnNum-10; //A vector that accounts for whether the piece should drop
        while(true) { 
            if (theBoard.pieceAt(indAbove) == 0 || theBoard.pieceAt(indAbove) == 9) //If the piece aboce is a blank or a dot break the loop.
			{
                break;
			}
            toDrop.push_back(indAbove); //Other wise continue to place the dropping pieces in the vector
            indAbove -= 10;
        }
		theBoard.setPieceAt( ( thePiece + direction), theBoard.pieceAt( thePiece));
		theBoard.setPieceAt( ( thePiece), 0);
		returnVal = true;
		theBoard.displayBoard(); //Display the new board after the drops
	}
	return returnVal;
}
//------------------------------------------------------------------------------------------------------------------
// populate the destroy vector manually
int populateDestroy(vector<int> &destroy, // The vector that will be used to destroy the pieces 
                    Board & theBoard) // The board class
{
	int foundOne = 0; //A counter checking for which character is found. 
	destroy.clear();// repopulate each time
	int thePiece;
	for(int i = 0; i<80; i++) //A loop through the entire board
	{
		if(theBoard.pieceAt(i) != 0 && theBoard.pieceAt(i) != 9) //If the piece is not a blank or a wall
		{
			if(foundOne > 0) 
			{
				thePiece = destroy.at(0); //Destroys the piecee
			}
			
			if(  ( theBoard.pieceAt(i) == theBoard.pieceAt(i+1)  )  
			   ||( theBoard.pieceAt(i) == theBoard.pieceAt(i-1)  )
			   ||( theBoard.pieceAt(i) == theBoard.pieceAt(i+10) )
			   ||( theBoard.pieceAt(i) == theBoard.pieceAt(i-10) )
			)// fill destroy with the indices of a piece if it has a neighbor
			{
				destroy.push_back(i);
				if(foundOne > 0 && theBoard.pieceAt(i) != theBoard.pieceAt(thePiece))// fill destroy with the indices of only one type of piece at a time.
				{
					destroy.pop_back();//remove dissimilar pieces
				}
				foundOne++;// record how many were found.
			}
		}
	}
	return foundOne;
}
//------------------------------------------------------------------------------------------------------------------
//A function that drops the pieces accordingly
void drop(vector<int> &toDrop, //The vector that stores the index values of the pieces that need to be dropped. 
          vector<int> &toDestroy, //A vector that stores pieces that will need to be destroyed.
          Board & theBoard){ //THe board class
	for(int index = 0; index < toDrop.size(); index++)//Looping through the to drop vector
    {
		while( (theBoard.pieceAt( toDrop.at( index)+10)) == 0)// piece under the current index
		{
			theBoard.setPieceAt( toDrop.at( index) +10, theBoard.pieceAt(toDrop.at( index))); //put piece at current index in the one below it.
			theBoard.setPieceAt(toDrop.at( index), 0);// set the current piece to 0
			toDrop.at(index) = toDrop.at(index)+10;// update the new index
			theBoard.displayBoard();
			this_thread::sleep_for(std::chrono::milliseconds(SleepAmount));// The animation
		}
	}
	for(int index = 0; index < toDrop.size(); index++) //A loop through the to drop vector
    {	
		int piece = theBoard.pieceAt(toDrop.at(index));
		if((theBoard.pieceAt(toDrop.at(index)+1) == piece) ) //if the same piece is to the right place it in the to destroy vector
		{
			toDestroy.push_back(toDrop.at(index));
		}
		if((theBoard.pieceAt(toDrop.at(index)+10) == piece))//if the same piece is below place it in the to destroy vector
		{
			toDestroy.push_back(toDrop.at(index));
		}
		if(( theBoard.pieceAt( toDrop.at(index) -1 ) == piece)) //if the same piece is to the left place it in the to destroy vector
		{
			toDestroy.push_back(toDrop.at(index));
		} 
	}
}
//------------------------------------------------------------------------------------------------------------------
//A function that will destroy the adjacent pieces
bool destroyAdjacentPieces(vector<int> &toDestroy, //The to destroy vector 
                           Board & theBoard, //The class
                           vector<int> &destroy, // THe vector used to destroy pieces
                           vector<int> &toDrop, //The vector that stores the pieces that need to drop
                           char row, //A row variable
                           int column) //A column variable
{
    int rowNum =  rowCharToRowNum(row); //A variable that indicates row numbers
	int columnNum = column; //Another column variable
    bool des = false; //A bool to control when the piece gets plased in the vector
	for(int i= 0; i < toDestroy.size();i++){ //A loop through the entire the vector which essentially contains the indexes for all pieces
        if(theBoard.pieceAt(toDestroy.at(i)) == theBoard.pieceAt(toDestroy.at(i)+10)){
            destroy.push_back( ( toDestroy.at( i)+10)); //If there is the same piece below place it in the destroy vector
            des = true; 
        }
        if(theBoard.pieceAt(toDestroy.at(i)) == theBoard.pieceAt(toDestroy.at(i)+1)){
            destroy.push_back( toDestroy.at( i)+1); //If there is the same piece to the right place it in the destroy vector
             des = true;
         }
         if(theBoard.pieceAt(toDestroy.at(i)) == theBoard.pieceAt(toDestroy.at(i)-1)){
            destroy.push_back(  toDestroy.at( i)-1); //If there is the same piece to the left place it in the destroy vector
			des = true;
         }
         if(des == true){ //Since the boolean is true place the index that we checked in the destroy vector
             destroy.push_back(toDestroy.at(i));
		 }
    }
	if(destroy.size() ==0) //if there is nothing in the vector nothing happens
	{
		return false; // no destuction was made
	}
	else
	{
		while ( populateDestroy(destroy, theBoard))
		{
			for(auto idx : destroy) { //Go through the entire vector and destroy each pieece
				theBoard.setPieceAt(idx, 0);
                int indAbove = idx-10;
                while(true) {
					if(indAbove > 79 || indAbove < 0) 
						break;
					if(theBoard.pieceAt(indAbove) == 0 ||  theBoard.pieceAt(indAbove) == 9) //if the above piece is a wall or a blank break the loop
					{
						break;
					}
					toDrop.push_back(indAbove); //else place the index in the vector
					indAbove -= 10;
				}
				destroy.clear(); //Clear the vector in between to clear the values and help indicate what is inside in there
			}
			populateDestroy(destroy, theBoard); 
			theBoard.displayBoard(); //Display the new board
		}
		return true;
	}
	return false;
}
//A function that checks if the level is done
bool isLevelDone(Board & theBoard) // Passes the board
{
	for(int i = 0; i < 79; i++) //Loops through and checks if the board is blank
	{
		if(theBoard.pieceAt(i) != 9 && theBoard.pieceAt(i) != 0)
		{
			return false;
		}
	}
	return true;
}
////------------------------------------------------------------------------------------------------------------------
// AllBoards constructor
AllBoards::AllBoards()
 {
    // Read in all the boards from the data file
    ifstream inputFileStream;  // declare the input file stream

    // Open input file and verify file open worked.
    inputFileStream.open( FileName);
    if( !inputFileStream.is_open()) {
        cout << "Could not find input file. " << FileName << ".  Exiting..." << endl;
        exit( -1);
    }
    // Read and discard the five lines of comments at the beginning of the file.
    string inputLine; // 
    for( int i=0; i<5; i++) { // gets first 5 lines
        getline(inputFileStream, inputLine);
    }
    
    // Now read each of the 118 (MaxNumberOfBoards) boards.  Each one starts with a comment that has the board number.
    for( int boardIndex = 0; boardIndex < MaxNumberOfBoards; boardIndex++) {
        // Read the comment with the board number
        getline(inputFileStream, inputLine);
        
        // For each board now read the BoardRows * BoardColumns number of board values, as integers
        for( int row=0; row<BoardRows; row++) {
            for( int col=0; col<BoardColumns; col++) {
                inputFileStream >> allBoards[ boardIndex][ row * BoardColumns + col];
            }
            // Get rid of end-of-line character at the end of each board, so we can get a clean start on reading the
            //   first line of the next board, on the line with the comment and board number.
            getline(inputFileStream, inputLine);
        }
    }//end for( int boardIndex=0...

    // Close the input file.
    inputFileStream.close();
}//end AllBoards() constructor
//------------------------------------------------------------------------------------------------------------------
//Function that displays the intial directions
void displayDirections()
{
    cout << "\nWelcome to Vexed!  \n"
         << "The objective is to place identical pieces next to each other, so that they vanish,   \n"
         << "clearing the board completely within the indicated number of moves. On each move      \n"
         << "enter the row, column, and direction (L or R) to move, in either upper or lower       \n"
         << "case. You may also enter 'x' to exit the program, or 'r' to reset the current level. \n"
         << endl;
}
//------------------------------------------------------------------------------------------------------------------
// Driver for the program, using the classes and functions declared above
int main()
{
	vector<int> toDrop; //Drop vector that is passed by reference and is updated in main. 
	vector<int> toDestroy; //to destroy vector that is passed by reference and is updated in main. 
    vector<int> destroy; //Destroy vector that is passed by reference and is updated in main. 
    AllBoards allTheBoards;     // Reads in and stores all the boards from a data file
    int currentBoardIndex = 0;  // Starting board index
    Board theBoard;             // The board instance, that is set to hold the values for each level
	int score = 0;              // Score accumulates par points for each level finished
	int moveCounter = 1;  //A move counter to track the number of moves
    displayDirections(); //Displays the initial function with the directions
	int column; // A column variable
	char row; //A row variable
	char direction; //A variable keeps track of the direction
    char arrayForMoves[2]; //A array that keeps track of the inputs 
	theBoard = allTheBoards.getBoard( currentBoardIndex); 
	theBoard.setPar(allTheBoards.getParValue(currentBoardIndex));
	theBoard.displayBoard(); //Display the board 
	while(true) //A loop through the moves from board to board
	{
		cout <<moveCounter<< ". Your move: "<<endl; //Gives the user a input option
		cin >> arrayForMoves[0];
        if(arrayForMoves[0] == 'x'){//exit condition 
            break;
            exit(-1);
        }
		if(arrayForMoves[0] == 'r') 
		{//reset condition
			theBoard = allTheBoards.getBoard( currentBoardIndex);
			theBoard.setPar(allTheBoards.getParValue(currentBoardIndex));
			theBoard.setLevel(currentBoardIndex);
			moveCounter = 1; 
			theBoard.displayBoard();
			continue;
		}
        cin>>arrayForMoves[1];
		if(arrayForMoves[0] == 's')
		{//select level for the user. 
			theBoard = allTheBoards.getBoard( int(arrayForMoves[1]-'0'));
			theBoard.setPar(allTheBoards.getParValue(int(arrayForMoves[1]-'0')));
			currentBoardIndex = int(arrayForMoves[1]-'0');
			theBoard.setLevel(currentBoardIndex);
			theBoard.displayBoard();
			continue;
		}
        cin>> arrayForMoves[2]; 
		if(!makemove(arrayForMoves[0], int(arrayForMoves[1]-'0'), arrayForMoves[2], theBoard, toDrop, toDestroy))//function that allows the user to make a move
		{
			moveCounter = 0;
		}
        while(toDrop.size()) { //While loop that constantly drops and destroys the pieces until the level is done. 
            drop(toDrop, toDestroy, theBoard);//Drop function to drop the pieces;
			toDrop.clear();//Clears the drop vector in order to store new values to drop after each move
            destroyAdjacentPieces(toDestroy,theBoard,destroy,toDrop,row,column); //Destroy function that clears the eboard
			toDestroy.clear(); //Clear the toDestroy vector to store new pieces to be checked to be destroyed
			if(isLevelDone(theBoard))//Checks if the level has been completed
			{
				if(moveCounter > theBoard.getPar())// over par; reset board.
				{
					cout <<"Sorry, you took "<< moveCounter<<" moves and you must finish within "<<theBoard.getPar()<<" moves before moving on."<<endl;
					toDestroy.clear(); //Clears all three vectors so new indices can be stored
					destroy.clear();
					toDrop.clear();
					theBoard = allTheBoards.getBoard(currentBoardIndex);
					theBoard.setLevel(currentBoardIndex);
					theBoard.displayBoard(); 
					moveCounter = 0;
					break;
				}
				moveCounter = 0;
				toDestroy.clear(); //Clears all three vectors so new indices can bee stored
				destroy.clear();
				toDrop.clear();
				cout << "Congratulations!  On to the next level. " << endl;//Indicates a level has been passed
				currentBoardIndex++;//Counter of the board index
				score += theBoard.getPar(); //Adds the par value to the score
				cout<<"Score: "<<score<<endl; //Display the score
				theBoard = allTheBoards.getBoard(currentBoardIndex);//Get the new board
				theBoard.setLevel(currentBoardIndex);
				theBoard.displayBoard(); //display new board
				break; // Break statement if loop is done
			}
        }
		moveCounter++;//Iterate counter
	}
    return 0;
}
