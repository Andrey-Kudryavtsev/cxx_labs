#include "LifeGame.h"

LifeGame::LifeGame(InputHandler & inputHandler, GameLogic & gameLogic)
    : m_inputHandler(inputHandler),
    m_gameLogic(gameLogic){}

void LifeGame::play()
{
    string command;
    cout << "   Turn " << m_gameLogic.m_turnCounter << ":" << endl;
    m_gameLogic.m_field.draw();
    while (!m_gameLogic.m_isOver)
    {
        getline(cin, command);
        switch (m_inputHandler.getCommand(command))
        {
            case Command::RESET:
                m_gameLogic.reset();
                break;
            case Command::SET:
                m_gameLogic.set(command);
                break;
            case Command::CLEAR:
                m_gameLogic.clear(command);
                break;
            case Command::STEP:
                m_gameLogic.step(command);
                break;
            case Command::BACK:
                m_gameLogic.back();
                break;
            case Command::SAVE:
                m_gameLogic.save(command);
                break;
            case Command::LOAD:
                m_gameLogic.load(command);
                break;
            case Command::WRONG_COMMAND:
                cout << "Please, enter correct command (reset, set XY, clear XY, step (N), back, save \"filename\", load \"filaname\")" << endl;
                break;
            case Command::WRONG_TURN_AMOUNT:
                cout << "Please, enter right parameter (N, where N = [1-" << INT_MAX << "])" << endl;
                break;
            case Command::WRONG_COORDS:
                cout << "Please, enter right coordinates (XY, where X = [A-J], Y = [0-9])" << endl;
                break;
        }
    }
}
