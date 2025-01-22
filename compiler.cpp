#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdlib>

using namespace std;
namespace fs = std::filesystem;

bool startsWith(const std::string& str, const std::string& prefix);

int main() {
    string path;
    string linestopper;
    string content;

    cout << "\033[31mWARNING!: YOU NEED g++ INSTALLED ON YOUR MACHINE. YOU WILL NEED TO INSTALL \033[0m"
         << "\033[33mMINGW64\033[0m"
         << "\033[31m IN ORDER TO USE g++.\033[0m" << '\n';

    cout << "The file path to be Compiled: ";
    getline(cin, path);

    fs::path pathExtension = path;
    if (pathExtension.extension() != ".navpp") {
        cout << "Use .navpp Extension instead of " << pathExtension.extension() << '\n';
        return 1;
    }

    ifstream file(path);
    if (!file) {
        cerr << "Error: Could not open file " << path << '\n';
        return 1;
    }

    if (!fs::exists("temp")) {
        fs::create_directory("temp");
    }

    cout << "Converting code to C++.........." << '\n';
    ofstream cppfile("temp/converted.cpp");

    cppfile << "#include <iostream>" << '\n';
    cppfile << "using namespace std;" << '\n';
    cppfile << "int main() {" << '\n';
    cppfile << "int num1;" << '\n';
    cppfile << "int num2;" << '\n';
    cppfile << "string mainvar;" << '\n';
    cppfile << "string linestopper;" << '\n';

    while (getline(file, content)) {
        if (startsWith(content, "write:")) {
            if (startsWith(content.substr(6), "%use var")) {
                cppfile << "cout << mainvar << \"\\n\";" << '\n';
            } else {
                cppfile << "cout << \"" << content.substr(6) << "\"<< '\\n';" << '\n';
            }
        } else if (startsWith(content, "var:")) {
            cppfile << "mainvar = \"" << content.substr(4) << "\";" << '\n';
        } else if (startsWith(content, "sum:") || startsWith(content, "add:")) {
            if (startsWith(content.substr(4), "input:")) {
                if (startsWith(content.substr(10), "num1:")) {
                    cppfile << "cin >> num1;" << '\n';
                } else if (startsWith(content.substr(10), "num2:")) {
                    cppfile << "cin >> num2;" << '\n';
                }
            } else if (startsWith(content.substr(4), "run()")) {
                cppfile << "cout << num1 + num2 << \"\\n\";" << '\n';
            }
        } else if (startsWith(content, "sub:")) {
            if (startsWith(content.substr(4), "input:")) {
                if (startsWith(content.substr(10), "num1:")) {
                    cppfile << "cin >> num1;" << '\n';
                } else if (startsWith(content.substr(10), "num2:")) {
                    cppfile << "cin >> num2;" << '\n';
                }
            } else if (startsWith(content.substr(4), "run()")) {
                cppfile << "cout << num1 - num2 << \"\\n\";" << '\n';
            }
        } else if (startsWith(content, "multi:")) {
            if (startsWith(content.substr(6), "input:")) {
                if (startsWith(content.substr(12), "num1:")) {
                    cppfile << "cin >> num1;" << '\n';
                } else if (startsWith(content.substr(12), "num2:")) {
                    cppfile << "cin >> num2;" << '\n';
                }
            } else if (startsWith(content.substr(6), "run()")) {
                cppfile << "cout << num1 * num2 << \"\\n\";" << '\n';
            }
        } else if (startsWith(content, "div:")) {
            if (startsWith(content.substr(4), "input:")) {
                if (startsWith(content.substr(10), "num1:")) {
                    cppfile << "cin >> num1;" << '\n';
                } else if (startsWith(content.substr(10), "num2:")) {
                    cppfile << "cin >> num2;" << '\n';
                }
            } else if (startsWith(content.substr(4), "run()")) {
                cppfile << "cout << num1 / num2 << \"\\n\";" << '\n';
            }
        }
    }
    cppfile << "cin >> linestopper;" << '\n';
    cppfile << "return 0;" << '\n';
    cppfile << "}" << '\n';

    cppfile.close();

    cout << "Compiling code using g++.........." << '\n';
    if (!fs::exists("Output")) {
        fs::create_directory("Output");
    }

    system("g++ temp/converted.cpp -o Output/Output.exe -mconsole");
    cout << "File saved at Output/Output.exe" << '\n';

    cin >> linestopper;
    return 0;
}

bool startsWith(const std::string& str, const std::string& prefix) {
    return str.substr(0, prefix.size()) == prefix;
}
