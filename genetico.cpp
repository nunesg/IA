#include <bits/stdc++.h>

using namespace std;

#define N 5

int get_rand(int mx){//gera numero aleatorio
    return ((rand()<<16)^rand())%mx;
}

struct state{
    int vet[8], fit;
    state(){
        for(int i=0; i<8; i++) vet[i] = get_rand(8);
    }
    state(int v[]){
        for(int i=0; i<8; i++) vet[i] = v[i];
    }

    int calc_fitness(){
        int ans=0;
        for(int i=0; i<8; i++){
            for(int j=0; j<8; j++){
                if(vet[i] == vet[j]) continue;//checa linhas iguais
                if(abs(i-j) == abs(vet[i]-vet[j])) continue;//checa diagonais
                ans++;
            }
        }
        return fit = ans/2;
    }
};


state go_genetic(state v[], int &ger){
    int flag=-1;//checa se ja achou a resposta ótima

    vector<state> vet;
    ger=0;
    do{
        //printf("GERACAO %d\n", ger);
        int maior=0;
        for(int i=0; i<N; i++){
            if(v[i].calc_fitness() == 28) flag = i;
            if(v[i].fit > v[maior].fit) maior= i;
            for(int j=0; j<v[i].fit; j++) vet.push_back(v[i]);
        }

        if(flag != -1) break;//achou resposta

        swap(v[0], v[maior]);//mantem o melhor na selecao
        for(int i=1; i<N; i++){//selecao
            int p = get_rand((int)vet.size());
            v[i] = vet[p];
        }
        vet.clear();

        for(int i=0; i<N-1; i+=2){//cross entre amostras adjacentes
            for(int j=0; j<8; j++){
                if(get_rand(100)<50) swap(v[i].vet[j], v[i+1].vet[j]);
            }
            for(int j=0; j<8; j++){//mutacao
                if(get_rand(100)<10) v[i].vet[j] = get_rand(8);
            }
        }
        ger++;
    }while(flag == -1);
    return v[flag];
}


int main(){

    srand(time(NULL));

    state v[N];
    int g=0;
    state ans = go_genetic(v, g);
    printf("\nGERACAO DA RESPOSTA = %d\n", g);
    for(int i=0; i<8; i++){
        printf("%d, ", ans.vet[i]);
        if(i==7) printf("\n");
    }
}
