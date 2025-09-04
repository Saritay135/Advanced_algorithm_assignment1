#include <iostream>
#include <memory>

struct Node {
    int row, col;
    double value;
    std::shared_ptr<Node> next;

    Node(int r, int c, double v) : row(r), col(c), value(v), next(nullptr) {}
};

class SparseMatrix {
private:
    std::shared_ptr<Node> head, tail;
    int rows, cols;

public:
    SparseMatrix(int r, int c) : rows(r), cols(c), head(nullptr), tail(nullptr) {}

    void add(int row, int col, double value) {
        if (value == 0) return; // Only store non-zero elements

        std::shared_ptr<Node> newNode = std::make_shared<Node>(row, col, value);
        if (!head) {
            head = tail = newNode; // First non-zero element
        } else {
            tail->next = newNode; // Append to the list
            tail = newNode;
        }
    }

    // Initialize the matrix by inputting zeros and non-zeros
    void inputFullMatrix() {
        double value;
        std::cout << "Enter the full matrix values row by row:\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                std::cin >> value; // Read each value including zeros
                add(i, j, value); // Only non-zero values will be added
            }
        }
    }

    void displayFullMatrix() const {
        std::shared_ptr<Node> current = head;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (current && current->row == i && current->col == j) {
                    std::cout << current->value << " ";
                    current = current->next;
                } else {
                    std::cout << "0 ";
                }
            }
            std::cout << "\n";
        }
    }

    void displayCompactForm() const {
        std::shared_ptr<Node> current = head;
        std::cout << "Sparse Matrix Elements:\n";
        while (current) {
            std::cout << "Row: " << current->row << ", Col: " << current->col << ", Value: " << current->value << std::endl;
            current = current->next;
        }
    }
};

int main() {
    int rows, cols;

    std::cout << "Enter the number of rows: ";
    std::cin >> rows;
    std::cout << "Enter the number of columns: ";
    std::cin >> cols;

    SparseMatrix matrix(rows, cols);

    matrix.inputFullMatrix();

    std::cout << "\nFull Matrix Display:\n";
    matrix.displayFullMatrix();

    std::cout << "\nCompact Form Display:\n";
    matrix.displayCompactForm();

    return 0;
}