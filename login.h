#ifndef LOGIN_H
#define LOGIN_H

#define MAX_USUARIO 50
#define MAX_SENHA 50
#define MAX_EMAIL 80

int login();
int verificaEmailValido(const char *email);
int emailExiste(const char *email);

#endif
