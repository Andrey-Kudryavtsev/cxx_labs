#include "RNA.h"

using namespace std;

RNA::RNA() {}

RNA::RNA(Nucl nucl, size_t nuclAmount)
{
    for (size_t i = 0; i < nuclAmount; i++)
    {
        add(nucl);
    }
}

RNA::RNA(const RNA & other)
{
    nuclAmount = other.nuclAmount;
    arrLength = other.arrLength;
    arrRNA = new size_t[arrLength];
    memcpy(arrRNA, other.arrRNA, arrLength * sizeof(size_t));
}

RNA::~RNA() { delete arrRNA; }

void RNA::printNucl(int nucl) const
{
    switch (nucl)
    {
        case 0:
            cout << "A";
            break;
        case 1:
            cout << "G";
            break;
        case 2:
            cout << "C";
            break;
        case 3:
            cout << "T";
            break;
        default:
            break;
    }
}

Nucl RNA::getNucl(size_t nuclNum) const
{
    size_t index = (size_t)ceil((float)nuclNum / (float)NUCL_PER_SIZE_T) - 1; // вычислениие индекса элемента массива, в котором лежит нужный нуклеотид
    size_t shift = (NUCL_PER_SIZE_T - (nuclNum - NUCL_PER_SIZE_T * index)) * 2; // значение, на которое нужно сдвинуть битовое представление числа, чтобы нужный нуклеотид оказаля в его конце. Пример: 00110000 -> 00000011, shift == 4
    size_t mask = (MASK << shift); // маска для "выбивания" нужного места в рнк
    Nucl nucl = static_cast<Nucl>(((*this).arrRNA[index] & mask) >> shift);

    return nucl;
}

RNA::Reference RNA::operator[](size_t nuclNum) { return Reference(nuclNum, * this); }

Nucl RNA::operator[](size_t nuclNum) const { return getNucl(nuclNum); }

bool RNA::operator==(const RNA & other) const
{
    if (nuclAmount == 0 && other.nuclAmount == 0) { return true; }

    if (nuclAmount != other.nuclAmount) { return false; }

    for (size_t i = 0; i < arrLength - 1; i++)
    {
        if (arrRNA[i] != other.arrRNA[i]) { return false; }
    }
    for (size_t i = NUCL_PER_SIZE_T * (arrLength - 1) + 1; i <= nuclAmount; i++)
    {
        if (getNucl(i) != other.getNucl(i)) { return false; }
    }

    return true;
}

bool RNA::operator!=(const RNA & other) const
{
    return !(*this == other);
}

RNA & RNA::operator=(RNA const & other)
{
    if (this == &other) { return * this; }

    arrLength = other.arrLength;
    nuclAmount = other.nuclAmount;
    if (arrLength != 0) {
        delete[] arrRNA;
        arrRNA = new size_t[arrLength];
        memcpy(arrRNA, other.arrRNA, arrLength * sizeof(size_t));
    }

    return * this;
}
RNA operator+(RNA & first, RNA & second)
{
    RNA tmp;
    tmp = first;

    for (size_t i = 1; i <= second.nuclAmount; i++)
    {
        tmp.add(second[i]);
    }

    return tmp;
}

RNA RNA::operator!() const
{
    RNA tmp;
    tmp.arrLength = arrLength;
    tmp.arrRNA = new size_t[arrLength];
    tmp.nuclAmount = nuclAmount;

    for (size_t i = 0; i < tmp.arrLength; i++)
    {
        tmp.arrRNA[i] = ~(arrRNA[i]);
    }

    return tmp;
}

bool RNA::isComplimentary(RNA & other) const
{
    return (*this == !other);
}

RNA & RNA::trim(size_t ind)
{
    nuclAmount = ind - 1;
    arrLength = (size_t)ceil((float)nuclAmount / (float)NUCL_PER_SIZE_T);
    size_t * tmp = new size_t[arrLength];
    memcpy(tmp, arrRNA, arrLength * sizeof(size_t));
    delete[] arrRNA;
    arrRNA = tmp;

    return *this;
}

