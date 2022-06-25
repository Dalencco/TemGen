#include <iostream>
#include <Urlmon.h>
#include <Windows.h>
#include <fstream>
#include <string>

using namespace std;

class App {
	public:
		void Init(string appName, int numberApp) 
		{
			this->name = appName.c_str();
			char result[MAX_PATH];
			this->path = std::string(std::string(result, GetModuleFileName(NULL, result, MAX_PATH)) + "\\..\\..\\" + name + "\\");
			this->errors = CDA(this->path);
			if (this->errors == 1)
			{
				cout << "[ Error ] > Failed to Creation Directory." << endl;
			}
			
			else 
			{
				cout << "[ Success ] > Directory Created. With the name: " << name << endl;	
				this->errors = Structure(numberApp);
				if (this->errors == 1) 
				{
					cout << "[ Error ] > The number is invalid." << endl;
				}
				
				else 
				{
					cout << "[ Success ] > Getting URL." << endl;
					
					this->errors = Download(this->url, this->path + this->name + ".zip");
					if (this->errors != 1)
					{
						cout << "[ Success ] > All Downloaded." << endl;
						this->errors = CallCMD();
						if (this->errors != 1)
						{
							cout << "[ Success ] > Template " << numberApp << " Full Downloaded." << endl;
						}
						
						else
						{
							cout << "[ Error ] > The Template No Downloaded, Because Dir Error or Path Error." << endl;
						}
					}
					
					else 
					{
						cout << "[ Error ] > No file Downloaded." << endl;
					}
				}
			}
		};
		
		int CDA(string f_path) {
			try 
			{
				CreateDirectory(f_path.c_str(), NULL);
				return 0;	
			}
			
			catch (...) 
			{
				return 1;
			}
		};
		
		int Download(string f_url, string f_file) {
			if (S_OK == URLDownloadToFile(NULL, f_url.c_str(), f_file.c_str(), 0, NULL))
			{
				cout << "[ Success ] > Downloaded." << endl;
				return 0;
			}
			else
			{
				cout << "[ Error ] > The error on Download File." << endl;
				return 1;	
			}
		};
		
		int CallCMD() {
			try {
				string con = this->path + "\\..\\" + "TemGenV2\\Scripts\\python.exe " + this->path + "\\..\\TemGenV2\\" + "index.py " + this->path + this->name + ".zip" + " " + this->path + "..\\" + this->name;
				system(con.c_str());
				return 0;
			}
			
			catch (...) {
				return 1;	
			}
		};
		
		int Structure(int number) {
			switch (number) {
				case 1:
					this->url = "https://github.com/Kentomii/TemGen/raw/main/templates/testtemplate.zip";
					return 0;
					break;
				default:
					return 1;
			};
		};
		
	protected:
		string url;
		string name;
		string cmd;
		string path;
		string file;
		int errors;
};

int main(int argc, char** argv) {
	
	App app;
	string appName;
	
	cout << "[ Name ] > ";
	cin >> appName;
	
	app.Init(appName.c_str(), 1);
	
	return 0;
}
