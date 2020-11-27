#include "GameLogic.h"

bool GameLogic::isOver() const
{
    return m_isOver;
}

void GameLogic::printStatus() const
{
    cout << "   Turn " << m_turnCounter << ":" << endl;
    cout << m_field;
}

void GameLogic::reset()
{
    m_backFlag = false; // после сброса поля нельзя выполнить back
    m_turnCounter = 0;
    m_field.reset();

    printStatus();
}

void GameLogic::set(const string & command)
{
    size_t x = command[4] - 'A';
    size_t y = command[5] - '0';
    m_backFlag = false; // после установки клетки нельзя выполнить back
    m_field.set(x, y);

    printStatus();
}

void GameLogic::clear(const string & command)
{
    size_t x = command[6] - 'A';
    size_t y = command[7] - '0';
    m_backFlag = false; // после очистки поля нельзя выполнить back
    m_field.clear(x, y);

    printStatus();
}

void GameLogic::step(const string & command)
{
    char cell;
    size_t neighbours;
    size_t turnAmount;
    try
    {
        turnAmount = stoi(command.substr(5));
    } catch (out_of_range& e)
    {
        turnAmount = 1;
    }
    m_backFlag = true; // после любого количества ходов можно выполнить back
    for (; turnAmount != 0; turnAmount--)
    {
        m_field.step();
        m_turnCounter++;
        for (size_t y = 0; y < m_field.getHeight(); y ++)
        {
            for (size_t x = 0; x < m_field.getWidth(); x++)
            {
                cell = m_field.getCell(x, y);
                neighbours = m_field.checkNeighbours(x, y);
                if (cell == '.')
                {
                    if (neighbours == 3) { m_field.set(x, y); }
                    else { m_field.clear(x, y); }
                } else if (cell == 'X')
                {
                    if (neighbours < 2 || neighbours > 3) { m_field.clear(x,y); }
                    else { m_field.set(x,y); }
                }
            }
        }
        printStatus();
        this_thread::sleep_for(chrono::milliseconds(300)); // уснуть на 300 миллисекунд (для красивого вывода ^.^)
        if (m_field.isEqual()) // если прошлое поле и текущее одинаковы, значит состояние не менялось, и игра заканчивается
        {
            m_isOver = true;
            break;
        }
    }
}

void GameLogic::back()
{
    if (m_backFlag)
    {
        m_turnCounter--;
        m_field.back();
        m_backFlag = false; // после выполнения back выполнить его еще раз нельзя без совершения хода

        printStatus();
    } else
    {
        cout << "Your can't travel back in time right now!" << endl;
    }
}

void GameLogic::save(const string & command) const
{
    string filenameOut = command.substr(5) + ".txt";
    ofstream fout;
    fout.open(filenameOut);
    m_field.save(fout);
    cout << "Field was successfully saved" << endl;
    fout.close();
}

void GameLogic::load(const string & command)
{
    string filenameIn = command.substr(5) + ".txt";
    ifstream fin;
    fin.open(filenameIn);
    if (!fin.is_open())
    {
        cout << "File doesn't exist" << endl;
    } else
    {
        m_backFlag = false; // нельзя выполнить back, если было загружено какое-либо поле
        m_turnCounter = 0;
        m_field.load(fin);
        printStatus();
        cout << "Field was successfully loaded" << endl;
    }
    fin.close();
}
