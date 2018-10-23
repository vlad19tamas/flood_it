#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include <QList>
#include <QString>

#include<vector>

class board : public QObject
{

    Q_OBJECT

    Q_PROPERTY(int boardProperty WRITE generateBoard)
    Q_PROPERTY(QStringList display READ getBoard NOTIFY displayBoard)
    Q_PROPERTY(QString flood WRITE colorBoard)
    Q_PROPERTY(int finished READ getNrOfMoves NOTIFY gameFinished)

public:
    board();

//setters
    void colorBoard(const QString color);
    void generateBoard(const int boardSize);

//getters
    QStringList getBoard() const;
    int getNrOfMoves();

signals:
    void displayBoard(QList<QString> boardGame);
    void gameFinished();

 private:
    void floodIt(int row, int col, int targetColor, int replacementColor);
    void didFinish();

//members
private:
    //board game
    std::vector<std::vector<int>> m_board;
    QList<QString> m_boardQML;

    //colors vector
    std::vector<int> colors = {1,2,3,4,5,6};//{red,green,blue,yellow,magenta,orange}

    int m_nrOfMoves;

};

#endif // BOARD_H
