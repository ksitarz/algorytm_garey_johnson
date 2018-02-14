#include <queue>
#include <iostream>
#define N 5					//liczba wierzcho�k�w
#define M1 3				//zasoby M1			
#define M2 4				//zasoby M2

using namespace std;

	int graf[N][N]={				//tablica po��cze� w grafie
					{0,1,1,0,0},
					{1,0,0,0,0},
					{1,0,0,1,1},
					{0,0,1,0,0},
					{0,0,1,0,0}
	};
	
	int zasoby[N][2]={				//zasoby M1 i M2 wymagane przez zadania
						{2,1},		
						{1,3},
						{2,2},
						{0,1},
						{1,2}
	};
	
	int color[N]={0,0,0,0,0};		//tablica kolor�w wierzcho�k�w 0 niepokolorowany 
	
	queue <int> wierzcholki;
	
	void kolorowanie(int wierzcholek)  //kolorowanie wierzcho�k�w
	{
		
		
		if(color[wierzcholek]==0)		//odwiedzenie pierwszego wierzcho�ka
		{
			wierzcholki.push(wierzcholek);	
			color[wierzcholek]=1;
		}
		
		for(int i=0;i<N;i++)
		{	
			if(graf[wierzcholek][i]==1 && color[i]==color[wierzcholek])  //przerwanie dzia�ania programu w przypadku nie dwudzielnego grafu
				{
					cout<<"Graf nie jest dwudzielny";					//je�li jest op��czenie mi�dzy wierzcho�kami i maj� ten sam kolor graf nie jest dwudzielny
					exit(0);
				}
			
			if(graf[wierzcholek][i]==1 && color[i]==0)  //kolorowanie i dodawanie kolejnych wierzcho�k�w do koleiki
				{	
					if(color[wierzcholek]==1)			
					color[i]=2;							//kolorowanie s�siedniego wierzcho�ka na przeciwny kolor  
					
					else if(color[wierzcholek]==2)
					color[i]=1;
					
					wierzcholki.push(i);				//dodanie go do kolejki odwiedzanych wierzcho�k�w
				}
				
		}
	
	if(!wierzcholki.empty())				//powt�rzenie funkcji dla kolejnych wierzcho�k�w z koleiki
		{
			int a=wierzcholki.front();		//je�li kolejka jest niepusta we� pierwszy wierzcho�ek i wywo�aj dla niego ponownie funkcje
			wierzcholki.pop();
			kolorowanie(a);
		}
	
	}
	
void skierowanie_grafu()					//przekszta�aca graf na skierowany w kierunku koloru "1" do "2"
{
	for(int i=0;i<N;i++)
		if(color[i]==2)
			for(int j=0;j<N;j++)
				graf[i][j]=0;
}

void zamiana_koloru()						//zamiana kolor�w "1" i "2", liczba wierzcho�k�w 1 musi by� mniejsza lub r�wna 2
	{
		int a;
		for(int i=0;i<N;i++)
			if(color[i]==1)
				a++;
		if(a>(N/2))
			for(int j=0;j<N;j++)
			{
				if(color[j]==1)
					color[j]=2;
				else if(color[j]==2)
					color[j]=1;
			}
			
			
	}
	

	
