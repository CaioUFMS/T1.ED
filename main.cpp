#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <cctype>
#include <fstream>

using namespace std;

string Minuscula(string s) // Função que transforma todo um texto em letras minúsculas
{
	string nova_s;

	for(int i = 0; i < s.length(); i++)
		nova_s += tolower(s[i]);
	
	return nova_s;
}

void PrintCalculaD(int m, int d[])
{
	for(int i = 0; i < m; i++)
	{
		cout << "d[" <<i << "] = " << d[i]+1 << endl;
	}
}

void CalculaD(string Y, int m, int d[])
{
	int j = 0, k = 1;
	d[0] = -1;
	while(k < m)
	{
		/*cout << Y[j] << " " << Y[k] <<endl;
		cout << j << " " << k <<endl;//*/


		if(Y[k] == Y[j])
		{
			d[k] = j;
			j++;
			k++;
		}
		else
		{
			//cout << j << " " << k << endl;
			if(j == 0)
			{
				d[k] = -1;
				k++;
			}
			else
				j = d[j-1]+1;
		}//*/
	}
}

int KMP(string X, string Y, int n, int m, int d[], int contaLinha)
{
	int i = 0, j = 0, contador = 0;
  int casamentos[(X.size()/Y.size())];
	bool igual;

	while(i-j <= n-m)
	{
		igual = true;
		while(j < m && igual == true)
		{
			if(X[i] == Y[j])
			{
				i++;
				j++;
			}
			else
			{
				igual = false;
			}
			//contador++;
		}

		if(igual)
		{
			//cout << Y << " " <<  contaLinha << endl;
			//cout << "Houve casamento de " << Y << " na linha: " << contaLinha << endl;
			//cout << "Iterações = " << contador << endl;
      casamentos[contador] = i - m;
      contador++;
		}

		if(j == 0)
		{
			i++;
			//contador++;
		}
		else
		{
			j = d[j-1]+1;
			//contador++;
		}
	}
	//cout << "Não houve casamento" << endl;
	//cout << "Iterações = " << contador << endl;
  if(contador == 0){
    return -1;
  }else{
    return contador;
  }
	
}


int main(int argc, char *argv[])
{
  //Declara recursos utilizados para a checagem
  ifstream arqPalavra;
  fstream novaString;
  string cadeia;
  string minuscula;
  string palavra;
  int contaLinha;
  int resultKmp;
  string palavraResult;
  string palavraAtual;
  string linha;

  //Abre o arquivo de palavras
  arqPalavra.open(argv[2]);
  if(arqPalavra.is_open()){
    //Executa um loop para cada palavra do arquivo
    while(arqPalavra >> palavra){
      //Prepara e realiza o pré-processamento da palavra
      	int m = palavra.size();
	    int d[m];
	    CalculaD(palavra, m, d);
      //Reinicia recursos para a saida das palavras
      contaLinha = 1;
      palavraAtual.clear();

      //Abre o arquivo de texto para busca
      novaString.open(argv[1],ios::in);
      if (novaString.is_open()){
        //Executa um loop de busca para cada linha do texto
        while(getline(novaString, linha)){
          linha = Minuscula(linha);
          int n = linha.size();
          resultKmp = KMP(linha, palavra, n, m, d, contaLinha);
          /*[TODO] Buscar palavra na linha com KMP*/
          //Checa se houve casamento
          if(resultKmp != -1){
            //Coloca o numero da linha na String X vezes, X sendo a quantidade de ocorrências
            for(int c = 1; c <= resultKmp; c++){
              //Se for o primeiro casamento, inicia a string de saída, se não, concatena a linha do novo casamento ao final dela
              if(palavraAtual.empty()){
                palavraAtual = palavra + " " + to_string(contaLinha);
              } else {
                palavraAtual = palavraAtual + " " + to_string(contaLinha);
              }
            }
          }
          //Finaliza o loop da linha aumentando a contagem
          contaLinha++;
        }
      //Após todos os loops de linha, fecha o arquivo
      novaString.close();
      }
      //Finaliza o loop da palavra, adicionando a string da palavra a string resultado
      if(!palavraAtual.empty()){
        if(palavraResult.empty()){
          palavraResult = palavraAtual;
        }else{
          palavraResult = palavraResult + "\n" + palavraAtual;
        }
      }
      }
    }
    //Após todos os loops da palavras, adiciona a saida ao arquivo e o fecha
    if(!palavraResult.empty()){
        //Abre o arquivo de saida
        novaString.open("saida.txt",ios::out);
        //Adiciona a string da palavra ao arquivo e passa para a proxima linha e fecha o arquivo
        cout << palavraResult;
        if (novaString.is_open()){
          novaString << palavraResult;
          novaString.close();
        }
    arqPalavra.close();
  }

  
	/*for(int i = 1; i < argc; i++)
		cout << argv[i] << endl;
  */
	/*ifstream arquivoE; Abrir arquivo, ler, deu certo...

	

	arquivoE.open("texto.txt"); 

	if(arquivoE.is_open()) {
		while(getline(arquivoE, linha)) {
			
			cout << linha << endl;
		}

	} else {
		cout << "N é possivel abrir" << endl;
	}*/

	

	/*int n = cadeia.size() - 1;
	int m = palavra.size() -1;


	int d[m];
	CalculaD(palavra, m, d);*/
	//PrintCalculaD(m, d);



	//cout << cadeia << endl;

	



	//cout << cadeia << endl << palavra << endl;

	//KMP(cadeia, palavra, n, m, d);


    return 0;
}
