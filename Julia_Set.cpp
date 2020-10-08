#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

	
/*void WRITE(bool **inarray, ofstream outfile, int r, int c){
	for (int row = 0; row < r; row++){
		string s = "";
		for (int col = 0; col < c; col++){
			if (inarray[row][col])
				s += "*";
			else s += "O";
		}
		outfile << s << endl;
	}	
}*/

struct complex{
		double real;
		double imag;
		double magnitude;
	};
	
struct plane{
	complex z;
};


complex Julia(complex z, complex c){
	complex result;
	result.real = (z.real*z.real-z.imag*z.imag)+c.real;
	result.imag = (2*z.real*z.imag) + c.imag;
	result.magnitude = hypot(result.real,result.imag);
	return result ;
}

bool DetCON(complex z0, complex c, int maxItterations, int radius){
	complex n = z0;
	
	n = Julia(z0,c); // itteration 1
	for (int IT = 2; IT <= maxItterations; IT++){
		n = Julia(n,c);	
	}
	
	if (n.magnitude <= radius)
		return true;
	else return false;
	
}

int main(){
	
	const unsigned int POWER = 250;
	
	
	const int PIX = 20*POWER; //discrete points for measurements
	const int ITT = 0.8*POWER; //base itterations before convergence is determined - max is 3 times this
	const int CON = 2; //radius of convergence
	const string filename = "RESULT.txt";
	const float axis = 0.003;
	
	bool pEND = false;
	
	while (!pEND){
	//cout << "Enter SR,ER,SC,EC" << endl;
	//cin >> SR >> ER >> SC >> EC;
	cout <<
	"======================================="<<endl<<endl<<
	
	"============================"<<endl<<
	"	Julia Set Generator"<<endl<<
	"============================"<<endl;
	
	cout << "Enter maximum real part"<<endl;
	
	float ER;
	cin >> ER;
	float SR= ER-2*abs(ER);
	float SC= 0.5*SR;
	float EC= -SC;
	
	complex crit;
	crit.real = 0;
	crit.imag = 0;
	crit.magnitude = 0;
	
	cout << "Enter the Coords of the additive index c"<<endl<<"<real part,imaginary part>"<<endl;
	char delimeter;
	cin >> crit.real >> delimeter >> crit.imag;
	crit.magnitude = hypot(crit.real,crit.imag);
	
	cout <<endl<< "Processing Started..."<<endl;
	
	float dr = (ER-SR)/PIX, dc = (EC-SC)/PIX;
	
	ofstream OUT;
	OUT.open(filename.c_str());
	for (float r = ER; r >= SR; r-=dr){
		string s = "";
		for (float c = SC; c <= EC; c+=dc){
			
			complex z;
			z.real = r;
			z.imag = c;
			z.magnitude = hypot(r,c);
			
			char d = '#';
					
			if (((r>-axis)&&(r<axis))||((c>-axis)&&(c<axis)))
				s += "=";	
			else if (DetCON(z, crit, ITT, CON)){
				d = '#';
				s += d;
			}
			else if (DetCON(z, crit, 1.2*ITT, CON)){
				d = '-';
				s += d;								
			}
			else if (DetCON(z, crit, 1.6*ITT, CON)){
				d = '.';
				s += d;								
			}
			else s += " ";
		
		}
		OUT << s << endl;			
	}
	
	OUT.close();
	
	cout << "Processing Complete"<<endl<<"[FILE SAVED - RESULT.txt]"<<endl<<endl;
	cout << "Itterate Process Again? [y/n]"<<endl;
	string response;
	cin >> response;
	if ((response=="y")||(response=="Y"))
		pEND = false;
	else pEND = true;
	
	cout <<endl<< "=======================================";
	
	}
	 
	return 0;
}
