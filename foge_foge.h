// Lista das funções do jogo
void liberarmapa();
void alocarmapa();
void lermapa();
void imprimirmapa();
int acabou();
void move(char direcao);

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