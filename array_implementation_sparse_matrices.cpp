#include <iostream>
#include <vector>
#include <tuple>

class SparseMatrix {
private:
    std::vector<std::tuple<int, int, double>> elements; 
    int rows;
    int cols;

public:
    SparseMatrix(int r, int c) : rows(r), cols(c) {}

    void add(int row, int col, double value) {
        if (value != 0) {
            elements.push_back(std::make_tuple(row, col, value));
        }
    }

    void display() {
        int k = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (k < elements.size() && i == std::get<0>(elements[k]) && j == std::get<1>(elements[k])) {
                    std::cout << std::get<2>(elements[k]) << " ";
                    k++;
                } else {
                    std::cout << "0 ";
                }
            }
            std::cout << "\n";
        }
    }
};

int main() {
    int rows, cols, num_elements;

    std::cout << "Enter the number of rows: ";
    std::cin >> rows;
    std::cout << "Enter the number of columns: ";
    std::cin >> cols;

    SparseMatrix matrix(rows, cols);

    std::cout << "Enter the number of non-zero elements: ";
    std::cin >> num_elements;

    for (int i = 0; i < num_elements; i++) {
        int row, col;
        double value;
        std::cout << "Enter row index, column index and value for element, seperating them with space " << i+1 << ": ";
        std::cin >> row >> col >> value;
        matrix.add(row, col, value);
    }

    std::cout << "Sparse Matrix:" << std::endl;
    matrix.display();

    return 0;
}