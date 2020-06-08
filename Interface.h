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
	private: System::Windows::Forms::Button^ MakeSolutionButton;
	private: System::Windows::Forms::Button^ ResetDataButton;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TextBox^ DistanceTextBox;
	private: System::Windows::Forms::TextBox^ BestDistance;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Button^ StopLoopButton;
	private: System::Windows::Forms::Button^ StartLoopButton;
	private: System::Windows::Forms::Button^ OpenFileDia;

	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::Button^ ShowSGraph;
	private: System::Windows::Forms::Button^ ShowPGraph;
	private: System::Windows::Forms::Button^ ShowBSolution;


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
			this->MakeSolutionButton = (gcnew System::Windows::Forms::Button());
			this->ResetDataButton = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->DistanceTextBox = (gcnew System::Windows::Forms::TextBox());
			this->BestDistance = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->StopLoopButton = (gcnew System::Windows::Forms::Button());
			this->StartLoopButton = (gcnew System::Windows::Forms::Button());
			this->OpenFileDia = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->ShowSGraph = (gcnew System::Windows::Forms::Button());
			this->ShowPGraph = (gcnew System::Windows::Forms::Button());
			this->ShowBSolution = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TablePheromones))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->TableDataset))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Graph))->BeginInit();
			this->SuspendLayout();
			// 
			// TextBoxFilename
			// 
			this->TextBoxFilename->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->TextBoxFilename->Location = System::Drawing::Point(1116, 52);
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
			this->label1->Location = System::Drawing::Point(1112, 29);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(229, 20);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Enter the name of file with data";
			// 
			// ButtonOpenFile
			// 
			this->ButtonOpenFile->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->ButtonOpenFile->Location = System::Drawing::Point(1158, 98);
			this->ButtonOpenFile->Name = L"ButtonOpenFile";
			this->ButtonOpenFile->Size = System::Drawing::Size(147, 40);
			this->ButtonOpenFile->TabIndex = 2;
			this->ButtonOpenFile->Text = L"Open C101.txt";
			this->ButtonOpenFile->UseVisualStyleBackColor = true;
			this->ButtonOpenFile->Click += gcnew System::EventHandler(this, &Interface::ButtonOpenFile_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(138, 19);
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
			this->TablePheromones->Size = System::Drawing::Size(367, 366);
			this->TablePheromones->TabIndex = 4;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(165, 431);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(86, 25);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Dataset";
			// 
			// TableDataset
			// 
			this->TableDataset->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->TableDataset->Location = System::Drawing::Point(24, 473);
			this->TableDataset->Name = L"TableDataset";
			this->TableDataset->Size = System::Drawing::Size(367, 301);
			this->TableDataset->TabIndex = 6;
			// 
			// Graph
			// 
			this->Graph->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->Graph->Location = System::Drawing::Point(422, 52);
			this->Graph->Name = L"Graph";
			this->Graph->Size = System::Drawing::Size(638, 630);
			this->Graph->TabIndex = 7;
			this->Graph->TabStop = false;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(1348, 157);
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
			this->ZoomIn->Location = System::Drawing::Point(672, 705);
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
			this->ZoomOut->Location = System::Drawing::Point(746, 705);
			this->ZoomOut->Name = L"ZoomOut";
			this->ZoomOut->Size = System::Drawing::Size(46, 45);
			this->ZoomOut->TabIndex = 10;
			this->ZoomOut->Text = L"-";
			this->ZoomOut->UseVisualStyleBackColor = true;
			this->ZoomOut->Click += gcnew System::EventHandler(this, &Interface::ZoomOut_Click);
			// 
			// MakeSolutionButton
			// 
			this->MakeSolutionButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->MakeSolutionButton->Location = System::Drawing::Point(1158, 232);
			this->MakeSolutionButton->Name = L"MakeSolutionButton";
			this->MakeSolutionButton->Size = System::Drawing::Size(147, 40);
			this->MakeSolutionButton->TabIndex = 11;
			this->MakeSolutionButton->Text = L"Make solution";
			this->MakeSolutionButton->UseVisualStyleBackColor = true;
			this->MakeSolutionButton->Click += gcnew System::EventHandler(this, &Interface::MakeSolutionButton_Click);
			// 
			// ResetDataButton
			// 
			this->ResetDataButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->ResetDataButton->Location = System::Drawing::Point(1158, 278);
			this->ResetDataButton->Name = L"ResetDataButton";
			this->ResetDataButton->Size = System::Drawing::Size(147, 40);
			this->ResetDataButton->TabIndex = 12;
			this->ResetDataButton->Text = L"Reset data";
			this->ResetDataButton->UseVisualStyleBackColor = true;
			this->ResetDataButton->Click += gcnew System::EventHandler(this, &Interface::ResetDataButton_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(428, 21);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(76, 20);
			this->label4->TabIndex = 13;
			this->label4->Text = L"Distance:";
			// 
			// DistanceTextBox
			// 
			this->DistanceTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->DistanceTextBox->Location = System::Drawing::Point(501, 21);
			this->DistanceTextBox->Multiline = true;
			this->DistanceTextBox->Name = L"DistanceTextBox";
			this->DistanceTextBox->Size = System::Drawing::Size(168, 22);
			this->DistanceTextBox->TabIndex = 14;
			// 
			// BestDistance
			// 
			this->BestDistance->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->BestDistance->Location = System::Drawing::Point(784, 21);
			this->BestDistance->Multiline = true;
			this->BestDistance->Name = L"BestDistance";
			this->BestDistance->Size = System::Drawing::Size(168, 22);
			this->BestDistance->TabIndex = 16;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(742, 22);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(46, 20);
			this->label5->TabIndex = 15;
			this->label5->Text = L"Best:";
			// 
			// StopLoopButton
			// 
			this->StopLoopButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->StopLoopButton->Location = System::Drawing::Point(1158, 370);
			this->StopLoopButton->Name = L"StopLoopButton";
			this->StopLoopButton->Size = System::Drawing::Size(147, 40);
			this->StopLoopButton->TabIndex = 18;
			this->StopLoopButton->Text = L"Stop loop";
			this->StopLoopButton->UseVisualStyleBackColor = true;
			this->StopLoopButton->Click += gcnew System::EventHandler(this, &Interface::StopLoopButton_Click);
			// 
			// StartLoopButton
			// 
			this->StartLoopButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->StartLoopButton->Location = System::Drawing::Point(1158, 324);
			this->StartLoopButton->Name = L"StartLoopButton";
			this->StartLoopButton->Size = System::Drawing::Size(147, 40);
			this->StartLoopButton->TabIndex = 17;
			this->StartLoopButton->Text = L"Start loop";
			this->StartLoopButton->UseVisualStyleBackColor = true;
			this->StartLoopButton->Click += gcnew System::EventHandler(this, &Interface::StartLoopButton_Click);
			// 
			// OpenFileDia
			// 
			this->OpenFileDia->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->OpenFileDia->Location = System::Drawing::Point(1158, 157);
			this->OpenFileDia->Name = L"OpenFileDia";
			this->OpenFileDia->Size = System::Drawing::Size(147, 40);
			this->OpenFileDia->TabIndex = 19;
			this->OpenFileDia->Text = L"Open File";
			this->OpenFileDia->UseVisualStyleBackColor = true;
			this->OpenFileDia->Click += gcnew System::EventHandler(this, &Interface::OpenFileDia_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Interface::openFileDialog1_FileOk);
			// 
			// ShowSGraph
			// 
			this->ShowSGraph->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->ShowSGraph->Location = System::Drawing::Point(1145, 489);
			this->ShowSGraph->Name = L"ShowSGraph";
			this->ShowSGraph->Size = System::Drawing::Size(173, 49);
			this->ShowSGraph->TabIndex = 20;
			this->ShowSGraph->Text = L"Show Solution   Graph";
			this->ShowSGraph->UseVisualStyleBackColor = true;
			this->ShowSGraph->Click += gcnew System::EventHandler(this, &Interface::ShowSGraph_Click);
			// 
			// ShowPGraph
			// 
			this->ShowPGraph->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->ShowPGraph->Location = System::Drawing::Point(1145, 431);
			this->ShowPGraph->Name = L"ShowPGraph";
			this->ShowPGraph->Size = System::Drawing::Size(173, 52);
			this->ShowPGraph->TabIndex = 21;
			this->ShowPGraph->Text = L"Show Phermones Graph";
			this->ShowPGraph->UseVisualStyleBackColor = true;
			this->ShowPGraph->Click += gcnew System::EventHandler(this, &Interface::ShowPGraph_Click);
			// 
			// ShowBSolution
			// 
			this->ShowBSolution->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->ShowBSolution->Location = System::Drawing::Point(1145, 544);
			this->ShowBSolution->Name = L"ShowBSolution";
			this->ShowBSolution->Size = System::Drawing::Size(173, 49);
			this->ShowBSolution->TabIndex = 22;
			this->ShowBSolution->Text = L"Show the best solution";
			this->ShowBSolution->UseVisualStyleBackColor = true;
			this->ShowBSolution->Click += gcnew System::EventHandler(this, &Interface::ShowBSolution_Click);
			// 
			// Interface
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1405, 786);
			this->Controls->Add(this->ShowBSolution);
			this->Controls->Add(this->ShowPGraph);
			this->Controls->Add(this->ShowSGraph);
			this->Controls->Add(this->OpenFileDia);
			this->Controls->Add(this->StopLoopButton);
			this->Controls->Add(this->StartLoopButton);
			this->Controls->Add(this->BestDistance);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->DistanceTextBox);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->ResetDataButton);
			this->Controls->Add(this->MakeSolutionButton);
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
	private:   int ZoomExp = 1;
			   int MoveGraphX = 0;
			   int MoveGraphY = 0;
			   bool isMousePressedOnGraph = false;
			   Point p1, p2;
			   
	private: System::Void ButtonOpenFile_Click(System::Object^ sender, System::EventArgs^ e);
	private: void FillPheromonesTable(vector<VERTEX*> vertexes);
	private: void FillDatasetTable(vector<VERTEX*> vertexes);
	public: void DrawGraph(vector<VERTEX*> vertexes);
	public: void DrawWay();
	public: void DrawBestWay();
	public: void DrawBestWayEdges();
	public: void DrawEdge(int num);
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void ZoomIn_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void ZoomOut_Click(System::Object^ sender, System::EventArgs^ e);

private: System::Void MakeSolutionButton_Click(System::Object^ sender, System::EventArgs^ e);

private: System::Void ResetDataButton_Click(System::Object^ sender, System::EventArgs^ e);
	   private: void MakeSolution2(vector<VERTEX*>& vertexes, vector<TRUCK*>& trucks, double vaporizeSpeed, double PheromoneAdded, double& totalDistance);

private: System::Void StartLoopButton_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void StopLoopButton_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void openFileDialog1_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e);

private: System::Void OpenFileDia_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void ShowPGraph_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void ShowSGraph_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void ShowBSolution_Click(System::Object^ sender, System::EventArgs^ e);
};
}
