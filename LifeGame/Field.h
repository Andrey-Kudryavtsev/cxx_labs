#ifndef LIFEGAME_FIELD_H
#define LIFEGAME_FIELD_H

#include <iostream>
#include <fstream>
using namespace std;

class Field
{
private:
    const size_t m_width = 10;
    const size_t m_height = 10;
    char ** m_curField;
    char ** m_prevField;
public:
    Field();
    size_t getWidth() { return m_width; }
    size_t getHeight() { return m_height; }
    void draw() const;
    bool isEqual();
    void reset();
    void set(size_t &, size_t &);
    void clear(size_t &, size_t &);
    void step();
    void back();
    char getCell(size_t &, size_t &);
    size_t checkNeighbours(size_t &, size_t &);
    void save(ofstream &);
    void load(ifstream &);
};

#endif //LIFEGAME_FIELD_H
