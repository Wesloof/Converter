#include "MyForm.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace System::IO;
using namespace System::Runtime::InteropServices;
using namespace Converterr;
using namespace System::Globalization;

std::string filenamez = "cfg.ini";
std::string filename2 = "saved.txt";
std::vector<double> numbers = {};
std::vector<std::string> lines = {};

[STAThread]
int main(array<String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew Converterr::MyForm());
    return 0;
}
struct markers {
    int markers_copy;
    int markers_input;
};

int changeflag(std::string flags) {
    std::ifstream file(filenamez);


    std::vector<std::string> lines;
    std::string line;

    while (std::getline(file, line)) {
        if (line == flags + "0") {
            line = flags + "1";
        }
        lines.push_back(line);
    }

    file.close(); 

    std::ofstream outFile(filenamez);

    for (const auto& l : lines) {
        outFile << l << std::endl;
    }

    outFile.close();
    return 0;
}

std::vector<double> extractNumbersAfterString(const std::string& query) {
    std::vector<double> numbers;
    std::ifstream file(filenamez);
    std::string line;
    bool found = false;

    if (query.empty()) {
        return { 0.0 }; // Если query пустая — возвращаем {0}
    }

    while (std::getline(file, line)) {
        if (line.find(query) != std::string::npos) {
            found = true;
            continue;
        }

        if (found) {
            if (line.empty()) {
                break; // Пустая строка — конец блока
            }

            size_t equalsSign = line.find('=');
            if (equalsSign != std::string::npos) {
                std::string numberStr = line.substr(equalsSign + 1);

                // Если строка "0" или "0.0" — добавляем 0
                if (numberStr == "0" || numberStr == "0.0") {
                    numbers.push_back(0.0);
                }
                // Если строка "null" или пустая — тоже 0
                else if (numberStr == "null" || numberStr.empty()) {
                    numbers.push_back(0.0);
                }
                // Пробуем распарсить число
                else {
                    std::istringstream iss(numberStr);
                    double number;
                    if (iss >> number) { // Если распарсилось (в т.ч. отрицательное)
                        numbers.push_back(number);
                    }
                    else { // Если не число (например, текст)
                        numbers.push_back(0.0);
                    }
                }
            }
        }
    }

    file.close();

    // Если после query не было строк с числами — возвращаем {0}
    if (numbers.empty()) {
        return { 0.0 };
    }

    return numbers;
}


