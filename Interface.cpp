#include "Interface.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

u_int trucksAmount;
u_int truckCapacity;
vector<TRUCK* > trucks;
vector<TRUCK* > trucksCopy;
u_int vertexAmount;
u_int vertexCapacity;
double x, y;
vector<VERTEX*> vertexes;
vector<VERTEX*> vertexesCopy;
vector<VERTEX> way;
vector<VERTEX> bestWay;

vector<EDGE> way_edges;
vector<EDGE> bestWay_edges;

double bestDistance = 999999999;

bool isLoop = false;

[STAThreadAttribute]
int main()
{
	srand(time(NULL));
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	AntsColonyUI::Interface form;
	Application::Run(% form);

	return 0;
}




System::Void AntsColonyUI::Interface::ButtonOpenFile_Click(System::Object^ sender, System::EventArgs^ e)
{
	/*if (TextBoxFilename->Text == "")
	{
		MessageBox::Show("The filename text box is empty!", "Error!");
		return;
	}*/
	// Getting filename from text box
	string filename = "C101.txt";
	//convert_String_To_string(TextBoxFilename->Text, filename);


	//if (!vertexes.empty())
		vertexes.clear();
		trucks.clear();

		// Reading data from the file
		ReadData(filename, vertexes, truckCapacity, trucksAmount);

		// Initialising dataset

		Initialize(vertexes, trucks, truckCapacity, trucksAmount);

	
	if(vertexesCopy.empty())
		transform(vertexes.begin(), vertexes.end(), back_inserter(vertexesCopy), cloneFunctor());
	if(trucksCopy.empty())
		transform(trucks.begin(), trucks.end(), back_inserter(trucksCopy), cloneFunctor());
	for (auto i : vertexesCopy)
	{
		i->SetPheromones(vertexesCopy , 1);
		i->SetDistances(vertexesCopy);
	}
	
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
		int x1 = vert->GetX()*ZoomExp + MoveGraphX;
		int y1 = vert->GetY() *ZoomExp + MoveGraphY;
		
		im->DrawEllipse(penDot, x1, y1, 10, 10);

		for (auto target : *vert->GetPheromones())
		{
			int x2 = target.first->GetX() * ZoomExp + MoveGraphX;
			int y2 = target.first->GetY() * ZoomExp + MoveGraphY;
			Color edge = Color::FromArgb(target.second * 50 > 255 ? 255 : target.second * 50, 255, 0, 0);
			penLine->Color = edge;
			im->DrawLine(penLine, x1, y1, x2, y2);

		}
	}
	delete im;
}

void AntsColonyUI::Interface::DrawWay()
{
	//Bitmap^ Img = gcnew Bitmap(Graph->Width, Graph->Height);
	//Graph->Image = Img;
	//Graphics^ im = Graphics::FromImage(Img);
	Graphics^ im = Graph->CreateGraphics();
	Color^ col = gcnew Color();

	Pen^ penDot = gcnew Pen(col->Black);
	penDot->Width = 5;

	Pen^ penLine = gcnew Pen(col->Black);
	penLine->Width = 3;

	for (int i = 0 ; i < way.size() - 1; ++i)
	{
		VERTEX vert = way[i];
		VERTEX vert2 = way[i + 1];
		int x1 = vert.GetX() * ZoomExp + MoveGraphX;
		int y1 = vert.GetY() * ZoomExp + MoveGraphY;

		im->DrawEllipse(penDot, x1, y1, 10, 10);

		int x2 = vert2.GetX() * ZoomExp + MoveGraphX;
		int y2 = vert2.GetY() * ZoomExp + MoveGraphY;

		im->DrawEllipse(penDot, x2, y2, 10, 10);

		im->DrawLine(penLine, x1, y1, x2, y2);
		Sleep(100);
	}
	delete im;
}

