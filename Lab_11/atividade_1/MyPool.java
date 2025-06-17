/* Disciplina: Programacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratório: 11 */
/* Codigo: Criando um pool de threads em Java */

import java.util.LinkedList;

//-------------------------------------------------------------------------------
//!!! Documentar essa classe !!!
class FilaTarefas {
    private final int nThreads; /* Núm. Threads */
    private final MyPoolThreads[] threads; /* Vetor de Threads */
    private final LinkedList<Runnable> queue; /* Fila de tarefas */
    private boolean shutdown; /* Boolean que indica se o pool não aceita mais tarefas ou não */

    // Construtor 
    public FilaTarefas(int nThreads) {
        // Inicialzação 
        this.shutdown = false;
        this.nThreads = nThreads;
        queue = new LinkedList<Runnable>();
        threads = new MyPoolThreads[nThreads];

        // Criação das threads
        for (int i=0; i<nThreads; i++) {
            threads[i] = new MyPoolThreads();
            threads[i].start();
        } 
    }

    // Adiciona uma tarefa à fila de tarefas, verifica se o pool não está fechado
    public void execute(Runnable r) {
        synchronized(queue) {
            if (this.shutdown) return;
            queue.addLast(r);
            queue.notify(); // Notifica uma thread que está esperando na fila de tarefas
        }
    }
    
    // Termina o pool de threads
    public void shutdown() {
        synchronized(queue) {
            this.shutdown=true; 
            queue.notifyAll(); // Notifica todas as threads que estão esperando na fila de tarefas
        }
        // Espera todas as threads terminarem
        for (int i=0; i<nThreads; i++) {
          try { threads[i].join(); } catch (InterruptedException e) { return; }
        }
    }

    // Classe interna que implementa a thread do pool
    private class MyPoolThreads extends Thread {
       public void run() {
         Runnable r;
         while (true) {
           synchronized(queue) {
             while (queue.isEmpty() && (!shutdown)) {
               try { queue.wait(); } // Espera por uma tarefa na fila
               catch (InterruptedException ignored){}
             }
             if (queue.isEmpty()) return;   
             r = (Runnable) queue.removeFirst(); // Remove a primeira tarefa da fila
           }
           try { r.run(); } // Executa a tarefa
           catch (RuntimeException e) {}
         } 
       } 
    } 
}
//-------------------------------------------------------------------------------

//--PASSO 1: cria uma classe que implementa a interface Runnable 
class Hello implements Runnable {
   String msg;
   public Hello(String m) { msg = m; }

   //--metodo executado pela thread
   public void run() {
      System.out.println(msg);
   }
}

class Primo implements Runnable {
   //...completar implementacao, recebe um numero inteiro positivo e imprime se esse numero eh primo ou nao
   private final int num;
   public Primo(int n) { this.num = n; }
   public void run() {
     if (num < 2){
        System.out.println(num + " não é primo");
        return; // Números menores que 2 não são primos
     }

     if (num == 2) {
        System.out.println(num + " é primo");
        return; // 2 é primo
     }

     if (num % 2 == 0) {
        System.out.println(num + " não é primo");
        return; // Números pares maiores que 2 não são primos
     }
     for (int i = 3; i <= Math.sqrt(num) + 1; i += 2) {
          if (num % i == 0) {
            System.out.println(num + " não é primo");
            return; // Encontrou um divisor, não é primo
          }
      }
     System.out.println(num + " é primo"); // Se não encontrou divisores, é primo
   }
}

//Classe da aplicação (método main)
class MyPool {
    private static final int NTHREADS = 10;

    public static void main (String[] args) {
      //--PASSO 2: cria o pool de threads
      FilaTarefas pool = new FilaTarefas(NTHREADS); 
      
      //--PASSO 3: dispara a execução dos objetos runnable usando o pool de threads
      for (int i = 0; i < 25; i++) {
        final String m = "Hello da tarefa " + i;
        Runnable hello = new Hello(m);
        pool.execute(hello);
        Runnable primo = new Primo(i);
        pool.execute(primo);
      }

      //--PASSO 4: esperar pelo termino das threads
      pool.shutdown();
      System.out.println("Terminou");
   }
}
