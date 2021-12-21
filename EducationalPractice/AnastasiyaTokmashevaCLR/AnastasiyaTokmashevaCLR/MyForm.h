#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <Windows.h>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <csignal>
#include <conio.h>
#include <cstdlib>
#include <string>
#include "Pipe.h"
#include <msclr\marshal_cppstd.h>

namespace AnastasiyaTokmashevaCLR {

	using namespace msclr::interop;
	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	typedef struct
	{
		//дескрипторы событий
		HANDLE  hePipeStart;
		HANDLE  hePipeReply;
		//дескрипторы пайпов
		HANDLE  child_in;
		HANDLE  parent_out;
		HANDLE  child_out;
		HANDLE  parent_in;
		//буфера
		char    read[1024];     //буфер для чтения данных
		char    send[1024];     //передаваемое значение
	}TheadParms;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
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
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	protected:
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::GroupBox^ groupBox1;

	private: System::Windows::Forms::TextBox^ textBox1;

	private: System::Windows::Forms::ProgressBar^ progressBar1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::ProgressBar^ progressBar2;
	private: System::Windows::Forms::GroupBox^ groupBox3;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label5;

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->progressBar2 = (gcnew System::Windows::Forms::ProgressBar());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(210, 353);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(178, 49);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Запуск";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(12, 353);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(92, 49);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Выход";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->progressBar2);
			this->groupBox1->Controls->Add(this->button5);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->button4);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->button3);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->textBox1);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F));
			this->groupBox1->Location = System::Drawing::Point(12, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(376, 199);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Конфигурация";
			// 
			// progressBar2
			// 
			this->progressBar2->Location = System::Drawing::Point(6, 172);
			this->progressBar2->Name = L"progressBar2";
			this->progressBar2->Size = System::Drawing::Size(198, 11);
			this->progressBar2->TabIndex = 7;
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(213, 162);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(157, 31);
			this->button5->TabIndex = 6;
			this->button5->Text = L"Сгенерировать";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MyForm::button5_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(6, 126);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(152, 18);
			this->label4->TabIndex = 5;
			this->label4->Text = L"Кол-во символов:  0";
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(213, 126);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(157, 31);
			this->button4->TabIndex = 4;
			this->button4->Text = L"Очистить файл";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(6, 95);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(0, 18);
			this->label1->TabIndex = 3;
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(213, 89);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(157, 31);
			this->button3->TabIndex = 2;
			this->button3->Text = L"Записать";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(6, 38);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(117, 18);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Сырые данные:";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(6, 59);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(364, 24);
			this->textBox1->TabIndex = 0;
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(9, 88);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(212, 27);
			this->progressBar1->TabIndex = 1;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Controls->Add(this->progressBar1);
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F));
			this->groupBox2->Location = System::Drawing::Point(12, 217);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(227, 130);
			this->groupBox2->TabIndex = 3;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Прогресс";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(6, 67);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(0, 18);
			this->label3->TabIndex = 2;
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->label6);
			this->groupBox3->Controls->Add(this->label5);
			this->groupBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11.25F));
			this->groupBox3->Location = System::Drawing::Point(245, 217);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(143, 130);
			this->groupBox3->TabIndex = 4;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Метаданные";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->label5->Location = System::Drawing::Point(6, 20);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(123, 52);
			this->label5->TabIndex = 8;
			this->label5->Text = L"Анастасия Токмашева\r\n501 группа 3 курс\r\n\r\n\r\n";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
			this->label6->Location = System::Drawing::Point(6, 71);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(7, 26);
			this->label6->TabIndex = 9;
			this->label6->Text = L"\r\n\r\n";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(400, 414);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		exit(1);
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		setlocale(0, "");

		SECURITY_ATTRIBUTES sa;//атрибуты защиты канала
		sa.lpSecurityDescriptor = NULL; //защита по умолчанию
		sa.nLength = sizeof(SECURITY_ATTRIBUTES);
		sa.bInheritHandle = true;//разрешаем наследование дескрипторов

	//обработка ошибок
		SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOOPENFILEERRORBOX | SEM_NOALIGNMENTFAULTEXCEPT);

		TheadParms tp = {};         //структура общих данных

		CreatePipe(&tp.parent_out, &tp.child_in, &sa, 0); //канал для stdin дочернего процесса
		CreatePipe(&tp.child_out, &tp.parent_in, &sa, 0); //канал для stdout дочернего процесса

		STARTUPINFO si;
		ZeroMemory(&si, sizeof(STARTUPINFO));
		si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
		//  si.wShowWindow = SW_HIDE;//скрываем окно дочернего процесса
			//подменяем дескрипторы
		si.hStdOutput = tp.parent_in;
		si.hStdError = tp.parent_in;
		si.hStdInput = tp.parent_out;

		//Создаём дочерний процесс
		WCHAR ModuleName[] = L"AnastasiyaTokmasheva_v1.1.exe";
		PROCESS_INFORMATION pi;
		CreateProcess(ModuleName, NULL, NULL, NULL, TRUE, ABOVE_NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi);                // здесь будут дескрипторы и идентификаторы нового процесса и его первичного потока

		//Создаем события для синхронизации
		tp.hePipeStart = CreateEvent(NULL,   // no security
			FALSE,  // explicit auto reset req
			FALSE,  // initial event reset
			NULL);  // no name

		tp.hePipeReply = CreateEvent(NULL,   // no security
			FALSE,  // explicit auto reset req
			FALSE,  // initial event reset
			NULL);  // no name

	//Создаем тред пайпов
		DWORD dwPipesThreadID;
		HANDLE hPipesThread = CreateThread((LPSECURITY_ATTRIBUTES)NULL, 0,
			(LPTHREAD_START_ROUTINE)Pipe::Arithmetic::PipesProc, &tp, 0, &dwPipesThreadID);  //параметром передаем адрес структуры данных

		System::String^ clrString = (textBox1->Text);
		std::string fileName = marshal_as <std::string> (clrString);
		const char* cstr = fileName.c_str();

		this->label3->Text = "Отправка и обработка...";

		SetEvent(tp.hePipeStart);

		for (int i = 0; i < 110; i += 10)
		{
			Sleep(100);
			this->progressBar1->Value = i;
		}
		this->label3->Text = "Готово!";

		//закрываем все, что понаоткрывали...
		CloseHandle(tp.child_in);//закрываем канал stdin дочернего процесса
		CloseHandle(tp.parent_out);//закрываем родительский принимающий пайп
		CloseHandle(tp.parent_in);
		CloseHandle(tp.child_out);

		CloseHandle(tp.hePipeReply);
		CloseHandle(tp.hePipeStart);
		TerminateThread(hPipesThread, 0);

		TerminateProcess(pi.hProcess, 0);//убиваем дочерний процесс
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	string str = asctime(timeinfo);
	System::String^ systemString = msclr::interop::marshal_as<System::String^>(str);
	this->label6->Text = systemString;
}
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	System::String^ clrString = (textBox1->Text);
	std::string rawData = marshal_as <std::string>(clrString);
	const char* cstr = rawData.c_str();

	int len = strlen(cstr);
	this->label4->Text = "Кол-во символов: " + System::Int32(len).ToString();

	std::ofstream out("text.txt", std::ios::app);
	if (out.is_open())
	{
		out << rawData;
		this->label1->Text = "Данные записаны";
		this->progressBar2->Value = 100;
	}
	else {
		this->label1->Text = "Ошибка записи";
	}
	out.close();
}
private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
	SetFileAttributes(L"log.txt", FILE_ATTRIBUTE_NORMAL);
	std::ofstream erase("text.txt", std::ios::out);
	erase.close();
	std::ofstream erase1("log.txt", std::ios::out);
	erase1.close();
	this->label4->Text = "Кол-во символов: " + System::Int32(0).ToString();
	this->label1->Text = "Данные очищены";
	this->progressBar2->Value = 0;
}
private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
	this->textBox1->Text = "";
	srand(time(0));
	for (int i = 0; i < 100; i++)
	{
		this->textBox1->Text = this->textBox1->Text + System::Int32(rand() % 10).ToString();
		this->progressBar2->Value = i + 1;
	}
}
};
}
