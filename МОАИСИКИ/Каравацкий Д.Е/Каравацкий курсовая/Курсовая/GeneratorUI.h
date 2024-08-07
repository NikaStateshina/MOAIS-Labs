#pragma once
#include "Generator.h";
#include "Test.h"
#include <msclr\marshal_cppstd.h>


namespace SequenceGenerator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;


	/// <summary>
	/// Сводка для Generator
	/// </summary>
	public ref class GeneratorUI : public System::Windows::Forms::Form
	{
	public:
		GeneratorUI(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~GeneratorUI()
		{
			if (components)
			{
				delete components;
			}
		}



	private: System::Windows::Forms::Button^ GenerateButton;
	private: System::Windows::Forms::CheckBox^ UpSeqCheckBox;
	private: System::Windows::Forms::CheckBox^ DownSeqCheckBox;
	private: System::Windows::Forms::CheckBox^ Medof3SeqCheckBox;
	private: System::Windows::Forms::CheckBox^ RandSeqCheckBox;





	private: System::Windows::Forms::TextBox^ SequnceLenghtTextBox;
	private: System::Windows::Forms::TextBox^ SequenceCountTextBox;


	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TabControl^ tabControl1;
	private: System::Windows::Forms::TabPage^ tabPage1;
	private: System::Windows::Forms::TabPage^ tabPage2;

	private:
		bool UpSeqBox = false, DownSeqBox = false, Med3Box = false, RandBox = false;
		int seqLen = 10;
		int amt = 1;
		const String^ file = "";
		const String^ dir = "";


	private: System::Windows::Forms::Button^ ChooseFileButton;
	private: System::Windows::Forms::Button^ TestButton;
	private: System::Windows::Forms::Button^ ChooseDirButton;






	protected:

	protected:



	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->GenerateButton = (gcnew System::Windows::Forms::Button());
			this->UpSeqCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->DownSeqCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->Medof3SeqCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->RandSeqCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->SequnceLenghtTextBox = (gcnew System::Windows::Forms::TextBox());
			this->SequenceCountTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->ChooseDirButton = (gcnew System::Windows::Forms::Button());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->TestButton = (gcnew System::Windows::Forms::Button());
			this->ChooseFileButton = (gcnew System::Windows::Forms::Button());
			this->tabControl1->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->SuspendLayout();
			// 
			// GenerateButton
			// 
			this->GenerateButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->GenerateButton->Location = System::Drawing::Point(9, 144);
			this->GenerateButton->Name = L"GenerateButton";
			this->GenerateButton->Size = System::Drawing::Size(189, 58);
			this->GenerateButton->TabIndex = 5;
			this->GenerateButton->Text = L"Генерировать";
			this->GenerateButton->UseVisualStyleBackColor = true;
			this->GenerateButton->Click += gcnew System::EventHandler(this, &GeneratorUI::GenerateButton_Click);
			// 
			// UpSeqCheckBox
			// 
			this->UpSeqCheckBox->AutoSize = true;
			this->UpSeqCheckBox->Location = System::Drawing::Point(9, 42);
			this->UpSeqCheckBox->Name = L"UpSeqCheckBox";
			this->UpSeqCheckBox->Size = System::Drawing::Size(242, 20);
			this->UpSeqCheckBox->TabIndex = 1;
			this->UpSeqCheckBox->Text = L"Упорядоченная по возрастанию";
			this->UpSeqCheckBox->UseVisualStyleBackColor = true;
			this->UpSeqCheckBox->CheckedChanged += gcnew System::EventHandler(this, &GeneratorUI::UpSeqCheckBox_CheckedChanged);
			// 
			// DownSeqCheckBox
			// 
			this->DownSeqCheckBox->AutoSize = true;
			this->DownSeqCheckBox->Location = System::Drawing::Point(9, 65);
			this->DownSeqCheckBox->Name = L"DownSeqCheckBox";
			this->DownSeqCheckBox->Size = System::Drawing::Size(221, 20);
			this->DownSeqCheckBox->TabIndex = 2;
			this->DownSeqCheckBox->Text = L"Упорядоченная по убыванию";
			this->DownSeqCheckBox->UseVisualStyleBackColor = true;
			this->DownSeqCheckBox->CheckedChanged += gcnew System::EventHandler(this, &GeneratorUI::DownSeqCheckBox_CheckedChanged);
			// 
			// Medof3SeqCheckBox
			// 
			this->Medof3SeqCheckBox->AutoSize = true;
			this->Medof3SeqCheckBox->Location = System::Drawing::Point(9, 88);
			this->Medof3SeqCheckBox->Name = L"Medof3SeqCheckBox";
			this->Medof3SeqCheckBox->Size = System::Drawing::Size(127, 20);
			this->Medof3SeqCheckBox->TabIndex = 3;
			this->Medof3SeqCheckBox->Text = L"Медиана из 3-х";
			this->Medof3SeqCheckBox->UseVisualStyleBackColor = true;
			this->Medof3SeqCheckBox->CheckedChanged += gcnew System::EventHandler(this, &GeneratorUI::Medof3SeqCheckBox_CheckedChanged);
			// 
			// RandSeqCheckBox
			// 
			this->RandSeqCheckBox->AutoSize = true;
			this->RandSeqCheckBox->Location = System::Drawing::Point(9, 111);
			this->RandSeqCheckBox->Name = L"RandSeqCheckBox";
			this->RandSeqCheckBox->Size = System::Drawing::Size(102, 20);
			this->RandSeqCheckBox->TabIndex = 4;
			this->RandSeqCheckBox->Text = L"Рандомная";
			this->RandSeqCheckBox->UseVisualStyleBackColor = true;
			this->RandSeqCheckBox->CheckedChanged += gcnew System::EventHandler(this, &GeneratorUI::RandSeqCheckBox_CheckedChanged);
			// 
			// SequnceLenghtTextBox
			// 
			this->SequnceLenghtTextBox->Cursor = System::Windows::Forms::Cursors::Default;
			this->SequnceLenghtTextBox->Location = System::Drawing::Point(237, 39);
			this->SequnceLenghtTextBox->MaxLength = 7;
			this->SequnceLenghtTextBox->Name = L"SequnceLenghtTextBox";
			this->SequnceLenghtTextBox->Size = System::Drawing::Size(243, 22);
			this->SequnceLenghtTextBox->TabIndex = 6;
			this->SequnceLenghtTextBox->Text = L"10";
			this->SequnceLenghtTextBox->TextChanged += gcnew System::EventHandler(this, &GeneratorUI::SequnceLenghtTextBox_TextChanged);
			this->SequnceLenghtTextBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &GeneratorUI::SequnceLenghtTextBox_KeyPress);
			// 
			// SequenceCountTextBox
			// 
			this->SequenceCountTextBox->Location = System::Drawing::Point(237, 88);
			this->SequenceCountTextBox->MaxLength = 1;
			this->SequenceCountTextBox->Name = L"SequenceCountTextBox";
			this->SequenceCountTextBox->Size = System::Drawing::Size(27, 22);
			this->SequenceCountTextBox->TabIndex = 7;
			this->SequenceCountTextBox->Text = L"1";
			this->SequenceCountTextBox->TextChanged += gcnew System::EventHandler(this, &GeneratorUI::SequenceCountTextBox_TextChanged);
			this->SequenceCountTextBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &GeneratorUI::SequenceCountTextBox_KeyPress);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(234, 23);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(253, 16);
			this->label1->TabIndex = 8;
			this->label1->Text = L"Кол-во элементов: (10 <= N <= 1000000)";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(234, 72);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(388, 16);
			this->label2->TabIndex = 9;
			this->label2->Text = L"Кол-во последовательностей выбранного типа: (0 < N < 10)";
			this->label2->Click += gcnew System::EventHandler(this, &GeneratorUI::label2_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(7, 17);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(177, 16);
			this->label3->TabIndex = 10;
			this->label3->Text = L"Тип последовательности:";
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Location = System::Drawing::Point(1, 0);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->Padding = System::Drawing::Point(0, 0);
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(614, 376);
			this->tabControl1->TabIndex = 11;
			// 
			// tabPage1
			// 
			this->tabPage1->BackColor = System::Drawing::SystemColors::Window;
			this->tabPage1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->tabPage1->Controls->Add(this->ChooseDirButton);
			this->tabPage1->Controls->Add(this->GenerateButton);
			this->tabPage1->Controls->Add(this->label1);
			this->tabPage1->Controls->Add(this->label2);
			this->tabPage1->Controls->Add(this->SequnceLenghtTextBox);
			this->tabPage1->Controls->Add(this->SequenceCountTextBox);
			this->tabPage1->Controls->Add(this->label3);
			this->tabPage1->Controls->Add(this->UpSeqCheckBox);
			this->tabPage1->Controls->Add(this->DownSeqCheckBox);
			this->tabPage1->Controls->Add(this->Medof3SeqCheckBox);
			this->tabPage1->Controls->Add(this->RandSeqCheckBox);
			this->tabPage1->Location = System::Drawing::Point(4, 25);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(606, 347);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Генератор";
			// 
			// ChooseDirButton
			// 
			this->ChooseDirButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->ChooseDirButton->Location = System::Drawing::Point(10, 208);
			this->ChooseDirButton->Name = L"ChooseDirButton";
			this->ChooseDirButton->Size = System::Drawing::Size(188, 58);
			this->ChooseDirButton->TabIndex = 11;
			this->ChooseDirButton->Text = L"Выбрать папку";
			this->ChooseDirButton->UseVisualStyleBackColor = true;
			this->ChooseDirButton->Click += gcnew System::EventHandler(this, &GeneratorUI::ChooseDirButton_Click);
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->TestButton);
			this->tabPage2->Controls->Add(this->ChooseFileButton);
			this->tabPage2->Location = System::Drawing::Point(4, 25);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(606, 347);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Тестирование";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// TestButton
			// 
			this->TestButton->Location = System::Drawing::Point(7, 70);
			this->TestButton->Name = L"TestButton";
			this->TestButton->Size = System::Drawing::Size(189, 58);
			this->TestButton->TabIndex = 1;
			this->TestButton->Text = L"Тест";
			this->TestButton->UseVisualStyleBackColor = true;
			this->TestButton->Click += gcnew System::EventHandler(this, &GeneratorUI::TestButton_Click);
			// 
			// ChooseFileButton
			// 
			this->ChooseFileButton->Location = System::Drawing::Point(7, 6);
			this->ChooseFileButton->Name = L"ChooseFileButton";
			this->ChooseFileButton->Size = System::Drawing::Size(189, 58);
			this->ChooseFileButton->TabIndex = 0;
			this->ChooseFileButton->Text = L"Выбрать файл";
			this->ChooseFileButton->UseVisualStyleBackColor = true;
			this->ChooseFileButton->Click += gcnew System::EventHandler(this, &GeneratorUI::ChooseFileButton_Click);
			// 
			// GeneratorUI
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->ClientSize = System::Drawing::Size(584, 341);
			this->Controls->Add(this->tabControl1);
			this->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"GeneratorUI";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Sequence Generator";
			this->tabControl1->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
