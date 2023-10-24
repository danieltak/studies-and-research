<!-- vscode-markdown-toc -->
* 1. [Introdução](#Introduo)
	* 1.1. [Concorrência vs Paralelismo](#ConcorrnciavsParalelismo)
		* 1.1.1. [Concorrência](#Concorrncia)
		* 1.1.2. [Paralelismo](#Paralelismo)
		* 1.1.3. [Conclusão](#Concluso)
	* 1.2. [Concorrência (Concurrency)](#ConcorrnciaConcurrency)
		* 1.2.1. [Join](#Join)
		* 1.2.2. [Detach](#Detach)
	* 1.3. [Thread Management](#ThreadManagement)
* 2. [Shared Resources](#SharedResources)
	* 2.1. [Mutexes are still potentially dangerous](#Mutexesarestillpotentiallydangerous)
	* 2.2. [Lock Guard](#LockGuard)

<!-- vscode-markdown-toc-config
	numbering=true
	autoSave=true
	/vscode-markdown-toc-config -->
<!-- /vscode-markdown-toc --># Threads

##  1. <a name='Introduo'></a>Introdução

https://medium.com/codex/c-multithreading-the-simple-way-95aa1f7304a2

###  1.1. <a name='ConcorrnciavsParalelismo'></a>Concorrência vs Paralelismo

https://freecontent.manning.com/concurrency-vs-parallelism/

####  1.1.1. <a name='Concorrncia'></a>Concorrência

Programação como a composição de processos de execução independente.

A concorrência diz respeito a várias tarefas que são iniciadas, executadas e concluídas em períodos de tempo sobrepostos, sem uma ordem específica. O paralelismo diz respeito a várias tarefas ou subtarefas da mesma tarefa que são executadas literalmente ao mesmo tempo em um hardware com vários recursos de computação, como um processador de vários núcleos. Como você pode ver, concorrência e paralelismo são semelhantes, mas não idênticos.


A concorrência é uma propriedade semântica de um programa ou sistema. Concorrência é quando várias tarefas estão em andamento por períodos de tempo sobrepostos. Observe que aqui não estamos falando sobre a execução real das tarefas, mas sobre o projeto do sistema - que as tarefas são independentes da ordem. Portanto, a concorrência é uma propriedade conceitual de um programa ou de um sistema, e tem mais a ver com a forma como o programa ou o sistema foi projetado.


Imagine que um cozinheiro esteja cortando salada e, de vez em quando, mexendo a sopa no fogão. Ele precisa parar de cortar, verificar o fogão e, em seguida, começar a cortar novamente, repetindo esse processo até que tudo esteja pronto.


Como você pode ver, temos apenas um recurso de processamento aqui, o cozinheiro, e sua concorrência está relacionada principalmente à logística; sem concorrência, o cozinheiro tem de esperar até que a sopa no fogão esteja pronta para cortar a salada.

![Concurrency](https://freecontent.manning.com/wp-content/uploads/concurrency-vs-parallelism_01.jpg)

####  1.1.2. <a name='Paralelismo'></a>Paralelismo

Programação como a execução simultânea de cálculos (possivelmente relacionados).

O paralelismo é uma propriedade de implementação. O paralelismo é literalmente a execução física simultânea de tarefas em tempo de execução e requer hardware com vários recursos de computação. Ele reside na camada de hardware.


De volta à cozinha, agora temos dois chefs, um que pode mexer e outro que pode cortar a salada. Dividimos o trabalho com outro recurso de processamento, outro chef.


O paralelismo é uma subclasse da concorrência: antes de poder realizar várias tarefas ao mesmo tempo, é preciso gerenciar várias tarefas primeiro.

![Parallelism](https://freecontent.manning.com/wp-content/uploads/concurrency-vs-parallelism_02.jpg)

####  1.1.3. <a name='Concluso'></a>Conclusão

A essência da relação entre concorrência e paralelismo é que os cálculos simultâneos podem ser paralelizados sem alterar a precisão do resultado, mas a concorrência em si não implica em paralelismo. Além disso, o paralelismo não implica concorrência; muitas vezes é possível para um otimizador pegar programas sem concorrência semântica e dividi-los em componentes paralelos por meio de técnicas como processamento de pipeline, operações SIMD de vetor amplo ou dividir e conquistar.

Como Rob Pike apontou: "Concorrência é lidar com muitas coisas ao mesmo tempo. Paralelismo é fazer muitas coisas ao mesmo tempo". Em uma CPU de núcleo único, é possível ter concorrência, mas não paralelismo. Mas ambos vão além do modelo sequencial tradicional, no qual as coisas acontecem uma de cada vez.

Para ter uma ideia melhor sobre a distinção entre concorrência e paralelismo, considere os seguintes pontos:

- Um aplicativo pode ser concorrente, mas não paralelo, o que significa que ele processa mais de uma tarefa ao mesmo tempo, mas não há duas tarefas sendo executadas no mesmo instante.
- Um aplicativo pode ser paralelo, mas não concorrente, o que significa que ele processa várias subtarefas de uma única tarefa ao mesmo tempo.
- Um aplicativo não pode ser paralelo nem concorrente, o que significa que ele processa uma tarefa por vez, sequencialmente, e a tarefa nunca é dividida em subtarefas.
- Um aplicativo pode ser paralelo e concorrente, o que significa que ele processa várias tarefas ou subtarefas de uma única tarefa ao mesmo tempo (executando-as em paralelo)

Não quero ser esse tipo de pessoa, mas a terminologia é importante. Com muita frequência, a conversa sobre o problema fica confusa porque uma pessoa pensa em concorrência e a outra pensa em paralelismo. Na prática, a distinção entre concorrência e paralelismo não é absoluta. Muitos programas têm aspectos de cada um deles.

Imagine que você tenha um programa que insere valores em uma tabela de hash. Se você distribuir a operação de inserção entre vários núcleos, isso é paralelismo. Mas coordenar o acesso à tabela de hash é concorrência.

###  1.2. <a name='ConcorrnciaConcurrency'></a>Concorrência (Concurrency)


Talvez a forma menos ameaçadora de multithreading seja a concorrência. A concorrência é geralmente entendida como a execução de várias threads ao mesmo tempo, mas sem partilhar quaisquer recursos. Isto significa que nenhuma estrutura de dados, memória ou outro é partilhado entre threads. A simultaneidade é normalmente utilizada para tarefas que podem ser divididas entre threads e trabalhadas de forma independente.

Para ilustrar isto, vejamos o exemplo de cada thread que recebe um ponteiro para um número inteiro, incrementa esse número inteiro e depois pára. Cada thread pode ser executada até incrementar o número algumas centenas de vezes. Depois, essas threads, muitas vezes chamadas de threads de "trabalho", juntam-se à thread principal. Todas as threads trabalham simultaneamente.

https://onlinegdb.com/TbSvhsU2C

```cpp
#include <thread>
#include <iostream>


void workFunc(int* ptr, size_t times)
{
	while(times--) {
		*ptr += 1;
	}
}


int main(int argc, char const *argv[])
{
	int* numbers = new int[3];

	std::thread t1(workFunc, numbers, 500);
	std::thread t2(workFunc, numbers + 1, 600);
	std::thread t3(workFunc, numbers + 2, 700);


	t1.join();
	t2.join();
	t3.join();

	for(int i = 0; i < 3; ++i)
		std::cout << "Number Slot " << (int)i << " is " << (int)numbers[i] << std::endl;

	delete[] numbers;
	return 0;
}
```

Result:

```
Number Slot 0 is 500
Number Slot 1 is 600
Number Slot 2 is 700
```

####  1.2.1. <a name='Join'></a>Join

Se é novo no multithreading, há algumas partes deste código que podem não fazer sentido. O método join() é provavelmente uma delas. Um detalhe importante a entender sobre o início de novas threads é que elas trabalham e funcionam totalmente separadas da thread principal, a thread que começa em main() . Como elas são totalmente separadas, temos que decidir um ponto no qual queremos esperar que elas completem o trabalho que lhes foi atribuído.

Pense em join() de forma semelhante a como duas pessoas podem se separar para fazer suas próprias tarefas separadas, e então "se juntar" novamente mais tarde. Se você estiver viajando ou indo a algum lugar com um amigo, você não quer simplesmente abandoná-lo! O ideal é esperar que ele se junte a nós novamente. A mesma lógica se aplica às threads. Sempre que são criadas threads adicionais, há a obrigação de indicar como se pretende que a thread central e principal atue.

####  1.2.2. <a name='Detach'></a>Detach

Você sempre precisa usar join nas threads? Não. Na verdade, há uma outra opção. Assim como no exemplo dos amigos, é possível que um amigo queira seguir seu próprio caminho de volta para casa e não se encontrar com você. No caso das threads, isso é chamado de detaching. Separar um thread significa permitir que ele trabalhe e conclua seu trabalho independentemente da thread principal. Porém, isso pode ser perigoso. Veja o exemplo a seguir, muito semelhante ao de join(), por exemplo.

```cpp
/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <thread>
#include <iostream>
#include <cstring>
#include <regex>
#include <algorithm>

void workFunc(int* ptr, size_t times)
{
	while(times--) {
		*ptr += 1;
	}
}

int main(int argc, char const *argv[])
{
	int* numbers = new int[3];

	std::thread t1(workFunc, numbers, 50000);
	std::thread t2(workFunc, numbers + 1, 60000);
	std::thread t3(workFunc, numbers + 2, 70000);

	t1.detach();
	t2.detach();
	t3.detach();

	delete[] numbers;
	return 0;
}
```

O primeiro risco aqui é usar o heap alocado depois de ter sido excluído. Ao contrário de join() , detach() não faz com que a thread de chamada pare ou espere por nada. Isso significa que, assim que a terceira chamada para detach() terminar, a thread de chamada excluirá a matriz de números. Se as threads criadas não tiverem concluído seu trabalho, eles estarão gravando em uma matriz excluída, o que corrompe a memória.

O segundo risco aqui é que os threads criados podem continuar em execução mesmo após o término do thread principal, se o trabalho deles não for concluído. Ou eles podem ser eliminados assim que o principal terminar. Esse é um comportamento indefinido (undefined behavior) de acordo com o padrão C++. Independentemente do que um compilador específico possa garantir, o comportamento indefinido é algo que deve ser evitado. Há casos de uso válidos para detach() , mas qualquer um deles exige alguma outra forma de sincronização entre threads para ser confiável.

###  1.3. <a name='ThreadManagement'></a>Thread Management

https://gist.github.com/convict-git/9e4da852bb034f4aa97b66596f2270f5

Cada programa em execução tem pelo menos uma thread que é ocupada por seu ponto de entrada. Pode haver muitas threads em um único programa e a memória é compartilhada entre todos os threads. Os objetos possuídos pelo thread principal (e compartilhados por outros threads como referência a ele) seriam destruídos assim que saíssem do escopo. Isso pode levar ao acesso corrupto à memória pelos demais threads.

Por isso, às vezes, é muito importante garantir que todos os threads sejam unidos usando `std::thread::join()` antes do término do thread principal. Outras vezes, você basicamente quer que um thread daemon seja executado em segundo plano, mesmo após o término do thread principal, e isso pode ser conseguido chamando `std::thread::detach()`, mas pode ou não ser possível unir um thread detached.

A RAII (Resource Acquisition Is Initialization, Aquisição de recursos é inicialização) é um famoso idioma de programação em C++ (na verdade, um termo errôneo), também (melhor) conhecido e compreendido como Gerenciamento de recursos vinculado ao escopo (Scope-Bound Resource Management). Em C++, assim que o objeto é declarado (*), o método construtor da classe é evocado, o que geralmente é responsável pela alocação de recursos. Da mesma forma, quando o objeto sai do escopo, o destrutor é chamado, o que geralmente é responsável por liberar os recursos adquiridos.

A RAII é uma boa maneira de garantir que um thread seja unido, escrevendo uma classe de wrapper como um contêiner para a instância do thread que chama a união em seu destrutor. Os funtores são usados de forma semelhante para envolver as funções, sobrecarregando o operador de chamada () que torna uma classe chamável.

O C++ tem uma biblioteca robusta para dar suporte ao gerenciamento de threads. Uma instância de thread pode receber qualquer chamável (funções, functors, binds ou funções lambda) e seus parâmetros como argumentos. É importante observar que os parâmetros chamam o construtor de cópia padrão para criar uma cópia do parâmetro em seu escopo. Portanto, para realmente "compartilhar" a memória entre o thread chamador e o thread receptor, os objetos de parâmetro devem ser envolvidos com `std::ref()` ou pela maneira convencional de chamar usando ponteiros. Para transferir a propriedade de um objeto, o objeto pode ser envolvido com `std::move()`, que evoca o construtor move em vez do construtor copy no momento da inicialização.

##  2. <a name='SharedResources'></a>Shared Resources

https://medium.com/codex/c-multithreading-the-simple-way-95aa1f7304a2

Um recurso em que dois threads diferentes podem acessar o mesmo endereço de memória é chamado de recurso compartilhado. É fundamental observar a ênfase no endereço. No exemplo anterior mostrado aqui, com vários threads acessando o mesmo array, esse não é um recurso compartilhado porque nenhum dos dois threads está lendo ou gravando no mesmo endereço de memória. A matriz poderia ter sido apenas quatro ponteiros inteiros separados; não há nada em uma matriz que a torne um recurso compartilhado.

Ao contrário da concorrência, um recurso compartilhado é usado quando é desejável que os threads executem trabalhos nos mesmos dados ou objetos. Isso significa que os objetos não são alocados na própria pilha de um thread, e apenas um é visível para outros threads. O que pode tornar isso difícil de entender é que, embora ambos os threads possam acessar algum recurso, eles nunca podem ver os outros threads acessando esse recurso.

Um ótimo exemplo de um recurso compartilhado na vida real é uma pista de pouso de um aeroporto à noite. Uma pista tem luzes piscantes para ajudar os aviões a se alinharem com ela enquanto se preparam para o pouso. Mas é muito difícil, se não impossível, que os outros aviões se vejam à noite, devido à escuridão e à velocidade com que se deslocam. Se um avião tentasse aterrissar na pista ao mesmo tempo que outro avião, seria desastroso. A única maneira de os aviões evitarem essas colisões é se coordenarem por meio do controle de tráfego aéreo.

Os threads funcionam da mesma forma, no sentido de que dependem de mecanismos de sincronização para coordenar o acesso aos recursos, como, por exemplo, não gravar neles exatamente ao mesmo tempo. O mecanismo que discutiremos aqui, que talvez seja o mais comum, é um mutex. Um mutex, conhecido pelo tipo `std::mutex`, permite que os threads adquiram bloqueios. Os bloqueios são uma forma de controle que permite que apenas um thread prossiga em uma seção de código por vez.

Vejamos [este exemplo](https://gist.githubusercontent.com/jweinst1/0efbf2c63d25c70b024299c7efbec9ff/raw/ed23466314e05e9fb7081b1e97e817976cce8edf/safequeue.cpp).

```cpp
#include <thread>
#include <mutex>
#include <queue>


template<class T>
class SafeQueue {
public:
	void push(const T& val) {
		std::lock_guard<std::mutex> lock(_m);
		_q.push(val);
	}

	bool pop(T& val) {
		std::lock_guard<std::mutex> lock(_m);
		if (!_q.empty()) {
			val = _q.front();
			_q.pop();
			return true;
		} else {
			return false;
		}
	}
private:
	std::mutex _m;
	std::queue<T> _q;
};
```

In the above example, the `push()` and `pop()` methods of the class both happen while the calling thread constructs a lock on the mutex associated with the queue. This lock is best used as an RAII style object, where it’s only active under some scope of code. Once the program finishes that scope, the lock guard object is destroyed, allowing another thread to construct and acquire a lock on the mutex. This pattern continues to satisfy the condition only one thread can modify the queue at a time.

###  2.1. <a name='Mutexesarestillpotentiallydangerous'></a>Mutexes are still potentially dangerous

Embora pareçam muito legais e diretos, os mutexes ainda podem ser perigosos. Quando um thread adquire um bloqueio em um mutex, ele é responsável por liberar ou destruir esse bloqueio para que outros threads também possam acessar o escopo seguro do código. O que acontece se um thread nunca libera o bloqueio que adquiriu? Bem, algo muito ruim.

Um deadlock ocorre quando um thread bloqueia um mutex, mas esse bloqueio, por algum motivo, nunca pode ser desbloqueado. Se isso acontecer, todos os threads ficarão bloqueados e aguardarão o mutex indefinidamente, sem fazer nenhum progresso ou trabalho.

A regra geral para os mutexes é pensar com cuidado e criticamente sobre o que um thread faz quando coloca um bloqueio em um mutex. É fundamental que um thread só bloqueie quando for absolutamente necessário o acesso de um único thread e, ao fazê-lo, trabalhe o mais rápido possível. Embora os mutexes forneçam um meio de acessar com segurança o mesmo recurso, eles o fazem com um custo de desempenho.

###  2.2. <a name='LockGuard'></a>Lock Guard

https://stackoverflow.com/a/35252160/7690982

Com o seguinte código:

```cpp
#include <iostream>
#include <thread>
#include <list>
#include <algorithm>
#include <mutex>

using namespace std;

// a global variable
std::list<int>myList;

// a global instance of std::mutex to protect global variable
std::mutex myMutex;

void addToList(int max, int interval)
{
    // the access to this function is mutually exclusive
    std::lock_guard<std::mutex> guard(myMutex);
    for (int i = 0; i < max; i++) {
        if( (i % interval) == 0) myList.push_back(i);
    }
}

void printList()
{
    // the access to this function is mutually exclusive
    std::lock_guard<std::mutex> guard(myMutex);
    for (auto itr = myList.begin(), end_itr = myList.end(); itr != end_itr; ++itr ) {
        cout << *itr << ",";
    }
}

int main()
{
    int max = 100;

    std::thread t1(addToList, max, 1);
    std::thread t2(addToList, max, 10);
    std::thread t3(printList);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
```

Observando a linha:

`std::lock_guard<std::mutex> guard(myMutex);`

Observe que o lock_guard faz referência ao mutex global myMutex. Ou seja, o mesmo mutex para todos os três threads. O que o lock_guard faz é basicamente isso:

- Ao ser construído, ele bloqueia o myMutex e mantém uma referência a ele.

- pós a destruição (ou seja, quando o escopo do guard é deixado), ele desbloqueia o myMutex.

O mutex é sempre o mesmo, não tem nada a ver com o escopo. O objetivo do lock_guard é apenas facilitar o bloqueio e o desbloqueio do mutex para você. Por exemplo, se você bloquear/desbloquear manualmente, mas sua função lançar uma exceção em algum lugar no meio, ela nunca chegará à instrução de desbloqueio.

Portanto, ao fazer isso manualmente, você precisa ter certeza de que o mutex está sempre desbloqueado. Por outro lado, o objeto lock_guard é destruído automaticamente sempre que a função é encerrada, independentemente de como ela é encerrada.

Isso evita ter que fazer unlock em todas as exceções e sempre realizar um try/catch para evitar o dead lock em caso de exceções.

