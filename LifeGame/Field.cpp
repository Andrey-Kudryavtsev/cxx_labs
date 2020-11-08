#include "Field.h"

void Field::draw() const
{
    cout << "     A  B  C  D  E  F  G  H  I  J" << endl << "    _____________________________" << endl;
    for (size_t i = 0; i < height; i++)
    {
        cout << i << "  | ";
        for (size_t j = 0; j < width; j++)
        {
            cout << curField[i][j] << "  ";
        }
        cout << endl;
    }
}

bool Field::isEqual()
{
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            if (curField[i][j] != prevField[i][j])
            {
                return false;
            };
        }
    }

    return true;
}

void Field::reset() {
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            curField[i][j] = '.';
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
        memcpy(prevField, curField, height * width);
    } else if (copyDest == CopyDest::IN_CUR)
    {
        memcpy(curField, prevField, height * width);
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
            size_t neighbourX = (x + width + j) % width;
            size_t neighbourY = (y + height + i) % height;
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
    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            fout << curField[i][j] << "  ";
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
        if (++x == width)
        {
            x = 0;
            y++;
        }
        fin >> c;
    }
}
