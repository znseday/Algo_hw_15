#include <iostream>
#include <vector>
#include <string>
#include <array>

#include "Bloom.h"
#include "Tests.h"

using namespace std;

void CreateTableForSimpleIntBigTests(double p, double fillRate)
{
    cout << "SimpleIntBigTests:" << endl;
    cout << "p(%)\t" << p*100 << endl;
    cout << "fillRate\t" << fillRate << endl;
    cout << "N(in_fact)\tN(max_for_bloom)\tm\tk\tFP_rate(%)" << endl;
    for (size_t i = 2; i <= 7; ++i)
    {
        size_t N = pow(10, i);
        cout << N << "\t";
        SimpleIntBigTest(N, true, p, 1/fillRate);
    }
    cout << "---------------------" << endl;
}


void CreateTableForStringTests(const string &testName, double p, double fillRate)
{
    cout << "StringTests:" << endl;
    cout << "p(%)\t" << p*100 << endl;
    cout << "fillRate\t" << fillRate << endl;
    cout << "N(in_fact)\tN(max_for_bloom)\tm\tk\tFP_rate(%)" << endl;
    for (size_t i = 2; i <= 7; ++i)
    {
        size_t N = pow(10, i);
        cout << N << "\t";
        TestStrings(testName, true, N, p, 1/fillRate);
    }
    cout << "---------------------" << endl;
}

int main()
{
//    GenStringDataSet("StringTest", 100);
//    GenStringDataSet("StringTest", 1'000);
//    GenStringDataSet("StringTest", 10'000);
//    GenStringDataSet("StringTest", 100'000);
//    GenStringDataSet("StringTest", 1'000'000);
//    GenStringDataSet("StringTest", 10'000'000);
//    return 0;

    IsDebugOutput = true;

    SimpleStringTest();
    cout << "---------------------" << endl;

    CreateTableForSimpleIntBigTests(0.01, 1.0);
    CreateTableForSimpleIntBigTests(0.02, 1.0);
    CreateTableForSimpleIntBigTests(0.001, 1.0);
    CreateTableForSimpleIntBigTests(0.01, 0.75);
    CreateTableForSimpleIntBigTests(0.02, 0.75);
    CreateTableForSimpleIntBigTests(0.001, 0.75);
    cout << "---------------------" << endl << endl;

    CreateTableForStringTests("StringTest", 0.01, 1.0);
    CreateTableForStringTests("StringTest", 0.02, 1.0);
    CreateTableForStringTests("StringTest", 0.001, 1.0);
    CreateTableForStringTests("StringTest", 0.01, 0.75);
    CreateTableForStringTests("StringTest", 0.02, 0.75);
    CreateTableForStringTests("StringTest", 0.001, 0.75);

    return 0;
}
