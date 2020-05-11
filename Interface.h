#pragma once

#include <vector>
#include <map>
#include <time.h>
#include <Windows.h>
#include "vertex.h"
#include "truck.h"
#include "AntsAlgorithm.h"
#include <conio.h>
#include "ReadData.h"

namespace AntsColonyUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ Interface
	/// </summary>
	public ref class Interface : public System::Windows::Forms::Form
	{
	public:
		Interface(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~Interface()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ TextBoxFilename;
	protected:
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ ButtonOpenFile;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::DataGridView^ TablePheromones;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::DataGridView^ TableDataset;
	private: System::Windows::Forms::PictureBox^ Graph;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ ZoomIn;
	private: System::Windows::Forms::Button^ ZoomOut;

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->TextBoxFilename = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->ButtonOpenFile = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->TablePheromones = (gcnew System::Windows::Forms::DataGridView());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->TableDataset = (gcnew System::Windows::Forms::DataGridView());
			this->Graph = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->ZoomIn = (gcnew System::Windows::Forms::Button());
			this->ZoomOut = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TablePheromones))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TableDataset))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Graph))->BeginInit();
			this->SuspendLayout();
			// 
			// TextBoxFilename
			// 
			this->TextBoxFilename->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->TextBoxFilename->Location = System::Drawing::Point(475, 75);
			this->TextBoxFilename->Multiline = true;
			this->TextBoxFilename->Name = L"TextBoxFilename";
			this->TextBoxFilename->Size = System::Drawing::Size(225, 40);
			this->TextBoxFilename->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(471, 52);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(229, 20);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Enter the name of file with data";
			// 
			// ButtonOpenFile
			// 
			this->ButtonOpenFile->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->ButtonOpenFile->Location = System::Drawing::Point(517, 121);
			this->ButtonOpenFile->Name = L"ButtonOpenFile";
			this->ButtonOpenFile->Size = System::Drawing::Size(147, 40);
			this->ButtonOpenFile->TabIndex = 2;
			this->ButtonOpenFile->Text = L"Open file";
			this->ButtonOpenFile->UseVisualStyleBackColor = true;
			this->ButtonOpenFile->Click += gcnew System::EventHandler(this, &Interface::ButtonOpenFile_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(141, 24);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(133, 25);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Pheromones";
			// 
			// TablePheromones
			// 
			this->TablePheromones->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->TablePheromones->Location = System::Drawing::Point(24, 52);
			this->TablePheromones->Name = L"TablePheromones";
			this->TablePheromones->Size = System::Drawing::Size(379, 682);
			this->TablePheromones->TabIndex = 4;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(543, 183);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(86, 25);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Dataset";
			// 
			// TableDataset
			// 
			this->TableDataset->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->TableDataset->Location = System::Drawing::Point(440, 211);
			this->TableDataset->Name = L"TableDataset";
			this->TableDataset->Size = System::Drawing::Size(297, 523);
			this->TableDataset->TabIndex = 6;
			// 
			// Graph
			// 
			this->Graph->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->Graph->Location = System::Drawing::Point(777, 52);
			this->Graph->Name = L"Graph";
			this->Graph->Size = System::Drawing::Size(616, 630);
			this->Graph->TabIndex = 7;
			this->Graph->TabStop = false;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(717, 143);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(45, 40);
			this->button1->TabIndex = 8;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Interface::button1_Click);
			// 
			// ZoomIn
			// 
			this->ZoomIn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 21.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->ZoomIn->Location = System::Drawing::Point(1042, 688);
			this->ZoomIn->Name = L"ZoomIn";
			this->ZoomIn->Size = System::Drawing::Size(46, 45);
			this->ZoomIn->TabIndex = 9;
			this->ZoomIn->Text = L"+";
			this->ZoomIn->UseVisualStyleBackColor = true;
			this->ZoomIn->Click += gcnew System::EventHandler(this, &Interface::ZoomIn_Click);
			// 
			// ZoomOut
			// 
			this->ZoomOut->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 21.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->ZoomOut->Location = System::Drawing::Point(1114, 689);
			this->ZoomOut->Name = L"ZoomOut";
			this->ZoomOut->Size = System::Drawing::Size(46, 45);
			this->ZoomOut->TabIndex = 10;
			this->ZoomOut->Text = L"-";
			this->ZoomOut->UseVisualStyleBackColor = true;
			this->ZoomOut->Click += gcnew System::EventHandler(this, &Interface::ZoomOut_Click);
			// 
			// Interface
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1405, 746);
			this->Controls->Add(this->ZoomOut);
			this->Controls->Add(this->ZoomIn);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->Graph);
			this->Controls->Add(this->TableDataset);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->TablePheromones);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->ButtonOpenFile);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->TextBoxFilename);
			this->Name = L"Interface";
			this->Text = L"Interface";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TablePheromones))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TableDataset))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Graph))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ButtonOpenFile_Click(System::Object^ sender, System::EventArgs^ e);
	private: void FillPheromonesTable(vector<VERTEX*> vertexes);
	private: void FillDatasetTable(vector<VERTEX*> vertexes);
	private: void DrawGraph(vector<VERTEX*> vertexes);
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void ZoomIn_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void ZoomOut_Click(System::Object^ sender, System::EventArgs^ e);
};
}
