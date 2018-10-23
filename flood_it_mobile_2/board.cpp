#include "board.h"

QString colorManagement(const int colorIndex)
{
    switch (colorIndex)
    {
        case 0:
            return "red";
            break;

        case 1:
            return "green";
            break;

        case 2:
            return "blue";
            break;

        case 3:
            return "yellow";
            break;

        case 4:
            return "magenta";
            break;

        case 5:
            return "orange";
            break;

        default:
            return "black";
            break;
    }
}

int convertColor(QString color)
{
    if (color == "red")
        return 0;


    if (color == "green")
        return 1;


    if (color == "blue")
        return 2;


    if (color == "yellow")
        return 3;


    if (color == "magenta")
        return 4;


    if (color == "orange")
        return 5;

   return 0;
}

board::board()
:m_nrOfMoves(0)
,m_board()
,m_boardQML()
{

}

//setters
void board::generateBoard(const int boardSize)
{
    //clear the previous board
        if(!m_board.empty())
        {
            m_board.clear();
            m_boardQML.clear();
            m_nrOfMoves = 0;
        }

        //initialize random seed
        srand(time(NULL));

        //for each position on the board generate a randon color from the possible colors vector
        for(size_t row = 0; row < boardSize; ++row)
        {
            std::vector<int> rowVector;
            for(size_t col = 0; col < boardSize; ++col)
            {
                int colorIndex = rand() % 5;
                rowVector.push_back(colors[colorIndex]);
                m_boardQML.push_back(colorManagement(colorIndex));
            }
            m_board.push_back(rowVector);
        }
    emit displayBoard(m_boardQML);
}

void board::colorBoard(const QString color)
{
    //using BFS get all the neighbours of the color from board[0][0] and color using the following rule:
    /*
        - change color of all the nodes that are in the bounderies of the comoponent composed of the selected color
        0 0 1 0          1 1 1 0
        0 1 0 0   -- \   1 1 0 0
        1 0 0 0   -- /   1 0 0 0
        1 1 1 0          1 1 1 0

     Flood-fill (node, target-color, replacement-color):
     1. If target-color is equal to replacement-color, return.
     2. If the color of node is not equal to target-color, return.
     3. Set the color of node to replacement-color.
     4. Perform Flood-fill (one step to the south of node, target-color, replacement-color).
     Perform Flood-fill (one step to the north of node, target-color, replacement-color).
     Perform Flood-fill (one step to the west of node, target-color, replacement-color).
     Perform Flood-fill (one step to the east of node, target-color, replacement-color).
     5. Return.
    */


    int newColor = colors[convertColor(color)];
    m_nrOfMoves++;
    floodIt(0,0,m_board[0][0],newColor);
    emit displayBoard(m_boardQML);
    didFinish();
}
//getters


//private methods
void board::floodIt(int row, int col, int targetColor, int replacementColor)
{
    if(row < 0 || row > m_board.size()-1 || col < 0 || col > m_board.size()-1)
    {
        return;
    }

    if(targetColor == replacementColor || m_board[row][col] != targetColor)
    {
        return;
    }

    m_board[row][col] = replacementColor;
    m_boardQML[m_board.size()*row + col] = colorManagement(replacementColor-1);

    if(row == m_board.size()-1 && col == m_board.size()-1)
    {
        return;
    }

    floodIt(row+1, col, targetColor, replacementColor);
    floodIt(row-1, col, targetColor, replacementColor);
    floodIt(row, col+1, targetColor, replacementColor);
    floodIt(row, col-1, targetColor, replacementColor);
}

void board::didFinish()
{
    int actualColor = m_board[0][0];
    for(size_t row = 0; row < m_board.size(); ++row)
    {
        for(size_t col = 0; col < m_board.size(); ++col)
        {
            if(m_board[row][col] != actualColor)
            {
                return;
            }
        }
    }
    emit gameFinished();
}


QStringList board::getBoard() const
{
    return QStringList(m_boardQML);
}

int board::getNrOfMoves()
{
    return m_nrOfMoves;
}
