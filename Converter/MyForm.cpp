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
        MessageBox::Show("�� ������� ������� ����: " + gcnew String(filenamez.c_str()), "������");
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
        MessageBox::Show("�� ������� ������� ���� ��� ������: " + gcnew String(filenamez.c_str()), "������");
        return 1;
    }

    for (const auto& l : lines) {
        outFile << l << std::endl;
    }

    outFile.close();
    return 0;
}

int change(std::string linec, std::string linen, double koef) {
    std::ifstream file(filenamez);

    if (!file.is_open()) {
        MessageBox::Show("������: �� ������� ������� ����", "������");
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
        MessageBox::Show("������ 'edit' �� ������� ��� ����� ��� ������������ �����.", "������");
        return 1;
    }

    if (!changeFound) {
        MessageBox::Show("Не найдены аргументы для замены");
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
        MessageBox::Show("������ ��� ������ � ����.", "������");
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
            MessageBox::Show("���� �� ���������� ��� �� ����� ���� ������.", "������");
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
                MessageBox::Show("������: ������������ ����� � ������ ������.", "������");
            }
        }

        // Populate text boxes
        textBox1->Text = Convert::ToString(numbers[0]);
        textBox2->Text = Convert::ToString(numbers[1]);
        textBox3->Text = Convert::ToString(numbers[2]);
        textBox4->Text = Convert::ToString(numbers[3]);
        textBox5->Text = Convert::ToString(numbers[4]);
        textBox6->Text = Convert::ToString(numbers[5]);
        textBox12->Text = Convert::ToString(numbers[6]);
        textBox11->Text = Convert::ToString(numbers[7]);
        textBox10->Text = Convert::ToString(numbers[8]);
        textBox9->Text = Convert::ToString(numbers[9]);
        textBox8->Text = Convert::ToString(numbers[10]);
        textBox7->Text = Convert::ToString(numbers[11]);
    }
}

String^ Replaced(String^ inp) {
    return inp->Replace(".", ",");
}

inline System::Void Converterr::MyForm::button1_Click(System::Object^ sender, System::EventArgs^ e) {
    std::ostringstream updatedLine;
    updatedLine << ConvertAndReplace(textBox1->Text) << "i";
    updatedLine << ConvertAndReplace(textBox2->Text) << "i";
    updatedLine << ConvertAndReplace(textBox3->Text) << "i";
    updatedLine << ConvertAndReplace(textBox4->Text) << "i";
    updatedLine << ConvertAndReplace(textBox5->Text) << "i";
    updatedLine << ConvertAndReplace(textBox6->Text) << "i";
    updatedLine << ConvertAndReplace(textBox12->Text) << "i";
    updatedLine << ConvertAndReplace(textBox11->Text) << "i";
    updatedLine << ConvertAndReplace(textBox10->Text) << "i";
    updatedLine << ConvertAndReplace(textBox9->Text) << "i";
    updatedLine << ConvertAndReplace(textBox8->Text) << "i";
    updatedLine << ConvertAndReplace(textBox7->Text);

    lines[0] = updatedLine.str();

    std::ofstream outFile(filename2);
    for (const auto& l : lines) {
        outFile << l << std::endl;
    }
    outFile.close();

    if (radioButton1->Checked == true)
    {
        change("[Col63]", "[Col67]", Convert::ToDouble(Replaced(textBox4->Text)));
        changeflag("P1L_EN=");
        change("[Col64]", "[Col68]", Convert::ToDouble(Replaced(textBox1->Text)));
        changeflag("P2L_EN=");
        change("[Col63]", "[Col69]", Convert::ToDouble(Replaced(textBox9->Text)));
        changeflag("P1H_EN=");
        change("[Col64]", "[Col70]", Convert::ToDouble(Replaced(textBox12->Text)));
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





        change("[Col79]", "[Col83]", Convert::ToDouble(Replaced(textBox6->Text)));

        change("[Col80]", "[Col84]", Convert::ToDouble(Replaced(textBox3->Text)));

        change("[Col79]", "[Col85]", Convert::ToDouble(Replaced(textBox7->Text)));

        change("[Col80]", "[Col86]", Convert::ToDouble(Replaced(textBox10->Text)));

        change("[Col95]", "[Col99]", Convert::ToDouble(Replaced(textBox5->Text)));

        change("[Col96]", "[Col100]", Convert::ToDouble(Replaced(textBox2->Text)));

        change("[Col95]", "[Col101]", Convert::ToDouble(Replaced(textBox8->Text)));

        change("[Col96]", "[Col102]", Convert::ToDouble(Replaced(textBox11->Text)));

        MessageBox::Show("Успешная конвертация типа 42", "Окно");
    }
    if (radioButton2->Checked == true)
    {
        change("[Col62]", "[Col68]", Convert::ToDouble(Replaced(textBox4->Text))); // dadp max h
        changeflag("P1L_EN=");
        change("[Col63]", "[Col67]", Convert::ToDouble(Replaced(textBox1->Text)));// dadp mix h
        changeflag("P2L_EN=");
        change("[Col62]", "[Col66]", Convert::ToDouble(Replaced(textBox9->Text)));
        changeflag("P1H_EN=");
        change("[Col63]", "[Col69]", Convert::ToDouble(Replaced(textBox12->Text)));
        changeflag("P2H_EN=");

        change("[Col70]", "[Col76]", 0);

        change("[Col70]", "[Col74]", 0);

        change("[Col71]", "[Col77]", 0);

        change("[Col71]", "[Col75]", 0);

        change("[Col86]", "[Col92]", 0);

        change("[Col86]", "[Col90]", 0);

        change("[Col87]", "[Col93]", 0);

        change("[Col87]", "[Col91]", 0);

        change("[Col102]", "[Col108]", 0);

        change("[Col102]", "[Col106]", 0);

        change("[Col103]", "[Col109]", 0);

        change("[Col103]", "[Col107]", 0);

        change("[Col78]", "[Col82]", Convert::ToDouble(Replaced(textBox6->Text)));
        change("[Col79]", "[Col83]", Convert::ToDouble(Replaced(textBox3->Text)));
        change("[Col78]", "[Col84]", Convert::ToDouble(Replaced(textBox7->Text)));
        change("[Col79]", "[Col85]", Convert::ToDouble(Replaced(textBox10->Text)));

        change("[Col94]", "[Col98]", Convert::ToDouble(Replaced(textBox5->Text)));

        change("[Col95]", "[Col99]", Convert::ToDouble(Replaced(textBox2->Text)));

        change("[Col94]", "[Col100]", Convert::ToDouble(Replaced(textBox8->Text)));

        change("[Col95]", "[Col101]", Convert::ToDouble(Replaced(textBox11->Text)));

        MessageBox::Show("Успешная конвертация типа 0.5", "Окно");
    }
}



inline System::Void Converterr::MyForm::button3_Click(System::Object^ sender, System::EventArgs^ e) {
}