private: System::Void ToolBar_ItemClicked(System::Object^ sender, System::Windows::Forms::ToolStripItemClickedEventArgs^ e) {
}
private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void textBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void UpSeqCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {

	CheckBox^ activeCheckBox = safe_cast<CheckBox^>(sender);
	if (activeCheckBox->Checked)
	{
		UpSeqBox = true;
	}
	else {
		UpSeqBox = false;
	}
}
private: System::Void DownSeqCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	CheckBox^ activeCheckBox = safe_cast<CheckBox^>(sender);
	if (activeCheckBox->Checked)
	{
		DownSeqBox = true;
	}
	else {
		DownSeqBox = false;
	}
}
private: System::Void Medof3SeqCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	CheckBox^ activeCheckBox = safe_cast<CheckBox^>(sender);
	if (activeCheckBox->Checked)
	{
		Med3Box = true;
	}
	else {
		Med3Box = false;
	}
}
private: System::Void RandSeqCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	CheckBox^ activeCheckBox = safe_cast<CheckBox^>(sender);
	if (activeCheckBox->Checked)
	{
		RandBox = true;
	}
	else {
		RandBox = false;
	}
}
private: System::Void SequnceLenghtTextBox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	if (!(e->KeyChar == 8 || (e->KeyChar >= 48 && e->KeyChar <= 57)))
	{
		e->Handled = true;
	}
}
private: System::Void SequnceLenghtTextBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	String^ textFromTextBox = SequnceLenghtTextBox->Text;
	if (textFromTextBox != "") {
		seqLen = System::Convert::ToInt32(textFromTextBox);
	}
	else {
		seqLen = 0;
	}
	/*if (seqLen > 1000000) {
		seqLen = 1000000;
		textFromTextBox = System::Convert::ToString(seqLen);
		SequnceLenghtTextBox->Text = textFromTextBox;
	}*/
}
private: System::Void SequenceCountTextBox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	if (!(e->KeyChar == 8 || (e->KeyChar >= 48 && e->KeyChar <= 57)))
	{
		e->Handled = true;
	}
}


