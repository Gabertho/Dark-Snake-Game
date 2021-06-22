# Dark Snake Game
Jogo produzido em C++ para a disciplina de Algoritmos e Estruturas de Dados I da Universidade Federal de São Carlos(UFSCar), utilizando a biblioteca SFML.
<p> O jogo se baseia em uma releitura do famoso jogo SNAKE, utilizando texturas e ambientações mais "pesadas", sendo entitulado "Dark Snake". </p>

## Desenvolvedores
<a href="https://github.com/Gabertho" alt="Github">
<p> Gabriel Bertho </p>
    
<a href="https://github.com/CarlosFontaneli" alt="Github">
<p> Carlos Eduardo Fontaneli </p></a>


## ESTRUTURAÇÃO
<p>No nosso projeto, utilizamos dois Tipos Abstratos de Dados(TAD) aprendidos na disciplina de Algoritmos e Estruturas de Dados I: Pilha(Stack) e Lista(Linked List).
Nesse contexto, destacamos a implementação e uso das referidas estruturas:
</p>

### PILHA

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

  <p>No trecho acima, observamos a linha em que incluímos a biblioteca stack da linguagem C++, a qual conta com métodos nativos para a implementação de pilhas, sempre  mantendo o aspecto LIFO(Last In First Out) da estrutura.
</p>

```cpp
#include <stack>
```
<p>Continuando, criamos um header(.hpp) chamado StateMan, que é a interface da classe StateManager(Controlador de Estados) responsável por controlar os diferentes estados do jogo. Esse conceito é semelhante à uma Máquina de Estados Finitos, em que, dada uma situação, um estado a representa e outro estado pode ser atingido a partir desse. 
</p>
<p>A pilha foi a estrutura de dado escolhida para essa classe pois é perfeita para controlar os estados do jogo. Para entender melhor, considere a situação de que você está jogando(estado de jogo) e clica no botão "Pause", abrindo o meno de Pause. Nesse caso, você provoca uma transição do estado de jogo para o estado de pause, ou melhor, você está empilhando o "estado de pause" que passa a ser o topo da pilha. Dada as propriedades da pilha, o único modo de você retornar para o estado de jogo, é desempilhando o estado de pause, ou seja, para voltar a jogar, você precisa despausar!
</p>
<p>Assim, temos os atributos privados booleanos m_add, m_replace e m_remove, os quais servem para podemos verificar o estado que o jogo se encontra e controlar as transições de acordo com certas situações.
</p>
<p>Em relação aos métodos públicos, temos o destrutor e o construtor padrão da classe, além do método Add(empilhar), PopCurrent(desempilhar)l, ProcessStateChange(faz o processamento necessário para as mudanças no jogo que a mudança de estado causará) e uma referência do tipo <State> para obter o estado atual do jogo.
</p>
    
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
  <p> No construtor, observamos a inicialização dos atributos privados. </p>
  <p> No método add, observamos o uso do método move para empilhar o novo estado recebido como parâmetro. </p>
  <p> No método PopCurrent, setamos o valor da variável boolean m_remove como verdadeiro, pois estamos desempilhando o topo. </p>
  <p> No método ProcessStateChange, fazemos uma verificação com estruturas condicionais para verificar como a pilha deve se comportar nos casos listados a seguir:  </p>
    <p> a) No primeiro caso, vemos que a pilha não está vazia e m_remove é verdadeiro, ou seja, devemos desempilhar o estado do topo. Para isso, utilizamos o método pop() presente na biblioteca Stack e posteriormente transicionamos o jogo para o novo topo utilizando o método Start() da biblioteca SFML. </p>
    <p> b) No segundo caso, vemos que é necessário empilhar um estado no jogo, e com isso verificamos se é necessário substituir o topo da pilha ou não. Depois, verificamos se a pilha está vazia e pausamos o estado do topo para que possamos adicionar um novo estado, o qual passa a ser o novo topo, o qual é inicializado com os métodos Init() e Start() da biblioteca SFML. </p>
 <p> No método GetCurrent, retornamos uma referência para o topo da pilha(estado atual do jogo).</p>

 ### Lista Encadeada Circular

 <p> Para a elaboração da cobra, utilizamos um Tipo de Dado Abstrato lista encadeada, pois cada porção do corpo da cobra é um item desta lista. Dessa forma, o fim da lista sempre será a cabeça da cobra(um iterador do método `list`), seu corpo são os itens da lista como um todo(usamos o método `list` tendo como itens `Sprites` uma classe da biblioteca gráfica responsável por desenhos que podem ser alterados ao longo do tempo) e seu começo sempre será a calda da cobra(um iterador do método `list`). Para tal criamos um classe cobra que abriga os métodos de criação da cobra e seus métodos de movimento.
 Para tal criamos um cabeçalho que inclue a biblioteca `<list>` da qual usaremos o TAD lista. Além disso, adicionamos os demais cabeçalhos necessários que fazem parte da biblioteca gráfica `SFML`. Dentro do cabeçalho declaramos os métods que são responsáveis pela criação da cobra e sua movimentação.<p>

