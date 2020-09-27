#include "Tests.h"
#include <vector>
#include <string>
#include <array>
#include <set>
#include <fstream>
//#include <cstdio>

#include "Bloom.h"
#include "UnitUniqueRandom.h"

using namespace std;

void GenStringDataSet(const std::string &testName, size_t N)
{
    cout << "Generating for N = " << N << "..." << endl;

    constexpr size_t M = 20;

    string line(M, '\0');
   // line.resize(M, '\0');
    set<string> present;
    size_t tN = N;
    for (size_t i = 0; i < tN; ++i)
    {
        for (size_t j = 0; j < M; ++j)
        {
            line[j] = 'a' + rand()%26;
        }
        auto [it, b] = present.insert(line);
        (void)it;
        if (!b)
            tN++;
    }

    string fn = testName + "_" + to_string(N) + "_present.txt";
    ofstream fPresent(fn);
    if (!fPresent)
    {
        perror(fn.c_str());
        return;
    }
    for (const auto & line : present)
        fPresent << line << endl;
    fPresent.close();

    fn = testName + "_" + to_string(N) + "_absent.txt";
    ofstream fAbsent(fn);
    if (!fAbsent)
    {
        perror(fn.c_str());
        return;
    }
    tN = N;
    for (size_t i = 0; i < tN; ++i)
    {
        for (size_t j = 0; j < M; ++j)
        {
            line[j] = 'a' + rand()%26;
        }
        auto it = present.find(line);
        if (it == present.end())
            fAbsent << line << endl;
        else
            tN++;
    }
    fAbsent.close();

    cout << "Finished" << endl;
}
//-----------------------------------------------------


void SimpleStringTest(double p /*= 0.01*/)
{
    cout << "SimpleStringTest:" << endl;
    constexpr size_t N = 10;
    Bloom<string> bloom(N, p);
    size_t countAllPositive = 0, countFalsePositive = 0;

    array<string, N> present = {"Apple", "Banana", "Grape", "Peach", "Pear", "Coffee", "Milk", "Pizza", "Chips", "Tea"};
    for (const auto & x : present)
        bloom.Add(x);

    array<string, N> absent = {"Cat", "Dog", "Snake", "Spider", "Hen", "Horse", "Fox", "Fish", "Crab", "Bird"};

    cout << endl;
    for (const auto & x : present)
    {
        if (bloom.Contains(x))
        {
            cout << "bloom contains " << x << " and it is correct" << endl;
            countAllPositive++;
        }
        else
            throw runtime_error("Something is wrong!");
    }

    for (const auto & x : absent)
    {
        if (bloom.Contains(x))
        {
            cout << "bloom contains " << x << " and it is a FALSE POSITIVE!" << endl;
            countFalsePositive++;

        }
        else
            cout << "bloom doesn't contain " << x << " and it is correct" << endl;
    }
    countAllPositive += countFalsePositive;

    cout << "Rate of False Positives = " << countFalsePositive/double(countAllPositive)*100.0 << " %" << endl;
}
//-----------------------------------------------------

void SimpleIntBigTest(size_t N, bool isSilence, double p /*= 0.01*/, double g /*= 1.0*/)
{
    //cout << "SimpleIntBigTest (with N = " << N << "):" << endl;
    Bloom<int> bloom(g*N, p);
    size_t countAllPositive = 0, countFalsePositive = 0;

    MyUniqueRandom uniqueRandom(2*N);

    vector<int> present(N);
    for (size_t i = 0; i < N; ++i)
        present[i] = uniqueRandom.GetNext();

    for (const auto & x : present)
        bloom.Add(x);

    vector<int> absent(N);
    for (size_t i = 0; i < N; ++i)
        absent[i] = uniqueRandom.GetNext();

    for (const auto & x : present)
    {
        if (bloom.Contains(x))
        {
            if (!isSilence) cout << "bloom contains " << x << " and it is correct" << endl;
            countAllPositive++;
        }
        else
            throw runtime_error("Something is wrong!");
    }

    for (const auto & x : absent)
    {
        if (bloom.Contains(x))
        {
            if (!isSilence) cout << "bloom contains " << x << " and it is a FALSE POSITIVE!" << endl;
            countFalsePositive++;

        }
        else
            if (!isSilence) cout << "bloom doesn't contain " << x << " and it is correct" << endl;
    }
    countAllPositive += countFalsePositive;

//    cout << "Rate of False Positives = " << countFalsePositive/double(countAllPositive)*100.0 << " %" << endl << endl;
    cout << countFalsePositive/double(countAllPositive)*100.0 << endl;
}
//-----------------------------------------------------

void TestStrings(const std::string &testName, bool isSilence, size_t N, double p /*= 0.01*/, double g /*= 1.0*/)
{
    //cout << "TestStrings (with N = " << N << "):" << endl;

    Bloom<string> bloom(g*N, p);
    size_t countAllPositive = 0, countFalsePositive = 0;

    string line;
    vector<string> present(N);
    string fn = testName + "_" + to_string(N) + "_present.txt";
    ifstream fPresent(fn);
    if (!fPresent)
    {
        perror(fn.c_str());
        return;
    }
    for (size_t i = 0; i < N; ++i)
    {
        fPresent >> line;
        present[i] = line;
        bloom.Add(line);
    }
    fPresent.close();

    vector<string> absent(N);
    fn = testName + "_" + to_string(N) + "_absent.txt";
    ifstream fAbsent(fn);
    if (!fAbsent)
    {
        perror(fn.c_str());
        return;
    }
    for (size_t i = 0; i < N; ++i)
    {
        fAbsent >> line;
        absent[i] = line;
    }
    fAbsent.close();

    for (const auto & x : present)
    {
        if (bloom.Contains(x))
        {
            if (!isSilence) cout << "bloom contains " << x << " and it is correct" << endl;
            countAllPositive++;
        }
        else
            throw runtime_error("Something is wrong!");
    }

    for (const auto & x : absent)
    {
        if (bloom.Contains(x))
        {
            if (!isSilence) cout << "bloom contains " << x << " and it is a FALSE POSITIVE!" << endl;
            countFalsePositive++;

        }
        else
            if (!isSilence) cout << "bloom doesn't contain " << x << " and it is correct" << endl;
    }
    countAllPositive += countFalsePositive;

    //cout << "Rate of False Positives = " << countFalsePositive/double(countAllPositive)*100.0 << " %" << endl << endl;
    cout << countFalsePositive/double(countAllPositive)*100.0 << endl;
}
//-----------------------------------------------------