private: System::Void SequenceCountTextBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	String^ textFromTextBox = SequenceCountTextBox->Text;
	if (textFromTextBox != "") {
		amt = System::Convert::ToInt32(textFromTextBox);
	}
	else {
		amt = 0;
	}
}
private: System::Void GenerateButton_Click(System::Object^ sender, System::EventArgs^ e) {
	
	if (!UpSeqBox && !DownSeqBox && !Med3Box && !RandBox) {
		MessageBox::Show(this, "Не выбрано ни одного типа генерируемой последовательности", "", MessageBoxButtons::OK, MessageBoxIcon::Information);
		return;
	}
	if (seqLen > 1000000) {
		MessageBox::Show(this,"Длинная последовательности > 1000000, введите число в диапозоне: 10...1000000", "Ошибка:", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
	if (seqLen < 10) {
		MessageBox::Show(this, "Длинная последовательности < 10, введите число в диапозоне: 10...1000000", "Ошибка:", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
	if (amt == 0) {
		MessageBox::Show(this, "Количество генерируеммых последовательностей = 0, введите число в диапозоне: 1..9", "Ошибка:", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	if (dir == "") {
		MessageBox::Show(this, "Не выбрана дирректория для генерации файлов", "Ошибка:", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
	std::string _dir = msclr::interop::marshal_as<std::string>(const_cast<System::String^>(dir));

	for (int i = 0; i < amt; i++) {

		if (UpSeqBox) {
			upSortedSequence(seqLen, _dir);
		}
		if (DownSeqBox) {
			downSortedSequence(seqLen, _dir);
		}
		if (Med3Box) {
			qsortKillSeqGen(seqLen, _dir);
		}
		if (RandBox) {
			randSequence(seqLen, _dir);
		}
	}
	MessageBox::Show(this, "Последовательности успешно сгенерированны", "", MessageBoxButtons::OK, MessageBoxIcon::Information);
}
private: System::Void ChooseFileButton_Click(System::Object^ sender, System::EventArgs^ e) {
	OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
	openFileDialog->InitialDirectory = "c:\\";
	openFileDialog->Filter = "All files (*.txt)|*.txt";

	if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		file = openFileDialog->FileName;
	}
}
private: System::Void TestButton_Click(System::Object^ sender, System::EventArgs^ e) {
	if (file == "") {
		MessageBox::Show(this, "Файл не выбран", "Ошибка!", MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}
	float time1 = 0, time2 = 0;
	unsigned comp1 = 0, comp2 = 0, assignment1 = 0, assignment2 = 0;

	std::string unmanaged = msclr::interop::marshal_as<std::string>(const_cast<System::String^>(file));

	testSort(time1, time2, comp1, comp2, assignment1, assignment2, unmanaged);

	MessageBox::Show(this, "QuickSort время: "+ System::Convert::ToString(time1) + "\n QuickSort сранения: " 
		+ System::Convert::ToString(comp1) + "\n QuickSort перестановки: " + System::Convert::ToString(assignment1) + 
		"\nIntroSort время: " + System::Convert::ToString(time2) + "\n IntroSort сранения: "
		+ System::Convert::ToString(comp2) + "\n IntroSort перестановки: " + System::Convert::ToString(assignment2), 
		"Результат:", MessageBoxButtons::OK, MessageBoxIcon::Information);
}
private: System::Void ChooseDirButton_Click(System::Object^ sender, System::EventArgs^ e) {
	FolderBrowserDialog^ folderBrowserDialog = gcnew FolderBrowserDialog();

	if (folderBrowserDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		dir = folderBrowserDialog->SelectedPath;
	}
}
};
}
