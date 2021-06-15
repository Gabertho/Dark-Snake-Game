# ProjetoAED1
Jogo produzido em C++ para a disciplina de Algoritmos e Estruturas de Dados I da Universidade Federal de São Carlos(UFSCar), utilizando a biblioteca SFML.


#ESTRUTURAÇÃO
No nosso projeto, utilizamos dois Tipos Abstratos de Dados(TAD) aprendidos na disciplina de Algoritmos e Estruturas de Dados I: Pilha(Stack) e Lista(Linked List).
Nesse contexto, destacamos a implementação e uso das referidas estruturas:

#PILHA
```cpp
#pragma once

#include <stack>
#include <memory>

#include <State.hpp>

namespace Engine
{
class StateMan
{
private:
    std::stack<std::unique_ptr<State>> m_stateStack;
    std::unique_ptr<State> m_newState;

    bool m_add;
    bool m_replace;
    bool m_remove;

public:
    StateMan();
    ~StateMan();

    void Add(std::unique_ptr<State> toAdd, bool replace = false);
    void PopCurrent();
    void ProcessStateChange();
    std::unique_ptr<State>& GetCurrent();
};

} // namespace Engine
```

  No trecho acima, observamos a linha em que incluímos a biblioteca stack da linguagem C++, a qual conta com métodos nativos para a implementação de pilhas, sempre  mantendo o aspecto LIFO(Last In First Out) da estrutura.
```cpp
#include <stack>
```
  Continuando, criamos um header(.hpp) chamado StateMan, que é a interface da classe StateManager(Controlador de Estados) responsável por controlar os diferentes estados do jogo. Esse conceito é semelhante à uma Máquina de Estados Finitos, em que, dada uma situação, um estado a representa e outro estado pode ser atingido a partir desse. 
  A pilha foi a estrutura de dado escolhida para essa classe pois é perfeita para controlar os estados do jogo. Para entender melhor, considere a situação de que você está jogando(estado de jogo) e clica no botão "Pause", abrindo o meno de Pause. Nesse caso, você provoca uma transição do estado de jogo para o estado de pause, ou melhor, você está empilhando o "estado de pause" que passa a ser o topo da pilha. Dada as propriedades da pilha, o único modo de você retornar para o estado de jogo, é desempilhando o estado de pause, ou seja, para voltar a jogar, você precisa despausar!
  Assim, temos os atributos privados booleanos m_add, m_replace e m_remove, os quais servem para podemos verificar o estado que o jogo se encontra e controlar as transições de acordo com certas situações.
  Em relação aos métodos públicos, temos o destrutor e o construtor padrão da classe, além do método Add(empilhar), PopCurrent(desempilhar)l, ProcessStateChange(faz o processamento necessário para as mudanças no jogo que a mudança de estado causará) e uma referência do tipo <State> para obter o estado atual do jogo.
   Agora, veremos a implementação dessa classe, presente no arquivo "StateMan.cpp"
  
  ```cpp
#include "StateMan.hpp"

Engine::StateMan::StateMan() : m_add(false), m_replace(false), m_remove(false)
{
}

Engine::StateMan::~StateMan()
{
}

void Engine::StateMan::Add(std::unique_ptr<State> toAdd, bool replace)
{
    m_add = true;
    m_newState = std::move(toAdd);

    m_replace = replace;
}

void Engine::StateMan::PopCurrent()
{
    m_remove = true;
}

void Engine::StateMan::ProcessStateChange()
{
    if(m_remove && (!m_stateStack.empty()))
    {
        m_stateStack.pop();

        if(!m_stateStack.empty())
        {
            m_stateStack.top()->Start();
        }

        m_remove = false;
    }

    if(m_add)
    {
        if(m_replace && (!m_stateStack.empty()))
        {
            m_stateStack.pop();
            m_replace = false;
        }

        if(!m_stateStack.empty())
        {
            m_stateStack.top()->Pause();
        }

        m_stateStack.push(std::move(m_newState));
        m_stateStack.top()->Init();
        m_stateStack.top()->Start();
        m_add = false;
    }
}

std::unique_ptr<Engine::State> &Engine::StateMan::GetCurrent()
{
    return m_stateStack.top();
}
  ```
  No construtor, observamos a inicialização dos atributos privados.
  No método add, observamos o uso do método move para empilhar o novo estado recebido como parâmetro.
  No método PopCurrent, setamos o valor da variável boolean m_remove como verdadeiro, pois estamos desempilhando o topo.
  No método ProcessStateChange, fazemos uma verificação com estruturas condicionais para verificar como a pilha deve se comportar. 
    a) No primeiro caso, vemos que a pilha não está vazia e m_remove é verdadeiro, ou seja, devemos desempilhar o estado do topo. Para isso, utilizamos o método pop() presente na biblioteca Stack e posteriormente transicionamos o jogo para o novo topo utilizando o método Start() da biblioteca SFML. 
    b) No segundo caso, vemos que é necessário empilhar um estado no jogo, e com isso verificamos se é necessário substituir o topo da pilha ou não. Depois, verificamos se a pilha está vazia e pausamos o estado do topo para que possamos adicionar um novo estado, o qual passa a ser o novo topo, o qual é inicializado com os métodos Init() e Start() da biblioteca SFML.
  No método GetCurrent, retornamos uma referência para o topo da pilha(estado atual do jogo).
