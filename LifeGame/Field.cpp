#include "Field.h"

void Field::draw() const
{
    cout << "     A  B  C  D  E  F  G  H  I  J" << endl << "    _____________________________" << endl;
    for (size_t y = 0; y < m_height; y++)
    {
        cout << y << "  | ";
        for (size_t x = 0; x < m_width; x++)
        {
            cout << curField[y][x] << "  ";
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
            if (curField[y][x] != prevField[y][x])
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
            curField[y][x] = '.';
        }
    }
}

void Field::set(size_t & x, size_t & y)
{
    curField[y][x] = 'X';
}

void Field::clear(size_t & x, size_t & y)
{
    curField[y][x] = '.';
}

void Field::copyField(CopyDest copyDest)
{
    if (copyDest == CopyDest::IN_PREV)
    {
        memcpy(prevField, curField, m_height * m_width);
    } else if (copyDest == CopyDest::IN_CUR)
    {
        memcpy(curField, prevField, m_height * m_width);
    }
}

char Field::getCell(size_t & x, size_t & y)
{
    return prevField[y][x];
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
            if (((neighbourY != y) || (neighbourX != x)) && (prevField[neighbourY][neighbourX] == 'X'))
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
            fout << curField[y][x] << "  ";
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
        curField[y][x] = c;
        prevField[y][x] = c;
        if (++x == m_width)
        {
            x = 0;
            y++;
        }
        fin >> c;
    }
}
