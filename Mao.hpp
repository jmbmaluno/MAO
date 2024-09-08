#ifndef MAO_H
#define MAO_H

#include "Elemento.hpp"
#include <climits>


//Calcula o piso do log de k na base 2
int log(int k){
    int res = 0;

    while (k != 1){
        k = k >> 1;
        res++;
    }

    return res;

}

class Mao{

    Elemento* vetor;
    int len;
    int altura;

    typedef struct{
        float d;
        int validos;
        int total;
    } Densidade;

    typedef struct{
        int pos;
        int pos_ant;
        int pos_suc;
    } ValorBusca;

    //Calcula a densidade dentro do intervalo i até j
    Densidade densidade(int i, int j, int validos = 0, int total = 0, bool inc = true){
        
        //Contando a qtde de elementos validos no vetor + 1 (que é o elemento que eu quero inserir)
        int qtde_validos;

        if(inc){
            qtde_validos = 1;
        }
        else{
            qtde_validos = 0;
        }

        int qtde_total = 0;


        if(validos != 0 && total != 0){
            qtde_validos = validos;
            qtde_total = total;
        }
        
        for(int k = i; k <= j; k++){
            if(vetor[k].valido){
                qtde_validos++;
            }

            qtde_total++;
        }
        
        return {(float)qtde_validos/qtde_total, qtde_validos, qtde_total};
    
    }

    ValorBusca busca_binaria(int pos_inicial, int pos_final, int k){
        int ant;
        int suc;


        if(pos_final < pos_inicial) {

            //Nesse caso, eu não achei k e sua posição no vetor será -1
            //Mas eu pegarei o resultado da pos_final para checar onde está o antecessor e sucessor
            //Partindo da pos_final, andarei para esquerda até achar um valor válido e esse será o antecessor
            //Partiando da pos_final, andarei para direita até achar um valor válido e esse será o sucessor
            //Se chegar no fim do vetor e não tiver antecessor válido, então ant = -1
            //Se chegar no fim do vetor e não tiver sucessor válido, então suc = len


            //buscando antecessor
            ant = pos_final;

            while(ant >= 0 && vetor[ant].valido == false){
                ant--;
            }

            //buscando sucessor
            suc = pos_final+1;

            while(suc <= len-1 && vetor[suc].valido == false){
                suc++;
            }

            return {-1, ant, suc};
        }

        int pos = (pos_inicial + pos_final)/2;

        if(vetor[pos].valido && vetor[pos].chave == k){
            
            //Nesse caso, achei k, logo partirei da posição dele para procurar linearmente o suc e o antecessor
            
            ant = pos-1;

            while(ant >= 0 && vetor[ant].valido == false){
                ant--;
            }

            suc = pos+1;
            while(suc <= len-1 && vetor[suc].valido == false){
                suc++;
            }
            
            return {pos,ant,suc};
        } 
        else{
            if(vetor[pos].valido && vetor[pos].chave < k) return busca_binaria(pos+1, pos_final, k);

            if(vetor[pos].valido && vetor[pos].chave > k) return busca_binaria(pos_inicial, pos-1, k);

            else{
                int n = len;
                int folha = pos/log(n);

                int qtde_por_folha = n/log(n);

                if(n != 2 && log(n) % 2 == 1 && folha != ((n-1)/log(n))){
                    qtde_por_folha = qtde_por_folha + 1;
                }

                int pos_inicial_folha = qtde_por_folha * folha;

                int i;

                for(i = pos_inicial_folha; i <= pos_final; i++){
                    if(vetor[i].valido){
                        if(vetor[i].chave == k){

                            //Nesse caso pos caiu em um valor vazio mas procurando na folha dele eu achei k
                            //Partindo da posição de k procurarei seu sucessor e seu antecessor
                            ant = i - 1;

                            while(ant >= 0 && vetor[ant].valido == false){
                                ant--;
                            }

                            suc = i+1;

                            while(suc <= len-1 && vetor[suc].valido == false){
                                suc++;
                            }

                            return {i, ant, suc};
                        }

                        if(vetor[i].chave > k) return busca_binaria(pos_inicial, i-1, k);
                    }
                }

                return busca_binaria(i+1, pos_final, k);

            }
        }
    }

    public:

    //O vetor começa com apenas 2 elementos
    Mao(){
        vetor = new Elemento[2];

        vetor[0] = {0, false};
        vetor[1] = {0, false};
        len = 2;
        altura = log(len);
    }

    Mao(Elemento* v, int l){
        vetor = v;
        len = l;
        altura = log(len);
    }

    void imprimir(){
        for(int i = 0; i < len; i++){
            if(vetor[i].valido){
                cout << vetor[i].chave << " ";
            }
        }

        cout << "\n";
    }
    
    int sucessor(int k){
        ValorBusca v = busca_binaria(0,len-1,k);

        if(v.pos_suc == len || v.pos_ant == len-1){
            return INT_MAX;
        }

        return vetor[v.pos_suc].chave;

    }

