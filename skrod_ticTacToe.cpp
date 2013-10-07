/* =====================================================================*/

//  TicTacToe
//  Created by Edward Skrod on 4/11/13.

// LIBRARY FILES
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

// GLOBAL CONSTANTS
const int NUM = 3;
const int TOTAL_TRIES = 9;

// TYPEDEF
typedef char Board[NUM][NUM];
typedef int BoardPositionUsed[NUM][NUM];

// FUNCTION PROTOTYPES
void PrintWelcome();
void PopulateArray(Board, BoardPositionUsed);
void PopulateArray(Board, BoardPositionUsed, int, int, char);
void PrintBoard(const Board);
void EnterRowColumn(int, int&, int&, char&, const Board, BoardPositionUsed);
void ArtificialIntelligence(const Board, const BoardPositionUsed, int&, int&);
void ComputerChoice(int&, int&);
void CheckForWinner(const Board, bool&);

// MAIN FUNCTION
int main()
{
    int  selectRow,         // For user to select the index position
         selectColumn,      // For user to select the index column
         count = 0;         // to keep track of interations in do/while loop
    char playerSelection;   // To pass the 'X' and 'O' char to the array
    bool gameOver = false;  
  

    // Initialize Tic Tac Toe board array
    Board ticTac;
    
    // Set up a parrallel array to track whether or not a
    // position on the board has been selected
    BoardPositionUsed ticTacSelected;

    // Print Welcome Message
    PrintWelcome();
    
    // Populate Array with Initial Variables
    PopulateArray(ticTac, ticTacSelected);
    
    // Print the blank board
    PrintBoard(ticTac);
    
    do {
      
        // Prompt User to select a row and column
        EnterRowColumn(count, selectRow, selectColumn, playerSelection, ticTac, ticTacSelected);
        
        // Save player selection into array
        PopulateArray(ticTac, ticTacSelected, selectRow, selectColumn, playerSelection);
       
        // Print populated board
        PrintBoard(ticTac);       
        
        // Check to see if there was a winner
        CheckForWinner(ticTac, gameOver);
        
        count++; 
        
    } while ((count < TOTAL_TRIES) && !gameOver);
        
    if (!gameOver)
        cout << "I'm Sorry! There was no winner this game." << endl;
        
   cout << "Thank you for playing Tic Tac Toe!" << endl << endl;
    
    return 0;
}

// FUNCTIONS
/* =====================================================================*/
void PrintWelcome()

// Used by Main()
// Prints a welcome message

{  // PrintWelcome
    
    cout <<  "         Welcome to Tic Tac Toe!   " << endl;
    cout <<  "========================================" << endl << endl;
    cout << "To select a Row and Column, enter two digits\n"
         << "in the format X <space> Y.  To select Row 1,\n"
         << "Col 1, enter 1 <space> 1." << endl << endl;

}  // Print Welcome

/* =====================================================================*/
void PopulateArray(Board ticTac,
                   BoardPositionUsed ticTacSelected)

// Used by Main()
// This function populates an array's elements with blanks
// and populates a parrellel array's elements to false.

{  // Populate Array
    
    for (int row = 0; row < NUM; row++){
        
        for (int col = 0; col < NUM; col++) {
            
            ticTac[row][col] = ' ';
            ticTacSelected[row][col] = 0;
         }           
    }  
}  // Populate Array

/* =====================================================================*/
// Overloaded PopulateArray function
void PopulateArray(Board ticTac,
                   BoardPositionUsed ticTacSelected,
                   int selectRow,
                   int selectColumn,
                   char playerSelection)
// Used by Main()
// This function populates the array's elements with
// Player 1 and the Computer's choice.  It also sets the
// parralel array's element to true

{  // PopulateArray
    
    // Populate array with Player's and Computer's choice
    ticTac[selectRow - 1][selectColumn -1] = playerSelection;
    
    // Set element in parrallel array to true to denote that
    // the element has been played
    ticTacSelected[selectRow - 1][selectColumn - 1] = 1;
    
} // End PopulateArray

/* =====================================================================*/
void PrintBoard(const Board ticTac)

