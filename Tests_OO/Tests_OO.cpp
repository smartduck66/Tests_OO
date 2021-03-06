//
// Book : "Programming -- Principles and Practice Using C++" de Bjarne Stroustrup (2ème édition : 2014)
// - Drill du chapitre 14 de l'ouvrage (page 515) 
// - Exercice 15 de la page 517
// - Class definition drill page 547
// - Chapitre 17 : drill
// Commit initial : 03/04/2018 
// Commit en cours : 12/05/2018 - chapitre 17
// Caractères spéciaux : [ ]   '\n'   {  }   ||   ~   _     @

// Librairie indispensable sous Windows et VC++
#include "stdafx.h"

// Librairie restreinte fournie par BS
#include "std_lib_facilities.h"

bool is_special_char(char c)	noexcept	// Helper : on vérifie si le char passé est un caractère spécial
{
	for (const char w : ";“”:[]*&^%$#@!")
		if (c == w)return true;
	return false;

}

struct Person {		
	Person() { }
	Person(string n, int a):name_p{n}, age_p{a} 
	{ 
	
		if (age_p<1 || age_p>150) throw Invalid();
		for (char& x : name_p) if (is_special_char(x))throw Invalid();
	
	}
	
	string name() const { return name_p; };
	int age() const { return age_p; };

	class Invalid {  };

private:
	string name_p{};
	int age_p{};

};

ostream& operator<<(ostream& os, const Person& p);
ostream& operator<<(ostream& os, const Person& p)
{
	return os << '(' << p.name() << ',' << p.age() << ')'<<endl;
}

istream& operator>>(istream& is, Person& p);
istream& operator>>(istream& is,Person& p)
{
	string name;
	int age;
	is >> name >> age;
	if (!is) return is;
	p = Person{name,age };     // update p
	return is;
}




// ***********************************************************************************
struct B1 {		// Classe de base 
	virtual void vf() const { cout << "B1::vf" << endl; }
	void f() const { cout << "B1::f" << endl; }

	//B1(const B1&) = delete;			// Copy constructor
	B1& operator=(const B1&) = delete;	// Copy assignment
	

};

struct D1 :B1 {	// Héritage mis en oeuvre
	void vf() const override { cout << "D1::vf" << endl; }
	void f() const { cout << "D1::f" << endl; }

};

struct D2 :D1 {
	void vf() const override { cout << "D2::vf" << endl; }
	void f() const { cout << "D2::f" << endl; }
	

};

struct B2 {		// Classe de base ne contenant AUCUNE fonction. Dans ce cas, c'est une classe abstraite. Aucun objet ne peut être directement instancié de cette classe.
	virtual void pvf() = 0;	// Une "pure" fonction virtuelle doit absolument être "overridée" dans une classe-fille et AUCUN objet B2 ne peut être construit directement
};

struct D21 :B2 {		// Héritage mis en oeuvre
	string s = "papa";
	void pvf() override { cout << "D21::pvf=" << s << endl; };

};

struct D22 :B2 {
	int i = 5;			// Encapsulation mise en oeuvre : ici, donnée publique (struct)
	void pvf() override { cout << "D22::pvf=" << i << endl; };

};


void f(B2& xx) {		// runtime polymorphism mis en oeuvre : la fonction dérivée est appelée en fonction du type de l'objet passé (d1 ou d2)
	xx.pvf();
};


// Exos 15 et 16 page 517 *******************************************************************
// On peut fortement améliorer la généricité des classes dérivées : à voir avec les Templates
struct Iterator1 {		
	virtual double* next() = 0;
	
};

struct Vector_iterator:Iterator1  {		// classe dérivée
	
	Vector_iterator(vector<double>&v) 
	{ 
		taille = v.size();
		if (taille>1)
			pd = &v[0];	// Equivalent à &(*v.begin())
		
	}

	double* next() override  { 
		if (pd == nullptr)
			return 0;
		else
		{
			for (unsigned int i = 0; i<taille; ++i)
			{
				if (i > 0) ++pd;	
				cout << *pd << endl;
			}

		}
	
	}

private:
	
	double* pd{};
	unsigned int taille = 0;

};


struct List_iterator :Iterator1 {		// Au contraire du cas "vecteur" ci-dessus, le containeur list réagit différemment et on passe alors par un itérateur pour le crawler
	List_iterator(list<double>&l)
	{
		p = l.begin();					// Définition de l'itérateur
		taille=l.size();		
	}

	double* next() override {			// La fonction overridée est donc légèrement différente de celle du vecteur	
		if (&(*p) == nullptr)
			return 0;
		else
		{
			
			for (unsigned int i = 0; i<taille; ++i)
			{
				if (i > 0) ++p;		
				cout << *p << endl;
			}
		}

	}


private:

