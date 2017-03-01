// Polinom.cpp: главный файл проекта.

#include "stdafx.h"
#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void Main(array<String^>^ args) 
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Polinom::MainForm ^form = gcnew Polinom::MainForm();
	Application::Run(form);
}