// Used by Main()

{   // PrintBoard

    cout <<  "          Col 1     Col 2     Col 3  " << endl;
    cout <<  "        ----------------------------- " << endl;
    
    // Print out the Tic Tac Toe Board
    for (int row = 0; row < NUM; row++){
        
        for (int col = 0; col < NUM; col++) {
            
            if (col == 0)
                cout << setw(5) << "Row " << (row + 1) << " |" << setw(5) << ticTac[row][col];
            else if (col == 1)
                cout << setw(5) << "|" << setw(5) << ticTac[row][col] << setw(5) << "|";
            else
                cout << setw(5) << ticTac[row][col] << setw(5) << "|";
            
        }   // end columns
        
        cout << endl;
        cout << "--------------------------------------" << endl;
        
    } // end rows
    
}   // End PrintBoard

/* =====================================================================*/
void EnterRowColumn(int count,
                    int& selectRow,
                    int& selectColumn,
                    char& playerSelection,
                    const Board ticTac,
                    BoardPositionUsed ticTacSelected)
// Used by Main()
// This function performs a check to determine whether it is Player 1
// or the Computer's turn.   Iteration 1 (when count = 0) and even numbered
// iterations are Player 1's turn.  When it is the computer's turn, the
// function prompts the user to hit <enter> and a position on the board
// is chosen by calling ComputerChoice().

{   // EnterRowColumn
    
    // Player 1
    if ((count == 0) || ((count % 2) == 0)){
        cout << "Player 1: Enter the Row and Column: ";
        cin >> selectRow >> selectColumn;
        
        while ((!cin) || (selectRow < 1) || (selectRow > 3) || (selectColumn < 1) || (selectColumn > 3)) {
            
            cin.clear();
            cin.ignore(80, '\n');

            
            cout << "Error:  You must enter two numbers between 1 and 3 in the format\n"
                 << "\"Row\" <space > \"Column\". Please try again: ";
            cin >> selectRow >> selectColumn;            
        }
        
        
        
        
        while (ticTacSelected[selectRow - 1][selectColumn - 1]) {
            
            cout << "You chose row " << selectRow << " column " << selectColumn << "." << endl;
            cout << "This board position has already been chosen.  Choose another position." << endl;
            cout << "Player 1: Enter the Row and Column: ";
            cin >> selectRow >> selectColumn;
        }
                
        cout << "\nYou chose row " << selectRow << " column " << selectColumn << "." << endl << endl;
        playerSelection = 'X';
    }
    
    // Computer
    else {
        
        bool intelligenceCheck = false;
        
        do {
            
            ComputerChoice(selectRow, selectColumn);            
            
            // Run ArtificialIntelligence once
            while(!intelligenceCheck){
                
                ArtificialIntelligence(ticTac, ticTacSelected, selectRow, selectColumn);
                intelligenceCheck = true;
            }
            
        } while (ticTacSelected[selectRow - 1][selectColumn - 1]);
            
        cout << "The computer chose row " << (selectRow) << ", column "
             << (selectColumn) << "." << endl << endl;
        
        playerSelection = 'O';
    }
} // End EnterRowColumn

/* =====================================================================*/
void ArtificialIntelligence(const Board ticTac,
                            const BoardPositionUsed ticTacSelected,
                            int& selectRow,
                            int& selectColumn)
// Used by EnterRowColumn
// This function performs a check against any two 'X' chars in a row,
// column or diagonal then sets selectRow and selectColumn with
// the position to block a win.  To prevent the function from choosing
// repeating a block, the function checks the array position to make sure
// it hasn't been populated (ticTacSelected)