void AntsColonyUI::Interface::DrawBestWay()
{
	Graphics^ im = Graph->CreateGraphics();
	Color^ col = gcnew Color();

	Pen^ penDot = gcnew Pen(col->Black);
	penDot->Width = 5;

	Pen^ penLine = gcnew Pen(col->Black);
	penLine->Width = 3;

	for (int i = 0; i < bestWay.size() - 1; ++i)
	{
		VERTEX vert = bestWay[i];
		VERTEX vert2 = bestWay[i + 1];
		int x1 = vert.GetX() * ZoomExp + MoveGraphX;
		int y1 = vert.GetY() * ZoomExp + MoveGraphY;

		im->DrawEllipse(penDot, x1, y1, 10, 10);

		int x2 = vert2.GetX() * ZoomExp + MoveGraphX;
		int y2 = vert2.GetY() * ZoomExp + MoveGraphY;

		im->DrawEllipse(penDot, x2, y2, 10, 10);

		im->DrawLine(penLine, x1, y1, x2, y2);
		Sleep(100);
	}
	delete im;
}

void AntsColonyUI::Interface::DrawBestWayEdges()
{
	Graphics^ im = Graph->CreateGraphics();
	Color^ col = gcnew Color();

	Pen^ penDot = gcnew Pen(col->Black);
	penDot->Width = 5;

	Pen^ penLine = gcnew Pen(col->Black);
	penLine->Width = 3;

	for (int i = 0; i < bestWay_edges.size(); ++i)
	{
		VERTEX vert = *bestWay_edges[i].from;
		VERTEX vert2 = *bestWay_edges[i].dest;
		if (i > 0 && bestWay_edges[i].truckID != bestWay_edges[i - 1].truckID)
		{
			Color nCol = Color::FromArgb(255, rand()%255, rand() % 255, rand() % 255);
			penLine->Color = nCol;
			penDot->Color = nCol;
		}
		int x1 = vert.GetX() * ZoomExp + MoveGraphX;
		int y1 = vert.GetY() * ZoomExp + MoveGraphY;

		im->DrawEllipse(penDot, x1, y1, 10, 10);

		int x2 = vert2.GetX() * ZoomExp + MoveGraphX;
		int y2 = vert2.GetY() * ZoomExp + MoveGraphY;

		im->DrawEllipse(penDot, x2, y2, 10, 10);

		im->DrawLine(penLine, x1, y1, x2, y2);
		Sleep(100);
	}
	delete im;
}

void AntsColonyUI::Interface::DrawWayEdges()
{
	Graphics^ im = Graph->CreateGraphics();
	Color^ col = gcnew Color();

	Pen^ penDot = gcnew Pen(col->Black);
	penDot->Width = 5;

	Pen^ penLine = gcnew Pen(col->Black);
	penLine->Width = 3;

	for (int i = 0; i < way_edges.size(); ++i)
	{
		VERTEX vert = *way_edges[i].from;
		VERTEX vert2 = *way_edges[i].dest;
		if (i > 0 && way_edges[i].truckID != way_edges[i - 1].truckID)
		{
			Color nCol = Color::FromArgb(255, rand() % 255, rand() % 255, rand() % 255);
			penLine->Color = nCol;
			penDot->Color = nCol;
		}
		int x1 = vert.GetX() * ZoomExp + MoveGraphX;
		int y1 = vert.GetY() * ZoomExp + MoveGraphY;

		im->DrawEllipse(penDot, x1, y1, 10, 10);

		int x2 = vert2.GetX() * ZoomExp + MoveGraphX;
		int y2 = vert2.GetY() * ZoomExp + MoveGraphY;

		im->DrawEllipse(penDot, x2, y2, 10, 10);

		im->DrawLine(penLine, x1, y1, x2, y2);
		Sleep(100);
	}
	delete im;
}

void AntsColonyUI::Interface::DrawEdge(int num)
{
	throw gcnew System::NotImplementedException();
}


System::Void AntsColonyUI::Interface::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	Bitmap^ Img = gcnew Bitmap(Graph->Width, Graph->Height);
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
}

System::Void AntsColonyUI::Interface::ZoomOut_Click(System::Object^ sender, System::EventArgs^ e)
{
	ZoomExp--;
	DrawGraph(vertexes);
}

