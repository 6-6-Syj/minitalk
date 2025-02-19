# MINITALK

##     1. Qu'est-ce qu'un signal ?

Un signal est une forme de communication inter-processus utilisée dans les systèmes Unix et POSIX. Il s'agit d'une notification asynchrone envoyée à un processus en cours d'exécution pour l'informer d'un événement spécifique.

Lorsqu'un signal est reçu, le système d'exploitation interrompt l'exécution normale du processus et déclenche une réaction prédéfinie, qui peut inclure la terminaison du processus.

Ce mécanisme permet une communication limitée mais efficace entre les processus, offrant un moyen standardisé de gérer diverses situations système.

##     2. Envoyer un signal avec l'appel système `kill` en C

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

##     3. Utilisation de sigaction

    int sigaction(int signum, const struct sigaction *restrict act, struct sigaction *restrict oldact);
    
Paramètres :
-   signum : le signal pour lequel on souhaite changer l'action,
-   act : un pointeur vers une structure de type sigaction qui va permettre entre autres d'indiquer une routine de gestion de signaux,
-   oldact : un pointeur vers une autre structure de type sigaction dans lequel on souhaiterait sauvegarder l'ancien comportement en réaction au signal. Si l'on n'a pas particulièrement besoin de sauvegarder l'ancienne réaction, on peut simplement mettre NULL ici.

En cas de succès, sigaction renvoie 0. En cas d'erreur, elle renvoie -1 et renseigne errno

##     4. Indiquer une routine de gestion de signaux dans la structure sigaction

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

##    5. Structures & types

###    struct sigaction
The sigaction() system call is used to change the action taken by
       a process on receipt of a specific signal.  (See signal(7) for an
       overview of signals.)

   signum specifies the signal and can be any valid signal except
   SIGKILL and SIGSTOP.

   If act is non-NULL, the new action for signal signum is installed
   from act.  If oldact is non-NULL, the previous action is saved in
   oldact.

The sigaction structure is defined as something like:

        struct sigaction	{
        void		(*sa_handler)(int);
        void		(*sa_sigaction)(int, siginfo_t *, void *);
        sigset_t	sa_mask;
        int			sa_flags;
        void		(*sa_restorer)(void);
        };

On some architectures a union is involved: do not assign to both
       sa_handler and sa_sigaction.

   The sa_restorer field is not intended for application use.  (POSIX
   does not specify a sa_restorer field.)  Some further details of
   the purpose of this field can be found in sigreturn(2).

   sa_handler specifies the action to be associated with signum and
   can be one of the following:

   •  SIG_DFL for the default action.

   •  SIG_IGN to ignore this signal.

   •  A pointer to a signal handling function.  This function
      receives the signal number as its only argument.

   If SA_SIGINFO is specified in sa_flags, then sa_sigaction (instead
   of sa_handler) specifies the signal-handling function for signum.
   This function receives three arguments, as described below.

   sa_mask specifies a mask of signals which should be blocked (i.e.,
   added to the signal mask of the thread in which the signal handler
   is invoked) during execution of the signal handler.  In addition,
   the signal which triggered the handler will be blocked, unless the
   SA_NODEFER flag is used.

   sa_flags specifies a set of flags which modify the behavior of the
   signal.  It is formed by the bitwise OR of zero or more of the
   following:

   SA_NOCLDSTOP
              If signum is SIGCHLD, do not receive notification when
              child processes stop (i.e., when they receive one of
              SIGSTOP, SIGTSTP, SIGTTIN, or SIGTTOU) or resume (i.e.,
              they receive SIGCONT) (see wait(2)).  This flag is
              meaningful only when establishing a handler for SIGCHLD.

   SA_NOCLDWAIT (since Linux 2.6)
          If signum is SIGCHLD, do not transform children into
          zombies when they terminate.  See also waitpid(2).  This
          flag is meaningful only when establishing a handler for
          SIGCHLD, or when setting that signal's disposition to
          SIG_DFL.

  If the SA_NOCLDWAIT flag is set when establishing a handler
  for SIGCHLD, POSIX.1 leaves it unspecified whether a
  SIGCHLD signal is generated when a child process
  terminates.  On Linux, a SIGCHLD signal is generated in
  this case; on some other implementations, it is not.

   SA_NODEFER
          Do not add the signal to the thread's signal mask while the
          handler is executing, unless the signal is specified in
          act.sa_mask.  Consequently, a further instance of the
          signal may be delivered to the thread while it is executing
          the handler.  This flag is meaningful only when
          establishing a signal handler.

   SA_ONSTACK
          Call the signal handler on an alternate signal stack
          provided by sigaltstack(2).  If an alternate stack is not
          available, the default stack will be used.  This flag is
          meaningful only when establishing a signal handler.

   SA_RESETHAND
          Restore the signal action to the default upon entry to the
          signal handler.  This flag is meaningful only when
          establishing a signal handler.

   SA_RESTART
          Provide behavior compatible with BSD signal semantics by
          making certain system calls restartable across signals.
          This flag is meaningful only when establishing a signal
          handler.  See signal(7) for a discussion of system call
          restarting.

   SA_RESTORER
          Not intended for application use.  This flag is used by C
          libraries to indicate that the sa_restorer field contains
          the address of a "signal trampoline".  See sigreturn(2) for
          more details.

   SA_SIGINFO (since Linux 2.2)
          The signal handler takes three arguments, not one.  In this
          case, sa_sigaction should be set instead of sa_handler.
          This flag is meaningful only when establishing a signal
          handler.

   SA_UNSUPPORTED (since Linux 5.11)
          Used to dynamically probe for flag bit support.

  If an attempt to register a handler succeeds with this flag
  set in act->sa_flags alongside other flags that are
  potentially unsupported by the kernel, and an immediately
  subsequent sigaction() call specifying the same signal
  number and with a non-NULL oldact argument yields
  SA_UNSUPPORTED clear in oldact->sa_flags, then
  oldact->sa_flags may be used as a bitmask describing which
  of the potentially unsupported flags are, in fact,
  supported.  See the section "Dynamically probing for flag
  bit support" below for more details.

   SA_EXPOSE_TAGBITS (since Linux 5.11)
          Normally, when delivering a signal, an architecture-
          specific set of tag bits are cleared from the si_addr field
          of siginfo_t.  If this flag is set, an architecture-
          specific subset of the tag bits will be preserved in
          si_addr.

  Programs that need to be compatible with Linux versions
  older than 5.11 must use SA_UNSUPPORTED to probe for
  support.

   The siginfo_t argument to a SA_SIGINFO handler
       When the SA_SIGINFO flag is specified in act.sa_flags, the signal
       handler address is passed via the act.sa_sigaction field.  This
       handler takes three arguments, as follows:

        
