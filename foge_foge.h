#define CIMA 'w'
#define BAIXO 's'
#define ESQUERDA 'a'
#define DIREITA 'd'
#define AVATAR '@'
#define FANTASMA 'F'
#define VAZIO '.'
#define PAREDE_VERTICAL '|'
#define PAREDE_HORIZONTAL '-'

// Variáveis globais
struct mapa {
    char** matriz;
    int linhas;
    int colunas;
};

typedef struct mapa MAPA;

struct posicao {
    int x;
    int y;
};

typedef struct posicao POSICAO;

// Lista das funções do jogo

void copiamapa(MAPA* destino, MAPA* origem);
int paraondevaiofantasma(int xatual, int yatual, int* xdestino, int* ydestino);
void fantasmas();
int ehparede(MAPA* m, int x, int y);
int ehumpersonagem(MAPA* m, char personagem, int x, int y);
int podeandar(MAPA* m, char personagem, int x, int y);
void liberarmapa(MAPA* m);
void alocarmapa(MAPA* m);
void lermapa(MAPA* m);
void imprimirmapa(MAPA* m);
int acabou();
int encontramapa(MAPA* m, POSICAO* p,char c);
int ehdirecao(char direcao);
int ehvalida(MAPA* m, int x, int y);
int ehvazia(MAPA* m, int x, int y);
void andanomapa(MAPA* m, int xorigem, int yorigem, int xdestino, int ydestino);
void move(char direcao);