    void inserir(int k, int profundidade = -2, int pos_filho = 0, int qtde_validos = 0, int qtde_total = 0, int ant = 0){
        int n = len;

        if(profundidade == -2){
            profundidade = log(n);
        }

        //Se tá tentando inserir na folha
        if(profundidade == log(n)){
            
            //posição do elemento anterior
            int ant = -1;

            //posição do elemento sucessor
            int i = 0;

            
            //Procurar entre quais posições o elemento vai ficar
            //Logo, vou procurar enquanto o elemento visto for invalido ou enquanto ele for valido e menor do que a chave que quero inserir
            ValorBusca v = busca_binaria(0, len-1, k);
            ant = v.pos_ant;

            //Vou incluir na folha do anterior
            int folha = ant/log(n);

            
            if(folha < 0){
                folha = 0;
            }

            int qtde_por_folha = n/log(n);


            //Caso de a folha ter tamanhos de intervalo diferentes. Ex: n = 8
            if(n != 2 && log(n) % 2 == 1 && folha != ((n-1)/log(n))){
                qtde_por_folha = qtde_por_folha + 1;
            }


            //Caso que n = 2, a folha já está cheia e quero incluir alguem maior do que todos os elementos
            if(qtde_por_folha * folha >= len){
                folha--;
            }

            //Calculando a posição em que folha começa e termina
            int pos_inicial = qtde_por_folha*folha;

            int pos_final = pos_inicial + qtde_por_folha-1;

            //Calculando a densidade do intervalo
            Densidade dens = densidade(pos_inicial, pos_final);
            
            //Se tá dentro do aceitável, então apenas rebalancear
            if(dens.d <= (3*log(n) + profundidade) / (4 * log(n))){
                rebalancear(vetor, pos_inicial, pos_final, k, ant);
            }
            //Se tá fora do aceitavel então chamo a função recursivamente para um nível acima
            else{
                inserir(k, profundidade-1, folha, dens.validos, dens.total, ant);
            }

           
        }
        else{
            if(profundidade >= 0){
                //Se meu filho é par, então tenho que fazer o scan para direita
                //Se meu filho é impar, então tenho que fazer o scan para esquerda

                int no = pos_filho >> 1;
                int pos_inicial = no * 2 * qtde_total;;
                int pos_final = pos_inicial + (2*qtde_total) -1;

                int inicial_filho = pos_filho * qtde_total;
                int final_filho = inicial_filho + qtde_total - 1;

                Densidade dens;

                //Caso do filho par
                if(pos_filho % 2 == 0){
                    //Caso de só ter um filho
                    if(pos_final >= len){
                        dens = densidade(inicial_filho, final_filho, qtde_validos, qtde_total);
                    }
                    else{
                        dens = densidade(final_filho + 1,pos_final, qtde_validos, qtde_total);
                    }
                }

                //Caso do filho impar
                else{
                    dens = densidade(pos_inicial, inicial_filho - 1, qtde_validos, qtde_total);
                }

                if(dens.d <= (float)(3*log(n) + profundidade) / (4 * log(n))){
                    rebalancear(vetor, pos_inicial, pos_final, k, ant);
                }

                else{
                    inserir(k, profundidade-1, no, dens.validos, dens.total, ant);
                }
            }
            
            //Caso de dobrar o tamanho do vetor
            else{
                len = 2*len;
                altura = log(len);
                Elemento* vetor_auxiliar = new Elemento[len];

                for(int i = 0; i < (len/2); i++){
                    vetor_auxiliar[i] = vetor[i];
                }

                //delete [] vetor;
                rebalancear(vetor_auxiliar, 0, len-1, k, ant);

                vetor = vetor_auxiliar;
            }
        }

    }

    //Praticamente igual ao algoritmo de inserir
    void remover(int k, int profundidade = -2, int pos_filho = 0, int qtde_validos = 0, int qtde_total = 0, int pos = 0){
        int n = len;

        if(profundidade == -2){
            profundidade = log(n);
        }

        if(profundidade == log(n)){
            
            //Pos de k no vetor
            int i = busca_binaria(0, len-1, k).pos;
            
            if(i > -1 && vetor[i].valido && vetor[i].chave == k){

                int folha = i/log(n);
            
                int qtde_por_folha = n/log(n);

                if(n != 2 && log(n) % 2 == 1 && folha != ((n-1)/log(n))){
                    qtde_por_folha = qtde_por_folha + 1;
                }

                int pos_inicial = qtde_por_folha * folha;

                int pos_final = pos_inicial + qtde_por_folha -1;

                vetor[i].valido = false;

                Densidade dens = densidade(pos_inicial, pos_final, false);

                if(dens.d >= (2*log(n) - profundidade)/(4*log(n))){
                    rebalancear(vetor, pos_inicial, pos_final, i);
                }

                else{
                    remover(k, profundidade-1, folha, dens.validos, dens.total, i);
                }
            }

        }
        else{
            if(profundidade >= 0){
                int no = pos_filho >> 1;
                int pos_inicial = no * 2 * qtde_total;
                int pos_final = pos_filho * qtde_total;

                int inicial_filho = pos_filho * qtde_total;
                int final_filho = inicial_filho * qtde_total -1;

                Densidade dens;

                if(pos_filho % 2 == 0){
                    if(pos_final >= len){
                        dens = densidade(inicial_filho, final_filho, qtde_validos, qtde_total, false);
                    }
                    else{
                        dens = densidade(final_filho + 1, pos_final, qtde_validos, qtde_total, false);
                    }
                }

                else{
                    dens = densidade(pos_inicial, inicial_filho-1, qtde_validos, qtde_total, false);
                }

                if(dens.d >= (2*log(n) - profundidade)/(4*log(n))){
                    rebalancear(vetor, pos_inicial, pos_final, pos);
                }

                else{
                    remover(k, profundidade-1, no, dens.validos, dens.total, pos);
                }
            }
            else{

                len = len/2;
                altura = log(len);
                Elemento* vetor_auxiliar = new Elemento[len];
                int cont_aux = 0;

                for(int i = 0; i < 2*len; i++){
                    if(vetor[i].valido){
                        vetor_auxiliar[cont_aux] = vetor[i];
                        cont_aux++;
                    }
                }

                rebalancear(vetor_auxiliar, 0, len-1);

                vetor = vetor_auxiliar;
            }
        }
    }

};


#endif