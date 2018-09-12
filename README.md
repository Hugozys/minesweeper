## A Command-Line Based Minesweeper

### Game Rule Introduction
The goal of the game is to uncover all the squares that do not contain mines without being "blown up" by clicking on a square with a mine underneath. 
The location of the mines is discovered by a process of logic. Clicking on the game board will reveal what is hidden underneath the chosen square or squares (a large number of blank squares may be revealed in one go if they are adjacent to each other). Some squares are blank but some contain numbers (1 to 8), each number being the number of mines adjacent to the uncovered square. To help avoid hitting a mine, the location of a suspected mine can be marked by flagging it with the right mouse button. The game is won once all blank squares have been uncovered without hitting a mine, any remaining mines not identified by flags being automatically flagged by the computer. 
However, in the event that a game is lost and the player mistakenly flags a safe square, 
that square will either appear with a red X covering the mine (denoting it as safe), or just a red X (also denoting it as safe). 
The game board comes in three set sizes: beginner, 
intermediate, and expert, though a custom option is available as well.

#### STEP 1
I think we can start from very simple plan. The first thing I'm gonna do is to try to build a very simple command-line based minesweep.
It may have a 9*9 board, it is a beginner level with 10 mines randomly located at those grids.

A user may do the following:

* He can enter a pair of coordinates consisting of x and y, namely (x,y) to investigate that paticular grid:
    * If the grid has not been investigated, then it will become non-empty
        * If the grid contains a mine, then the player loses and board should display all the mines.
        * If not contains, then the grid will show a numerical value or blank, the game will continue.
    * If the grid has already been investigate, it will let user choose another grid that hasn't been investiaged yet.
* The user can choose to mark a unexplored grid if he suspects that grid is actually a mine. He can also undo it. The grid will
become a question mark.

For the current concern:
I should figure out how to design the board class:
* It SHOULD have a data strcuture to hold the information about each grid
* It SHOULD have a field to hold the information about the  total mine numbers
* It SHOULD have a method to print itself every time.

Your goal by this weekend would be to write out this board class and some of the methods, successfully render the board on the terminal (check Jun 3rd)

Your goal by this weekend would be to write the recursive rendering method of board class (when the game starts, the user is able to randomly explore a grid, and the there may be multiple grids revealed instead of just the one the user chooses (Jun 10th)

Your goal is to write the main function which enable interaction with the player. It involves:

-click a grid (DONE)

-mark a grid  (DONE)

-designate board size and mine numbers (DONE)

-tell the player if he loses or wins (DONE)

    
#### STEP 2
We could make it multiple difficulties. Beginner, Intermediate and Hard with larger board size and more mines.
The player should be able to choose between these levels

Your goal is to improve your main function in such a way that if the user enter "b" command while playing or he finished one round, he should be brought back to a status where the game would let him choose difficulties (easy medium hard customize) and start a new round. You should also implement checking if the player wins after every update to the board

To keep the integrity of board displaying, you should add constraint on the max number of rows and columns the player is allowed
to put in, You could take use of the alphabet displaying the columns and rows. So the maximum rows(columns) number SHOULD be
0-9 + [A-T] = 10 + 20 = 30
Notice that this needs you to change some parsing function so that it can support the following command:
c A D
m F G


Your goal is to implement print help function(Done)

Your goal is to test the program further






### STEP 3
It will be really awesome if we could have a GUI version of this game