System::Void AntsColonyUI::Interface::MakeSolutionButton_Click(System::Object^ sender, System::EventArgs^ e)
{

		way.clear();
		double solutionDistance = 0;
		for (auto vert : vertexesCopy)
		{
			if (vert->GetType() != vertexTYPE::warehouse)
				vert->NullFilledCapacity();
		}
		trucksCopy.clear();
		transform(trucks.begin(), trucks.end(), back_inserter(trucksCopy), cloneFunctor());
		MakeSolution2(vertexesCopy, trucksCopy, 0.0008, 0, solutionDistance);
		// Drawing the phermones table
		FillPheromonesTable(vertexesCopy);
		FillDatasetTable(vertexesCopy);

		TableDataset->AutoResizeColumns();

		// Drawing Graph
		DrawGraph(vertexesCopy);

		DistanceTextBox->Text = Convert::ToString(solutionDistance);

		if (solutionDistance < bestDistance)
		{
			bestDistance = solutionDistance;
			BestDistance->Text = Convert::ToString(bestDistance);
			bestWay.clear();
			for (int j = 0; j < way.size(); ++j)
				bestWay.push_back(way[j]);
			//break;
		}
		
	return System::Void();
}

System::Void AntsColonyUI::Interface::ResetDataButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	//vertexesCopy = vertexes;
	vertexesCopy.clear();
	transform(vertexes.begin(), vertexes.end(), back_inserter(vertexesCopy), cloneFunctor());
	trucksCopy.clear();
	transform(trucks.begin(), trucks.end(), back_inserter(trucksCopy), cloneFunctor());
	for (auto i : vertexesCopy)
	{
		i->SetPheromones(vertexesCopy, 1);
		i->SetDistances(vertexesCopy);
	}
	FillPheromonesTable(vertexesCopy);
	FillDatasetTable(vertexesCopy);
	return System::Void();
}

void AntsColonyUI::Interface::MakeSolution2(vector<VERTEX*>& vertexes, vector<TRUCK*>& trucks, double vaporizeSpeed, double PheromoneAdded, double& totalDistance)
{
	vector<VERTEX*> vertexesCopy = vertexes;
	way.clear();
	way_edges.clear();
	//vector<VERTEX*> saved;
	//for (int i = 0; i < vertexesCopy.size(); ++i)
	//{
	//	VERTEX* tmp = vertexesCopy[i]->clone();
	//	saved.push_back(tmp);
	//}

	//for (auto i : saved)
	//{
	//	//i->SetPheromones(vertexesCopy , 1);
	//	for (int j = i->GetID() + 1; j < saved.size(); ++j)
	//	{
	//		i->GetPheromones()->insert(pair<VERTEX*, double>(saved[j], vertexes[i->GetID()]->GetPheromone(vertexes[j])));
	//	}
	//	i->SetDistances(saved);
	//}

	int totalTime = 0;
		for (auto truck : trucks)
		{
			int currentTime = 0;
			
			while (truck->GetFilledCapacity() > 0 && vertexesCopy.size() > 1 && currentTime <= vertexes[0]->GetDueTime())
			{
				vector<VERTEX*> availableVertexes;
				for (int i = 0; i < vertexesCopy.size(); ++i)
				{
					int arrivalTime = ((vertexes[truck->GetCurrentVertexID()])->GetDistance(vertexes[vertexesCopy[i]->GetID()]) / truck->GetVelocity()) + currentTime;
					if (arrivalTime > vertexesCopy[i]->GetDueTime() || vertexesCopy[i]->GetID() == truck->GetCurrentVertexID())
						continue;

					availableVertexes.push_back(vertexes[vertexesCopy[i]->GetID()]);
				}
				if (availableVertexes.size() == 0)
				{
					//currentTime = vertexes[0]->GetDueTime() + 10;
					//continue;
					break;
				}
				TruckRide(vertexes, vertexesCopy, availableVertexes, truck, PheromoneAdded, totalDistance, way, way_edges, currentTime);
				DecreasePheromones(vertexesCopy, vaporizeSpeed);
				//Sleep(300);
				//FillPheromonesTable(vertexes);
				//FillDatasetTable(vertexes);
			}
			totalTime += currentTime;
		}
		
	//}

	if (totalDistance < bestDistance)
	{
		bestDistance = totalDistance;
		BestDistance->Text = Convert::ToString(bestDistance);
		bestWay.clear();
		for (int j = 0; j < way.size(); ++j)
			bestWay.push_back(way[j]);
		bestWay_edges.clear();
		for (int j = 0; j < way_edges.size(); ++j)
			bestWay_edges.push_back(way_edges[j]);
		//break;
	}
	//else {
	//	for (auto i : vertexes)
	//	{
	//		//i->SetPheromones(vertexesCopy , 1);
	//		i->GetPheromones()->clear();
	//		for (int j = i->GetID() + 1; j < vertexes.size(); ++j)
	//		{
	//			i->GetPheromones()->insert(pair<VERTEX*, double>(vertexes[j], saved[i->GetID()]->GetPheromone(saved[j])));
	//		}
	//		i->SetDistances(vertexes);
	//	}
	//}
	//throw gcnew System::NotImplementedException();
}