void maksymalne_skojarzenie()
{
	queue <int> P1;				//kolejka dla procesora P1
	queue <int> P2;				//kolejka dla procesora P2
	
	queue <int> zadania_P1;		//zadania do przydzielenia dla P1
	queue <int> zadania_P2;		//zadania do przydzielenia dla P2
	
	int nieprzydzielone_zadania[N]={1,1,1,1,1};		//tablica nieprzydzielonych zada�
	
	int m1=0;		//zasoby M1 zestawu zada�
	int m2=0;		//zasoby M2 zestawu zada�
	int zadanie_P2=-1;				//aktualnie najlepsze zadanie dla P2
	int zadanie_P2_zasoby[2]={0,0};	//zasoby aktualnie najlepszego zestawu zada�	
	
	
	int przepustowosc[N+2][N+2]={0};	//macierz przepustowo�ci
		
	
	for(int i=0;i<N+2;i++)								//przepisanie po��cze� do macierzy przepustowo�ci i dodanie �r�d�a S(5) i uj�cia T(6)
		for(int j=0;j<N+2;j++)
			{
				if(i<N && j<N)
					przepustowosc[i][j]=graf[i][j];
					
				else if(i==N && color[j]==1)
					przepustowosc[i][j]=1;
					
				else if(j==N+1 && color[i]==2)
					przepustowosc[i][j]=1;
					
				
			}
			
		/*	
			for(int i=0;i<N+2;i++)			//test macierzy przepustowo�ci
		{
			for(int j=0;j<N+2;j++)
				cout<<przepustowosc[i][j];
				cout<<endl;
			}*/
			
	for(int i=0;i<N;i++)					//wybranie zada� dla P1
		if(przepustowosc[N][i]==1)
			zadania_P1.push(i);	
			
		while(!zadania_P1.empty())
		{
			for(int i=0;i<N;i++)											//wybranie mo�liwych zada� dla P2
				if(przepustowosc[zadania_P1.front()][i]==1 && nieprzydzielone_zadania[i]==1)
					zadania_P2.push(i);
					
		while(!zadania_P2.empty())											//wyb�r nojlepszego zadania dla P2
		{
			m1=zasoby[zadania_P1.front()][0]+zasoby[zadania_P2.front()][0];
			m2=zasoby[zadania_P1.front()][1]+zasoby[zadania_P2.front()][1];
			
			if(m1>M1 || m2>M2)  								//przekroczone mo�liwo�ci zasobowe
				zadania_P2.pop();
				
			else if(zadanie_P2!=-1)								//wybranie zestawu zada� wykorzystuj�cego wi�ksz� cz�� dost�pnych zasob�w
			{
				if((m1+m2)>(zadanie_P2_zasoby[0]+zadanie_P2_zasoby[1]))
					{
						zadanie_P2=zadania_P2.front();
						zadanie_P2_zasoby[0]=m1;
						zadanie_P2_zasoby[1]=m2;
						zadania_P2.pop();
					}
				else
						zadania_P2.pop();
			}
				
			else if(zadanie_P2==-1)								//wybranie pierwszego z mo�liwych zada� dla P2
			{
				zadanie_P2=zadania_P2.front();
				zadanie_P2_zasoby[0]=m1;
				zadanie_P2_zasoby[1]=m2;
				zadania_P2.pop();
				
			}
		
				
		}
		P1.push(zadania_P1.front());							//przypisanie wybranych zada� procesorom
		P2.push(zadanie_P2);
		
		nieprzydzielone_zadania[zadania_P1.front()]=0;			//oznaczenie zada� jako uszeregowane
		nieprzydzielone_zadania[zadanie_P2]=0;
		
		zadania_P1.pop();										//wyczyszczenie kolejki zadania_P1 i zresetowanie zarto�ci zadanie_P2
		zadanie_P2=-1;
			
			
		}
		
		for(int i=0;i<N;i++)									//sprawdzenie czy s� jakie� zadania kt�re nie mog�y zosta� zr�wnoleglone i przypisanie ich do P1
			if(nieprzydzielone_zadania[i]==1)
			{
				P1.push(i);
				nieprzydzielone_zadania[i]=0;
			}
				
		
		
	/*	for(int i=0;i<N;i++)						//test nieprzydzielonych zada�
		cout<<nieprzydzielone_zadania[i]<<endl;
		cout<<endl;*/

		
		int x=P1.size();						//wy�wietlenie wyniku na ekranie
		int z=P1.size()-P2.size();
		
		for(int i=0;i<P1.size()+1;i++)
		{
			cout<<"-------";
			
		}
		cout<<endl;
		cout<<"|   P1   |";
		
		while(!P1.empty())
		{
			cout<<"  "<<P1.front()+1<<"  |";
			P1.pop();
			
		}
		cout<<endl;
		
		for(int i=0;i<x+1;i++)
			cout<<"-------";
			

		cout<<endl;
		cout<<"|   P2   |";
		
		while(!P2.empty())
		{
			cout<<"  "<<P2.front()+1<<"  |";
			P2.pop();	
		}
		for(z;z>0;z--)
			cout<<"     |";
		
		cout<<endl;
		for(int i=0;i<x+1;i++)
			cout<<"-------";
		
		cout<<endl;
			
}

int main()
{
	kolorowanie(0);						//sprawdzenie czy graf jest dwudzielny i podzielenie wierzcho�k�w na 1 i 2
	zamiana_koloru();					//sprawdzenie czy nie trzeba zamieni� wierzcho�k�w z 1 na 2 i z 2 na 1, 1>=2
	skierowanie_grafu();				//przekszta�cenie grafu na skierowany w kierunku z 1 do 2
	maksymalne_skojarzenie();			//uszeregowanie zada� i wy�wietlenie wyniku
		
	
	 return 0;
}
