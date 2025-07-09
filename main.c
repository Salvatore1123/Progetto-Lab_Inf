#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "club.h"

int main() {
    struct Club club = {NULL, NULL};
    char nome_completo[100];
    char scelta;

    caricaClientiDaFile(&club.elenco_clienti);
    aggiungiCorso(&club.elenco_corsi, "Padel", 20);
    aggiungiCorso(&club.elenco_corsi, "Tennis", 15);
    aggiungiCorso(&club.elenco_corsi, "Ping pong", 10);
    aggiungiCorso(&club.elenco_corsi, "Badminton", 25);

    printf("RACKET CLUB\n");
    printf("\nMenu:\n");
    printf("1. Inserisci un nuovo cliente\n");
    printf("2. Visualizza tutti i clienti\n");
    printf("3. Visualizza corsi disponibili\n");
    printf("4. Prenota un corso\n");
    printf("5. Esci\n");

    while (1) {
        printf("\nScelta: ");
        scanf(" %c", &scelta);
        if (scelta == '1') {
            printf("\nInserisci il nome e cognome del cliente, o 'x' per terminare: ");
            getchar();
            fgets(nome_completo, sizeof(nome_completo), stdin);
            nome_completo[strcspn(nome_completo, "\n")] = '\0';
            if (strcmp(nome_completo, "x") != 0) {
                aggiungiCliente(&club.elenco_clienti, nome_completo);
                FILE *file = fopen("clienti_club.txt", "a");
                if (file != NULL) {
                    fprintf(file, "%s\n", nome_completo);
                    fclose(file);
                }
                printf("Cliente aggiunto con successo!\n");
            }
        } else if (scelta == '2') {
            visualizzaClienti(club.elenco_clienti);
        } else if (scelta == '3') {
            visualizzaCorsi(club.elenco_corsi);
        } else if (scelta == '4') {
            int corso_scelto;
            struct Cliente *cliente_scelto = NULL;


            if (club.elenco_corsi == NULL) {
                printf("Nessun corso disponibile al momento.\n");
            } else {

                visualizzaCorsi(club.elenco_corsi);
                printf("\nInserisci il numero del corso: ");
                scanf("%d", &corso_scelto);

                printf("\nInserisci il nome e cognome del cliente: ");
                getchar();
                fgets(nome_completo, sizeof(nome_completo), stdin);
                nome_completo[strcspn(nome_completo, "\n")] = '\0';

                struct Cliente *p = club.elenco_clienti;
                while (p != NULL && cliente_scelto == NULL) {
                    if (strcmp(p->nome_completo, nome_completo) == 0) {
                        cliente_scelto = p;
                      }
                    p = p->next;
                }
                    if (cliente_scelto == NULL) {

                printf("Cliente non trovato.\n");
                } else {
                    struct Corso *corso = club.elenco_corsi;
                    int i = 1;
                    while (corso != NULL && i < corso_scelto) {
                        corso = corso->next;
                        i++;
                    }
                    if (corso != NULL) {
                        registraCliente(corso, cliente_scelto);
                    } else {
                        printf("Corso non valido.\n");
                    }
                }
            }
        } else if (scelta == '5') {

            printf("Arrivederci!\n");
            return 0;
        } else {
            printf("Scelta non valida. Riprova.\n");
                    }
    }
    return 0;
}

