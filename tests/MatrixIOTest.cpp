#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <Eigen/Dense>
#include <fstream>
#include <cstdio>
#include "matrixIO.hpp"

using namespace Eigen;

BOOST_AUTO_TEST_SUITE(MatrixIOTests)

BOOST_AUTO_TEST_CASE(OpenDataValid)
{
    const std::string fileName = "test_matrix.csv";
    const int size = 2;
    
    // Create a temporary CSV file
    std::ofstream file(fileName);
    file << "1.0, 2.0\n3.0, 4.0\n";
    file.close();

    MatrixXd expected(size, size);
    expected << 1.0, 2.0, 3.0, 4.0;

    MatrixXd result = matrixIO::openData(fileName, size);

    BOOST_TEST(result(0, 0) == expected(0, 0));
    BOOST_TEST(result(0, 1) == expected(0, 1));
    BOOST_TEST(result(1, 0) == expected(1, 0));
    BOOST_TEST(result(1, 1) == expected(1, 1));

    // Clean up
    std::remove(fileName.c_str());
}

BOOST_AUTO_TEST_CASE(OpenDataInvalidRows)
{
    const std::string fileName = "test_matrix_invalid_rows.csv";
    const int size = 2;
    
    // Create a temporary CSV file with only 1 row
    std::ofstream file(fileName);
    file << "1.0, 2.0\n";
    file.close();

    BOOST_CHECK_THROW(matrixIO::openData(fileName, size), std::runtime_error);

    // Clean up
    std::remove(fileName.c_str());
}

BOOST_AUTO_TEST_CASE(OpenDataInvalidCols)
{
    const std::string fileName = "test_matrix_invalid_cols.csv";
    const int size = 2;
    
    // Create a temporary CSV file with 3 columns in the second row
    std::ofstream file(fileName);
    file << "1.0, 2.0\n3.0, 4.0, 5.0\n";
    file.close();

    BOOST_CHECK_THROW(matrixIO::openData(fileName, size), std::runtime_error);

    // Clean up
    std::remove(fileName.c_str());
}

BOOST_AUTO_TEST_SUITE_END()
