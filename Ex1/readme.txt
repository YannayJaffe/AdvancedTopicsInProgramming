Note that I'm submitting alone.
Due to encoding issues (the e-mail is in Hebrew), I'm adding a pdf with the relevant e-mail confirmation.

notes:
1. I treat blank lines as legit lines, in a way that I'm skipping those without any impact on the result.
2. My design is as follows:
	2.1 There is a Match class that holds both players (instances of class Player) and a game board (instance of a class GameBoardForPlayers).
	2.2 GameBoardForPlayers inherits from GameBoard class because i want to give friend privilleges to Players on the board and no one else, however I want to 	keep some of the board's internals as private.
	2.3 There are classes that represent a game piece, game moves and initial placing of the pieces.
	2.4 Players are responsible for placing the pieces on the board.
	2.5 When generating a game move/game initialization, there is a check that the format is legal.
	2.6 When performing placement/movement of pieces there is a check that the placement/movement is legal. The check is done by the players, and in a 	second thought, maybe I should had given the responsibillity of the check to the board.
	2.7 Match class is resposible for alternating the players, update scores, and keep trck of the winner.
3. When playing a game you should:
	3.1 Generate a Match instance, providing the paths for the input files
	3.2 Call Match::loadBoard, which performs the loading of the board by bothe of the players
	3.3 Call Match::printInitErrors which prints the errors that occured during board initialization
	3.4 Call Match::playMoves in order to simulate the entire game (after the loading succeeded)
	3.4 Call Match::printMoveErrors in order to print the error that occured (if occured) during the match
	3.5 Call Match::printWinner in order to print the summary of the game.
4. note: for the different print methods you need to provide an opened std::ostream object (such as a file, standard output...)