	list<double>::iterator p;			// On stocke l'itérateur et pas un double* pd
	unsigned int taille = 0;

};


void print(Iterator1& xx) {		// runtime polymorphism mis en oeuvre : la fonction dérivée est appelée en fonction du type de l'objet passé (vector ou list)
	xx.next();
};

void print_array(ostream& os,double* a,int size) {		// Helper function : drill 4, page 622
	for (int i = 0; i < size; ++i)
		os << a[i] << "-";
	cout << endl;
};


int main()
{
	try
	{
		// A mettre dans la 1ère ligne du "main" pour afficher les caractères accentués sous la console Windows
		std::locale::global(std::locale("fr-FR"));

		vector <double> v1{ 1.2,2.3,3.4,4.1,5.9 };
		Vector_iterator vf{ v1 };
		list <double> l1{ 6.1,6.2,6.3,6.4,6.5 };
		List_iterator vl{ l1 };
		print(vf);
		print(vl);
		
		cout << "-------------------------------------------------------------------------------" << endl;

		// Drill ********************************************************
		B1 b;
		b.vf();
		b.f();
		cout << "-------"<<endl;

		D1 d;
		d.vf();
		d.f();
		cout << "-------" << endl;
		
		B1& bb = d;
		bb.vf();
		bb.f();
		cout << "-------" << endl;
				
		D2 d2;
		d2.vf();
		d2.f();
		cout << "-------" << endl;
		
		D21 d21;
		d21.pvf();
		cout << "-------" << endl;

		D22 d22;
		d22.pvf();
		cout << "-------" << endl;

		f(d21);
		f(d22);
		cout << "-------" << endl;
		// **********************************************************************
		
		// Drill page 547
		Person p{"Goofy",63};
		cout << p;
		/*
		
		Person saisie{};
		vector <Person> team{};
		
		cout << "Saisis une personne (CTRL N pour sortir) :" << endl;
		while(cin>>saisie) {
			team.push_back(saisie);
			
		}

		for (auto p : team)
			cout << p;
		
		*/

		// Chapitre 17
		ostream myout(std::cout.rdbuf());
		int x = 7;
		int *pi = &x;
		*pi = 27;
		double dd = 15.6;
		bool bbv = false;

		cout << "x==" << x <<" ; pi==" << pi << " ; contents of pi==" << *pi << endl;
		cout << "the size of int is " << sizeof(int) << ' ' << sizeof(x) << endl;
		cout << "the size of int* is " << sizeof(int*) << ' ' << sizeof(pi) << endl;
		cout << "the size of Person is " << sizeof(Person) << ' ' << sizeof(p) << endl;
		cout << "the size of double is " << sizeof(double) << ' ' << sizeof(dd) << endl;
		cout << "the size of bool is " << sizeof(bool) << ' ' << sizeof(bbv) << endl;

		double *pp = new double[4];	// Création d'une array sur la free store (new)
		*pp = 7.7;					// Initialisation du 1er élément
		double xx = *pp;
		pp[1] = 8.8;				// Initialisation des autres éléments
		pp[2] = 9.9;
		pp[3] = 10.10;
		double yy = pp[2];
		cout << "*pp=" << *pp << " ; xx=" << xx << endl;
		cout << "yy=" <<yy << endl;
		
		double *p1 = pp;	// p1 pointe sur l'array pp
		cout << "*******************" << endl;
		print_array(myout, p1, 4);
		
		double* ppp = new double[4]{ 0.1,0.2,0.3,0.4 };
		double* p2 = ppp;	// p2 pointe sur l'array ppp
		p1 = p2;			// p1 ne pointe plus sur pp mais sur ppp...
		
		print_array(myout, p1, 4);	// ... donc les valeurs affichées sont celles de ppp
		print_array(myout, pp, 4);	// Les valeurs initiales de pp n'ont pas été modifiées
		
		delete[]pp;
		delete[]ppp;
		

		double* pcrash = new double;
		double* qcrash=new double[1000];
		qcrash[700] = 7.7;
		cout << "qcrash[700] = " << qcrash[700] << endl;
		qcrash = pcrash;
		double dcrash = qcrash[700];
		cout << "dcrash = " << dcrash << endl;

		// Drill page 622
		double* test = new double[10] {10,20,30,40,50,60,70,80,90,100};
		print_array(myout, test,10);
		delete[]test;

			
		// Attente écran
		keep_window_open("q");

		return 0;
	}
	
	catch (Person::Invalid&)
	{
	cerr << "error: Mauvaise saisie ! \n";
	keep_window_open("q");	// For some Windows(tm) setup
	return 1;
	}
	

	catch (runtime_error& e)
	{	// this code is to produce error messages
		cout << e.what() << '\n';
		keep_window_open("q");	// For some Windows(tm) setups
	}
}