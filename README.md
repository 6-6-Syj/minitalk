# minitalk

## Qu'est-ce qu'un signal ?

Un signal est une forme de communication inter-processus utilisée dans les systèmes Unix et POSIX. Il s'agit d'une notification asynchrone envoyée à un processus en cours d'exécution pour l'informer d'un événement spécifique.

Lorsqu'un signal est reçu, le système d'exploitation interrompt l'exécution normale du processus et déclenche une réaction prédéfinie, qui peut inclure la terminaison du processus.

Ce mécanisme permet une communication limitée mais efficace entre les processus, offrant un moyen standardisé de gérer diverses situations système.

## Envoyer un signal avec l'appel système `kill` en C

Dans un précédent article sur la création et la terminaison de processus fils, on a rapidement vu l'appel système kill de la bibliothèque signal.h. Il existe plusieurs autres appels systèmes pour demander au système d'envoyer un signal depuis notre programme en C, mais celui-ci est le plus communément utilisé. Rappelons son prototype :

    int kill(pid_t pid, int sig);
Ses paramètres sont :

-   pid : l'identifiant du processus ou du groupe de processus auquel envoyer le signal. On peut ici spécifier :
    -   un entier positif : le PID d'un processus,
    -   un entier négatif : le PGID d'un groupe de processus,
    -   0 : tous les processus dans le groupe du processus appelant,
    -   -1 : tous les processus dans le système pour lequel le processus appelant a la permission d'envoyer un signal (sauf le processus 1, init).
    -   sig : le signal à envoyer au processus.

La fonction kill renvoie 0 en cas de succès et en cas d'erreur, -1, avec `errno mis à jour pour indiquer les détails de l'erreur.

## Utilisation de sigaction

    int sigaction(int signum, const struct sigaction *restrict act, struct sigaction *restrict oldact);
    
Paramètres :
-   signum : le signal pour lequel on souhaite changer l'action,
-   act : un pointeur vers une structure de type sigaction qui va permettre entre autres d'indiquer une routine de gestion de signaux,
-   oldact : un pointeur vers une autre structure de type sigaction dans lequel on souhaiterait sauvegarder l'ancien comportement en réaction au signal. Si l'on n'a pas particulièrement besoin de sauvegarder l'ancienne réaction, on peut simplement mettre NULL ici.

En cas de succès, sigaction renvoie 0. En cas d'erreur, elle renvoie -1 et renseigne errno

### Indiquer une routine de gestion de signaux dans la structure sigaction

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
        bzero(&act, sizeof(act));
        act.sa_handler = &sigint_handler;
        sigaction(SIGINT, &act, NULL);
    }
    
    int main(void)
    {
        set_signal_action();
        while (1)
        continue;
        return (0);
    }

Ce programme intercepte le signal SIGINT (Ctrl+C) et affiche un message au lieu de terminer le processus.

La variable sa_handler de la structure sigaction spécifie l'action qui doit être associée au signal. On peut lui indiquer une de trois choses :

-   SIG_DFL pour l'action par défaut,
-   SIG_IGN pour ignorer le signal,
-   un pointeur vers une routine de gestion de signal.


