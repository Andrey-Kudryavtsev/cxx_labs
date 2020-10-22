//
// Created by Admin on 18.10.2020.
//

#ifndef GOOGLETESTEXAMPLE_RNA_H
#define GOOGLETESTEXAMPLE_RNA_H

#include <iostream>
#include <cstdint>
#include <cmath>

const size_t NUCL_PER_SIZE_T = sizeof(size_t) * 8 / 2; // количество нуклеотидов, вмещающихся в один size_t
const size_t MASK = 3;

enum Nucl
{
    A = 0,
    G = 1,
    C = 2,
    T = 3
};

class RNA
{
private:
    size_t * arrRNA = nullptr;
    size_t nuclAmount = 0;
    size_t arrLength = 0;

    void printNucl(int) const;
    Nucl getNucl(size_t) const;
public:
    RNA();
    RNA(Nucl, size_t);
    RNA(const RNA &);
    ~RNA();

    class Reference
    {
    private:
        RNA & rna;
        size_t nuclNum;
    public:
        Reference(size_t, RNA &);

        Reference & operator=(Nucl);
        Reference & operator=(Reference);
        operator Nucl();
    };

    Reference operator[](size_t);
    Nucl operator[](size_t) const;
    bool operator==(const RNA &) const;
    bool operator!=(const RNA &) const;
    RNA & operator=(RNA const &);
    friend RNA operator+(RNA &, RNA &);
    RNA operator!() const;
    bool isComplimentary(RNA &) const;
    RNA & trim(size_t);
    RNA split(size_t);
    void add(Nucl);
    void print() const;
    size_t getNuclAmount() const;
    size_t capacity() const;
};

#endif //GOOGLETESTEXAMPLE_RNA_H
