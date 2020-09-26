#include <iostream>
#include <cstdint>

#define NUCL_PER_SIZE_T sizeof(size_t) * 8 / 2 // количество нуклеотидов, вмещающихся в один size_t

using namespace std;

enum Nucl
{
    A = 0,
    G = 1,
    C = 2,
    T = 3
};

class RNA {
private:
    size_t * arrRNA = nullptr;
    long int nuclAmount = 0;
    long int arrLength = 0;
public:
    void add(Nucl n)
    {
        if (arrRNA == nullptr) // если пустая рнк
        {
            arrRNA = new size_t[1];
            arrRNA[0] = (size_t)n << ((NUCL_PER_SIZE_T * (arrLength + 1) - nuclAmount) * 2 - 2);

            nuclAmount++;
            arrLength++;
        } else if (nuclAmount / arrLength >= NUCL_PER_SIZE_T) // если массив size_t полностью заполнен нуклеотидами
        {
            size_t * tmp = new size_t[arrLength + 1]; //создание нового массива
            for (size_t i = 0; i < arrLength; i++) // копирование всех нуклеотидов в новый массив
            {
                tmp[i] = arrRNA[i];
            }
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

    void print()
    {
        size_t mask;
        if (sizeof(size_t) == 4) // вычисление маски в зависимости от размера size_t // почему-то CLion пишет "condition is always true"...
        {
            mask = 0b11000000'00000000'00000000'00000000;
        } else
        {
            mask = 0b11000000'00000000'00000000'00000000'00000000'00000000'00000000'00000000;
        }

        for (size_t i = 0; i < arrLength; i++)
        {
            size_t border = (nuclAmount - i * NUCL_PER_SIZE_T < NUCL_PER_SIZE_T) ? nuclAmount - i * NUCL_PER_SIZE_T : NUCL_PER_SIZE_T;
            for (size_t j = 0; j < border; j++)
            {
                size_t shift = 2 * j;
                int  nucl = (int)((arrRNA[i] & (mask >> shift)) >> (sizeof(size_t) * 8 - shift - 2));
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
        }
    }

    RNA()
    {

    }
};

int main() {
    RNA rna;
    string chain;
    cout << "Enter nucleotides you want to add (wrong nucleotides won't be added):" << endl;
    cin >> chain;
    for (size_t i = 0; i < chain.length() ; i++)
    {
        switch (chain[i])
        {
            case 'A':
                rna.add(A);
                break;
            case 'G':
                rna.add(G);
                break;
            case 'C':
                rna.add(C);
                break;
            case 'T':
                rna.add(T);
                break;
            default:
                break;
        }
    }

    rna.print();
    return 0;
}
