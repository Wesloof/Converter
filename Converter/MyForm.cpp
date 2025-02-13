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

std::string filenamez = "cfg.ini";
std::string filename2 = "saved.txt";
std::vector<double> numbers = {};
std::vector<std::string> lines = {};

[STAThread]
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew MyForm);
    return 0;
}

int changeflag(std::string flags) {
    std::ifstream file(filenamez); // Open file for reading

    if (!file.is_open()) {
        MessageBox::Show("Не удалось открыть файл: " + gcnew String(filenamez.c_str()), "Ошибка");
        return 1;
    }

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(file, line)) {
        if (line == flags + "0") {
            line = flags + "1"; // Update line
        }
        lines.push_back(line);
    }

    file.close(); // Close for reading

    std::ofstream outFile(filenamez);
    if (!outFile.is_open()) {
        MessageBox::Show("Не удалось открыть файл для записи: " + gcnew String(filenamez.c_str()), "Ошибка");
        return 1;
    }

    for (const auto& l : lines) {
        outFile << l << std::endl;
    }

    outFile.close();
    return 0;
}

std::vector<double> extractNumbersAfterString(const std::string& query) {
    std::vector<double> numbers; // Вектор для хранения чисел
    std::ifstream file(filenamez); // Открываем файл для чтения
    std::string line;
    bool found = false;

    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл!" << std::endl;
        return numbers; // Возвращаем пустой вектор, если файл не открылся
    }

    while (std::getline(file, line)) { // Читаем файл построчно
        if (line.find(query) != std::string::npos) {
            found = true; // Нашли строку с запросом
            continue; // Переходим к следующей строке
        }

        if (found) {
            if (line.empty()) { // Если встретили пустую строку, прекращаем поиск
                break;
            }

            // Удаляем префикс "RowX=" и извлекаем число
            size_t equalsSign = line.find('=');
            if (equalsSign != std::string::npos) {
                std::string numberStr = line.substr(equalsSign + 1);
                std::istringstream iss(numberStr);
                double number;
                if (iss >> number) {
                    numbers.push_back(number); // Добавляем число в вектор
                }
            }
        }
    }

    file.close(); // Закрываем файл
    return numbers; // Возвращаем вектор чисел
}


