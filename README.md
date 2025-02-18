# <span style="color:#6e5494; font-size:2.5em;">minitalk</span>

## <span style="color:#82AAFF; font-size:1.8em;">Qu'est-ce qu'un signal ?</span>

Un signal est une forme de communication inter-processus utilisée dans les systèmes <span style="color:#c792ea;">Unix</span> et <span style="color:#c792ea;">POSIX</span>. Il s'agit d'une notification asynchrone envoyée à un processus en cours d'exécution pour l'informer d'un événement spécifique.

Lorsqu'un signal est reçu, le système d'exploitation interrompt l'exécution normale du processus et déclenche une réaction prédéfinie, qui peut inclure la terminaison du processus.

Ce mécanisme permet une communication limitée mais efficace entre les processus, offrant un moyen standardisé de gérer diverses situations système.

## <span style="color:#82AAFF; font-size:1.8em;">Envoyer un signal avec l'appel système `kill` en C</span>

Dans un précédent article sur la création et la terminaison de processus fils, on a rapidement vu l'appel système `<span style="color:#c792ea;">kill</span>` de la bibliothèque `<span style="color:#c792ea;">signal.h</span>`. Il existe plusieurs autres appels systèmes pour demander au système d'envoyer un signal depuis notre programme en C, mais celui-ci est le plus communément utilisé. Rappelons son prototype :

int kill(pid_t pid, int sig);
Ses paramètres sont :

-   `<span style="color:#c792ea;">pid</span>` : l'identifiant du processus ou du groupe de processus auquel envoyer le signal. On peut ici spécifier :
    -   un entier positif : le PID d'un processus,
    -   un entier négatif : le PGID d'un groupe de processus,
    -   0 : tous les processus dans le groupe du processus appelant,
    -   -1 : tous les processus dans le système pour lequel le processus appelant a la permission d'envoyer un signal (sauf le processus 1, init).
-   `<span style="color:#c792ea;">sig</span>` : le signal à envoyer au processus.

La fonction `<span style="color:#c792ea;">kill</span>` renvoie 0 en cas de succès et en cas d'erreur, -1, avec `<span style="color:#c792ea;">errno</span>` mis à jour pour indiquer les détails de l'erreur.

## <span style="color:#82AAFF; font-size:1.8em;">Utilisation de sigaction</span>

int sigaction(int signum, const struct sigaction *restrict act, struct sigaction *restrict oldact);
Paramètres :

-   `<span style="color:#c792ea;">signum</span>` : le signal pour lequel on souhaite changer l'action,
-   `<span style="color:#c792ea;">act</span>` : un pointeur vers une structure de type `<span style="color:#c792ea;">sigaction</span>` qui va permettre entre autres d'indiquer une routine de gestion de signaux,
-   `<span style="color:#c792ea;">oldact</span>` : un pointeur vers une autre structure de type `<span style="color:#c792ea;">sigaction</span>` dans lequel on souhaiterait sauvegarder l'ancien comportement en réaction au signal. Si l'on n'a pas particulièrement besoin de sauvegarder l'ancienne réaction, on peut simplement mettre NULL ici.

En cas de succès, `<span style="color:#c792ea;">sigaction</span>` renvoie 0. En cas d'erreur, elle renvoie -1 et renseigne `<span style="color:#c792ea;">errno</span>`.

### <span style="color:#82B1FF; font-size:1.5em;">Indiquer une routine de gestion de signaux dans la structure sigaction</span>

#include <signal.h>
#include <stdio.h>
#include <strings.h>

// Routine de gestion de SIGINT
void sigint_handler(int signal)
{
if (signal == SIGINT)
printf("\nIntercepted SIGINT!\n");
}

void set_signal_action(void)
{
struct sigaction act;

La variable `<span style="color:#c792ea;">sa_handler</span>` de la structure `<span style="color:#c792ea;">sigaction</span>` spécifie l'action qui doit être associée au signal. On peut lui indiquer une de trois choses :

-   `<span style="color:#c792ea;">SIG_DFL</span>` pour l'action par défaut,
-   `<span style="color:#c792ea;">SIG_IGN</span>` pour ignorer le signal,
-   un pointeur vers une routine de gestion de signal.

### <span style="color:#82B1FF; font-size:1.5em;">Exemple de code</span>

bzero(&act, sizeof(act));
act.sa_handler = &sigint_handler;
sigaction(SIGINT, &act, NULL);

int main(void)
{
set_signal_action();
while (1)
continue;
return (0);
}

Ce programme intercepte le signal `<span style="color:#c792ea;">SIGINT</span>` (Ctrl+C) et affiche un message au lieu de terminer le processus.
