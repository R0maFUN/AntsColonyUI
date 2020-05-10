#include "Interface.h"

using namespace System;
using namespace System::Windows::Forms;

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
	TablePheromones->RowCount = vertexes.size() * vertexes.size();
	TablePheromones->ColumnCount = 3;
	
	// Drawing the phermones table
	FillPheromonesTable(vertexes);

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