###    siginfo_t

   The siginfo_t argument to a SA_SIGINFO handler
       When the SA_SIGINFO flag is specified in act.sa_flags, the signal
       handler address is passed via the act.sa_sigaction field.  This
       handler takes three arguments, as follows:

           void handler(int sig, siginfo_t *info, void *ucontext)
           {
               ...
           }

   These three arguments are as follows

   sig    The number of the signal that caused invocation of the
          handler.

   info   A pointer to a siginfo_t, which is a structure containing
          further information about the signal, as described below.

   ucontext
          This is a pointer to a ucontext_t structure, cast to
          void *.  The structure pointed to by this field contains
          signal context information that was saved on the user-space
          stack by the kernel; for details, see sigreturn(2).
          Further information about the ucontext_t structure can be
          found in getcontext(3) and signal(7).  Commonly, the
          handler function doesn't make any use of the third
          argument.

   The siginfo_t data type is a structure with the following fields:
       
        siginfo_t	{
        int      si_signo;			Signal number
        int      si_errno;			An errno value
        int      si_code;			Signal code
        int      si_trapno;			Trap number that caused hardware-generated sign
        pid_t    si_pid;			Sending process ID 
        uid_t    si_uid;			Real user ID of sending process 
        int      si_status;			Exit value or signal 
        clock_t  si_utime;			User time consumed     
        clock_t  si_stime;			System time consumed        
        union sigval si_value;		Signal value        
        int      si_int;			POSIX.1b signal        
        void    *si_ptr;			POSIX.1b signal        
        int      si_overrun;		Timer overrun count; POSIX.1b timers        
        int      si_timerid;		Timer ID; POSIX.1b timers        
        void    *si_addr;			Memory location which caused fault       
        long     si_band;			Band event        
        int      si_fd;				File descriptor        
        short    si_addr_lsb;		Least significant bit of address        
        void    *si_lower;			Lower bound when address violation occurred        
        void    *si_upper;			Upper bound when address violation occurred        
        int      si_pkey;			Protection key on PTE that caused fault        
        void    *si_call_addr;		Address of system call instruction        
        int      si_syscall;		Number of attempted system call
        unsigned int si_arch; 		Architecture of attempted system call
        }


###    sigset_t
  Conformément à la norme POSIX, les masques ne sont pas de type int mais de type sigset_t défini dans le fichier /usr/include/asm/signal.h par l'une des définitions suivantes :
 
    typedef unsigned long sigset_t;
     
    typedef struct {
        unsigned long sig[_NSIG_WORDS];
    } sigset_t;
