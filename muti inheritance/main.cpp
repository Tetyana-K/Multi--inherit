#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Worker
{

protected:
	string fullname_;
	int id_;
	static int counter; 
public:
	Worker(string fulln = "Noname"):fullname_(fulln), id_( ++counter)
	{
		cout<< "\t\tCtor Worker done : " << fullname_ << endl;
	}
	void Show() const
	{
		cout << "Name :\t" << fullname_ <<  "\tId :\t" << id_ << endl;
	}
};

class Programmer: public virtual Worker
{
private:
	vector<string> skills;
public:
	Programmer(string name): Worker(name)
	{
		skills.push_back("C");
		cout<< "\t\tCtor Programmer works : " << fullname_ << endl;
	}
	void AddSkill(string skill)
	{
		skills.push_back(skill);
	}
	void ShowSkills()const
	{
		cout << fullname_ << "'s skills:\t"; // fullname_ доступно , бо protected 
		for(unsigned  i = 0; i < skills.size(); ++i)
			cout<<skills[i]<<"\t";
		cout << endl;
	}
};
class Singer: public virtual Worker
{

protected:
private:
	int voice_;
	enum {numVoices = 7};
	static string namesvoices[numVoices];
public:
	enum {other, alto, contralto, soprano, bass, baritone, tenor};

	Singer(string name="Noname", int voice = other): Worker(name), voice_(voice)
	{
		cout<< "\t\tCtor Singer(string, int) : " << fullname_ << endl;
	}
	Singer(const Worker & worker, int voice = other): Worker(worker), voice_(voice)
	{
		cout<< "\t\tCtor Singer( const Worker &, int) : " << fullname_ << endl;
	}
	void Show() const
	{
		cout << "Singer " ;
		Worker::Show();
		cout << "Voice : " << namesvoices[voice_] << "\n";
	}
};
class SingingProgrammer: public Programmer, public Singer
{
public:
//якщо базовий клас(Worker) не віртуальний
	/*SingingProgrammer(string name, int voice=other): Programmer(name), Singer(name, voice)
	{
		cout<< "\t\tCtor SingingProgrammer(string=, int=) : " << Singer:: fullname_ << endl;
	}*/
	// якщо базовий клас  віртуальний і потрібний конструктор з параметрами для баз. класу
	SingingProgrammer(string name, int voice = other) : /*Worker(name),*/ Programmer(name), Singer(name, voice)
	{
		 cout<< "\t\tCtor SingingProgrammer(string=, int=) : " <<  fullname_ << endl;
	}
	
};
int Worker::counter= 0;
string Singer::namesvoices[numVoices]= {"other","alto", "contralto", "soprano", "bass", "baritone", "tenor"};
#define LINE cout << "__________________________________________________________________\n";

int main( )
{
	Worker Peter("Peter Ivaniv"), Ilya("Ilya Bendoff");
	Peter.Show();
	Ilya.Show();
	LINE

	Programmer Vania("Vania Teresh");
	Vania.Show();
	Vania.AddSkill("C++");
	Vania.AddSkill("C#");

	Vania.ShowSkills();
	LINE

	Singer Serg("Serg Napkin", Singer::bass);
	Serg.Show();
	LINE

	Singer Peter2(Peter, Singer::tenor);
	Peter2.Show();

	LINE

	// Peter2 = Ilya;
	// Peter2.Show();
	//cout << "+++ \n";
	//LINE

	SingingProgrammer Vlad("Vlad Roshin", Singer::alto);
	Vlad.Show(); // помилка компіляції якщо  баз клас невіртуальний
	//Vlad.Singer::Show();
	Vlad.ShowSkills();
	//Vlad.Programmer::Show();
	//Vlad.Singer::Show();
	
}