System::Void AntsColonyUI::Interface::StartLoopButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	isLoop = true;
	int j = 0;
	while (isLoop && j < 50)
	{
		for (auto vert : vertexesCopy)
		{
			if (vert->GetType() != vertexTYPE::warehouse)
				vert->NullFilledCapacity();
		}
		trucksCopy.clear();
		transform(trucks.begin(), trucks.end(), back_inserter(trucksCopy), cloneFunctor());
		/*for (auto i : vertexesCopy)
		{
			i->SetPheromones(vertexesCopy, 1);
			i->SetDistances(vertexesCopy);
		}*/

		double dist = 0;
		MakeSolution2(vertexesCopy, trucksCopy, 0.0008, 0, dist);
		/*DrawGraph(vertexesCopy);*/

		DistanceTextBox->Text = Convert::ToString(dist);

		if (dist < bestDistance)
		{
			bestDistance = dist;
			BestDistance->Text = Convert::ToString(bestDistance);
		}
		++j;
	}
	DrawGraph(vertexesCopy);
	return System::Void();
}

System::Void AntsColonyUI::Interface::StopLoopButton_Click(System::Object^ sender, System::EventArgs^ e)
{
	isLoop = false;
	DrawGraph(vertexesCopy);
	return System::Void();
}

System::Void AntsColonyUI::Interface::openFileDialog1_FileOk(System::Object^ sender, System::ComponentModel::CancelEventArgs^ e)
{
	string filename;
	convert_String_To_string(openFileDialog1->FileName, filename);


	//if (!vertexes.empty())
	vertexes.clear();
	trucks.clear();

	// Reading data from the file
	ReadData(filename, vertexes, truckCapacity, trucksAmount);

	// Initialising dataset

	Initialize(vertexes, trucks, truckCapacity, trucksAmount);

	if (vertexesCopy.empty())
		transform(vertexes.begin(), vertexes.end(), back_inserter(vertexesCopy), cloneFunctor());
	if (trucksCopy.empty())
		transform(trucks.begin(), trucks.end(), back_inserter(trucksCopy), cloneFunctor());
	for (auto i : vertexesCopy)
	{
		i->SetPheromones(vertexesCopy, 1);
		i->SetDistances(vertexesCopy);
	}

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
}

System::Void AntsColonyUI::Interface::OpenFileDia_Click(System::Object^ sender, System::EventArgs^ e)
{
	openFileDialog1->ShowDialog();
}

System::Void AntsColonyUI::Interface::ShowPGraph_Click(System::Object^ sender, System::EventArgs^ e)
{
	DrawGraph(vertexesCopy);
}

System::Void AntsColonyUI::Interface::ShowSGraph_Click(System::Object^ sender, System::EventArgs^ e)
{
	DrawWayEdges();
	//DrawWay();
	//Sleep(100);
}

System::Void AntsColonyUI::Interface::ShowBSolution_Click(System::Object^ sender, System::EventArgs^ e)
{
	//DrawBestWay();
	DrawBestWayEdges();
}

System::Void AntsColonyUI::Interface::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (TextBoxFilename->Text == "")
	{
		MessageBox::Show("The filename text box is empty!", "Error!");
		return;
	}
	// Getting filename from text box
	string filename;// = "C101.txt";
	convert_String_To_string(TextBoxFilename->Text, filename);
	PrintWayToFile(bestWay_edges, filename);
}
