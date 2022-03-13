#include<bits/stdc++.h>

using namespace std;

class Multime{
    int *v = nullptr;
    int dimensiune;

    public:
    // constructori
        Multime();// constructor de initializare
        Multime(int);// constructor de initializare cu dimensiune fixa
        Multime(int, int); // constructor de initializare cu dimensiune fixa si valoare default
        Multime(int, int []);// constructor de initializare cu dimensiune fixa si vector predefinit
        Multime(Multime &); // constructor de copiere
    // destructor
        ~Multime(); // destructor

    // Gets & Sets
        int GetDimension();
        void SetDimension(int); // acest setter nu va fi folosit in program
        int* GetSet();
        void SetSet(int []);
        void ResetSet(int);

    // Methods
        int ValidSet();
        void ArrayToSet();
        void DisplaySet();
        void ChangeElement(int, int);
        void ReinitSet(int , int []);
   // Metode tema bonus
        int InSet(int);
        int DisjointSets(Multime);
        int* ReferenceToValue(int);
        void SortingFunction(Multime&, char, void (*function)(Multime&, char));

    // Operatori
    friend Multime operator+ (Multime m1, Multime m2);
	friend Multime operator- (Multime m1, Multime m2);
	friend Multime operator* (Multime m1, Multime m2);
    // Operatori tema bonus
    friend int operator== (Multime m1, Multime m2);
    friend int operator!= (Multime m1, Multime m2);
    friend int operator! (Multime m1);

	Multime& operator= (const Multime &multime)
	{
		delete[] v;
		dimensiune = 0;
		v = nullptr;

		dimensiune = multime.dimensiune;
		v = new int[dimensiune];
		for(int i = 0; i < dimensiune; i++)
			v[i] = multime.v[i];
		return *this;
	}

	friend std::istream& operator>> (std::istream& in,  Multime& multime);
	friend std::ostream& operator<< (std::ostream& out, const Multime& multime);
};

#pragma region Constr&Destr

Multime::Multime(){
    dimensiune = 0;
    v = new int[dimensiune];
}

Multime::Multime(int no_of_elements)
{
    dimensiune = no_of_elements;
    v = new int[dimensiune];
    for(int i = 0;i<dimensiune;i++)
    {
        v[i] = 0;
    }
}
/*
    Constructorul de mai jos nu respecta notiunea de multime, deoarece multimea este formata doar din elemente distincte
*/
Multime::Multime(int no_of_elements, int default_value)
{
    dimensiune = no_of_elements;
    v = new int[dimensiune];
    for(int i=0;i<dimensiune;i++)
    {
        v[i] = default_value;
    }
}

Multime::Multime(int no_of_elements, int arr[])
{

    for(int i=0;i<no_of_elements-1;i++)
    {
        bool duplicate = false;
        for(int j=i+1;j<no_of_elements;j++)
        {
            if(arr[i] == arr[j])
            {
                duplicate = true;
                for(int k=j;k<no_of_elements-1;k++)
                {
                    arr[k] = arr[k+1];
                }
                j = j - 1;
                no_of_elements = no_of_elements - 1;
            }
        }
    }

    dimensiune = no_of_elements;
    v = new int[dimensiune];
    for(int i=0;i<dimensiune;i++)
    {
        v[i] = arr[i];
    }
    ArrayToSet();
}

Multime::Multime(Multime &multime)
{
    dimensiune = multime.dimensiune;
    v = new int[dimensiune];
    for(int i=0;i<dimensiune;i++)
    {
        v[i] = multime.v[i];
    }
}

Multime::~Multime(){
    delete[] v;
    dimensiune = 0;
    v = nullptr;
}

#pragma endregion

#pragma region GetsAndSets

int Multime::GetDimension(){
    return dimensiune;
}

void Multime::SetDimension(int dimensiune)
{
    this->dimensiune = dimensiune;
}

