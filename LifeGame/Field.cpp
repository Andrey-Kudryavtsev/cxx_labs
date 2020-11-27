#include "Field.h"

Field::Field()
{
    m_curField = new char*[m_height];
    m_prevField = new char*[m_height];
    for (size_t i = 0; i < m_height; i++)
    {
        m_curField[i] = new char[m_width];
        m_prevField[i] = new char[m_width];
        for (size_t j = 0; j < m_width; j++)
        {
            m_curField[i][j] = '.';
            m_prevField[i][j] = '.';
        }
    }
}

Field::~Field()
{
    for (size_t i = 0; i < m_height; i++)
    {
        delete [] m_curField[i];
        delete [] m_prevField[i];
    }
    delete [] m_curField;
    delete [] m_prevField;
}

size_t Field::getWidth() const
{
    return m_width;
}

size_t Field::getHeight() const
{
    return m_height;
}

std::ostream & operator<<(std::ostream & out, const Field & field)
{
    out << "     A  B  C  D  E  F  G  H  I  J" << endl << "    _____________________________" << endl;
    for (size_t y = 0; y < field.m_height; y++)
    {
        out << y << "  | ";
        for (size_t x = 0; x < field.m_width; x++)
        {
            cout << field.m_curField[y][x] << "  ";
        }
        out << endl;
    }

    return out;
}

bool Field::isEqual() const
{
    for (size_t y = 0; y < m_height; y++)
    {
        for (size_t x = 0; x < m_width; x++)
        {
            if (m_curField[y][x] != m_prevField[y][x])
            {
                return false;
            }
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
            m_prevField[y][x] = '.';
        }
    }
}

void Field::set(const size_t & x, const size_t & y)
{
    m_curField[y][x] = 'X';
}

void Field::clear(const size_t & x, const size_t & y)
{
    m_curField[y][x] = '.';
}

void Field::step()
{
    swap(m_curField, m_prevField);
}

void Field::back()
{
    swap(m_curField, m_prevField);
}

char Field::getCell(const size_t & x, const size_t & y) const
{
    return m_prevField[y][x];
}

size_t Field::checkNeighbours(const size_t & x, const size_t & y) const
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

void Field::save(ofstream & fout) const
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
