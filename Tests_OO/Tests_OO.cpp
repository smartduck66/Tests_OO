//
// Book : Drill du chapitre 14 de l'ouvrage (page 515)
// "Programming -- Principles and Practice Using C++" de Bjarne Stroustrup (2ème édition : 2014)
// Commit initial : 03/04/2018 
// Commit en cours : Mise en oeuvre des bases de la programmation OO
// Caractères spéciaux : [ ]   '\n'   {  }   ||   ~   _     @

// Librairie indispensable sous Windows et VC++
#include "stdafx.h"

// Librairie restreinte fournie par BS
#include "std_lib_facilities.h"

// Code de test *************************************************************************************************************

struct B1 {		// Classe de base 
	virtual void vf() const { cout << "B1::vf" << endl; }
	void f() const { cout << "B1::f" << endl; }
	
};

struct D1 :B1 {	// Héritage mis en oeuvre
	void vf() const override { cout << "D1::vf" << endl; }
	void f() const { cout << "D1::f" << endl; }

};

struct D2 :D1 {
	void vf() const override { cout << "D2::vf" << endl; }
	void f() const { cout << "D2::f" << endl; }
	

};

struct B2 {		// Classe de base ne contenant AUCUNE fonction
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



int main()
{
	try
	{
		// A mettre dans la 1ère ligne du "main" pour afficher les caractères accentués sous la console Windows
		std::locale::global(std::locale("fr-FR"));

		
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

		


		keep_window_open();

		return 0;
	}
	/*
	catch (XXXXXXX::Invalid&)
	{
	cerr << "error: ???????????????????? ! \n";
	keep_window_open("q");	// For some Windows(tm) setup
	return 1;
	}
	*/

	catch (runtime_error& e)
	{	// this code is to produce error messages
		cout << e.what() << '\n';
		keep_window_open("q");	// For some Windows(tm) setups
	}
}