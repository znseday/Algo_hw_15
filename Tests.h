#ifndef TESTS_H
#define TESTS_H

//#include <cstddef>
#include <string>

void GenStringDataSet(const std::string &testName, size_t N);

void SimpleStringTest(double p = 0.01);
void SimpleIntBigTest(size_t N, bool isSilence, double p = 0.01, double g = 1.0);

void TestStrings(const std::string &testName, bool isSilence, size_t N, double p = 0.01, double g = 1.0);

#endif // TESTS_H