RNA RNA::split(size_t ind)
{
    RNA tmp;
    for (size_t i = ind; i <= nuclAmount; i++)
    {
        Nucl nucl = (*this)[i];
        tmp.add(nucl);
    }
    trim(ind);

    return tmp;
}

void RNA::add(Nucl n)
{
    if (arrRNA == nullptr) // если пустая рнк
    {
        arrRNA = new size_t[1];
        arrRNA[0] = (size_t)n << ((NUCL_PER_SIZE_T * (arrLength + 1) - nuclAmount) * 2 - 2);

        nuclAmount++;
        arrLength++;
    } else if (nuclAmount / arrLength >= NUCL_PER_SIZE_T) // если массив size_t полностью заполнен нуклеотидами
    {
        size_t * tmp = new size_t[arrLength + 1]; // создание нового массива
        memcpy(tmp, arrRNA, arrLength * sizeof(size_t)); // копирование всех нуклеотидов в новый массив
        tmp[arrLength] = (size_t)n << ((NUCL_PER_SIZE_T * (arrLength + 1) - nuclAmount) * 2 - 2);
        delete[] arrRNA;
        arrRNA = tmp;

        nuclAmount++;
        arrLength++;
    } else
    {
        size_t shift = (NUCL_PER_SIZE_T * arrLength - nuclAmount) * 2 - 2;
        arrRNA[arrLength-1] = arrRNA[arrLength-1] | ((size_t)n << shift);

        nuclAmount++;
    }
}

void RNA::print() const
{
    size_t mask = MASK << (sizeof(size_t) * 8 - 2);

    for (size_t i = 0; i < arrLength; i++)
    {
        size_t border = (nuclAmount - i * NUCL_PER_SIZE_T < NUCL_PER_SIZE_T) ? nuclAmount - i * NUCL_PER_SIZE_T : NUCL_PER_SIZE_T;
        for (size_t j = 0; j < border; j++)
        {
            size_t shift = 2 * j;
            int nucl = (int)((arrRNA[i] & (mask >> shift)) >> (sizeof(size_t) * 8 - shift - 2));
            printNucl(nucl);
        }
        cout << " ";
    }
    cout << endl;
}

size_t RNA::getNuclAmount() const { return nuclAmount; }

size_t RNA::capacity() const { return arrLength; }

RNA::Reference::Reference(size_t nuclNum, RNA &rna) : nuclNum(nuclNum), rna(rna) {}

RNA::Reference & RNA::Reference::operator=(Nucl nucl)
{
    if (nuclNum > rna.nuclAmount)
    {
        for (size_t i = 0; i < rna.nuclAmount - nuclNum; i++)
        {
            rna.add(nucl);
        }
    } else {
        size_t index = (size_t) ceil((float)nuclNum / (float)NUCL_PER_SIZE_T) - 1; // вычислениие индекса элемента массива, в котором лежит нужный нуклеотид
        size_t shift = (NUCL_PER_SIZE_T - (nuclNum - NUCL_PER_SIZE_T * index)) * 2; // значение, на которое нужно сдвинуть битовое представление числа, чтобы нужный нуклеотид оказаля в его конце. Пример: 00110000 -> 00000011, shift == 4
        size_t addingMask = (size_t) nucl << shift; // маска для добавления нуклеотида
        size_t mask = MASK << shift; // маска для "выбивания" нужного места в рнк
        rna.arrRNA[index] = (rna.arrRNA[index] & ~mask) | addingMask;
    }

    return * this;
}

RNA::Reference & RNA::Reference::operator=(Reference ref)
{
    Nucl nucl = ref.rna.getNucl(ref.nuclNum);
    rna[nuclNum] = nucl;

    return * this;
}

RNA::Reference::operator Nucl() { return rna.getNucl(nuclNum); }
