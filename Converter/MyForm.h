#pragma once

namespace Converterr {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:






















	private: System::Windows::Forms::Button^ button1;

	private: System::Windows::Forms::Button^ button2;

	private: System::Windows::Forms::RadioButton^ radioButton2;
	private: System::Windows::Forms::RadioButton^ radioButton1;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::TextBox^ adp60;

	private: System::Windows::Forms::TextBox^ tmax;

	private: System::Windows::Forms::TextBox^ t0;

	private: System::Windows::Forms::TextBox^ tmin;

	private: System::Windows::Forms::TextBox^ adp51;

	private: System::Windows::Forms::TextBox^ adp40;

	private: System::Windows::Forms::TextBox^ apd71;



	private: System::Windows::Forms::Label^ label15;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::Label^ label12;


	private: System::Windows::Forms::Label^ label18;
	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::Label^ label16;
	private: System::Windows::Forms::Label^ label21;
	private: System::Windows::Forms::GroupBox^ groupBox3;
	private: System::Windows::Forms::Label^ label24;
	private: System::Windows::Forms::TextBox^ uref;
	private: System::Windows::Forms::Label^ isensas;
	private: System::Windows::Forms::TextBox^ isens;
	private: System::Windows::Forms::Label^ sadsda;
	private: System::Windows::Forms::TextBox^ rbot;










	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->uref = (gcnew System::Windows::Forms::TextBox());
			this->isensas = (gcnew System::Windows::Forms::Label());
			this->isens = (gcnew System::Windows::Forms::TextBox());
			this->sadsda = (gcnew System::Windows::Forms::Label());
			this->rbot = (gcnew System::Windows::Forms::TextBox());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->tmax = (gcnew System::Windows::Forms::TextBox());
			this->t0 = (gcnew System::Windows::Forms::TextBox());
			this->tmin = (gcnew System::Windows::Forms::TextBox());
			this->adp51 = (gcnew System::Windows::Forms::TextBox());
			this->adp40 = (gcnew System::Windows::Forms::TextBox());
			this->apd71 = (gcnew System::Windows::Forms::TextBox());
			this->adp60 = (gcnew System::Windows::Forms::TextBox());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->SuspendLayout();
			// 
			// radioButton2
			// 
			this->radioButton2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->radioButton2->AutoSize = true;
			this->radioButton2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButton2->ForeColor = System::Drawing::Color::Navy;
			this->radioButton2->Location = System::Drawing::Point(288, 78);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->radioButton2->Size = System::Drawing::Size(197, 50);
			this->radioButton2->TabIndex = 27;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"Типа 0.5";
			this->radioButton2->UseVisualStyleBackColor = true;
			this->radioButton2->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton2_CheckedChanged);
			// 
			// radioButton1
			// 
			this->radioButton1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->radioButton1->AutoSize = true;
			this->radioButton1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->radioButton1->ForeColor = System::Drawing::Color::Navy;
			this->radioButton1->Location = System::Drawing::Point(11, 78);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(186, 50);
			this->radioButton1->TabIndex = 26;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Типа 42";
			this->radioButton1->UseVisualStyleBackColor = true;
			this->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &MyForm::radioButton1_CheckedChanged);
			// 
			// button1
			// 
			this->button1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->button1->Enabled = false;
			this->button1->ForeColor = System::Drawing::Color::Navy;
			this->button1->Location = System::Drawing::Point(265, 134);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(220, 87);
			this->button1->TabIndex = 23;
			this->button1->Text = L"Конверт";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->button2->ForeColor = System::Drawing::Color::Navy;
			this->button2->Location = System::Drawing::Point(6, 134);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(209, 87);
			this->button2->TabIndex = 24;
			this->button2->Text = L"Выбрать файл";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->groupBox2->BackColor = System::Drawing::Color::WhiteSmoke;
			this->groupBox2->Controls->Add(this->label24);
			this->groupBox2->Controls->Add(this->uref);
			this->groupBox2->Controls->Add(this->isensas);
			this->groupBox2->Controls->Add(this->isens);
			this->groupBox2->Controls->Add(this->sadsda);
			this->groupBox2->Controls->Add(this->rbot);
			this->groupBox2->Controls->Add(this->label18);
			this->groupBox2->Controls->Add(this->label17);
			this->groupBox2->Controls->Add(this->label16);
			this->groupBox2->Controls->Add(this->label15);
			this->groupBox2->Controls->Add(this->label14);
			this->groupBox2->Controls->Add(this->label13);
			this->groupBox2->Controls->Add(this->label12);
			this->groupBox2->Controls->Add(this->tmax);
			this->groupBox2->Controls->Add(this->t0);
			this->groupBox2->Controls->Add(this->tmin);
			this->groupBox2->Controls->Add(this->adp51);
			this->groupBox2->Controls->Add(this->adp40);
			this->groupBox2->Controls->Add(this->apd71);
			this->groupBox2->Controls->Add(this->adp60);
			this->groupBox2->Location = System::Drawing::Point(498, 42);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(478, 346);
			this->groupBox2->TabIndex = 1;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Коэфициенты";
			this->groupBox2->Visible = false;
			// 
			// label24
			// 
			this->label24->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label24->AutoSize = true;
			this->label24->Font = (gcnew System::Drawing::Font(L"Cascadia Mono", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label24->ForeColor = System::Drawing::Color::Navy;
			this->label24->Location = System::Drawing::Point(277, 297);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(65, 30);
			this->label24->TabIndex = 22;
			this->label24->Text = L"Uref";
			// 
			// uref
			// 
			this->uref->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->uref->Font = (gcnew System::Drawing::Font(L"Cascadia Mono", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->uref->Location = System::Drawing::Point(345, 297);
			this->uref->Name = L"uref";
			this->uref->Size = System::Drawing::Size(127, 34);
			this->uref->TabIndex = 21;
			// 
			// isensas
			// 
			this->isensas->AutoSize = true;
			this->isensas->Font = (gcnew System::Drawing::Font(L"Cascadia Mono", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->isensas->ForeColor = System::Drawing::Color::Navy;
			this->isensas->Location = System::Drawing::Point(41, 300);
			this->isensas->Name = L"isensas";
			this->isensas->Size = System::Drawing::Size(91, 30);
			this->isensas->TabIndex = 20;
			this->isensas->Text = L"I sens";
			// 
			// isens
			// 
			this->isens->Font = (gcnew System::Drawing::Font(L"Cascadia Mono", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->isens->Location = System::Drawing::Point(138, 297);
			this->isens->Name = L"isens";
			this->isens->Size = System::Drawing::Size(127, 34);
			this->isens->TabIndex = 19;
			// 
			// sadsda
			// 
			this->sadsda->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->sadsda->AutoSize = true;
			this->sadsda->Font = (gcnew System::Drawing::Font(L"Cascadia Mono", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->sadsda->ForeColor = System::Drawing::Color::Navy;
			this->sadsda->Location = System::Drawing::Point(277, 230);
			this->sadsda->Name = L"sadsda";
			this->sadsda->Size = System::Drawing::Size(65, 30);
			this->sadsda->TabIndex = 18;
			this->sadsda->Text = L"Rbot";
			// 
			// rbot
			// 
			this->rbot->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->rbot->Font = (gcnew System::Drawing::Font(L"Cascadia Mono", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->rbot->Location = System::Drawing::Point(345, 230);
			this->rbot->Name = L"rbot";
			this->rbot->Size = System::Drawing::Size(127, 34);
			this->rbot->TabIndex = 17;
			// 
			// label18
			// 
			this->label18->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"Cascadia Mono", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label18->ForeColor = System::Drawing::Color::Navy;
			this->label18->Location = System::Drawing::Point(300, 89);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(39, 30);
			this->label18->TabIndex = 16;
			this->label18->Text = L"T0";
			// 
			// label17
			// 
			this->label17->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"Cascadia Mono", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label17->ForeColor = System::Drawing::Color::Navy;
			this->label17->Location = System::Drawing::Point(300, 157);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(39, 30);
			this->label17->TabIndex = 15;
			this->label17->Text = L"T+";
			// 
			// label16
			// 
			this->label16->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"Cascadia Mono", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label16->ForeColor = System::Drawing::Color::Navy;
			this->label16->Location = System::Drawing::Point(300, 29);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(39, 30);
			this->label16->TabIndex = 14;
			this->label16->Text = L"T-";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Cascadia Mono", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label15->ForeColor = System::Drawing::Color::Navy;
			this->label15->Location = System::Drawing::Point(6, 230);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(117, 30);
			this->label15->TabIndex = 13;
			this->label15->Text = L"ADP(5;1)";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Cascadia Mono", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label14->ForeColor = System::Drawing::Color::Navy;
			this->label14->Location = System::Drawing::Point(6, 157);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(117, 30);
			this->label14->TabIndex = 12;
			this->label14->Text = L"ADP(4;0)";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Cascadia Mono", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label13->ForeColor = System::Drawing::Color::Navy;
			this->label13->Location = System::Drawing::Point(6, 87);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(117, 30);
			this->label13->TabIndex = 11;
			this->label13->Text = L"ADP(7;1)";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Cascadia Mono", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label12->ForeColor = System::Drawing::Color::Navy;
			this->label12->Location = System::Drawing::Point(6, 27);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(117, 30);
			this->label12->TabIndex = 10;
			this->label12->Text = L"ADP(6;0)";
			// 
			// tmax
			// 
			this->tmax->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->tmax->Font = (gcnew System::Drawing::Font(L"Cascadia Mono", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tmax->Location = System::Drawing::Point(345, 157);
			this->tmax->Name = L"tmax";
			this->tmax->Size = System::Drawing::Size(127, 34);
			this->tmax->TabIndex = 6;
			// 
			// t0
			// 
			this->t0->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->t0->Font = (gcnew System::Drawing::Font(L"Cascadia Mono", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->t0->Location = System::Drawing::Point(345, 89);
			this->t0->Name = L"t0";
			this->t0->Size = System::Drawing::Size(127, 34);
			this->t0->TabIndex = 5;
			// 
			// tmin
			// 
			this->tmin->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->tmin->Font = (gcnew System::Drawing::Font(L"Cascadia Mono", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tmin->Location = System::Drawing::Point(345, 27);
			this->tmin->Name = L"tmin";
			this->tmin->Size = System::Drawing::Size(127, 34);
			this->tmin->TabIndex = 4;
			// 
			// adp51
			// 
			this->adp51->Font = (gcnew System::Drawing::Font(L"Cascadia Mono", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->adp51->Location = System::Drawing::Point(138, 230);
			this->adp51->Name = L"adp51";
			this->adp51->Size = System::Drawing::Size(130, 34);
			this->adp51->TabIndex = 3;
			// 
			// adp40
			// 
			this->adp40->Font = (gcnew System::Drawing::Font(L"Cascadia Mono", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->adp40->Location = System::Drawing::Point(138, 157);
			this->adp40->Name = L"adp40";
			this->adp40->Size = System::Drawing::Size(130, 34);
			this->adp40->TabIndex = 2;
			// 
			// apd71
			// 
			this->apd71->Font = (gcnew System::Drawing::Font(L"Cascadia Mono", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->apd71->Location = System::Drawing::Point(138, 87);
			this->apd71->Name = L"apd71";
			this->apd71->Size = System::Drawing::Size(130, 34);
			this->apd71->TabIndex = 1;
			// 
			// adp60
			// 
			this->adp60->Font = (gcnew System::Drawing::Font(L"Cascadia Mono", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->adp60->Location = System::Drawing::Point(138, 27);
			this->adp60->Name = L"adp60";
			this->adp60->Size = System::Drawing::Size(130, 34);
			this->adp60->TabIndex = 0;
			this->adp60->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox13_TextChanged);
			// 
			// label21
			// 
			this->label21->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->label21->AutoSize = true;
			this->label21->Font = (gcnew System::Drawing::Font(L"Courier New", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label21->ForeColor = System::Drawing::Color::Navy;
			this->label21->Location = System::Drawing::Point(141, 9);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(250, 25);
			this->label21->TabIndex = 28;
			this->label21->Text = L"Конвертер v3.F_45";
			// 
			// groupBox3
			// 
			this->groupBox3->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->groupBox3->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->groupBox3->Controls->Add(this->button1);
			this->groupBox3->Controls->Add(this->radioButton1);
			this->groupBox3->Controls->Add(this->radioButton2);
			this->groupBox3->Controls->Add(this->button2);
			this->groupBox3->Location = System::Drawing::Point(8, 389);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(491, 227);
			this->groupBox3->TabIndex = 2;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Выбор действия";
			this->groupBox3->Enter += gcnew System::EventHandler(this, &MyForm::groupBox3_Enter);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(500, 628);
			this->Controls->Add(this->label21);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Name = L"MyForm";
			this->Text = L"Конвертер 3.F.45";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void radioButton1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		button1->Enabled = true;
	}
	private: System::Void radioButton2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		button1->Enabled = true;
	}
	private: System::Void textBox13_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void groupBox3_Enter(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}