void replaceNumbersBelowString(const std::string& query, const std::vector<double>& newNumbers) {
    std::ifstream inFile(filenamez); // Открываем файл для чтения
    std::vector<std::string> lines; // Вектор для хранения строк файла
    std::string line;
    bool found = false;
    size_t replaceStartIndex = 0; // Индекс строки, с которой начинается замена

    if (!inFile.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл для чтения!" << std::endl;
        return;
    }

    // Читаем файл построчно и сохраняем строки в вектор
    while (std::getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close(); // Закрываем файл

    // Ищем строку с запросом
    for (size_t i = 0; i < lines.size(); ++i) {
        if (lines[i].find(query) != std::string::npos) {
            found = true;
            replaceStartIndex = i + 1; // Замена начинается со следующей строки
            break;
        }
    }

    if (!found) {
        std::cerr << "Строка не найдена!" << std::endl;
        return;
    }

    // Перезаписываем строки с числами до пустой строки
    size_t rowNumber = 1; // Нумерация для префиксов Row1=, Row2= и т.д.
    for (size_t i = replaceStartIndex; i < lines.size(); ++i) {
        if (lines[i].empty()) { // Останавливаемся на пустой строке
            break;
        }

        // Формируем новую строку с префиксом и числом
        std::ostringstream oss;
        oss << "Row" << rowNumber << "=" << newNumbers[rowNumber - 1];
        lines[i] = oss.str(); // Перезаписываем строку
        rowNumber++;

        if (rowNumber > newNumbers.size()) { // Если числа закончились, прекращаем замену
            break;
        }
    }

    // Открываем файл для записи (перезаписываем)
    std::ofstream outFile(filenamez);
    if (!outFile.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл для записи!" << std::endl;
        return;
    }

    // Записываем обновленные строки в файл
    for (const auto& l : lines) {
        outFile << l << std::endl;
    }
    outFile.close(); // Закрываем файл
}

int change(std::string linec, std::string linen, double koef) {
    std::ifstream file(filenamez);

    if (!file.is_open()) {
        MessageBox::Show("Ошибка: Не удалось открыть файл", "Ошибка");
        return 1;
    }

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

    if (!editFound || editIndex + 8 >= lines.size()) {
        MessageBox::Show("Строка 'edit' не найдена или после нее недостаточно строк.", "Ошибка");
        return 1;
    }

    if (!changeFound) {
        MessageBox::Show("Строка 'change' не найдена.", "Ошибка");
        return 1;
    }

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

    std::ofstream outFile(filenamez);
    if (!outFile.is_open()) {
        MessageBox::Show("Ошибка при записи в файл.", "Ошибка");
        return 1;
    }

    for (const auto& l : lines) {
        outFile << l << std::endl;
    }

    outFile.close();
    return 0;
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
    // Open file dialog and check if file exists
    OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;

    if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
        // Convert the selected file path to a std::string
        std::string filePath = msclr::interop::marshal_as<std::string>(openFileDialog1->FileName);
        std::cout << "Selected File Path: " << filePath << std::endl;

        // Check if file exists before proceeding
        if (!std::ifstream(filePath)) {
            MessageBox::Show("Файл не существует или не может быть открыт.", "Ошибка");
            return;
        }

        filenamez = filePath;
        std::ifstream file(filename2);

        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        file.close();

        std::string firstLine = lines[0];
        std::stringstream ss(firstLine);
        std::string token;

        while (std::getline(ss, token, 'i')) {
            try {
                double num = std::stod(token);
                numbers.push_back(num);
            }
            catch (const std::invalid_argument&) {
                MessageBox::Show("Ошибка: некорректное число в первой строке.", "Ошибка");
            }
        }

        // Populate text boxes
        adp60->Text = Convert::ToString(numbers[0]);
        apd71->Text = Convert::ToString(numbers[1]);
        adp40->Text = Convert::ToString(numbers[2]);
        adp51->Text = Convert::ToString(numbers[3]);
        tmin->Text = Convert::ToString(numbers[4]);
        tmax->Text = Convert::ToString(numbers[5]);
        t0->Text = Convert::ToString(numbers[6]);
        etmin->Text = Convert::ToString(numbers[7]);
        etmax->Text = Convert::ToString(numbers[8]);
    }
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
    updatedLine << ConvertAndReplace(etmin->Text) << "i";
    updatedLine << ConvertAndReplace(etmax->Text);

    lines[0] = updatedLine.str();

    std::ofstream outFile(filename2);
    for (const auto& l : lines) {
        outFile << l << std::endl;
    } 
    outFile.close();

    if (radioButton1->Checked == true)
    {
       //change("[Col63]", "[Col67]", Convert::ToDouble(textBox4->Text));
        changeflag("P1L_EN=");
        //change("[Col64]", "[Col68]", Convert::ToDouble(textBox1->Text));
        changeflag("P2L_EN=");
        //change("[Col63]", "[Col69]", Convert::ToDouble(textBox9->Text));
        changeflag("P1H_EN=");
        //change("[Col64]", "[Col70]", Convert::ToDouble(textBox12->Text));
        changeflag("P2H_EN=");

        change("[Col70]", "[Col73]", 0);

        change("[Col70]", "[Col75]", 0);

        change("[Col70]", "[Col77]", 0);

        change("[Col72]", "[Col76]", 0);

        change("[Col72]", "[Col78]", 0);

        change("[Col87]", "[Col91]", 0);

        change("[Col87]", "[Col93]", 0);

        change("[Col88]", "[Col94]", 0);

        change("[Col88]", "[Col92]", 0);

        change("[Col55]", "[Col59]", 0);

        change("[Col55]", "[Col61]", 0);

        change("[Col56]", "[Col60]", 0);

        change("[Col56]", "[Col62]", 0);

        //s
        change("[Col103]", "[Col109]", 0);

        change("[Col103]", "[Col107]", 0);

        change("[Col104]", "[Col110]", 0);

        change("[Col104]", "[Col108]", 0);
        std::vector<double> adp0 = extractNumbersAfterString("[Col63]");
        std::vector<double> adp1 = extractNumbersAfterString("[Col64]");
        std::vector<double> adp6;
        std::vector<double> adp7;
        std::vector<double> adp4;
        std::vector<double> adp5;
        for (int i = 0; i < adp0.size(); i++)
        {
            adp6.push_back(adp0[i] + Convert::ToDouble(adp60->Text) * (adp1[i] - adp0[i]) * (
                Convert::ToDouble(tmax->Text) - Convert::ToDouble(t0->Text)) / 
                Convert::ToDouble(etmax->Text));
            adp7.push_back(adp6[i] + (Convert::ToDouble(apd71->Text) + 1) * (adp1[i] - adp0[i])
            * (Convert::ToDouble(tmax->Text) - Convert::ToDouble(t0->Text)) / Convert::ToDouble(etmax->Text));
            adp4.push_back(adp0[i] + Convert::ToDouble(adp40->Text) * (adp1[i] - adp0[i]) * (
                Convert::ToDouble(tmin->Text) - Convert::ToDouble(t0->Text)) /
                Convert::ToDouble(etmin->Text));
            adp5.push_back(adp4[i] + (Convert::ToDouble(adp51->Text) + 1) * (adp1[i] - adp0[i])
                * (Convert::ToDouble(tmin->Text) - Convert::ToDouble(t0->Text)) / Convert::ToDouble(etmin->Text));
        }

        std::vector<double> adt0 = extractNumbersAfterString("[Col79]");
        std::vector<double> adt45;
        std::vector<double> adt67;
        for (int i = 0; i < adp0.size(); i++)
        {
            adt45.push_back(adt0[i] + 0.002144 *(Convert::ToDouble(tmin->Text) - Convert::ToDouble(t0->Text))
            * (adt0[i] - (620 * 0.00065 / 4) * 100));
            adt67.push_back(adt0[i] + 0.002916 * (Convert::ToDouble(tmax->Text) - Convert::ToDouble(t0->Text))
                * (adt0[i] - (620 * 0.00065 / 4) * 100));
        }

        replaceNumbersBelowString("[Col68]", adp6);
        replaceNumbersBelowString("[Col67]", adp7);
        replaceNumbersBelowString("[Col70]", adp4);
        replaceNumbersBelowString("[Col69]", adp5);

        replaceNumbersBelowString("[Col83]", adt45);
        replaceNumbersBelowString("[Col84]", adt45);
        replaceNumbersBelowString("[Col85]", adt67);
        replaceNumbersBelowString("[Col86]", adt67);


        change("[Col95]", "[Col99]", 0);

        change("[Col96]", "[Col100]", 0);

        change("[Col95]", "[Col101]", 0);

        change("[Col96]", "[Col102]", 0);

        MessageBox::Show("Успех", "Успех");
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

        change("[Col70]", "[Col76]", 0);

        change("[Col70]", "[Col74]", 0);

        change("[Col71]", "[Col77]", 0);

        change("[Col71]", "[Col75]", 0);

        change("[Col86]", "[Col92]", 0);

        change("[Col86]", "[Col90]", 0);

        change("[Col87]", "[Col93]", 0);

        change("[Col87]", "[Col91]", 0);

        change("[Col54]", "[Col58]", 0);

        change("[Col54]", "[Col60]", 0);

        change("[Col55]", "[Col59]", 0);

        change("[Col55]", "[Col61]", 0);
        
        change("[Col102]", "[Col108]", 0);

        change("[Col102]", "[Col106]", 0);

        change("[Col103]", "[Col109]", 0);

        change("[Col103]", "[Col107]", 0);

        std::vector<double> adp0 = extractNumbersAfterString("[Col62]");
        std::vector<double> adp1 = extractNumbersAfterString("[Col63]");
        std::vector<double> adp6;
        std::vector<double> adp7;
        std::vector<double> adp4;
        std::vector<double> adp5;
        for (int i = 0; i < adp0.size(); i++)
        {
            adp6.push_back(adp0[i] + Convert::ToDouble(adp60->Text) * (adp1[i] - adp0[i]) * (
                Convert::ToDouble(tmax->Text) - Convert::ToDouble(t0->Text)) /
                Convert::ToDouble(etmax->Text));
            adp7.push_back(adp6[i] + (Convert::ToDouble(apd71->Text) + 1) * (adp1[i] - adp0[i])
                * (Convert::ToDouble(tmax->Text) - Convert::ToDouble(t0->Text)) / Convert::ToDouble(etmax->Text));
            adp4.push_back(adp0[i] + Convert::ToDouble(adp40->Text) * (adp1[i] - adp0[i]) * (
                Convert::ToDouble(tmin->Text) - Convert::ToDouble(t0->Text)) /
                Convert::ToDouble(etmin->Text));
            adp5.push_back(adp4[i] + (Convert::ToDouble(adp51->Text) + 1) * (adp1[i] - adp0[i])
                * (Convert::ToDouble(tmin->Text) - Convert::ToDouble(t0->Text)) / Convert::ToDouble(etmin->Text));
        }

        std::vector<double> adt0 = extractNumbersAfterString("[Col78]");
        std::vector<double> adt45;
        std::vector<double> adt67;
        for (int i = 0; i < adp0.size(); i++)
        {
            adt45.push_back(adt0[i] + 0.002144 * (Convert::ToDouble(tmin->Text) - Convert::ToDouble(t0->Text))
                * (adt0[i] - (620 * 0.00065 / 4) * 100));
            adt67.push_back(adt0[i] + 0.002916 * (Convert::ToDouble(tmax->Text) - Convert::ToDouble(t0->Text))
                * (adt0[i] - (620 * 0.00065 / 4) * 100));
        }

        replaceNumbersBelowString("[Col68]", adp6);
        replaceNumbersBelowString("[Col69]", adp7);
        replaceNumbersBelowString("[Col66]", adp4);
        replaceNumbersBelowString("[Col67]", adp5);

        replaceNumbersBelowString("[Col82]", adt45);
        replaceNumbersBelowString("[Col83]", adt45);
        replaceNumbersBelowString("[Col84]", adt67);
        replaceNumbersBelowString("[Col85]", adt67);

        change("[Col94]", "[Col98]", 0);

        change("[Col95]", "[Col99]", 0);

        change("[Col94]", "[Col100]", 0);

        change("[Col95]", "[Col101]", 0);

        MessageBox::Show("Успех", "Успех");
    }
    }

    

inline System::Void Converterr::MyForm::button3_Click(System::Object^ sender, System::EventArgs^ e) {
}
