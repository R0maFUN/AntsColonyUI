#include "Interface.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

u_int trucksAmount;
u_int truckCapacity;
vector<TRUCK* > trucks;

u_int vertexAmount;
u_int vertexCapacity;
double x, y;
vector<VERTEX*> vertexes;
int ZoomExp = 1;

[STAThreadAttribute]
int main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	AntsColonyUI::Interface form;
	Application::Run(% form);

	return 0;
}


System::Void AntsColonyUI::Interface::ButtonOpenFile_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (TextBoxFilename->Text == "")
	{
		MessageBox::Show("The filename text box is empty!", "Error!");
		return;
	}
	// Getting filename from text box
	string filename;
	convert_String_To_string(TextBoxFilename->Text, filename);

	// Reading data from the file
	ReadData(filename, vertexes, truckCapacity, trucksAmount);

	// Initialising dataset
	Initialize(vertexes, trucks, truckCapacity, trucksAmount);
	
	// Creating the pheromones table
	TablePheromones->RowCount = vertexes.size() * (vertexes.size() - 1) / 2;
	TablePheromones->ColumnCount = 3;
	
	// Creating the dataset table
	TableDataset->RowCount = vertexes.size();
	TableDataset->ColumnCount = 5;

	// Drawing the phermones table
	FillPheromonesTable(vertexes);
	FillDatasetTable(vertexes);

	TableDataset->AutoResizeColumns();

	// Drawing Graph
	DrawGraph(vertexes);

	return System::Void();
}

void AntsColonyUI::Interface::FillPheromonesTable(vector<VERTEX*> vertexes)
{
	TablePheromones->Columns[0]->HeaderCell->Value = "FROM";
	TablePheromones->Columns[1]->HeaderCell->Value = "TO";
	TablePheromones->Columns[2]->HeaderCell->Value = "Pheromone";
	int k = 0;
	for (auto i : vertexes)
		for (auto j : *i->GetPheromones())
		{
			TablePheromones->Rows[k]->Cells[0]->Value = i->GetID();
			TablePheromones->Rows[k]->Cells[1]->Value = j.first->GetID();
			TablePheromones->Rows[k]->Cells[2]->Value = j.second;
			k++;
		}
}

void AntsColonyUI::Interface::FillDatasetTable(vector<VERTEX*> vertexes)
{
	TableDataset->Columns[0]->HeaderCell->Value = "ID";
	TableDataset->Columns[1]->HeaderCell->Value = "X";
	TableDataset->Columns[2]->HeaderCell->Value = "Y";
	TableDataset->Columns[3]->HeaderCell->Value = "Type";
	TableDataset->Columns[4]->HeaderCell->Value = "Filled Capacity";
	int k = 0;
	for (auto i : vertexes)
	{
		TableDataset->Rows[k]->Cells[0]->Value = i->GetID();
		TableDataset->Rows[k]->Cells[1]->Value = i->GetX();
		TableDataset->Rows[k]->Cells[2]->Value = i->GetY();
		TableDataset->Rows[k]->Cells[3]->Value = Convert::ToString( i->GetType()) ;
		TableDataset->Rows[k]->Cells[4]->Value = i->GetFilledCapacity();
		k++;
	}
}

void AntsColonyUI::Interface::DrawGraph(vector<VERTEX*> vertexes)
{
	//Graphics^ im = Graph->CreateGraphics();
	Bitmap^ Img = gcnew Bitmap(Graph->Width, Graph->Height);
	Graph->Image = Img;
	Graphics^ im = Graphics::FromImage(Img);

	Color^ col = gcnew Color();

	Pen^ penDot = gcnew Pen(col->Red);
	penDot->Width = 5;

	Pen^ penLine = gcnew Pen(col->Black);
	penLine->Width = 3;

	for (auto vert : vertexes)
	{
		int x1 = vert->GetX()*ZoomExp;
		int y1 = vert->GetY() *ZoomExp ;
		
		im->DrawEllipse(penDot, x1, y1, 5, 5);

		for (auto target : *vert->GetPheromones())
		{
			int x2 = target.first->GetX() * ZoomExp ;
			int y2 = target.first->GetY() * ZoomExp ;

			im->DrawLine(penLine, x1, y1, x2, y2);

		}
	}
	delete im;
}


System::Void AntsColonyUI::Interface::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	Bitmap^ Img = gcnew Bitmap(Graph->Width , Graph->Height);
	Graph->Image = Img;
	Graphics^ g = Graphics::FromImage(Img);
	//Graphics^ g = Graph->CreateGraphics();
	//Color a = Color::FromArgb(0, 255, 0, 0);
	//Pen^ p = gcnew Pen(a, 20.0f);
	for (int y = 1; y < 15; ++y)
	{
		Color a = Color::FromArgb(y*10, 255, 0, 0);
		Pen^ p = gcnew Pen(a, 7.0f);
		Point pt1 = Point(10, y*10);
		Point pt2 = Point(100, y*10);
		g->DrawLine(p, pt1, pt2);
	}
	
	return System::Void();
}

System::Void AntsColonyUI::Interface::ZoomIn_Click(System::Object^ sender, System::EventArgs^ e)
{
	ZoomExp++;
	DrawGraph(vertexes);
	/*Graph->SizeMode = PictureBoxSizeMode::CenterImage;
	Graph->Height += 50;
	Graph->Width += 50;
	Graph->SizeMode = PictureBoxSizeMode::Zoom;
	return System::Void();
	*/
}

System::Void AntsColonyUI::Interface::ZoomOut_Click(System::Object^ sender, System::EventArgs^ e)
{
	ZoomExp--;
	DrawGraph(vertexes);
	/*
	Graph->SizeMode = PictureBoxSizeMode::CenterImage;
	Graph->Height -= 50;
	Graph->Width -= 50;
	Graph->SizeMode = PictureBoxSizeMode::StretchImage;
	*/
	return System::Void();
}