void replaceNumbersBelowString(const std::string& query, const std::vector<double>& newNumbers) {
    std::ifstream inFile(filenamez);
    std::vector<std::string> lines;
    std::string line;
    bool found = false;
    size_t replaceStartIndex = 0;

    while (std::getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();

    for (size_t i = 0; i < lines.size(); ++i) {
        if (lines[i].find(query) != std::string::npos) {
            found = true;
            replaceStartIndex = i + 1;
            break;
        }
    }


   
    size_t rowNumber = 1;
    for (size_t i = replaceStartIndex; i < lines.size(); ++i) {
        if (lines[i].empty()) {
            break;
        }

        std::ostringstream oss;
        if (newNumbers[rowNumber - 1] != 0)
        {
            if (newNumbers[rowNumber - 1] != -1.24475)
            {
                oss << "Row" << rowNumber << "=" << newNumbers[rowNumber - 1];
            }
            else
            {
                oss << "Row" << rowNumber << "=";
            }
            
        }
        else
        {
            oss << "Row" << rowNumber << "=";
        }
        lines[i] = oss.str();
        rowNumber++;

        if (rowNumber > newNumbers.size()) {
            break;
        }
    }

    std::ofstream outFile(filenamez);

    for (const auto& l : lines) {
        outFile << l << std::endl;
    }
    outFile.close();
}
int write_infile(std::vector<std::string> all_lines)
{
    std::ofstream outFile(filenamez);
    if (!outFile.is_open()) {
        MessageBox::Show("Файл не найден.", "Ошибка");
        return 1;
    }

    for (const auto& l : all_lines) {
        outFile << l << std::endl;
    }

    outFile.close();
    return 0;
}
int change(std::string linec, std::string linen, double koef) {
    std::ifstream file(filenamez);

    std::vector<std::string> lines;
    std::string line;
    bool editFound = false, changeFound = false;
    size_t editIndex = 0, changeIndex = 0;

    while (std::getline(file, line)) {
        lines.push_back(line);
        if (line == linec && !editFound) {
            editFound = true;
            editIndex = lines.size() - 1;
        }
        if (line == linen && !changeFound) {
            changeFound = true;
            changeIndex = lines.size() - 1;
        }
    }

    file.close();

    std::vector<std::string> updatedLines;

    for (size_t i = 1; i <= 8; ++i) {
        std::string& currentLine = lines[editIndex + i];
        size_t equalPos = currentLine.find('=');
        if (equalPos == std::string::npos) {
            updatedLines.push_back("");
            continue;
        }

        std::string valueStr = currentLine.substr(equalPos + 1);

        if (valueStr.empty() || valueStr == "0") {
            updatedLines.push_back("Row" + std::to_string(i) + "=");
            continue;
        }

        double value = 0.0;
        try {
            value = std::stod(valueStr);
        }
        catch (const std::invalid_argument&) {
            updatedLines.push_back("");
            continue;
        }

        value += koef;

        std::string updatedLine = "Row" + std::to_string(i) + "=" + std::to_string(value);
        updatedLines.push_back(updatedLine);
    }

    size_t changeInsertIndex = changeIndex + 1;
    size_t linesToReplace = min(updatedLines.size(), lines.size() - changeInsertIndex);

    for (size_t i = 0; i < updatedLines.size(); ++i) {
        if (i < linesToReplace) {
            lines[changeInsertIndex + i] = updatedLines[i];
        }
        else {
            lines.insert(lines.begin() + changeInsertIndex + i, updatedLines[i]);
        }
    }
    write_infile(lines);
    return 0;
}

String^ Replaced(String^ input)
{
    // Получаем текущие региональные настройки системы
    CultureInfo^ culture = CultureInfo::CurrentCulture;

    // Получаем системный разделитель дробной части (это строка, например, "." или ",")
    String^ systemDecimalSeparatorStr = culture->NumberFormat->NumberDecimalSeparator;

    // Извлекаем первый символ из строки (разделитель)
    wchar_t systemDecimalSeparator = systemDecimalSeparatorStr[0];

    // Определяем, какой разделитель используется в строке (точка или запятая)
    wchar_t inputDecimalSeparator = input->Contains(",") ? L',' : L'.';

    // Если разделитель в строке не совпадает с системным, заменяем его
    if (inputDecimalSeparator != systemDecimalSeparator)
    {
        // Заменяем разделитель в строке на системный
        return input->Replace(inputDecimalSeparator.ToString(), systemDecimalSeparatorStr);
    }

    // Если разделитель совпадает, возвращаем строку без изменений
    return input;
}

std::string ConvertAndReplace(System::String^ managedString) {
    std::string stdString = msclr::interop::marshal_as<std::string>(managedString);
    for (char& ch : stdString) {
        if (ch == ',') {
            ch = '.';
        }
    }
    return stdString;
}

inline System::Void Converterr::MyForm::button2_Click(System::Object^ sender, System::EventArgs^ e) {
    numbers.clear(); // Чистим старые данные
    lines.clear();
    
    // 1. Открываем диалог и получаем ВЫБРАННЫЙ файл (filenamez)
    OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;
    if (openFileDialog1->ShowDialog() != System::Windows::Forms::DialogResult::OK) {
        return;
    }

    // Сохраняем путь в filenamez
    filenamez = msclr::interop::marshal_as<std::string>(openFileDialog1->FileName);


    std::ifstream file(filename2);
    if (!file.is_open()) {
        std::ofstream createFile(filename2);
        if (!createFile) {
            MessageBox::Show("Не создаётся filename2", "Ошибка");
            return;
        }
        createFile.close();
    }
    else {
        // Читаем весь filename2
        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty()) {
                // Парсим данные через 'i'
                size_t pos = 0;
                while ((pos = line.find('i')) != std::string::npos) {
                    std::string token = line.substr(0, pos);
                    line.erase(0, pos + 1);
                    try {
                        numbers.push_back(std::stod(token));
                    }
                    catch (...) {
                        numbers.push_back(0.0);
                    }
                }
                // Последнее число после последнего 'i'
                if (!line.empty()) {
                    try {
                        numbers.push_back(std::stod(line));
                    }
                    catch (...) {
                        numbers.push_back(0.0);
                    }
                }
            }
        }
        file.close();
    }

    // Если нихуя не считали - заполняем нулями
    if (numbers.size() < 10) {
        numbers.resize(10, 0.0);
        MessageBox::Show("Данных нет или файл пустой!", "Warning");
    }

    adp60->Text = Convert::ToString(numbers[0]);
    apd71->Text = Convert::ToString(numbers[1]);
    adp40->Text = Convert::ToString(numbers[2]);
    adp51->Text = Convert::ToString(numbers[3]);
    tmin->Text = Convert::ToString(numbers[4]);
    tmax->Text = Convert::ToString(numbers[5]);
    t0->Text = Convert::ToString(numbers[6]);
    uref->Text = Convert::ToString(numbers[7]);
    isens->Text = Convert::ToString(numbers[8]);
    rbot->Text = Convert::ToString(numbers[9]);
    groupBox2->Visible = true;
    groupBox2->Location = Point(8, 37);
}

