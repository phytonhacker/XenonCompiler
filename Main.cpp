#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "Globals.h"
// TeeStream: fájl + konzol egyben
class TeeStream {
public:
    TeeStream(std::ostream& a, std::ostream& b) : stream1(a), stream2(b) {}

    template <typename T>
    TeeStream& operator<<(const T& val) {
        stream1 << val;
        stream2 << val;
        return *this;
    }

    TeeStream& operator<<(std::ostream& (*manip)(std::ostream&)) {
        stream1 << manip;
        stream2 << manip;
        return *this;
    }

private:
    std::ostream& stream1;
    std::ostream& stream2;
};

std::string getCurrentTimestampFilename() {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S") << ".txt";
    return oss.str();
}

int main() {
    std::string filename = getCurrentTimestampFilename();
    std::ofstream logfile(filename);
    if (!logfile) {
        std::cerr << "Nem sikerült megnyitni a log fájlt!" << std::endl;
        return 1;
    }

    TeeStream out(std::cout, logfile);

    while (true) {
        out << "...............Welcome............." << std::endl;
        out << "1. Compile (java => jar)" << std::endl;
        out << "2. Compile (Main.cpp => Runable programfile)" << std::endl;
        out << "3. settings (java Checker: ON, G++ checck: ON)" << std::endl;
        out << "0. Exit" << std::endl;
        out << "..................................." << std::endl;

        std::string Ch;
        std::cin >> Ch;

        if (Ch == "0") break;

        if (Ch == "1") {
            if (Globals::JAvaChacker == true) {
                out << "Java checking" << std::endl;
                system("java --version");
                out << "logger on" << std::endl;
                out << "compile" << std::endl;
                system("mvn clean package");
            } else {
                out << "logger on" << std::endl;
                out << "compile" << std::endl;
                system("mvn clean package");
            }
        }

        if (Ch == "2") {
            if (Globals::GppCheck == true) {
                system("g++ --version");
                system("g++ Main.cpp -o CompiledBYXENONCompiler");
            } else {
                system("g++ Main.cpp -o CompiledBYXENONCompiler");
            }
        }

        if (Ch == "3") {
            Globals::GppCheck = !Globals::GppCheck;
            Globals::JAvaChacker = !Globals::JAvaChacker;
        }
    }

    out << "Log mentve ide: " << filename << std::endl;
    logfile.close();
    return 0;
}

