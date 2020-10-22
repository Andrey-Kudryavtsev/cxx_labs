#include <gtest/gtest.h>
#include "RNA.h"

RNA createRNA(std::string rnaStr)
{
    RNA rna;

    for (size_t i = 0; i < rnaStr.length(); i++)
    {
        switch (rnaStr[i])
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

    return rna;
}

Nucl charToNucl(char c)
{
    switch (c)
    {
        case 'A':
            return A;
            break;
        case 'G':
            return G;
            break;
        case 'C':
            return C;
            break;
        case 'T':
            return T;
            break;
        default:
            break;
    }
}

TEST(TestEquality, test1)
{
    RNA rna1;
    RNA rna2;

    EXPECT_EQ(true, rna1 == rna2);
}

TEST(TestEquality, test2)
{
    RNA rna1;
    RNA rna2 = createRNA("GCATGCTACGTACGGCATATACGATCGA");

    EXPECT_EQ(false, rna1 == rna2);
}

TEST(TestEquality, test3)
{
    RNA rna1 = createRNA("CGATCGATCGATCGATCG");
    RNA rna2 = createRNA("CGATCGATCGATCGATCG");

    EXPECT_EQ(true, rna1 == rna2);
}

TEST(TestEquality, test4)
{
    RNA rna1 = createRNA("CGTAGGCTAGC");
    RNA rna2 = createRNA("CTAACGGCTAC");

    EXPECT_EQ(false, rna1 == rna2);
}

TEST(TestEquality, test5)
{
    RNA rna1 = createRNA("CGTAGGCTAGC");
    RNA rna2 = createRNA("CGTAGGCTAGCGCAGTCA");

    EXPECT_EQ(false, rna1 == rna2);
}
///------------------------------------------------------------------------------------------------------------------///

TEST(TestNotEquality, test1)
{
    RNA rna1;
    RNA rna2;

    EXPECT_EQ(false, rna1 != rna2);
}

TEST(TestNotEquality, test2)
{
    RNA rna1;
    RNA rna2 = createRNA("GCATGCTACGTACGGCATATACGATCGA");

    EXPECT_EQ(true, rna1 != rna2);
}

TEST(TestNotEquality, test3)
{
    RNA rna1 = createRNA("CGATCGATCGATCGATCG");
    RNA rna2 = createRNA("CGATCGATCGATCGATCG");

    EXPECT_EQ(false, rna1 != rna2);
}

TEST(TestNotEquality, test4)
{
    RNA rna1 = createRNA("CGTAGGCTAGC");
    RNA rna2 = createRNA("CTAACGGCTAC");

    EXPECT_EQ(true, rna1 != rna2);
}

TEST(TestNotEquality, test5)
{
    RNA rna1 = createRNA("CGTAGGCTAGC");
    RNA rna2 = createRNA("CGTAGGCTAGCGCAGTCA");

    EXPECT_EQ(true, rna1 != rna2);
}
///------------------------------------------------------------------------------------------------------------------///
TEST(TestAssignment, test1)
{
    RNA rna1;
    RNA rna2;
    rna2 = rna1;

    EXPECT_EQ(true, rna1 == rna2);
}

TEST(TestAssignment, test2)
{
    RNA rna1 = createRNA("GCATCGACGATCGA");
    RNA rna2;
    rna2 = rna1;

    EXPECT_EQ(true, rna1 == rna2);
}

TEST(TestAssignment, test3)
{
    RNA rna1 = createRNA("GCATCGACGATCGA");
    RNA rna2;
    rna1 = rna2;

    EXPECT_EQ(true, rna1 == rna2);
}

TEST(TestAssignment, test4)
{
    RNA rna1 = createRNA("GCATCGACGATCGA");
    RNA rna2 = createRNA("AAATCAGCATCAGT");
    rna2 = rna1;

    EXPECT_EQ(true, rna1 == rna2);
}
///------------------------------------------------------------------------------------------------------------------///

TEST(TestCopyConstructor, test1)
{
    RNA rna1;
    RNA rna2(rna1);

    EXPECT_EQ(true, rna1 == rna2);
}

TEST(TestCopyConstructor, test2)
{
    RNA rna1 = createRNA("AAGTACGCTAGCTACG");
    RNA rna2(rna1);

    EXPECT_EQ(true, rna1 == rna2);
}
///------------------------------------------------------------------------------------------------------------------///

TEST(TestAddition, test1)
{
    RNA rna1;
    RNA rna2;
    RNA rna3 = rna1 + rna2;
    RNA rna4 = rna2 + rna1;

    EXPECT_EQ(true, rna1 == rna3);
    EXPECT_EQ(true, rna1 == rna4);
}

TEST(TestAddition, test2)
{
    RNA rna1 = createRNA("ATGCATCGATCGTCATC");
    RNA rna2;
    RNA rna3 = rna1 + rna2;
    RNA rna4 = rna2 + rna1;

    EXPECT_EQ(true, rna1 == rna3);
    EXPECT_EQ(true, rna1 == rna4);
}

TEST(TestAddition, test3)
{
    RNA rna1 = createRNA("GTACTGCTAGCTGAC");
    RNA rna2 = createRNA("ATCATCTGACTACTG");
    RNA rna3 = createRNA("GTACTGCTAGCTGACATCATCTGACTACTG");
    RNA rna4 = createRNA("ATCATCTGACTACTGGTACTGCTAGCTGAC");
    RNA rna5 = rna1 + rna2;
    RNA rna6 = rna2 + rna1;

    EXPECT_EQ(true, rna3 == rna5);
    EXPECT_EQ(true, rna4 == rna6);
}
///------------------------------------------------------------------------------------------------------------------///

TEST(TestSquareBracketsRead, test1)
{
    std::string rnaStr = "GCGATCGCATCTACGA";
    RNA rna = createRNA("GCGATCGCATCTACGA");

    for (size_t i = 0; i < rnaStr.length(); i++)
    {
        EXPECT_EQ(charToNucl(rnaStr[i]), static_cast<Nucl>(rna[i+1]));
    }
}

TEST(TestSquareBracketsRead, test2)
{
    std::string rnaStr = "ATACGAACTGCTATTCCCCTAAGCTGCAGCTATGCGAAGGCTGACCTG";
    RNA rna = createRNA(rnaStr);

    for (size_t i = 0; i < rnaStr.length(); i++)
    {
        EXPECT_EQ(charToNucl(rnaStr[i]), static_cast<Nucl>(rna[i+1]));
    }
}

TEST(TestSquareBracketsRead, test3)
{
    std::string rnaStr = "GCATGCATCGATCGTAATCGCGCGACTCGATCGACTGACTACGACGATTTACGACTACTAGCTAGCTACGATTCGCGACTAGCATCGTACGAGCAGCTCGAATCGTC";
    RNA rna = createRNA(rnaStr);

    for (size_t i = 0; i < rnaStr.length(); i++)
    {
        EXPECT_EQ(charToNucl(rnaStr[i]), static_cast<Nucl>(rna[i+1]));
    }
}
///------------------------------------------------------------------------------------------------------------------///

TEST(TestSquareBracketsWrite, test1)
{
    std::string rnaStr1 = "ACAACACTCGACTGCACTGGATCTGTAGC";
    std::string rnaStr2 = "GGCTACGACGACTCATTCAGCAGATCATG";
    RNA rna1 = createRNA(rnaStr1);
    RNA rna2 = createRNA(rnaStr2);

    for (size_t i = 0; i < rnaStr1.length(); i++)
    {
        rna1[i + 1] = charToNucl(rnaStr2[i]);
    }

    EXPECT_EQ(true, rna1 == rna2);
}

TEST(TestSquareBracketsWrite, test2)
{
    RNA rna = createRNA("ACGGACTACCGGACTCGATCG");

    rna[rna.getNuclAmount() + 2] = T;
    EXPECT_EQ(T, static_cast<Nucl>(rna[rna.getNuclAmount() - 1]));
    EXPECT_EQ(T, static_cast<Nucl>(rna[rna.getNuclAmount()]));

    rna[rna.getNuclAmount() + 27] = C;
    for (size_t i = rna.getNuclAmount() - 26; i <= rna.getNuclAmount(); i++)
    {
        EXPECT_EQ(C, static_cast<Nucl>(rna[i]));
    }
}

TEST(TestSquareBracketsWrite, test3)
{
    RNA rna1 = createRNA("ACGACGGCAGACTCAGACGCTGACTAC");
    RNA rna2 = createRNA("GCGATCGCAGCATCAGGCATACTCAGCGCAGACTGGCAGCTCGAGCT");

    for (size_t i = 1; i <= rna2.getNuclAmount(); i++)
    {
        rna1[i] = rna2[i];
    }

    EXPECT_EQ(true, rna1 == rna2);
}
///------------------------------------------------------------------------------------------------------------------///

TEST(TestNegation, test1)
{
    RNA rna1;
    RNA rna2;
    rna2 = !rna1;

    EXPECT_EQ(true, rna1 == rna2);
}

TEST(TestNegation, test2)
{
    RNA rna1 = createRNA("CGACGATCCAGACGTACACGAATATCAAGCT");
    RNA rna2 = createRNA("GCTGCTAGGTCTGCATGTGCTTATAGTTCGA");
    rna1 = !rna1;

    EXPECT_EQ(true, rna1 == rna2);
}
///------------------------------------------------------------------------------------------------------------------///

TEST(TestIsComplimentary, test1)
{
    RNA rna1 = createRNA("CGACGATCCAGACGTACACGAATATCAAGCT");
    RNA rna2 = createRNA("GCTGCTAGGTCTGCATGTGCTTATAGTTCGA");

    EXPECT_EQ(true, rna1.isComplimentary(rna2));
}

TEST(TestIsComplimentary, test2)
{
    RNA rna1 = createRNA("CGACGATCCAGACGTACACGAATATCAAGCT");
    RNA rna2 = createRNA("GCTGCTAGGTCTGCATGTGCTTATAGTTCGT");

    EXPECT_EQ(false, rna1.isComplimentary(rna2));
}
///------------------------------------------------------------------------------------------------------------------///

TEST(TestTrim, test1)
{
    RNA rna1 = createRNA("GACGATACGAGCCATAG");
    RNA rna2;
    rna1 = rna1.trim(1);

    EXPECT_EQ(true, rna1 == rna2);
}

TEST(TestTrim,test2)
{
    RNA rna1 = createRNA("GCATCGCAGACGTCAAGCGCATACGCGATCATCATC");
    RNA rna2 = createRNA("GCATCGCAGACGTCAAGC");
    rna1 = rna1.trim(19);

    EXPECT_EQ(true, rna1 == rna2);
}
///------------------------------------------------------------------------------------------------------------------///

TEST(TestSplit, test1)
{
    RNA rna1 = createRNA("AGCGATCAGAGCATACTAGTAGCGACATCAGT");
    RNA rna2 = createRNA("AGCGATCAGAGCATACTAG");
    RNA rna3 = createRNA("TAGCGACATCAGT");
    RNA rna4 = rna1.split(20);

    EXPECT_EQ(true, rna1 == rna2);
    EXPECT_EQ(true, rna4 == rna3);
}
///------------------------------------------------------------------------------------------------------------------///


