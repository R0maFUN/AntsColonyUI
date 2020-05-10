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
	Graphics^ im = Graph->CreateGraphics();

	Color^ col = gcnew Color();

	Pen^ penDot = gcnew Pen(col->Red);
	penDot->Width = 5;

	Pen^ penLine = gcnew Pen(col->Black);
	penLine->Width = 3;

	for (auto vert : vertexes)
	{
		int x1 = vert->GetX()*5 ;
		int y1 = vert->GetY() * 5 ;
		
		im->DrawEllipse(penDot, x1, y1, 5, 5);

		for (auto target : *vert->GetPheromones())
		{
			int x2 = target.first->GetX() * 5 ;
			int y2 = target.first->GetY() * 5 ;

			im->DrawLine(penLine, x1, y1, x2, y2);

		}
	}

}


System::Void AntsColonyUI::Interface::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	Graphics^ g = Graph->CreateGraphics();
	Pen^ p = gcnew Pen(Color::Blue, 1.0f);
	Point pt1 = Point(10, 10);
	Point pt2 = Point(100, 100);
	g->DrawLine(p, pt1, pt2);
	return System::Void();
}
