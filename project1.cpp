#include <iostream>
#include <fstream>
#include <unordered_map>
#include <cctype>
#include <limits>
#include <locale>

using namespace std;

template <typename StringType>
bool isEnglishText(const StringType &text)
{
    std::locale loc;
    for (auto c : text)
    {
        if (!std::isalnum(c, loc) && !std::ispunct(c, loc) && !std::isspace(c, loc))
        {
            return false;
        }
    }
    return true;
}

void processText(const string &text, unordered_map<char, int> &charFrequency)
{
    for (char c : text)
    {
        if (std::isalnum(c))
        {
            charFrequency[c]++;
        }
    }
}

//
string inputText()
{
    cout << "Nhap van ban (nhap 'endtext' de ket thuc):\n";
    string inputText;
    string line;

    while (true)
    {
        // Sử dụng getline để đọc từng dòng nhập
        getline(cin, line);

        // Nếu dòng nhập là "endtext", kết thúc vòng lặp
        if (line == "endtext")
        {
            break;
        }

        // Kiểm tra nếu dòng nhập không phải tiếng Anh
        if (!isEnglishText(line))
        {
            cerr << "Van ban khong phai tieng Anh.\n";
            continue;
        }

        // Nếu dòng nhập không rỗng, thêm vào văn bản tổng
        if (!line.empty())
        {
            inputText += line + "\n";
        }
    }

    return inputText;
}

string inputFileName()
{
    string fileName;
    bool validInput = false;

    while (!validInput)
    {
        cout << "Nhap ten tep tin: ";
        getline(cin, fileName);

        ifstream testFile(fileName);
        if (testFile.good())
        {
            validInput = true;
            testFile.close();
        }
        else
        {
            cerr << "Ten tep tin khong hop le hoac tep tin khong ton tai. Vui long nhap lai.\n";
        }
    }

    return fileName;
}

bool readFromFile(const string &fileName, string &content)
{
    ifstream inputFile(fileName);

    if (!inputFile.is_open())
    {
        cerr << "Khong the mo tep tin.\n";
        return false;
    }

    string line;
    while (getline(inputFile, line))
    {
        content += line + "\n";
    }

    if (inputFile.fail() && !inputFile.eof())
    {
        cerr << "Loi khi doc tu tep tin.\n";
        inputFile.close();
        return false;
    }

    inputFile.close();
    return true;
}

void outputCharFrequency(const unordered_map<char, int> &charFrequency)
{
    cout << "Tan suat cac chu cai va chu so trong van ban:\n";
    for (const auto &pair : charFrequency)
    {
        if (std::isalnum(pair.first))
        {
            cout << pair.first << ": " << pair.second << "\n";
        }
    }
}

int getUserInputChoice(unordered_map<char, int> &charFrequency)
{
    int choice;
    cout << "Chon lua nhap du lieu:\n";
    cout << "1. Nhap van ban tu ban phim\n";
    cout << "2. Nhap ten tep tin\n";
    cout << "Lua chon cua ban: ";

    if (!(cin >> choice))
    {
        cerr << "Lua chon khong hop le. Vui long nhap lai.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1; // Indicates an invalid choice
    }

    cin.ignore();

    switch (choice)
    {
    case 1:
        processText(inputText(), charFrequency);
        break;
    case 2:
    {
        string fileName = inputFileName();
        string content;

        if (!readFromFile(fileName, content))
        {
            return -1; // Indicates an invalid choice
        }

        processText(content, charFrequency);
        break;
    }
    default:
        cerr << "Lua chon khong hop le. Vui long nhap lai.\n";
        return -1; // Indicates an invalid choice
    }

    return choice;
}

int main()
{
    unordered_map<char, int> charFrequency;

    int choice;
    do
    {
        choice = getUserInputChoice(charFrequency);
    } while (choice == -1);

    outputCharFrequency(charFrequency);

    return 0;
}
