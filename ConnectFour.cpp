#include <iostream>
#include <string>
using namespace std;

class ConnectFour{
  int board[6][7] = {{0}};
  string player1Col = "\u001b[31m";
  string player2Col = "\u001b[34m";
  string winRowCol = "\u001b[93m";
  string white = "\u001b[37m";

public:
  // empty constructor
  ConnectFour(){}

  // start a game of connect four
  void playGame(){
    while(true){
      // print intro
      cout << "---Connect Four---\n";

      int numOfPlayers;
      string input;
      cout << "How many players? (0-2): ";
      cin >> input;

      while(input != "0" && input != "1" && input != "2"){
        cout << "Invalid number of players!\n";
        cout << "How many players? (0-2): ";
        cin >> input;
      }
      
      numOfPlayers = stoi(input);
      cout << endl;

      if(numOfPlayers == 1){
        onePlayerGame();
      }
      else if(numOfPlayers == 2){
        twoPlayerGame();
      }
      else{
        zeroPlayerGame();
      }
      
      cout << "Play Again? (y/n): ";
      cin >> input;

      if(input[0] == 'y'){
        clearBoard();
        cout << "\n";
        continue;
      }
      else if (input[0] == 'n'){
        cout << "Goodbye!";
        break;
      }
      
      while(input[0] != 'y' && input[0] != 'n'){
        cout << "Invalid command.\nPlay Again? (y/n): ";
        cin >> input;

        if(input[0] == 'y'){
        clearBoard();
        cout << "\n";
        continue;
      }
      else if (input[0] == 'n'){
        cout << "Goodbye!";
        break;
      }
      }
      
    }
  }
private:
  void twoPlayerGame(){
    cout << "Player 1 vs Player 2\n";
    int playerTurn = 1;

    // two player game loop
    while(true){
      string input;

      // print out the board every round
      printBoard();

      // ask for current player for their input
      if(playerTurn == 1) cout << player1Col;
      else cout << player2Col;
      cout << "Player " << playerTurn << ": " << white;
      cin >> input;

      // quit if asked
      if(input[0] == 'q')
        break;
      // check that the input isn't out of bounds
      if(input[0] < '1' || input[0] > '7'){
        cout << "invalid input, q to quit\n";
        continue;
      }

      // convert the string into an int
      int inputCol = input[0] - 48;
      // decrement so its within the array
      inputCol--;

      // row of last placed piece
      int currRow = getRow(inputCol);
      // add a piece at input position
      // if piece cannot be placed reset round without changing player
      if(!addPlayerPiece(currRow, inputCol, playerTurn)){
        cout << "Cannot place piece there.\n";
        continue;
      }

      // check if player won
      if(checkWinningPiece(currRow, inputCol, playerTurn)){
        if(playerTurn == 1) cout << player1Col;
        else cout << player2Col;
        cout << "Player " << playerTurn << white << " has won\n";
        printBoard();
        break;
      }

      if(boardFull()){
        printBoard();
        cout << "Draw\n";
        break;
      }
      //flip playerturn
      playerTurn = (playerTurn % 2) + 1;
    }
  }

  void onePlayerGame(){
    srand(time(NULL));

    int currTurn = 1;
    int computerTurn;
    int humanTurn;

    cout << "Would you like to go first(1) or second(2)?: ";
    cin >> humanTurn;

    computerTurn = (humanTurn % 2) + 1;

    cout << "\nPlayer 1 vs Computer\n";

    // one player game
    while(true){
      // print out the board every round
      printBoard();

      /* human turn */
      if(humanTurn == currTurn){
        string input;

        // ask for player for their input
        if(currTurn == 1) cout << player1Col;
        else cout << player2Col;
        cout << "Player " << currTurn << ": " << white;
        cin >> input;

        // quit if asked
        if(input[0] == 'q')
          break;
        // check that the input isn't out of bounds
        if(input[0] < '1' || input[0] > '7'){
          cout << "invalid input, q to quit\n";
          continue;
        }

        // convert the string into an int
        int inputCol = input[0] - 48;
        // decrement so its within the array
        inputCol--;

        // row of last placed piece
        int currRow = getRow(inputCol);
        // add a piece at input position
        // if piece cannot be placed reset round without changing player
        if(!addPlayerPiece(currRow, inputCol, currTurn)){
          cout << "Cannot place piece there.\n";
          continue;
        }

        // check if player won
        if(checkWinningPiece(currRow, inputCol, currTurn)){
          if(currTurn == 1) cout << player1Col;
          else cout << player2Col;
          cout << "Player " << currTurn << white << " has won\n";
          printBoard();
          break;
        }

      } // end of human turn

      /* computer turn */
      if(currTurn == computerTurn){
        if(currTurn == 1) cout << player1Col;
        else cout << player2Col;
        cout << "Computer " << ": " << white;
        
        // get the best piece
        int computerMove = getComputerTurn(currTurn);
        cout << computerMove+1 << endl;
        int compRow = getRow(computerMove);

        addPlayerPiece(compRow, computerMove, currTurn);

        // check if player won
        if(checkWinningPiece(compRow, computerMove, currTurn)){
          if(currTurn == 1) cout << player1Col;
          else cout << player2Col;
          cout << "Computer " << white << " has won\n";
          printBoard();
          break;
        }
        
      }// end of computer turn

      if(boardFull()){
        cout << "Draw\n";
        printBoard();
        break;
      }
      //flip playerturn
      currTurn = (currTurn % 2) + 1;
    }
  }

