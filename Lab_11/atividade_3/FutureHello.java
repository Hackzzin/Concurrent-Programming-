/* Disciplina: Programacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Laboratório: 11 */
/* Codigo: Exemplo de uso de futures */
/* -------------------------------------------------------------------*/

import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

import java.util.ArrayList;
import java.util.List;

//classe runnable
class MyCallable implements Callable<Long> {
  //construtor
  MyCallable() {
  }
 
  //método para execução
  public Long call() throws Exception {
    long s = 0;
    for (long i=1; i<=100; i++) {
      s++;
    }
    return s;
  }
}

class Primo implements Callable<Long> {
   private final long num;
   public Primo(long n) { this.num = n; }
   public Long call() {
     if (num < 2){
        return 0L; // Números menores que 2 não são primos
     }

     if (num == 2) {
        return 1L; // 2 é primo
     }

     if (num % 2 == 0) {
        return 0L; // Números pares maiores que 2 não são primos
     }
     for (int i = 3; i <= Math.sqrt(num) + 1; i += 2) {
          if (num % i == 0) {
            return 0L; // Encontrou um divisor, não é primo
          }
      }
      return 1L; 
   }
}

//classe do método main
public class FutureHello  {
  private static final long N = 10000;
  private static final int NTHREADS = 10;

  public static void main(String[] args) {
    //cria um pool de threads (NTHREADS)
    ExecutorService executor = Executors.newFixedThreadPool(NTHREADS);
    //cria uma lista para armazenar referencias de chamadas assincronas
    List<Future<Long>> list = new ArrayList<Future<Long>>();

    for (int i = 0; i < N; i++) {
      Primo worker = new Primo(i);
      Future<Long> submit = executor.submit(worker);
      list.add(submit);
    }

    System.out.println(list.size());
    //pode fazer outras tarefas...

    //recupera os resultados e faz o somatório final
    long todosPrimos = 0;
    for (Future<Long> future : list) {
      try {
        todosPrimos += future.get(); //bloqueia se a computação nao tiver terminado
      } catch (InterruptedException e) {
        e.printStackTrace();
      } catch (ExecutionException e) {
        e.printStackTrace();
      }
    }
    System.out.println(todosPrimos + " números primos encontrados");
    executor.shutdown();
  }
}