inline System::Void Converterr::MyForm::button1_Click(System::Object^ sender, System::EventArgs^ e) {
    std::ostringstream updatedLine;
    updatedLine << ConvertAndReplace(adp60->Text) << "i";
    updatedLine << ConvertAndReplace(apd71->Text) << "i";
    updatedLine << ConvertAndReplace(adp40->Text) << "i";
    updatedLine << ConvertAndReplace(adp51->Text) << "i";
    updatedLine << ConvertAndReplace(tmin->Text) << "i";
    updatedLine << ConvertAndReplace(tmax->Text) << "i";
    updatedLine << ConvertAndReplace(t0->Text) << "i";
    updatedLine << ConvertAndReplace(uref->Text) << "i";
    updatedLine << ConvertAndReplace(isens->Text) << "i";
    updatedLine << ConvertAndReplace(rbot->Text);

    if (lines.empty()) {
        lines.push_back(updatedLine.str());
    }
    else {
        lines[0] = updatedLine.str();
    }
    {
        std::ofstream clearFile(filename2, std::ios::trunc);
        // Просто открытие в режиме trunc очистит файл
    }

    // Затем записываем новые данные
    std::ofstream outFile(filename2, std::ios::trunc);
    if (!outFile.is_open()) {
        std::cerr << "Error: Failed to open file for writing!" << std::endl;
        return;
    }

    outFile << updatedLine.str() << std::endl;
    outFile.close();

    

    if (radioButton1->Checked == true)
    {
        changeflag("P1L_EN=");
        changeflag("P2L_EN=");
        changeflag("P1H_EN=");
        changeflag("P2H_EN=");
        
        std::vector<markers> source = {
            {71, 73},
            {71, 75},
            {71, 77},

            {72, 76},
            {72, 78},

            {87, 91},
            {87, 93},
            
            {88, 94},
            {88, 92},

            {55, 59},
            {55, 61},

            {56, 60},
            {56, 62},
            
            {103, 109},
            {103, 107},
            
            {104, 110},
            {104, 108},
            
            {95, 99},
            {95, 101},
            
            {96, 100},
            {96, 102},
        };
        std::string linecopy;
        std::string linepaste;
        for (const markers& marker : source) {
            linecopy = "[Col" + std::to_string(marker.markers_copy) + "]";
            linepaste = "[Col" + std::to_string(marker.markers_input) + "]";
            int err = change(linecopy, linepaste, 0);
            if (err != 0) {
                MessageBox::Show("В ходе переноса была обнаружена ошибка", "Предупреждение");
            }
        }
        std::vector<double> adp0 = extractNumbersAfterString("[Col63]");
        std::vector<double> adp1 = extractNumbersAfterString("[Col64]");
        std::vector<double> adp6;
        std::vector<double> adp7;
        std::vector<double> adp4;
        std::vector<double> adp5;
        for (int i = 0; i < adp0.size(); i++)
        {
            adp6.push_back(adp0[i] + Convert::ToDouble(Replaced(adp60->Text)) * (adp1[i] - adp0[i]));
            adp7.push_back(adp6[i] + (Convert::ToDouble(Replaced(apd71->Text)) + 1) * (adp1[i] - adp0[i]));
            adp4.push_back(adp0[i] + Convert::ToDouble(Replaced(adp40->Text)) * (adp1[i] - adp0[i]));
            adp5.push_back(adp4[i] + (Convert::ToDouble(Replaced(adp51->Text)) + 1) * (adp1[i] - adp0[i]));
        }

        std::vector<double> adt0 = extractNumbersAfterString("[Col79]");
        std::vector<double> adt45;
        std::vector<double> adt67;
        for (int i = 0; i < adp0.size(); i++)
        {
            adt45.push_back(adt0[i] + 0.002144 * (Convert::ToDouble(Replaced(tmin->Text)) - Convert::ToDouble(Replaced(t0->Text)))
                * (adt0[i] - (Convert::ToDouble(Replaced(rbot->Text)) * Convert::ToDouble(Replaced(isens->Text))
                    / Convert::ToDouble(Replaced(uref->Text))) * 100));
            adt67.push_back(adt0[i] + 0.002916 * (Convert::ToDouble(Replaced(tmax->Text)) - Convert::ToDouble(Replaced(t0->Text)))
                * (adt0[i] - (Convert::ToDouble(Replaced(rbot->Text)) * Convert::ToDouble(Replaced(isens->Text))
                    / Convert::ToDouble(Replaced(uref->Text))) * 100));
        }

        replaceNumbersBelowString("[Col69]", adp6);
        replaceNumbersBelowString("[Col70]", adp7);
        replaceNumbersBelowString("[Col67]", adp4);
        replaceNumbersBelowString("[Col68]", adp5);

        replaceNumbersBelowString("[Col83]", adt45);
        replaceNumbersBelowString("[Col84]", adt45);
        replaceNumbersBelowString("[Col85]", adt67);
        replaceNumbersBelowString("[Col86]", adt67);

        MessageBox::Show("Успешная конвертация", "Окно");
    }
    if (radioButton2->Checked == true)
    {
        //change("[Col63]", "[Col69]", Convert::ToDouble(textBox4->Text)); // dadp max h
        changeflag("P1L_EN=");
        //change("[Col62]", "[Col68]", Convert::ToDouble(textBox1->Text));// dadp mix h
        changeflag("P2L_EN=");
        //change("[Col63]", "[Col67]", Convert::ToDouble(textBox9->Text));
        changeflag("P1H_EN=");
        //change("[Col62]", "[Col66]", Convert::ToDouble(textBox12->Text));
        changeflag("P2H_EN=");

        std::vector<markers> source = {
            {70, 76},
            {70, 74},

            {71, 77},
            {71, 75},

            {86, 92},
            {86, 90},

            {87, 93},
            {87, 91},

            {54, 58},
            {54, 60},

            {55, 59},
            {55, 61},

            {102, 108},
            {102, 106},

            {103, 109},
            {103, 107},

            {94, 98},
            {94, 100},

            {95, 99},
            {95, 101},
        };
        std::string linecopy;
        std::string linepaste;
        for (const markers& marker : source) {
            linecopy += "[Col" + std::to_string(marker.markers_copy) + "]";
            linepaste = "[Col" + std::to_string(marker.markers_input) + "]";
            int err = change(linecopy, linepaste, 0);
            if (err != 0) {
                MessageBox::Show("В ходе переноса была обнаружена ошибка", "Предупреждение");
            }
        }

        std::vector<double> adp0 = extractNumbersAfterString("[Col62]");
        std::vector<double> adp1 = extractNumbersAfterString("[Col63]");
        std::vector<double> adp6;
        std::vector<double> adp7;
        std::vector<double> adp4;
        std::vector<double> adp5;
        for (int i = 0; i < adp0.size(); i++)
        {
            adp6.push_back(adp0[i] + Convert::ToDouble(Replaced(adp60->Text)) * (adp1[i] - adp0[i]));
            adp7.push_back(adp6[i] + (Convert::ToDouble(Replaced(apd71->Text)) + 1) * (adp1[i] - adp0[i]));
            adp4.push_back(adp0[i] + Convert::ToDouble(Replaced(adp40->Text)) * (adp1[i] - adp0[i]));
            adp5.push_back(adp4[i] + (Convert::ToDouble(Replaced(adp51->Text)) + 1) * (adp1[i] - adp0[i]));
        }

        std::vector<double> adt0 = extractNumbersAfterString("[Col78]");
        std::vector<double> adt45;
        std::vector<double> adt67;
        for (int i = 0; i < adp0.size(); i++)
        {
            adt45.push_back(adt0[i] + 0.002144 * (Convert::ToDouble(Replaced(tmin->Text)) - Convert::ToDouble(Replaced(t0->Text)))
                * (adt0[i] - (Convert::ToDouble(Replaced(rbot->Text)) * Convert::ToDouble(Replaced(isens->Text))
                    / Convert::ToDouble(Replaced(uref->Text))) * 100));
            adt67.push_back(adt0[i] + 0.002916 * (Convert::ToDouble(Replaced(tmax->Text)) - Convert::ToDouble(Replaced(t0->Text)))
                * (adt0[i] - (Convert::ToDouble(Replaced(rbot->Text)) * Convert::ToDouble(Replaced(isens->Text))
                    / Convert::ToDouble(Replaced(uref->Text))) * 100));
        }

        replaceNumbersBelowString("[Col68]", adp6); // Позже: создать структуру и вектор для маркеров
        replaceNumbersBelowString("[Col69]", adp7);
        replaceNumbersBelowString("[Col66]", adp4);
        replaceNumbersBelowString("[Col67]", adp5);

        replaceNumbersBelowString("[Col82]", adt45);
        replaceNumbersBelowString("[Col83]", adt45);
        replaceNumbersBelowString("[Col84]", adt67);
        replaceNumbersBelowString("[Col85]", adt67);

        MessageBox::Show("Успешная конвертация", "Окно");
    }
}



inline System::Void Converterr::MyForm::button3_Click(System::Object^ sender, System::EventArgs^ e) {
}