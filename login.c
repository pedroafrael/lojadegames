#include <stdio.h>
#include <string.h>
#include "login.h"

const char usuarioCorreto[] = "pedro";
const char senhaCorreta[] = "123456";

int login() {
    char usuario[MAX_USUARIO];
    char senha[MAX_SENHA];

    while (1) {
        printf("Usuario: ");
        scanf("%49s", usuario);
        printf("Senha: ");
        scanf("%49s", senha);

        if (strcmp(usuario, usuarioCorreto) == 0 && strcmp(senha, senhaCorreta) == 0) {
            printf("Login realizado com sucesso!\\n");
            return 1;
        } else {
            printf("Usuario ou senha incorretos. Tente novamente.\\n");
        }
    }
}

int verificaEmailValido(const char *email) {
    if (strlen(email) >= MAX_EMAIL) return 0;

    if (strchr(email, '@') == NULL) return 0;

    return 1;
}

int emailExiste(const char *email) {
    FILE *fp = fopen("emails_cadastrados.txt", "r");
    if (!fp) return 0;

    char linha[MAX_EMAIL];
    while (fgets(linha, sizeof(linha), fp)) {
        linha[strcspn(linha, "\\n")] = 0;
        if (strcmp(linha, email) == 0) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}