```cpp
#pragma once

#include <list>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class Snake : public sf::Drawable
{
private:
    std::list<sf::Sprite> m_body;
    std::list<sf::Sprite>::iterator m_head;
    std::list<sf::Sprite>::iterator m_tail;

public:
    Snake();
    ~Snake();

    void Init(const sf::Texture &texture);
    void Move(const sf::Vector2f &direction);
    bool IsOn(const sf::Sprite &other) const;
    void Grow(const sf::Vector2f &direction);
    bool IsSelfIntersecting() const;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
```
<p> Agora, dentro da unidade de software dos métods da cobra temos o cabeçalho declarado apenas. Como construtor inicilizamos a cabeça como o final da lista e a cauda como o começo. A cabeça é inicilizada com um decremento, pois neste estado a lista ainda está vazia. O destrutor é vazio(padrão).<p>

```cpp
#include "Snake.hpp"

Snake::Snake() : m_body(std::list<sf::Sprite>(4))
{
    m_head = --m_body.end();
    m_tail = m_body.begin();
}

Snake::~Snake()
{
}
```

O método `Init` fica responsável por dar início a cobra, colocando seu tamanho conforme a proporção do mapa e iniciando sua textura através de métodos da biblioteca gráfica.

```cpp
void Snake::Init(const sf::Texture &texture)
{
    float x = 16.f;
    for (auto &piece : m_body)
    {
        piece.setTexture(texture);
        piece.setPosition({x, 16.f});
        x += 16.f;
    }
}
```

O método `Move` cuida do movimento da cobra, atualizando o valor da cauda para frente da cabeça, isso cria a sensação de movimento do personagem. Incrementa-se a cauda e caso ela esteja na posição da cabeça reinicia-se sua posição.
```cpp
void Snake::Move(const sf::Vector2f &direction)
{
    m_tail->setPosition(m_head->getPosition() + direction);
    m_head = m_tail;
    ++m_tail;

    if (m_tail == m_body.end())
    {
        m_tail = m_body.begin();
    }
}
```

Os métodos `IsOn`, `Grow` e `IsSelfIntersecting` verificação se a cobra está tocando os limites do mapa, deve crescer, pois está sobre uma comida e se a cobra encostou em si mesma, respectivamente.
``` cpp
void Snake::Grow(const sf::Vector2f &direction)
{
    sf::Sprite newPiece;
    newPiece.setTexture(*(m_body.begin()->getTexture()));
    newPiece.setPosition(m_head->getPosition() + direction);

    m_head = m_body.insert(++m_head, newPiece);
}

bool Snake::IsSelfIntersecting() const
{
    bool flag = false;

    for (auto piece = m_body.begin(); piece != m_body.end(); ++piece)
    {
        if (m_head != piece)
        {
            flag = IsOn(*piece);

            if (flag)
            {
                break;
            }
        }
    }

    return flag;
}
```
O método `draw` fica responsável pelo desenho do corpo da cobra pelo mapa.
```cpp
void Snake::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto &piece : m_body)
    {
        target.draw(piece);
    }
}
```



