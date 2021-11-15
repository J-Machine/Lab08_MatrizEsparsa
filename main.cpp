#include<bits/stdc++.h>

using namespace std;

template<class T>
class Nodo {
    public:
        int fil;
        int col;
        int dato;
        Nodo<T> * sig_fil;
        Nodo<T> * sig_col;
    public:
        Nodo():fil{0},col{0},sig_fil{0},sig_col{0}{}
        Nodo(T d , int fila , int colu): dato{d} , fil{fila}, col{colu} , sig_fil{nullptr} ,sig_col{nullptr} {} 
};


template<class T , int n_fil , int n_col>
class MD {
    private:
        Nodo<T> * row[n_fil];
        Nodo<T> * col[n_col];
    public:
        MD()
        {
            for(int i = 0 ; i < n_fil ; i++) row[i] = 0;
            for(int i = 0 ; i < n_col ; i++) col[i] = 0;
        }

        bool find_col(int f , int c , Nodo<T> ** & q)
        {
            if(f < n_fil) { 
                q = &row[f];
                while (*q) {
                    if((*q)->col == c) {
                        return true;
                    }
                    if((*q)->col > c) {
                        return false; 
                    }
                    q = &((*q)->sig_col);
                } 
            }
            return false;
        }

        bool find_fil(int f , int c , Nodo<T> ** & p)
        {
            if(c < n_col) { 
                p = &col[c];
                while(*p){
                    if((*p)->fil == f ) {
                        return true;
                    }
                    if((*p)->fil > f ) {
                        return false;
                    }
                    p = &((*p)->sig_fil);
                }
            }
            return false;
        }
        //////////////////INSERTAR ///////////////////
        void insert(int fil, int col , T d)
        {
            Nodo<T> ** p ;
            Nodo<T> ** q;
            bool a = find_fil(fil,col,p);
            bool b = find_col(fil,col,q);
            if(!a && !b){
                Nodo<T> * newnodo  = new Nodo<T>(d,fil,col);
                newnodo->sig_col = *q;
                newnodo->sig_fil = *p;
                *q = *p = newnodo; 
            }
        }
        
        //////////////////INSERTAR DATO///////////////////
        /* Inserta el dato en la fil y col. Si tiene un dato, lo sobreescribe. Si no se puede insertar
            retorna  -1 
        */
        int insertarDato(int fil, int col, int _dato)
        {
            if((fil < n_fil && fil>=0) && (col < n_col && col>=0))
            {
                Nodo<T> ** p ;
                Nodo<T> ** q;
                bool a = find_fil(fil,col,p);
                bool b = find_col(fil,col,q);
                if(a && b){
                    (*p)->dato = _dato;
                }  else  {
                    insert(fil, col, _dato);
                }
                return _dato;
            }
            return -1;
        }
        //////////////////MOSTRAR MAYOR FILA///////////////////
        void mostrarMayorFila()   
        {
            Nodo<T> ** q; 
            for(int j = 0; j < n_fil; j++) {
                int mayor = 0;
                for(int i = 0; i < n_col; i++ )
                {
                    if(find_fil(j,i,q) )
                        if ((*q)->dato >  mayor ) mayor=(*q)->dato;
                }
                cout << "- Mayor de la fila " << j <<": " <<mayor<<endl;
            }
        }
        //////////////////SUMA COLUMNAS///////////////////
        void sumaColumnas()
        {   
            Nodo<T> ** q; 
            for(int i = 0; i < n_col; i++ )
            {
                int suma = 0;
                for(int j = 0; j < n_fil; j++ )
                {
                    if(find_col(j,i,q)){
                        suma = suma + (*q)->dato ; 
                    } 
                }
                cout << "- Suma de la columna " << i <<": " <<suma<<endl;
            }
        }
        //////////////////MOSTRAR PARES FILA///////////////////
        void mostrarParesFilas()
        {
            Nodo<T> ** q; 
            int par=0;
            for(int j = 0; j < n_fil; j++) {
                cout << "- Pares de la fila " << j <<": ";
                for(int i = 0; i < n_col; i++ )
                {
                    if(find_col(j,i,q) ) {
                        if ( esPar( (*q)->dato) ) {
                            par = (*q)->dato;
                            cout <<" - "<<par;
                        } else {
                            cout << "Ninguno";
                        }
                    }
                }
                cout <<endl;
            }
        }

        //////////////////IMPRIMIR MATRIZ///////////////////
        void print() 
        {
            Nodo<T> ** q; 
            for(int j = 0; j < n_fil;j++) {
                for(int i = 0; i < n_col;i++ )
                {
                    if(find_col(j,i,q)) cout<<" "<<(*q)->dato<<" ";
                    else cout<<" 0 ";
                }
                cout<<"\n";
            }
        }
        //////////////////ELIMINAR DATO///////////////////
        void eliminarDato(int fil, int col ){
            Nodo<T> ** p; 
            Nodo<T> ** q; 
            Nodo<T> *temp; 
            Nodo<T> *temp1; 
            Nodo<T> *temp2; 
            Nodo<T> *temp3; 
            
            if(find_col(fil,col,q) && find_fil(fil,col,p)  ){
                temp=(*q);
                temp2=(*p);
                temp1=temp->sig_col;
                temp3=temp2->sig_fil;
                (*q)=temp1;
                (*p)=temp3;
                delete temp;  
                
            } 
        }

