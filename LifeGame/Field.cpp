#include "Field.h"

Field::Field()
{
    m_curField = new char*[m_height];
    for (size_t i = 0; i < m_height; i++)
    {
        m_curField[i] = new char[m_width];
        for (size_t j = 0; j < m_width; j++)
        {
            m_curField[i][j] = '.';
        }
    }
    m_prevField = m_curField;
}

Field::~Field()
{
    if (m_prevField != m_curField)
    {
        for (size_t i = 0; i < m_height; i++)
        {
            delete[] m_prevField[i];
        }
        delete [] m_prevField;
    }
    for (size_t i = 0; i < m_height; i++)
    {
        delete[] m_curField[i];
    }
    delete [] m_curField;
}

void Field::draw() const
{
    cout << "     A  B  C  D  E  F  G  H  I  J" << endl << "    _____________________________" << endl;
    for (size_t y = 0; y < m_height; y++)
    {
        cout << y << "  | ";
        for (size_t x = 0; x < m_width; x++)
        {
            cout << m_curField[y][x] << "  ";
        }
        cout << endl;
    }
}

bool Field::isEqual()
{
    for (size_t y = 0; y < m_height; y++)
    {
        for (size_t x = 0; x < m_width; x++)
        {
            if (m_curField[y][x] != m_prevField[y][x])
            {
                return false;
            };
        }
    }

    return true;
}

void Field::reset() {
    for (size_t y = 0; y < m_height; y++)
    {
        for (size_t x = 0; x < m_width; x++)
        {
            m_curField[y][x] = '.';
        }
    }
    m_prevField = m_curField;
}

void Field::set(size_t & x, size_t & y)
{
    m_curField[y][x] = 'X';
}

void Field::clear(size_t & x, size_t & y)
{
    m_curField[y][x] = '.';
}

void Field::step()
{
    if (m_prevField != m_curField) // если это указатели на разные области памяти, то нужно очистить m_prevField
    {
        for (size_t i = 0; i < m_height; i++)
        {
            delete[] m_prevField[i];
        }
        delete [] m_prevField;
        m_prevField = m_curField; // ...и адресовать его на m_curField
    }
    m_curField = new char *[m_height];
    for (size_t i = 0; i < m_height; i++)
    {
        m_curField[i] = new char[m_width];
    }
}

void Field::back()
{
    for (size_t i = 0; i < m_height; i++) {
        delete[] m_curField[i];
    }
    delete[] m_curField;
    m_curField = m_prevField;
}

char Field::getCell(size_t & x, size_t & y)
{
    return m_prevField[y][x];
}

size_t Field::checkNeighbours(size_t & x, size_t & y)
{
    size_t neighbours = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            size_t neighbourX = (x + m_width + j) % m_width;
            size_t neighbourY = (y + m_height + i) % m_height;
            if (((neighbourY != y) || (neighbourX != x)) && (m_prevField[neighbourY][neighbourX] == 'X'))
            {
                neighbours++;
            }
        }
    }

    return neighbours;
}

void Field::save(ofstream & fout)
{
    for (size_t y = 0; y < m_height; y++)
    {
        for (size_t x = 0; x < m_width; x++)
        {
            fout << m_curField[y][x] << "  ";
        }
        fout << endl;
    }
}

void Field::load(ifstream & fin)
{
    size_t x = 0;
    size_t y = 0;
    char c;

    fin >> c;
    while (fin)
    {
        m_curField[y][x] = c;
        m_prevField[y][x] = c;
        if (++x == m_width)
        {
            x = 0;
            y++;
        }
        fin >> c;
    }
}
