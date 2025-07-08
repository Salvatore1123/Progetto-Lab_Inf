#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "club.h"

void aggiungiClienteAllaFine(struct Cliente **testa, struct Cliente *nuovo_cliente) {
    if (*testa == NULL) {
        *testa = nuovo_cliente;
        nuovo_cliente->next = NULL;
    } else {
        struct Cliente *p = *testa;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = nuovo_cliente;
        nuovo_cliente->next = NULL;
    }
}

void aggiungiCliente(struct Cliente **elenco_clienti, char *nome_completo) {
    struct Cliente *nuovo_cliente = (malloc)(sizeof(struct Cliente));

    strcpy(nuovo_cliente->nome_completo, nome_completo);
    nuovo_cliente->next = NULL;

    aggiungiClienteAllaFine(elenco_clienti, nuovo_cliente);
}

void aggiungiCorso(struct Corso **elenco_corsi, char *nome, int posti_disponibili) {
    struct Corso *nuovo_corso = (malloc)(sizeof(struct Corso));

    strcpy(nuovo_corso->nome, nome);
    nuovo_corso->posti_disponibili = posti_disponibili;
    nuovo_corso->prenotati = NULL;
    nuovo_corso->num_prenotati = 0;
    nuovo_corso->next = *elenco_corsi;
    *elenco_corsi = nuovo_corso;
}

void visualizzaClienti(struct Cliente *elenco_clienti) {
    printf("\nLista dei clienti registrati:\n");
    while (elenco_clienti != NULL) {
        printf("%s\n", elenco_clienti->nome_completo);
        elenco_clienti = elenco_clienti->next;
    }
}
void visualizzaCorsi(struct Corso *elenco_corsi) {
    printf("\nCorsi disponibili:\n");
    int numero_corso = 1;
    while (elenco_corsi != NULL) {
        printf("%d. %s - Posti disponibili: %d\n", numero_corso, elenco_corsi->nome, elenco_corsi->posti_disponibili);
        printf("   Prenotati: ");
        if (elenco_corsi->num_prenotati == 0) {
            printf("Nessun cliente prenotato.\n");
        } else {
            struct Cliente *p = elenco_corsi->prenotati;
            while (p != NULL) {
                printf("%s", p->nome_completo);
                if (p->next != NULL) {
                    printf(", ");
                }
                p = p->next;
            }
            printf("\n");
        }
        elenco_corsi = elenco_corsi->next;
        numero_corso++;
    }
}

void registraCliente(struct Corso *corso, struct Cliente *cliente) {
    if (corso->num_prenotati < corso->posti_disponibili) {

        struct Cliente *nuovo_prenotato = (malloc)(sizeof(struct Cliente));
        strcpy(nuovo_prenotato->nome_completo, cliente->nome_completo);
        nuovo_prenotato->next = corso->prenotati;

        corso->prenotati = nuovo_prenotato;
        corso->num_prenotati++;
        corso->posti_disponibili--;

        printf("Cliente registrato per il corso di %s.\n", corso->nome);
    } else {
        printf("Spiacenti, il corso di %s   pieno.\n", corso->nome);
    }
}

void caricaClientiDaFile(struct Cliente **elenco_clienti) {
    FILE *file = fopen("clienti_club.txt", "r");
    if (file == NULL) {
        printf("Errore durante l'apertura del file clienti_club.txt.\n");
        return;
    }

    char nome_completo[100];
    while (fgets(nome_completo, sizeof(nome_completo), file) != NULL) {
        nome_completo[strcspn(nome_completo, "\n")] = '\0';
        aggiungiCliente(elenco_clienti, nome_completo);
    }

    fclose(file);
}