        bool esPar(T d){
            if (d%2==0 && d!=0)
                return true;
            return false;
        }

        //////////////////ELIMINAR PARES///////////////////
        void eliminarPares(){
            Nodo<T> ** q; 
            for(int j = 0; j < n_fil;j++) {
                for(int i = 0; i < n_col;i++ )
                {
                    if(find_col(j,i,q) ){
                        if (esPar( (*q)->dato) ) {
                            eliminarDato(j,i);
                        }
                    }    
                }
            }
        }

        //////////////////ELIMINAR MAYOR///////////////////
        void eliminarMayor(){
            Nodo<T> ** q; 
            int may=0,a,b;
            for(int j = 0; j < n_fil;j++) {
                for(int i = 0; i < n_col;i++ )
                {
                    if(find_col(j,i,q) ){
                        if ((*q)->dato >=  may ) {
                            may=(*q)->dato;
                            a=j;
                            b=i;
                        }
                    }    
                }
                
            }
            eliminarDato(a,b);
        }

        //////////////ELIMINAR MAYOR DE CADA FILA/////////////
        void eliminarMayorFila(){
            Nodo<T> ** q; 
            for(int j = 0; j < n_fil;j++) {
                int may=0,a=0,b=0;
                for(int i = 0; i < n_col;i++ )
                {
                    if(find_fil(j,i,q) ){
                        if ((*q)->dato >  may ) {
                            may=(*q)->dato;
                            a=j;
                            b=i;
                        }
                    }    
                }
                eliminarDato(a,b);
            }
        }

         //////////////VACIAR MATRIZ/////////////
        void clear(){
            for (int i = 0; i < n_fil; i++) {
                for (int j = 0; j < n_col; j++) {
                    eliminarDato(i,j);
                }
            }
        }

         //////////////BUSCAR/////////////
        bool find(T d) {
            Nodo<T> ** q; 
            for(int j = 0; j < n_fil;j++) {
                for(int i = 0; i < n_col;i++ )
                {
                    if(find_col(j,i,q)) 
                    {
                        if((*q)->dato == d)
                        {
                            return true;
                        }
                    }
                }
            }
            return false;
        }
        


};
int main()
{
    MD<int,10,10> sparsa;
    int x;
    int a, b;
    int p,q;
    do
    {
        cout << "\nMENU\n";
        cout << "1) Generar Matriz Diagonal\n";
        cout << "2) Imprimir Matriz\n";
        cout << "3) Insertar Dato\n";
        cout << "4) Mostrar Mayor de cada Fila\n";
        cout << "5) Suma de Columnas\n";
        cout << "6) Mostrar pares de cada Fila\n";
        cout << "7) Eliminar dato\n";
        cout << "8) Eliminar Pares\n";
        cout << "9) Eliminar Mayor\n";
        cout << "10) Eliminar mayor de cada Fila\n";
        
        cout << "11) Buscar\n";
        cout << "12) Clear\n";
        cout << "13) SALIR\n";
        cout << "\nIngrese la opcion: ";
        cin >> a;
        switch (a)
        {
            case 1:
                for(int i = 0 ; i < 10; i++)
                {
                    int j = i+1;
                    sparsa.insert(i,i,j);
                    
                }

                break;
            case 2:
                cout << endl;
                cout << " -------MATRIZ ESPARZA ------- "<<endl;
                sparsa.print();
                break;

            case 3:
                int f, c, d;
                cout << "*Ingrese fila:"<<endl; cin>>f;
                cout << "*Ingrese columna:"<<endl; cin>>c;
                cout << "*Ingrese dato:"<<endl; cin>>d;
                cout<< "-> Dato insertado: "<< sparsa.insertarDato(f,c,d) <<endl;
                sparsa.print();
                break;
            case 4:
                sparsa.mostrarMayorFila();
                break;

            case 5:
                sparsa.sumaColumnas();
                break;
            
            case 6:
                sparsa.mostrarParesFilas();
                break;

            case 7:
                cout << endl;
                cout << " Ingrese fila del valor a eliminar: ";cin >> p;
                cout << " Ingrese columna del valor a eliminar: ";cin >> q;
                sparsa.eliminarDato(p,q);
                cout << endl;
                break;
            case 8:
                cout << endl;
                cout<<"Eliminando Pares "<<endl;
                sparsa.eliminarPares();
                cout << endl;
                break;
            case 9:
                cout << endl;
                cout<<"Eliminando Mayor "<<endl;
                sparsa.eliminarMayor();
                break;
            case 10:
                cout << endl;
                cout<<"Eliminando  Mayor de cada Fila "<<endl;
                sparsa.eliminarMayorFila();
                break;
            case 11:
                cout << endl;
                cout << " Ingrese valor para buscar : ";
                cin >> x;
                cout << (sparsa.find(x) ? " Encontrado" : " No encontrado") << endl;
                cout << endl;
                break;
            case 12:
                cout << endl;
                cout<<"Vaciando matriz esparza "<<endl;
                sparsa.clear();
                break;

            case 13:
                cout << endl;
                cout << "Seguro que quiere salir?(SI=1)(NO=0) :";
                cin >> b;
                cout << endl;
                if (b == 1)
                    a = 0;
                else if(b == 0)
                    break;
        }
    } while (a != 0);
    return 0;
}
