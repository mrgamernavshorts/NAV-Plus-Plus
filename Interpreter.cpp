#include <iostream>
#include <fstream>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;
bool startsWith(const std::string& str, const std::string& prefix);

int main() {
    string path;
    string content;
    string mainvar;
    string linestopper;
    string autorunpath;
    string autoruncontent;

    int num1;
    int num2;

    fs::path autorunfilepath = "autorun_init.txt";
    if (fs::exists(autorunfilepath)) {
        ifstream autorunfile("autorun_init.txt");
        getline(autorunfile, autoruncontent);
        path = autoruncontent;
        autorunfile.close();
    }
    if (path == "") {
        cout << "Enter the path to the File: ";
        getline(cin, path);
    }
    if (path == "autorun") {
        cout << "Enter the path you want to run Automatically: ";
        cin >> autorunpath;
        ofstream autorunfile("autorun_init.txt");
        autorunfile << autorunpath;
        autorunfile.close();
        cout << "autorun created! close the app and restart";
        cin >> linestopper;
        exit(1);
    }

    fs::path pathExtenstion = path;
    if ((pathExtenstion.extension() == ".navpp") == false) {
        cout << "Use .navpp Extension instead of " << pathExtenstion.extension();
    }

    ifstream file(path);
    while (!file.eof()) {
        getline(file, content);
        if (!startsWith(content, " ")) {
            if (startsWith(content, "write")) {
                if (startsWith(content.substr(6), "%use var")) {
                    cout << mainvar << '\n';
                } else {
                    cout << content.substr(6) << "\n";
                }
            } else if (startsWith(content, "var:")) {
                mainvar = content.substr(4);
            } else if (startsWith(content, "sum:") || startsWith(content, "add:")) {
                if (startsWith(content.substr(4), "input:")) {
                    if (startsWith(content.substr(10), "num1:")) {
                        cin >> num1;
                    } else if (startsWith(content.substr(10), "num2:")) {
                        cin >> num2;
                    }
                } else if (startsWith(content.substr(4), "run()")) {
                    cout << num1 + num2 << '\n';
                }
            } else if (startsWith(content, "sub:")) {
                if (startsWith(content.substr(4), "input:")) {
                    if (startsWith(content.substr(10), "num1:")) {
                        cin >> num1;
                    } else if (startsWith(content.substr(10), "num2:")) {
                        cin >> num2;
                    }
                } else if (startsWith(content.substr(4), "run()")) {
                    cout << num1 - num2 << '\n';
                }
            } else if (startsWith(content, "multi:")) {
                if (startsWith(content.substr(6), "input:")) {
                    if (startsWith(content.substr(12), "num1:")) {
                        cin >> num1;
                    } else if (startsWith(content.substr(12), "num2:")) {
                        cin >> num2;
                    }
                } else if (startsWith(content.substr(6), "run()")) {
                    cout << num1 * num2 << '\n';
                }
            } else if (startsWith(content, "div:")) {
                if (startsWith(content.substr(4), "input:")) {
                    if (startsWith(content.substr(10), "num1:")) {
                        cin >> num1;
                    } else if (startsWith(content.substr(10), "num2:")) {
                        cin >> num2;
                    }
                } else if (startsWith(content.substr(4), "run()")) {
                    cout << num1 / num2 << '\n';
                }
            }
        }
    }

    cout << '\n';
    cin >> linestopper;
    return 0;
}

bool startsWith(const std::string& str, const std::string& prefix) {
    return str.substr(0, prefix.size()) == prefix;
}
