#ifndef LIFEGAME_FIELD_H
#define LIFEGAME_FIELD_H

#include <iostream>
#include <fstream>
using namespace std;

enum class CopyDest
{
    IN_PREV,
    IN_CUR,
};

class Field
{
private:
    static const size_t width = 10;
    static const size_t height = 10;
    char curField[height][width] = {{'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                                    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                                    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                                    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                                    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                                    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                                    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                                    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                                    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                                    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'}};
    char prevField[height][width] = {{'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                                     {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                                     {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                                     {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                                     {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                                     {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                                     {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                                     {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                                     {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                                     {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'}};
public:
    size_t getWidth() { return width; }
    size_t getHeight() { return height; }
    void draw() const;
    bool isEqual();
    void reset();
    void set(size_t &, size_t &);
    void clear(size_t &, size_t &);
    void copyField(CopyDest);
    char getCell(size_t &, size_t &);
    size_t checkNeighbours(size_t &, size_t &);
    void save(ofstream &);
    void load(ifstream &);
};

#endif //LIFEGAME_FIELD_H
