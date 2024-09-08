#include "Mao.hpp"
#include <fstream>

/*
João Marcos Brito Matias - 494952
Manutenção de Arquivos Ordenados
*/
 
int main(int nargs, char* argv[]){

    if(nargs <= 1){
        
        cout << "não há argumentos suficientes para o programa rodar\n";
        cout << "Tente colocar como argumento o txt para executar ações na árvore\n";
        return 1;

        return 0;
    }

    string entrada = argv[1];

    ifstream arq (entrada.data());

    string s;

    Mao M;
    int v = 0;
    int linha = 0;

    while(!arq.eof()){
        string instrucao;

        try{
            if(getline(arq, s)){
                instrucao = s.substr(0, 3);
                linha = linha + 1;

                if("INC" == s.substr(0,3)){ 
                    M.inserir(stoi(s.substr(4)));
                }

                if("IMP" == s.substr(0,3)){
                    M.imprimir();
                }

                if("REM" == s.substr(0,3)){
                    M.remover(stoi(s.substr(4)));
                }

                if("SUC" == s.substr(0,3)){

                    int res =  M.sucessor(stoi(s.substr(4)));

                    if(res == INT_MAX) cout << "INFINITO\n";
                    else cout << res << "\n";
                }
            }
        }
        catch(exception& e){
            cout << "\nERRO: A INSTRUÇÃO '" << instrucao <<"' NA LINHA " << linha <<" NÃO ESTÁ ESCRITA CORRETAMENTE\n";

            
            if("INC" == instrucao) cout << "O correto é 'INC' 'valor que será incluso'\n";
            if("REM" == instrucao) cout << "O correto é 'REM' 'valor que será removido'\n";
            if("SUC" == instrucao) cout << "O correto é 'SUC' 'valor que será buscado' 'versão'\n";
            if("IMP" == instrucao) cout << "O correto é 'IMP' 'versão'\n";

            cout << "Corrija o arquivo de texto\n\n";

        

            return 1;
        }
    }
}