  void zeroPlayerGame(){
    cout << "Computer 1 vs Computer 2\n";
    srand(time(NULL));

    int currTurn = 1;

    while(true){
      printBoard();

      if(currTurn == 1) cout << player1Col;
        else cout << player2Col;
      cout << "Computer " << currTurn << ": " << white;
        
      // get the best piece
      int computerMove = getComputerTurn(currTurn);
      cout << computerMove+1 << endl;
      int compRow = getRow(computerMove);

      addPlayerPiece(compRow, computerMove, currTurn);

      // check if player won
      if(checkWinningPiece(compRow, computerMove, currTurn)){
        if(currTurn == 1) cout << player1Col;
        else cout << player2Col;
        cout << "Computer " << currTurn << white << " has won\n";
        printBoard();
        break;
      }

      if(boardFull()){
        cout << "Draw\n";
        printBoard();
        break;
      }
      //flip playerturn
      currTurn = (currTurn % 2) + 1;
    }
  }

  bool addPlayerPiece(int row, int col, int player){
    if(row < 0) return false;
    board[row][col] = player;
    return true;
  }

  bool checkWinningPiece(int row, int col, int player){
    // create a new 2d array to hold the spaces so we can color them
    int** rowSpaces = new int*[4];
    for(int i = 0; i < 4; i++)
      rowSpaces[i] = new int[2];

    if(isFourInRow(row, col, player, rowSpaces)){
      for(int i = 0; i < 4; i++){
        board[rowSpaces[i][0]][rowSpaces[i][1]] = 3;
        delete[] rowSpaces[i];
      }
      delete[] rowSpaces;
      return true;
    }

    // delete the 2d arrray
    for(int i = 0; i < 4; i++)
      delete[] rowSpaces[i];
    delete[] rowSpaces;
    // no winnings
    return false;
  }
  
  bool isFourInRow(int row, int col, int player, int** spaces = nullptr){
    // U, L, UL, UR
    int moveOps[8] = {-1,0,  0,-1,  -1,-1,  -1,1};

    // loop though all four possible matching directs
    for(int i = 0; i < 8; i+=2)
    {
      // the current row and col we are checking
      int currRow = row;
      int currCol = col;

      // track the current place in the list of matching places
      if(spaces != nullptr){
        spaces[0][0] = row;
        spaces[0][1] = col;
      }
      
      // how many in a row we have found
      int rowCount = 1;

      // first loop to check first direction
      for(int j = 0; j < 3; j++)
      {
        // reached the end stop checking this direction
        if(currRow+moveOps[i] > 5 || currRow+moveOps[i] < 0 || currCol+moveOps[i+1] > 6 || currCol+moveOps[i+1] < 0)
          break;
        
        // next piece doesnt match so stop checking this direction
        if (board[currRow + moveOps[i]][currCol + moveOps[i+1]] != player)
          break;
        
        // piece matched, so continue to check next piece in the row
        currRow = currRow + moveOps[i];
        currCol = currCol + moveOps[i+1];

        // save the matching place at the current row count
        if(spaces != nullptr){
          spaces[rowCount][0] = currRow;
          spaces[rowCount][1] = currCol;
        }
        
        // add to the number we have found in a row
        rowCount++;
      }

      // reset the postion back to the placed piece
      currRow = row;
      currCol = col;

      // second loop to check the other direction
      for(int j = 0; j < 3; j++)
      {
        // reached edge of board stop checking
        if(currRow-moveOps[i] > 5 || currRow-moveOps[i] < 0 || currCol-moveOps[i+1] > 6 || currCol-moveOps[i+1] < 0)
          break;

        
        // next piece doesnt match so stop checking this direction
        if (board[currRow - moveOps[i]][currCol - moveOps[i+1]] != player)
          break;
        
        // piece matched, so continue to check next piece in the row
        currRow = currRow - moveOps[i];
        currCol = currCol - moveOps[i+1];

        // save the matching place at the current row count
        if(spaces != nullptr){
          spaces[rowCount][0] = currRow;
          spaces[rowCount][1] = currCol;
        }
        
        // add to the number we have found in a row
        rowCount++;
      }

      // there is a four in row
      if(rowCount == 4) return true;
    }
    return false;
  }