{  // ArtificialIntelligence

    /*---------------------------DEFENSE--------------------------------*/
    /*--------------------------CHECK ROWS------------------------------*/
    
    // Check Row 1, Column 1 and 2 for Xs.
    // Put O in Row 1, Col. 3
    if ((ticTac[0][0] == 'X')               // Position 0,0 is X
        && (ticTac[0][1] == 'X')            // Position 0,1 is X
        && (ticTacSelected[0][2] == 0))     // Position 0,2 has not been used
    {
        selectRow = 1;
        selectColumn = 3;
    }
    
    // Check Row 2, Column 1 and 2 for Xs.
    // Put O in Row 2, Col. 3
    else if ((ticTac[1][0] == 'X')
             && (ticTac[1][1] == 'X')
             && (ticTacSelected[1][2] == 0))
    {
        selectRow = 2;
        selectColumn = 3;
    }
    
    // Check Row 3, Column 1 and 2 for Xs.
    // Put O in Row 3, Col. 3
    else if ((ticTac[2][0] == 'X')
             && (ticTac[2][1] == 'X')
             && (ticTacSelected[2][2] == 0))
    {
        selectRow = 3;
        selectColumn = 3;
    }
    
    // Check Row 1, Column 2 and 3
    // Put O in Row 1, Column 1
    else if ((ticTac[0][1] == 'X')
             && (ticTac[0][2] == 'X')
             && (ticTacSelected[0][0] == 0))
    {
        selectRow = 1;
        selectColumn = 1;
    }
    
    // Check Row 2, Column 2 and 3
    // Put O in Row 2, Column 1
    else if ((ticTac[1][1] == 'X')
             && (ticTac[1][2] == 'X')
             && (ticTacSelected[1][0] == 0))
    {
        selectRow = 2;
        selectColumn = 1;
    }
    
    // Check Row 3, Column 2 and 3
    // Put O in Row 3, Column 1
    else if ((ticTac[2][1] == 'X')
             && (ticTac[2][2] == 'X')
             && (ticTacSelected[2][0] == 0))
    {
        selectRow = 3;
        selectColumn = 1;
    }
    
    // Check Row 1, Column 1 and 3
    // Put O in Row 1, Column 2
    else if ((ticTac[0][0] == 'X')
             && (ticTac[0][2] == 'X')
             && (ticTacSelected[0][1] == 0))
    {
        selectRow = 1;
        selectColumn = 2;
    }
    
    // Check Row 2, Column 1 and 3
    // Put O in Row 2, Column 2
    // This check is redundant given else statement below
    else if ((ticTac[1][0] == 'X')
             && (ticTac[1][2] == 'X')
             && (ticTacSelected[1][1] == 0))
    {
        selectRow = 2;
        selectColumn = 2;
    }
    
    // Check Row 3, Column 1 and 3
    // Put O in Row 3, Column 2
    else if ((ticTac[2][0] == 'X')
             && (ticTac[2][2] == 'X')
             && (ticTacSelected[2][1] == 0))
    {
        selectRow = 3;
        selectColumn = 2;
    }
    
    /*--------------------------CHECK COLUMNS--------------------------*/
    // Check Column 1, Rows 1 and 2
    // Put O in Column 1, Row 3
    else if ((ticTac[0][0] == 'X')
             && (ticTac[1][0] == 'X')
             && (ticTacSelected[2][0] == 0))
    {
        selectRow = 3;
        selectColumn = 1;
    }
    
    // Check Column 2, Rows 1 and 2
    // Put O in Column 2, Row 3
    else if ((ticTac[0][1] == 'X')
             && (ticTac[1][1] == 'X')
             && (ticTacSelected[2][1] == 0))
    {
        selectRow = 3;
        selectColumn = 2;
    }
    
    // Check Column 3, Rows 1 and 2
    // Put O in Column 3, Row 3
    else if ((ticTac[0][2] == 'X')
             && (ticTac[1][2] == 'X')
             && (ticTacSelected[2][2] == 0))
    {
        selectRow = 3;
        selectColumn = 3;
    }
    
    // Check Column 1, Rows 2 and 3
    // Put O in Column 1, Row 1
    else if ((ticTac[1][0] == 'X')
             && (ticTac[2][0] == 'X')
             && (ticTacSelected[0][0] == 0))
    {
        selectRow = 1;
        selectColumn = 1;
    }
    
    // Check Column 2, Rows 2 and 3
    // Put O in Column 2, Row 1
    else if ((ticTac[1][1] == 'X')
             && (ticTac[2][1] == 'X')
             && (ticTacSelected[0][1] == 0))
    {
        selectRow = 1;
        selectColumn = 2;
    }
    
    // Check Column 3, Rows 2 and 3
    // Put O in Column 3, Row 1
    else if ((ticTac[1][2] == 'X')
             && (ticTac[2][2] == 'X')
             && (ticTacSelected[0][2] == 0))
    {
        selectRow = 1;
        selectColumn = 3;
    }
    
    // Check Column 1, Rows 1 and 3
    // Put O in Column 1, Row 2
    else if ((ticTac[0][0] == 'X')
             && (ticTac[2][0] == 'X')
             && (ticTacSelected[1][0] == 0))
    {
        selectRow = 2;
        selectColumn = 1;
    }
    
    // Check Column 2, Rows 1 and 3
    // Put O in Column 2, Row 2
    // Redundant due to else statement below
    else if ((ticTac[0][1] == 'X')
             && (ticTac[2][1] == 'X')
             && (ticTacSelected[1][1] == 0))
    {
        selectRow = 2;
        selectColumn = 2;
    }
    
    // Check Column 3, Rows 1 and 3
    // Put O in Column 3, Row 2
    else if ((ticTac[0][2] == 'X')
             && (ticTac[2][2] == 'X')
             && (ticTacSelected[1][2] == 0))
    {
        selectRow = 2;
        selectColumn = 3;
    }

    /*-------------------------CHECK DIAGONALS-------------------------*/
    // Check Row 1, Column 1 & Row 2, Column 2
    // Put O in Row 3, Column 3
    else if ((ticTac[0][0] == 'X')
             && (ticTac[1][1] == 'X')
             && (ticTacSelected[2][2] == 0))
    {
        selectRow = 3;
        selectColumn = 3;
    }
    
    // Check Row 2, Column 2 & Row 3, Column 3
    // Put O in Row 1, Column 1
    else if ((ticTac[1][1] == 'X')
             && (ticTac[2][2] == 'X')
             && (ticTacSelected[0][0] == 0))
    {
        selectRow = 1;
        selectColumn = 1;
    }
    
    // Check Row 1, Column 1 & Row 3, Column 3
    // Put O in Row 2, Column 2
    else if ((ticTac[0][0] == 'X')
             && (ticTac[2][2] == 'X')
             && (ticTacSelected[1][1] == 0))
    {
        selectRow = 2;
        selectColumn = 2;
    }
    
    // Check Row 1, Column 3 & Row 2, Column 2
    // Put O in Row 3, Column 1
    else if ((ticTac[0][2] == 'X')
             && (ticTac[1][1] == 'X')
             && (ticTacSelected[2][0] == 0))
    {
        selectRow = 3;
        selectColumn = 1;
    }
    
    // Check Row 3, Column 1 & Row 2, Column 2
    // Put O in Row 1, Column 3
    else if ((ticTac[2][0] == 'X')
             && (ticTac[1][1] == 'X')
             && (ticTacSelected[0][2] == 0))
    {
        selectRow = 1;
        selectColumn = 3;
    }

    /*---------------------------OFFENSE--------------------------------*/    
    // Check to see if center position on board is occupied
    // if not, set selectRow and selectColumn to center
    else if ((ticTac[1][1] != 'X') && (ticTac[1][1] != 'O'))
    {
        
        selectRow = 2;
        selectColumn = 2;
    }
    
    
    // Check for any two 'O' chars in a row, column or diagonal then set
    // selectRow and selectColumn with the position to win.
    
    /*--------------------------CHECK ROWS------------------------------*/
    
    // Check Row 1, Column 1 and 2 for Xs.
    // Put O in Row 1, Col. 3
    else if ((ticTac[0][0] == 'O')               // Position 0,0 is X
        && (ticTac[0][1] == 'O')            // Position 0,1 is X
        && (ticTacSelected[0][2] == 0))     // Position 0,2 has not been used
    {
        selectRow = 1;
        selectColumn = 3;
    }
    
    // Check Row 2, Column 1 and 2 for Xs.
    // Put O in Row 2, Col. 3
    else if ((ticTac[1][0] == 'O')
             && (ticTac[1][1] == 'O')
             && (ticTacSelected[1][2] == 0))
    {
        selectRow = 2;
        selectColumn = 3;
    }
    
    // Check Row 3, Column 1 and 2 for Xs.
    // Put O in Row 3, Col. 3
    else if ((ticTac[2][0] == 'O')
             && (ticTac[2][1] == 'O')
             && (ticTacSelected[2][2] == 0))
    {
        selectRow = 3;
        selectColumn = 3;
    }
    
    // Check Row 1, Column 2 and 3
    // Put O in Row 1, Column 1
    else if ((ticTac[0][1] == 'O')
             && (ticTac[0][2] == 'O')
             && (ticTacSelected[0][0] == 0))
    {
        selectRow = 1;
        selectColumn = 1;
    }
    
    // Check Row 2, Column 2 and 3
    // Put O in Row 2, Column 1
    else if ((ticTac[1][1] == 'O')
             && (ticTac[1][2] == 'O')
             && (ticTacSelected[1][0] == 0))
    {
        selectRow = 2;
        selectColumn = 1;
    }
    
    // Check Row 3, Column 2 and 3
    // Put O in Row 3, Column 1
    else if ((ticTac[2][1] == 'O')
             && (ticTac[2][2] == 'O')
             && (ticTacSelected[2][0] == 0))
    {
        selectRow = 3;
        selectColumn = 1;
    }
    
    // Check Row 1, Column 1 and 3
    // Put O in Row 1, Column 2
    else if ((ticTac[0][0] == 'O')
             && (ticTac[0][2] == 'O')
             && (ticTacSelected[0][1] == 0))
    {
        selectRow = 1;
        selectColumn = 2;
    }
    
    // Check Row 2, Column 1 and 3
    // Put O in Row 2, Column 2
    // This check is redundant given else statement below
    else if ((ticTac[1][0] == 'O')
             && (ticTac[1][2] == 'O')
             && (ticTacSelected[1][1] == 0))
    {
        selectRow = 2;
        selectColumn = 2;
    }
    
    // Check Row 3, Column 1 and 3
    // Put O in Row 3, Column 2
    else if ((ticTac[2][0] == 'O')
             && (ticTac[2][2] == 'O')
             && (ticTacSelected[2][1] == 0))
    {
        selectRow = 3;
        selectColumn = 2;
    }
    
    /*--------------------------CHECK COLUMNS--------------------------*/
    // Check Column 1, Rows 1 and 2
    // Put O in Column 1, Row 3
    else if ((ticTac[0][0] == 'O')
             && (ticTac[1][0] == 'O')
             && (ticTacSelected[2][0] == 0))
    {
        selectRow = 3;
        selectColumn = 1;
    }
    
    // Check Column 2, Rows 1 and 2
    // Put O in Column 2, Row 3
    else if ((ticTac[0][1] == 'O')
             && (ticTac[1][1] == 'O')
             && (ticTacSelected[2][1] == 0))
    {
        selectRow = 3;
        selectColumn = 2;
    }
    
    // Check Column 3, Rows 1 and 2
    // Put O in Column 3, Row 3
    else if ((ticTac[0][2] == 'O')
             && (ticTac[1][2] == 'O')
             && (ticTacSelected[2][2] == 0))
    {
        selectRow = 3;
        selectColumn = 3;
    }
    
    // Check Column 1, Rows 2 and 3
    // Put O in Column 1, Row 1
    else if ((ticTac[1][0] == 'O')
             && (ticTac[2][0] == 'O')
             && (ticTacSelected[0][0] == 0))
    {
        selectRow = 1;
        selectColumn = 1;
    }
    
    // Check Column 2, Rows 2 and 3
    // Put O in Column 2, Row 1
    else if ((ticTac[1][1] == 'O')
             && (ticTac[2][1] == 'O')
             && (ticTacSelected[0][1] == 0))
    {
        selectRow = 1;
        selectColumn = 2;
    }
    
    // Check Column 3, Rows 2 and 3
    // Put O in Column 3, Row 1
    else if ((ticTac[1][2] == 'O')
             && (ticTac[2][2] == 'O')
             && (ticTacSelected[0][2] == 0))
    {
        selectRow = 1;
        selectColumn = 3;
    }
    
    // Check Column 1, Rows 1 and 3
    // Put O in Column 1, Row 2
    else if ((ticTac[0][0] == 'O')
             && (ticTac[2][0] == 'O')
             && (ticTacSelected[1][0] == 0))
    {
        selectRow = 2;
        selectColumn = 1;
    }
    
    // Check Column 2, Rows 1 and 3
    // Put O in Column 2, Row 2
    // Redundant due to else statement below
    else if ((ticTac[0][1] == 'O')
             && (ticTac[2][1] == 'O')
             && (ticTacSelected[1][1] == 0))
    {
        selectRow = 2;
        selectColumn = 2;
    }
    
    // Check Column 3, Rows 1 and 3
    // Put O in Column 3, Row 2
    else if ((ticTac[0][2] == 'O')
             && (ticTac[2][2] == 'O')
             && (ticTacSelected[1][2] == 0))
    {
        selectRow = 2;
        selectColumn = 3;
    }
    
    /*-------------------------CHECK DIAGONALS-------------------------*/
    // Check Row 1, Column 1 & Row 2, Column 2
    // Put O in Row 3, Column 3
    else if ((ticTac[0][0] == 'O')
             && (ticTac[1][1] == 'O')
             && (ticTacSelected[2][2] == 0))
    {
        selectRow = 3;
        selectColumn = 3;
    }
    
    // Check Row 2, Column 2 & Row 3, Column 3
    // Put O in Row 1, Column 1
    else if ((ticTac[1][1] == 'O')
             && (ticTac[2][2] == 'O')
             && (ticTacSelected[0][0] == 0))
    {
        selectRow = 1;
        selectColumn = 1;
    }
    
    // Check Row 1, Column 1 & Row 3, Column 3
    // Put O in Row 2, Column 2
    else if ((ticTac[0][0] == 'O')
             && (ticTac[2][2] == 'O')
             && (ticTacSelected[1][1] == 0))
    {
        selectRow = 2;
        selectColumn = 2;
    }
    
    // Check Row 1, Column 3 & Row 2, Column 2
    // Put O in Row 3, Column 1
    else if ((ticTac[0][2] == 'O')
             && (ticTac[1][1] == 'O')
             && (ticTacSelected[2][0] == 0))
    {
        selectRow = 3;
        selectColumn = 1;
    }
    
    // Check Row 3, Column 1 & Row 2, Column 2
    // Put O in Row 1, Column 3
    else if ((ticTac[2][0] == 'O')
             && (ticTac[1][1] == 'O')
             && (ticTacSelected[0][2] == 0))
    {
        selectRow = 1;
        selectColumn = 3;
    }
    
    /*-----------------------USE THE RANDOM NUM-------------------------*/     
    else {
        // If none of the above conditions are met
        // Do nothing (i.e. keep random numbers)
    }
}  // End ArtificialIntelligence

