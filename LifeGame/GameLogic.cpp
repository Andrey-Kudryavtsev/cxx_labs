#include "GameLogic.h"

void GameLogic::reset()
{
    backFlag = false; // после сброса поля нельзя выполнить back
    turnCounter = 0;
    m_field.reset();

    cout << "   Turn " << turnCounter << ":" << endl;
    m_field.draw();
}

void GameLogic::set(string & command)
{
    size_t x = command[4] - 'A';
    size_t y = command[5] - '0';
    backFlag = false; // после установки клетки нельзя выполнить back
    m_field.set(x, y);

    cout << "   Turn " << turnCounter << ":" << endl;
    m_field.draw();
}

void GameLogic::clear(string & command)
{
    size_t x = command[6] - 'A';
    size_t y = command[7] - '0';
    backFlag = false; // после очистки поля нельзя выполнить back
    m_field.clear(x, y);

    cout << "   Turn " << turnCounter << ":" << endl;
    m_field.draw();
}

void GameLogic::step(string & command)
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
    backFlag = true; // после любого количества ходов можно выполнить back
    for (; turnAmount != 0; turnAmount--)
    {
        m_field.copyField(CopyDest::IN_PREV);
        turnCounter++;
        for (size_t y = 0; y < m_field.getHeight(); y ++)
        {
            for (size_t x = 0; x < m_field.getWidth(); x++)
            {
                cell = m_field.getCell(x, y);
                neighbours = m_field.checkNeighbours(x, y);
                if ((cell == '.') && (neighbours == 3))
                {
                    m_field.set(x, y);
                } else if ((cell == 'X') && (neighbours < 2 || neighbours > 3))
                {
                    m_field.clear(x, y);
                }
            }
        }
        cout << "   Turn " << turnCounter << ":" << endl;
        m_field.draw();
        this_thread::sleep_for(chrono::milliseconds(300)); // уснуть на 300 миллисекунд (для красивого вывода ^.^)
        if (m_field.isEqual()) // если прошлое поле и текущее одинаковы, значит состояние не менялось, и игра заканчивается
        {
            isOver = true;
            break;
        }
    }
}

void GameLogic::back()
{
    if (backFlag)
    {
        turnCounter--;
        m_field.copyField(CopyDest::IN_CUR);
        backFlag = false; // после выполнения back выполнить его еще раз нельзя без совершения хода

        cout << "   Turn " << turnCounter << ":" << endl;
        m_field.draw();
    } else
    {
        cout << "Your can't travel back in time right now!" << endl;
    }
}

void GameLogic::save(string & command)
{
    string filenameOut = command.substr(5) + ".txt";
    ofstream fout;
    fout.open(filenameOut);
    m_field.save(fout);
    cout << "Field was successfully saved" << endl;
    fout.close();
}

void GameLogic::load(string & command)
{
    string filenameIn = command.substr(5) + ".txt";
    ifstream fin;
    fin.open(filenameIn);
    if (!fin.is_open())
    {
        cout << "File doesn't exist" << endl;
    } else
    {
        backFlag = false; // нельзя выполнить back, если было загружено какое-либо поле
        turnCounter = 0;
        cout << "   Turn " << turnCounter << ":" << endl;
        m_field.load(fin);
        m_field.draw();
        cout << "Field was successfully loaded" << endl;
    }
    fin.close();
}
