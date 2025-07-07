#ifndef CLUB_H
#define CLUB_H
#define MAX_CLIENTI 100
struct Cliente {
    char nome_completo[100];
    struct Cliente *next;
};

struct Corso {
    char nome[50];
    int posti_disponibili;
    struct Cliente *prenotati;
    int num_prenotati;
    struct Corso *next;
};

struct Club {
    struct Cliente *elenco_clienti;
    struct Corso *elenco_corsi;
};

void aggiungiClienteAllaFine(struct Cliente **testa, struct Cliente *nuovo_cliente);
void aggiungiCliente(struct Cliente **elenco_clienti, char *nome_completo);
void visualizzaClienti(struct Cliente *elenco_clienti);
void caricaClientiDaFile(struct Cliente **elenco_clienti);

void aggiungiCorso(struct Corso **elenco_corsi, char *nome, int posti_disponibili);
void visualizzaCorsi(struct Corso *elenco_corsi);
void registraCliente(struct Corso *corso, struct Cliente *cliente);

#endif