/* =====================================================================*/
void ComputerChoice(int& randomNum1, int& randomNum2)
// Used by ArtificialIntelligence()
// This function generates random numbers to pass back to the
// EnterRowColumn function.

{  // Computer Choice
    
    // Seed srand
    int seed = static_cast<int>(time(0));
    srand(seed);
    
    randomNum1 = rand() % 3;        // Generate random num 0 - 2
    randomNum2 = rand() % 3;        // then add 1
 
    randomNum1 += 1;
    randomNum2 += 1;
    
}  // Computer Choice

/* =====================================================================*/
void CheckForWinner(const Board ticTac,
                    bool& gameOver)
// Used by Main()
// This function checks for a winner by looking for three Xs or Os in
// a row, column or diagonal

{  // CheckForWinner
    
    // PLAYER 1 WINS
    /*--------------------------CHECK ROWS------------------------------*/
    if ((ticTac[0][0] == 'X') && (ticTac[0][1] == 'X')
                              && (ticTac[0][2] == 'X'))
    {
        cout << "Player 1 Wins" << endl;
        gameOver = true;
    }
    else if ((ticTac[1][0] == 'X') && (ticTac[1][1] == 'X')
                                   && (ticTac[1][2] == 'X'))
    {
        cout << "Player 1 Wins" << endl;
        gameOver = true;
    }
    else if ((ticTac[2][0] == 'X') && (ticTac[2][1] == 'X')
                                   && (ticTac[2][2] == 'X'))
    {
        cout << "Player 1 Wins" << endl;
        gameOver = true;
    }
    
    /*--------------------------CHECK COLUMNS--------------------------*/
    else if ((ticTac[0][0] == 'X') && (ticTac[1][0] == 'X')
                                   && (ticTac[2][0] == 'X'))
    {
        cout << "Player 1 Wins" << endl;
        gameOver = true;
    }
    else if ((ticTac[0][1] == 'X') && (ticTac[1][1] == 'X')
                                   && (ticTac[2][1] == 'X'))
    {
        cout << "Player 1 Wins" << endl;
        gameOver = true;
    }
    else if ((ticTac[0][2] == 'X') && (ticTac[1][2] == 'X')
                                   && (ticTac[2][2] == 'X'))
    {
        cout << "Player 1 Wins" << endl;
        gameOver = true;
    }
    
    /*-------------------------CHECK DIAGONALS-------------------------*/
    else if ((ticTac[0][0] == 'X') && (ticTac[1][1] == 'X')
                                   && (ticTac[2][2] == 'X'))
    {
        cout << "Player 1 Wins" << endl;
        gameOver = true;
    }
    else if ((ticTac[2][0] == 'X') && (ticTac[1][1] == 'X')
                                   && (ticTac[0][2] == 'X'))
    {
        cout << "Player 1 Wins" << endl;
        gameOver = true;
    }
        
    // COMPUTER WINS
    /*--------------------------CHECK ROWS------------------------------*/
    else if ((ticTac[0][0] == 'O') && (ticTac[0][1] == 'O')
                                   && (ticTac[0][2] == 'O'))
    {
        cout << "The Computer Wins" << endl;
        gameOver = true;
    }
    else if ((ticTac[1][0] == 'O') && (ticTac[1][1] == 'O')
                                   && (ticTac[1][2] == 'O'))
    {
        cout << "The Computer Wins" << endl;
        gameOver = true;
    }
    else if ((ticTac[2][0] == 'O') && (ticTac[2][1] == 'O')
                                   && (ticTac[2][2] == 'O'))
    {
        cout << "The Computer Wins" << endl;
        gameOver = true;
    }
    
    /*--------------------------CHECK COLUMNS--------------------------*/
    else if ((ticTac[0][0] == 'O') && (ticTac[1][0] == 'O')
                                   && (ticTac[2][0] == 'O'))
    {
        cout << "The Computer Wins" << endl;
        gameOver = true;
    }
    else if ((ticTac[0][1] == 'O') && (ticTac[1][1] == 'O')
                                   && (ticTac[2][1] == 'O'))
    {
        cout << "The Computer Wins" << endl;
        gameOver = true;
    }
    else if ((ticTac[0][2] == 'O') && (ticTac[1][2] == 'O')
                                   && (ticTac[2][2] == 'O'))
    {
        cout << "The Computer Wins" << endl;
        gameOver = true;
    }
    
    /*-------------------------CHECK DIAGONALS-------------------------*/
    else if ((ticTac[0][0] == 'O') && (ticTac[1][1] == 'O')
                                   && (ticTac[2][2] == 'O'))
    {
        cout << "The Computer Wins" << endl;
        gameOver = true;
    }
    else if ((ticTac[2][0] == 'O') && (ticTac[1][1] == 'O')
                                   && (ticTac[0][2] == 'O'))
    {
        cout << "The Computer Wins" << endl;
        gameOver = true;
    }
    
    // No Winner Yet
    else
        gameOver = false;
    
}  // CheckForWinner
/* =====================================================================*/


