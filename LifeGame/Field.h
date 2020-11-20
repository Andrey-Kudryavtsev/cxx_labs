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
    ~Field();
    size_t getWidth() const;
    size_t getHeight() const;
    friend std::ostream & operator<<(std::ostream &, const Field &);
    bool isEqual() const;
    void reset();
    void set(const size_t &, const size_t &);
    void clear(const size_t &, const size_t &);
    void step();
    void back();
    char getCell(const size_t &, const size_t &) const;
    size_t checkNeighbours(const size_t &, const size_t &) const;
    void save(ofstream &) const;
    void load(ifstream &);
};

#endif //LIFEGAME_FIELD_H
