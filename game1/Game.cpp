#include "Game.h"
//funçoes privada;
void Game::initVariables() // variaveis
{ 
    this->window= nullptr;

    // logica de jogo
    this->points = 0; // pontos
    this->enemySpawnTImerMax = 10.f; // tempo maximo de desova dos inimigos
    this->enemySpawnTimer = this->enemySpawnTImerMax ; // tempo de desova dos inimigos
    this->maxEnemies = 10;  // maximo de inimigos 
    this->mouseHeld = false;  // mause segurado
}
void Game::initWindow() // iniciaçao de janela
{   
    this->videoMode.height = 600; // altura
    this-> videoMode.width = 800;  // largura
    this->window = new sf::RenderWindow(this->videoMode, "Game i On ", sf::Style::Titlebar | sf::Style::Close); // configuraçao da janela
    this->window->setFramerateLimit(60);//definir limite de taxa de quadros
}
void Game::initEnemies()//inimigos
{   
    this->enemy.setPosition(10.f, 10.f);//posição definida
    this->enemy.setSize(sf::Vector2f(100.f,100.f)); //definir o tamanho
    this->enemy.setScale(sf::Vector2f(0.5f,0.5f));//escala definida
    this->enemy.setFillColor(sf::Color::Cyan); //definir cor de preenchimento
    //this->enemy.setOutlineColor(sf::Color::Green);//definir a cor da linha
    //this->enemy.setOutlineThickness(1.f);//definir a espessura da linha
}
//contrutor // destruidor
Game::Game()
{  
    this->initVariables();
    this->initWindow();
    this->initEnemies();
}
Game::~Game()
{
    delete this->window;
}
//Acessores
const bool Game::running() const
{
     return this->window->isOpen(); 
}
// funçoes
void Game::spawnEnemy() //gerar inimigos
{
    /*
        @return void
        gera inimigos e define suas cores e posições
        definir posições aleatórias
        definir cor aleatórias
        adiciona inimigo ao vector
    */
   this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        0.f
   );//posição de inimigos

   this->enemy.setFillColor(sf::Color::Green);// a cor que enemy tera

    //gerador de inimigos
   this->enemies.push_back(this->enemy);

   
}
void Game::pollEvents()
{
    while(this->window->pollEvent(this->ev))
    {
        switch(this->ev.type)
        {
            case sf::Event::Closed:
            window->close();
            break;
            case sf::Event::KeyPressed:
            if(this->ev.key.code == sf::Keyboard::Escape)
            break;    
        }
    }
    
}
void Game::updateMausePositions()// atualizacoes de posição de mause
{
    /*
       @return void 

       updates sobre posiçao do mause
            *A posição do mause e relativa a janela(window)->(vector2i)
    */
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);  //posição do mause
    this->mousePosview = this->window->mapPixelToCoords(this->mousePosWindow);// visualiçao da posicao do mause -- codernada de mapa de pixel.
}
void Game::updateEnemies()// atualiza inimigos
{   
    /*
       @return void 

        atualize o tempo de desova do enemy e desova os enemies(inimigos)  
        quando a quantidade total de inimigos é menor que o máximo
        move os inimigos para baixo
        remover os inimigos na borda da tela
    */

    //atualizando o tempo de desova do inimigo

    if(this->enemies.size() < this->maxEnemies) // Se o tamanho dos enemies for menor que o maximo de enemies
    {
        if(this->enemySpawnTimer >= this->enemySpawnTImerMax)  // Se a desova de enemy for maio ou igual o limite maximo da desova.
        {
            //desovar o inimigo e zerar o tempo
            this->spawnEnemy(); // desovar de enemy
            this->enemySpawnTimer = 0.f;  // tempor de desovar
        }
        else
            this->enemySpawnTimer += 1.f;   // tempor de desovar
    } 

    // movendo enemies e atualizando
    for(int i=0; i < this->enemies.size(); i++) // Se indice for menor que tamanho de enemies ?
    {   
        bool deleted = false;   // 

       this->enemies[i].move(0.f,5.f);//

       //verificar se foi clicado
       if(sf::Mouse::isButtonPressed(sf::Mouse::Left))// Se preciona o botao esquerdo do mause.
       {
           if(this->enemies[i].getGlobalBounds().contains(this->mousePosview)) // Se este enemies obtem limites global, contem a vizualicao da posicao do mause.
           {
               deleted = true;

               //Ganha pontos
               this->points += 10.f;
           }
       }

       //se o enemies está além da parte inferior da tela
        if(this->enemies[i].getPosition().y > this->window->getSize().y ) // se a posicao do enemies for maior que o tamanho da janela(window)
            {
                deleted = true;
            }
        // No final sera deletado
        if(deleted)
             this->enemies.erase(this->enemies.begin() +i); // Se os enemies foram apagados -- e se recomeçaram    
    }     
}
void Game::update()//atualização
{
    this->pollEvents();

    this->updateMausePositions();
    
    this->updateEnemies();

}
void Game::renderEnemies()
{
    //renderizando todos os inimigos
    for(auto &e : this->enemies)
    {
        this->window->draw(e);
    }    
}
void Game::render()
{
    this->window->clear();
    // desenha objeto do game.
    this->renderEnemies();

    this->window->display();
}