int* Multime::GetSet()
{
    return v;
}

void Multime::SetSet(int a[])
{
    if(dimensiune > 0)
    {
        for(int i=0;i<dimensiune;i++)
        {
            v[i] = a[i];
        }
    }
    else{
        cout<<"Numarul de elemente nu a fost setat"<<endl;
    }
}


void Multime::ResetSet(int no_of_elements)
{
    // resetare dimensiune si pointer
    dimensiune = 0;
    delete[] v;
    v = nullptr;
    // initializare dimensiune si pointer
    dimensiune = no_of_elements;
    v = new int[dimensiune];
}

#pragma endregion

#pragma region Methods

int Multime::ValidSet(){
    if(dimensiune > 0)
    {
        for(int i=0;i<dimensiune-1;i++)
        {
            for(int j=i+1;j<dimensiune;j++)
            {
                if(v[i] == v[j])
                    return 0;
            }
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

void Multime::ArrayToSet(){
    bool duplicate = true;
    // verificam daca avem cel putin un elemenet in array
    if(dimensiune > 0)
    {
        for(int i=0;i<dimensiune-1;i++)
        {
            bool duplicate = false;
            for(int j=i+1;j<dimensiune;j++)
            {
                if(v[i] == v[j])
                {
                    duplicate = true;
                    for(int k=j;k<dimensiune-1;k++)
                    {
                        v[k] = v[k+1];
                    }
                    j = j - 1;
                    dimensiune = dimensiune - 1;
                }
            }
        }
    }
    else{
        cout<<"Numarul de elemente nu a fost setat"<<endl;
    }
}

void Multime::DisplaySet()
{
    if(dimensiune > 0)
    {
        for(int i=0;i<dimensiune;i++)
        {
            cout<<v[i]<<" ";
        }
        cout<<endl;
    }
    else{
        cout<<"Numarul de elemente nu a fost setat"<<endl;
    }
}

void Multime::ChangeElement(int index, int element)
{
    if(dimensiune > 0)
    {
        if(index < dimensiune && index >= 0)
        {
            v[index] = element;
            ArrayToSet();

        }
        else{
            cout<<"Indexul nu este valid"<<endl;
        }
    }
    else{
        cout<<"Numarul de elemente nu a fost setat"<<endl;
    }
}

void Multime::ReinitSet(int no_of_elements, int a[])
{
    dimensiune = 0;
    delete[] v;

    dimensiune = no_of_elements;
    v = new int[dimensiune];
    for(int i=0; i<dimensiune; i++)
    {
        v[i] = a[i];
    }
    ArrayToSet();
}

#pragma endregion

#pragma region Functions

Multime Reunion(Multime m1, Multime m2)
{
    Multime reunionSet, nullSet(1, 0);

    if(m1.GetDimension() > 0 || m2.GetDimension() > 0)
    {
        if(m1.ValidSet() == 0 && m2.ValidSet() == 0)
        {
            cout<<"Ambii parametri nu sunt multimi si trebuie sa folosesti ArrayToSet pentru a transforma fiecare parametru intr-un set"<<endl;
        }
        else if(m1.ValidSet() == 0){
            cout<<"Primul parametru nu este multime si trebuie sa folosesti ArrayToSet pentru a transforma primul parametru intr-un set"<<endl;
        }
        else if(m2.ValidSet() == 0)
        {
            cout<<"Al doilea parametru nu este multime si trebuie sa folosesti ArrayToSet pentru a transforma al doilea parametru intr-un set"<<endl;
        }
        else
        {
            int dimension = m1.GetDimension() + m2.GetDimension();

            int dim1 = m1.GetDimension();
            int dim2 = m2.GetDimension();

            reunionSet.ResetSet(dimension);
            for(int i=0;i<dim1;i++)
            {
                reunionSet.ChangeElement(i, m1.GetSet()[i]);
            }

            for(int i=0;i<dim2;i++)
            {
                reunionSet.ChangeElement(dim1, m2.GetSet()[i]);
                dim1++;
            }

            if(reunionSet.ValidSet() == 0)
            {
                reunionSet.ArrayToSet();
            }

        }
        return reunionSet;
    }
    else{
        cout<<"Parametrii nu au valori"<<endl;
    }
    return nullSet;
}

Multime Difference(Multime m1, Multime m2)
{
    Multime differenceSet, nullSet(1, 0);

    if(m1.GetDimension() > 0 || m2.GetDimension() > 0)
    {
        if(m1.ValidSet() == 0 && m2.ValidSet() == 0)
        {
            cout<<"Ambii parametri nu sunt multimi si trebuie sa folosesti ArrayToSet pentru a transforma fiecare parametru intr-un set"<<endl;
        }
        else if(m1.ValidSet() == 0){
            cout<<"Primul parametru nu este multime si trebuie sa folosesti ArrayToSet pentru a transforma primul parametru intr-un set"<<endl;
        }
        else if(m2.ValidSet() == 0)
        {
            cout<<"Al doilea parametru nu este multime si trebuie sa folosesti ArrayToSet pentru a transforma al doilea parametru intr-un set"<<endl;
        }
        else
        {
            int dimension = m1.GetDimension() + m2.GetDimension();

            int dim1 = m1.GetDimension();
            int dim2 = m2.GetDimension();

            int differenceIndex = 0;
            int no_of_diff_numbers = 0;

            for(int i=0;i<dim1;i++)
            {
                bool diff = true;
                for(int j=0;j<dim2;j++)
                {
                    if(m1.GetSet()[i] == m2.GetSet()[j])
                        diff = false;
                }
                if(diff == true)
                {
                    no_of_diff_numbers++;
                }
            }

            if(no_of_diff_numbers)
            {
                differenceSet.ResetSet(no_of_diff_numbers);
                for(int i=0;i<dim1;i++)
                {
                    bool diff = true;
                    for(int j=0;j<dim2;j++)
                    {
                        if(m1.GetSet()[i] == m2.GetSet()[j])
                            diff = false;
                    }
                    if(diff == true)
                    {
                        differenceSet.ChangeElement(differenceIndex, m1.GetSet()[i]);
                        differenceIndex++;
                    }
                }
                return differenceSet;
            }
            else{
                cout<<"Multime vida"<<endl;
            }
        }
    }
    else{
        cout<<"Parametrii nu au valori"<<endl;
    }
    return nullSet;
}

Multime Intersection(Multime m1, Multime m2)
{
    Multime intersectionSet, nullSet(1, 0);

    if(m1.GetDimension() > 0 || m2.GetDimension() > 0)
    {
        if(m1.ValidSet() == 0 && m2.ValidSet() == 0)
        {
            cout<<"Ambii parametri nu sunt multimi si trebuie sa folosesti ArrayToSet pentru a transforma fiecare parametru intr-un set"<<endl;
        }
        else if(m1.ValidSet() == 0){
            cout<<"Primul parametru nu este multime si trebuie sa folosesti ArrayToSet pentru a transforma primul parametru intr-un set"<<endl;
        }
        else if(m2.ValidSet() == 0)
        {
            cout<<"Al doilea parametru nu este multime si trebuie sa folosesti ArrayToSet pentru a transforma al doilea parametru intr-un set"<<endl;
        }
        else
        {
            int dimension = m1.GetDimension() + m2.GetDimension();

            int dim1 = m1.GetDimension();
            int dim2 = m2.GetDimension();

            int intersectionIndex = -1;
            int no_of_equal_numbers = 0;

            for(int i=0;i<dim1;i++)
            {
                for(int j=0;j<dim2;j++)
                {
                    if(m1.GetSet()[i] == m2.GetSet()[j])
                        no_of_equal_numbers++;
                }
            }

            if(no_of_equal_numbers)
            {
                intersectionSet.ResetSet(no_of_equal_numbers);
                for(int i=0;i<dim1;i++)
                {
                    for(int j=0;j<dim2;j++)
                    {
                        if(m1.GetSet()[i] == m2.GetSet()[j])
                        {
                            intersectionIndex++;
                            intersectionSet.ChangeElement(intersectionIndex, m1.GetSet()[i]);
                        }
                    }
                }
                return intersectionSet;
            }
            else{
                cout<<"Multime vida"<<endl;
            }
        }
    }
    else{
        cout<<"Parametrii nu au valori"<<endl;
    }
    return nullSet;
}

//Cerinte Bonus

int Egalitate(Multime m1, Multime m2)
{
    bool ok = true;
    if(m1.GetDimension() != m2.GetDimension())
    {
        return 0;
    }
    for(int i=0;i<m1.GetDimension() && ok == true;i++)
    {
        bool ok_aux = false;
        for(int j=0;j<m2.GetDimension() && ok_aux == false;j++)
        {
            if(m1.GetSet()[i] == m2.GetSet()[j])
            {
                ok_aux = true;
            }
        }
        if(ok_aux == false)
        {
            ok = false;
        }
    }
    return ok;
} 

int VerificareVid(Multime m1)
{
    int x = m1.GetDimension();
    if(x == 0)
    {
        return 1;
    }
    return 0;
}

int Multime::InSet(int value)
{
    for(int i=0;i<dimensiune;i++)
    {
        if(v[i] == value)
            return 1;
    }
    return 0;
}

int Multime::DisjointSets(Multime m2)
{
    for(int i=0;i<dimensiune;i++)
    {
        for(int j=0;j<m2.GetDimension();j++)
        {
            if(v[i] == m2.GetSet()[j])
            {
                return 0;
            }
        }
    }
    return 1;
}

int* Multime::ReferenceToValue(int position)
{
    if(position < 0 || position >= dimensiune)
    {
        return 0;
    }
    int *p = &v[position];
    return p;
}

void sortare(Multime &m, char x)
{
    if(x == '<')
    {
        for(int i=0;i<m.GetDimension()-1;i++)
        {
            for(int j=i+1;j<m.GetDimension();j++)
            {
                if(m.GetSet()[i] > m.GetSet()[j])
                {
                    int aux = m.GetSet()[i];
                    m.GetSet()[i] = m.GetSet()[j];
                    m.GetSet()[j] = aux;
                }
            }
        }
    }
    else{
        for(int i=0;i<m.GetDimension()-1;i++)
        {
            for(int j=i+1;j<m.GetDimension();j++)
            {
                if(m.GetSet()[i] < m.GetSet()[j])
                {
                    int aux = m.GetSet()[i];
                    m.GetSet()[i] = m.GetSet()[j];
                    m.GetSet()[j] = aux;
                }
            }
        }
    }
}

void Multime::SortingFunction(Multime &m,char x, void (*sortare)(Multime&, char))
{
    sortare(m,x);
}

// Cerinte Bonus Final

Multime* ReadSets(int &no_of_sets)
{
    Multime* multime = new Multime[no_of_sets];

    for(int i=0;i<no_of_sets;i++)
    {
        int no_of_elements = 0;
        cout<<"Va aflati la multimea cu numarul "<<i+1<<endl;
        cout<<"Numarul de elemente pentru multimea "<<i+1<<" este: "<<endl;
        cin>>no_of_elements;
        int* arr = new int[no_of_elements];
        cout<<"Acum introduceti "<<no_of_elements<<" elemente"<<endl;
        for(int j=0;j<no_of_elements;j++)
        {
            cout<<"Elementul "<<j+1<<" : ";
            cin>>arr[j];
        }

        Multime aux(no_of_elements, arr);
        multime[i] = aux;

        cout<<"Multimea "<<i+1<<" este : ";
        cout<<multime[i]<<endl;
    }
    cout<<"Toate cele "<<no_of_sets<<" multimi sunt: "<<endl;
    for(int i=0;i<no_of_sets;i++)
    {
        cout<<i+1<<": "<<multime[i]<<endl;
    }
    return multime;
}

void Read(Multime* &multime)
{
    int no_of_sets;
    cout<<"Numarul de multimi este: "<<endl;
    cin>>no_of_sets;
    multime = new Multime[no_of_sets];
    multime = ReadSets(no_of_sets);
}

void Menu(Multime* &multime)
{
    int command = 0;
    while(command != 1)
    {
        cout<<endl;
        cout<<"Introduceti numarul comenzii:"<<endl;
        cout<<"1. Iesire"<<endl;
        cout<<"2. Afisare date"<<endl;
        cout<<"3. Verificare multime"<<endl;
        cout<<"4. Conversie vector citit in multime prin eliminarea duplicatelor"<<endl;
        cout<<"5. Reuniunea a 2 multimi"<<endl;
        cout<<"6. Diferenta a 2 multimi"<<endl;
        cout<<"7. Intersectia a 2 multimi"<<endl;
        cout<<"8. Citire de alte date (cele salvate vor fi pierdute"<<endl;
        cout<<"Comanda: ";
        cin>>command;
        if(command == 1)
        {
            break;
        }
        else if(command == 2)
        {
            cout<<"Multimile citite sunt: "<<endl;
            for(int i=0;i<multime->GetDimension();i++)
            {
                cout<<i+1<<": "<<multime[i]<<endl;
            }
        }
        else if(command == 3)
        {
            cout<<"Multimile citite sunt: "<<endl;
            for(int i=0;i<multime->GetDimension();i++)
            {
                cout<<i+1<<": "<<multime[i]<<endl;
            }
            int indexVerificare;
            cout<<"Introduceti indicele vectorului pe care vreti sa il verificati: ";
            cin>>indexVerificare;
            if( 0<= indexVerificare && indexVerificare <= multime->GetDimension())
            {
                if(multime[indexVerificare-1].ValidSet())
                {
                    cout<<"Vector valid"<<endl;
                }
                else{
                    char new_command;
                    cout<<"Vectorul nu este multime. Doriti sa fie convertit la multime? Y sau N: ";
                    cin>>new_command;
                    if(toupper(new_command) == 'Y')
                    {
                        multime[indexVerificare-1].ArrayToSet();
                        cout<<"Vector convertit la multime si forma lui actuala este: "<<multime[indexVerificare-1]<<endl;
                    }
                }
            }
            else{
                cout<<"Index nevalid"<<endl;
            }
        }
        else if(command == 4)
        {
            int indexSet;
            cout<<"Multimile citite sunt: "<<endl;
            for(int i=0;i<multime->GetDimension();i++)
            {
                cout<<i+1<<": "<<multime[i]<<endl;
            }

            cout<<"Introduceti indicele vectorului care sa fie convertit la multime: ";
            cin>>indexSet;

            if( 0<= indexSet && indexSet <= multime->GetDimension())
            {
                if(multime[indexSet-1].ValidSet())
                {
                    cout<<"Vectorul este deja multime"<<endl;
                }
                else{
                    multime[indexSet-1].ArrayToSet();
                    cout<<"Vector convertit la multime: "<<multime[indexSet-1]<<endl;
                }
            }
            else{
                cout<<"Index nevalid"<<endl;
            }
        }
        else if(command == 5)
        {
            cout<<"Multimile citite sunt: "<<endl;
            for(int i=0;i<multime->GetDimension();i++)
            {
                cout<<i+1<<": "<<multime[i]<<endl;
            }
            int firstSet, secondSet;
            cout<<"Indexul primei multimi: ";
            cin>>firstSet;
            cout<<endl;
            cout<<"Indexul celei de-a doua multimi: ";
            cin>>secondSet;

            if(multime[firstSet-1].ValidSet() && multime[secondSet-1].ValidSet())
            {
                cout<<"Reuniunea este: ";
                cout<<multime[firstSet-1] + multime[secondSet-1]<<endl;
            }
        }
        else if(command == 6)
        {
            cout<<"Multimile citite sunt: "<<endl;
            for(int i=0;i<multime->GetDimension();i++)
            {
                cout<<i+1<<": "<<multime[i]<<endl;
            }
            int firstSet, secondSet;
            cout<<"Indexul primei multimi: ";
            cin>>firstSet;
            cout<<endl;
            cout<<"Indexul celei de-a doua multimi: ";
            cin>>secondSet;

            if(multime[firstSet-1].ValidSet() && multime[secondSet-1].ValidSet())
            {
                cout<<"Diferenta este: ";
                cout<<multime[firstSet-1] - multime[secondSet-1]<<endl;
            }
        }
        else if(command  == 7)
        {
            cout<<"Multimile citite sunt: "<<endl;
            for(int i=0;i<multime->GetDimension();i++)
            {
                cout<<i+1<<": "<<multime[i]<<endl;
            }
            int firstSet, secondSet;
            cout<<"Indexul primei multimi: ";
            cin>>firstSet;
            cout<<endl;
            cout<<"Indexul celei de-a doua multimi: ";
            cin>>secondSet;

            if(multime[firstSet-1].ValidSet() && multime[secondSet-1].ValidSet())
            {
                cout<<"Intersectia este: ";
                cout<<multime[firstSet-1] * multime[secondSet-1]<<endl;
            }
        }
        else if(command == 8)
        {
            multime = nullptr;
            Read(multime);
        }
        else{
            cout<<"Comanda nu e acceptata. Reincercati"<<endl;
        }
    }
    cout<<"Iesire"<<endl;
}

#pragma endregion

#pragma region Operators

Multime operator+ (Multime m1, Multime m2)
{
	return Reunion(m1, m2);
}
Multime operator- (Multime m1, Multime m2)
{
	return Difference(m1, m2);
}
Multime operator* (Multime m1, Multime m2)
{
	return Intersection(m1, m2);
}
// Cerinte Bonus
int operator== (Multime m1, Multime m2)
{
    return Egalitate(m1, m2);
}

int operator!= (Multime m1, Multime m2)
{
    return !Egalitate(m1, m2);
}

int operator! (Multime m1)
{
    return VerificareVid(m1);
}

// Cerinte Bonus Final

std::istream& operator>> (std::istream& in,  Multime& multime)
{
	delete[] multime.v;
	multime.dimensiune = 0;
	multime.v = nullptr;
    in>>multime.dimensiune;
	multime.v = new int[multime.dimensiune];
    for(int i = 0; i < multime.dimensiune; i++)
		in>>multime.v[i];
	return in;
}

std::ostream& operator<< (std::ostream& out, const Multime& multime)
{
	std::cout<<"{";
	for(int i = 0; i < multime.dimensiune - 1; i++)
		out<<multime.v[i]<<", ";

	out<<multime.v[multime.dimensiune - 1];
	std::cout<<"}"<<std::endl;

	return out;
}


#pragma endregion

int main()
{

    cout<<"Introdu Y pentru a incepe sau N pentru a iesi: ";
    char command;
    cin>>command;
    while(toupper(command) != 'Y')
    {
        if(toupper(command) == 'N')
        {
            return 0;
        }
        else
            cout<<"Comanda nevalida"<<endl;
        cout<<"Introdu Y pentru a incepe sau N pentru a iesi: ";
        cin>>command;
    }
    cout<<"Trebuie sa introduceti multimile dorile pentru a incepe"<<endl;
    Multime* multime;
    Read(multime);
    Menu(multime);
    return 0;
}
