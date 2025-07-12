#include <iostream>
#include <fstream>
#include <format>

const std::size_t buffer_size = 4096; // 4 bytes
bool SUCCESS = false;

void copy(const std::string& source, const std::string& destination, bool& task) {
    std::ifstream ist{source, std::ios::binary};
    if (!ist) throw std::runtime_error("can't open the source file.\nconfirm that the file exist.");

    std::ofstream ost{destination, std::ios::binary};
    if (!ost) throw std::runtime_error("can't open the destination file.\n");

    char buffer[buffer_size];
    while (ist.read(buffer, buffer_size)) {
        ost.write(buffer, ist.gcount());
    }
    if (ist.gcount() > 0) ost.write(buffer, ist.gcount());
    task = true;
    return;
}

int main( int argc, char* argv[]) {
    if(argc == 3) {
        std::string source  = argv[1];
        std::string destination = argv[2];

        copy(source, destination, SUCCESS);
        if (SUCCESS) {
            std::cout << std::format("Operation successful.\nContents of {}, was successfully copied to {}", source, destination) << std::endl;
        } else {
            std::cout << "Oops!\nThe copy operation failed!" << std::endl;
        }
    } else {
        std::cout << "Inappropriate number of arguments. Expected two." << std::endl;
    }
}