  void printBoard(){
    // top border
    for(int i = 0; i < 17; i++){
      cout << "-";
    }
    cout << endl;
    
    for(int i = 0; i < 6; i++){
      // side of board
      cout << "| ";
      for(int j = 0; j < 7; j++){
        if(board[i][j] == 0)
          cout << "  ";
        else if(board[i][j] == 1)
          cout << player1Col << "O " << white;
        else if(board[i][j] == 2)
          cout << player2Col << "O " << white;
        else if(board[i][j] == 3)
          cout << winRowCol << "O " << white;
      }
      cout << "|" <<endl;
    }
    for(int i = 0; i < 17; i++){
      cout << "-";
    }
    cout << endl;
    cout << "  ";
    for(int i = 1; i <= 7; i++){
      cout << i << " ";
    }
    cout << "\n\n";
  }
  
  int getComputerTurn(int player){
    int bestPlaceScore = 0;
    int bestPlace = rand() % 6;
    while(board[0][bestPlace] != 0) bestPlace = rand()%6; // make the best place is empty
    //cout << "[START] starting turn\n";

    // loop through, checking all possible positions
    for(int col = 0; col < 7; ++col){
      /* get the row piece will be placed at */
      int row = getRow(col); 
      // if row is full skip this column   
      if(row < 0) continue;

      int currPlaceScore = 0; // score for this place
      //cout << "[CHECK] checking place: " << col+1 << "  currScore: " << currPlaceScore << endl;

      // U, L, UL, UR
      int moveOps[8] = {-1,0,  0,-1,  -1,-1,  -1,1};

      /*---------------------------------------------------------------------------------------*/
      /* check how many in a row this would have */
      // loop though all directions seeing how many in row this place can make
      for(int i = 0; i < 8; i+=2) {
        // the current row and col we are checking
        int currRow = row;
        int currCol = col;

        int rowCount = 1;
        // first loop to check first direction
        for(int j = 0; j < 3; j++)
        {
          // reached the end stop checking this direction
          if(currRow+moveOps[i] > 5 || currRow+moveOps[i] < 0 || currCol+moveOps[i+1] > 6 || currCol+moveOps[i+1] < 0)
            break;
        
          // next piece doesnt match so stop checking this direction
          if (board[currRow + moveOps[i]][currCol + moveOps[i+1]] != player)
            break;
        
          // piece matched, so continue to check next piece in the row
          currRow = currRow + moveOps[i];
          currCol = currCol + moveOps[i+1];
        
          // add to the number we have found in a row
          currPlaceScore++;
          rowCount++;
          //cout << "[MATCH] match found  currScore: " << currPlaceScore << endl;
        }

        // reset the postion back to the placed piece
        currRow = row;
        currCol = col;

        // second loop to check the other direction
        for(int j = 0; j < 3; j++)
        {
          // reached edge of board stop checking
          if(currRow-moveOps[i] > 5 || currRow-moveOps[i] < 0 || currCol-moveOps[i+1] > 6 || currCol-moveOps[i+1] < 0)
            break;

        
          // next piece doesnt match so stop checking this direction
          if (board[currRow - moveOps[i]][currCol - moveOps[i+1]] != player)
            break;
        
          // piece matched, so continue to check next piece in the row
          currRow = currRow - moveOps[i];
          currCol = currCol - moveOps[i+1];
        
          // add to the number we have found in a row
          currPlaceScore++;
          rowCount++;
          //cout << "[MATCH] match found  currScore: " << currPlaceScore << endl;
        }
        //cout << "[ROW] rowCount: " << rowCount << endl;
        if(rowCount == 3){
          currPlaceScore += 3;
        }
        // this place will win the game make its score highest possible
        if(rowCount == 4) {
          //cout << "[WIN] found 4-in-row  currScore: " << currPlaceScore << endl;
          currPlaceScore = 200;
        }   
      }
      //cout << "[SCORE] finshed 4-in-row check  currScore: " << currPlaceScore << endl;
      // if this is a winning location end search, it is the best possible choice
      if(currPlaceScore == 200){
        bestPlace = col;
        //cout << "[WIN] found winning place at: " << col+1 << endl;
        break;
      }

      /*---------------------------------------------------------------------------------------*/
      /* check to block opponent's 4 in a row */
      
      // get the number of the other player
      int otherPlayer = (player % 2) + 1;
      
      // pretend we are the oppenet, if this place would give 4 in row, good move because we block
      for(int i = 0; i < 8; i+=2){
        int rowCount = 1;
        // the current row and col we are checking
        int currRow = row;
        int currCol = col;

        // first loop to check first direction
        for(int j = 0; j < 3; j++)
        {
          // reached the end stop checking this direction
          if(currRow+moveOps[i] > 5 || currRow+moveOps[i] < 0 || currCol+moveOps[i+1] > 6 || currCol+moveOps[i+1] < 0)
            break;
        
          // next piece doesnt match so stop checking this direction
          if (board[currRow + moveOps[i]][currCol + moveOps[i+1]] != otherPlayer)
            break;
        
          // piece matched, so continue to check next piece in the row
          currRow = currRow + moveOps[i];
          currCol = currCol + moveOps[i+1];
        
          // add to the number we have found in a row
          rowCount++;
        }

        // reset the postion back to the placed piece
        currRow = row;
        currCol = col;

        // second loop to check the other direction
        for(int j = 0; j < 3; j++)
        {
          // reached edge of board stop checking
          if(currRow-moveOps[i] > 5 || currRow-moveOps[i] < 0 || currCol-moveOps[i+1] > 6 || currCol-moveOps[i+1] < 0)
            break;

          // next piece doesnt match so stop checking this direction
          if (board[currRow - moveOps[i]][currCol - moveOps[i+1]] != otherPlayer)
            break;
        
          // piece matched, so continue to check next piece in the row
          currRow = currRow - moveOps[i];
          currCol = currCol - moveOps[i+1];
        
          // add to the number we have found in a row
          rowCount++;
        }
        //cout << "[OPROW] rowCount: " << rowCount << endl;
        // blocking a 3 in row is not a bad move
        if(rowCount == 3){
          currPlaceScore+=3;
          //cout << "[BLOCK] can block 3-in-row at: " << i+1 << "  currScore: " << currPlaceScore << endl;
        }
        // not placing here would lose game so high score
        if(rowCount == 4){
          currPlaceScore = 100;
          //cout << "[BLOCK] can block 4-in-row at: " << i+1 << "  currScore: " << currPlaceScore << endl;
        }
      }
      //cout << "[SCORE] finished block check  currScore: " << currPlaceScore << endl;
      // not placing here will lose the game but continue looking for a winning space
      if(currPlaceScore == 100) {
        //cout << "[BLOCK] 4-in-row block continue check  currScore: " << currPlaceScore << endl;
        bestPlace = col;
        bestPlaceScore = currPlaceScore;
        continue;
      }

      /*---------------------------------------------------------------------------------------*/
      /* check if this place gives oppnonet 4 in row */ 

      board[row][col] = player; // pretend like we placed this piece
      
      // loop through all possible opponet moves
      for(int i = 0; i < 7; i++){
        int opRow = getRow(i);
        if(opRow < 0) continue;
        // if oppnent can make a 4 in row this move was bad
        if(isFourInRow(opRow, i, otherPlayer)){
          currPlaceScore = -100;
          //cout << "[THROW] gives 4-in-row  currScore: " << currPlaceScore << endl;
          break;
        }
      }

      // undo the change we made to board
      board[row][col] = 0;
      //cout << "[SCORE] final currScore: " << currPlaceScore << endl;
      if(currPlaceScore > bestPlaceScore){
        //cout << "[NEW] replace best score  prev: " << bestPlaceScore;
        bestPlaceScore = currPlaceScore;
        bestPlace = col;
        //cout << " new: " << bestPlaceScore << endl;
        //cout << "[NEW] new best space: " << bestPlace << endl;
      }

    }// end of checking all positions

    return bestPlace;
  }

  int getRow(int col){
    // if column is full cannot place there
    if(board[0][col] != 0) return -1;

    // check all rows of col for empty space
    for(int i = 5; i >= 0; i--){
      // if space is empty mark board as player
      if(board[i][col] == 0){
        return i;
      }
    }
    return -1;
  }

  bool boardFull(){
    bool full = true;

    for(int i = 0; i < 7; i++){
      if(board[0][i] == 0){
        full = false;
        break;
      }
    }
    return full;
  }

  void clearBoard(){
    for(int i = 0; i < 6; i++){
      for(int j = 0; j < 7; j++)
        board[i][j] = 0;
    }
  }
};