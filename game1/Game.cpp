#include "Game.h"

//funçoes privada;
void Game::initVariables() // variaveis
{ 
    this->window= nullptr;

    // logica de jogo
    this->endGame = false;
    this->points = 0; // pontos
    this->health = 20; //
    this->enemySpawnTImerMax = 20.f; // tempo maximo de desova dos inimigos
    this->enemySpawnTimer = this->enemySpawnTImerMax ; // tempo de desova dos inimigos
    this->maxEnemies = 5;  // maximo de inimigos 
    this->mouseHeld = false;  // mause segurado
}
void Game::initWindow() // iniciaçao de janela
{   
    this->videoMode.height = 600; // altura
    this-> videoMode.width = 800;  // largura
    this->window = new sf::RenderWindow(this->videoMode, "Game i On ", sf::Style::Titlebar | sf::Style::Close); // configuraçao da janela
    this->window->setFramerateLimit(60);//definir limite de taxa de quadros
}
void Game::initFonts()// iniciaçao de fontes
{
   if( this->font.loadFromFile("fonts//Dosis-Light.ttf"))
   {
       std::cout << "ERROR::GAME::INITFONTES::Failed to Loard font!" << "\n";
   }
}
void Game::initText() // iniciaçao de textos
{
    this->uiText.setFont(this->font);  // define fontes
    this->uiText.setCharacterSize(24); //definir o tamanho do caractere
    this->uiText.setFillColor(sf::Color::White);// definir cor de preenchimento
    this->uiText.setString("NONE");// 
}
void Game::initEnemies()//inimigos
{   
    this->enemy.setPosition(10.f, 10.f);//posição definida
    this->enemy.setSize(sf::Vector2f(100.f,100.f)); //definir o tamanho
    this->enemy.setFillColor(sf::Color::Cyan); //definir cor de preenchimento
    //this->enemy.setOutlineColor(sf::Color::Green);//definir a cor da linha
    //this->enemy.setOutlineThickness(1.f);//definir a espessura da linha
}
//contrutor // destruidor
Game::Game()
{  
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initText();
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
const bool Game::getEndGame() const
{
    return this->endGame;  
}
// funçoes
void Game::spawnEnemy() //gerar inimigos
{
    /*
        @return void
        gera inimigos e define seu tipo, cor e posições aleatoriamente
        define um tipo aleatório de diferença
        definir posições aleatórias
        definir cor aleatórias
        adiciona inimigo ao vector
    */
   this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        0.f
   );//posição de inimigos

    //randomiza o tipo de enemy
    int type = rand() %5;

    switch(type)
    {
    case 0:
        this->enemy.setSize(sf::Vector2f(10.f,10.f)); //definir o tamanho
        this->enemy.setFillColor(sf::Color::Magenta);// a cor que enemy tera
        break;
    case 1:
        this->enemy.setSize(sf::Vector2f(30.f,30.f)); //definir o tamanho
        this->enemy.setFillColor(sf::Color::Blue);// a cor que enemy tera
        break;
    case 2:
        this->enemy.setSize(sf::Vector2f(50.f,50.f)); //definir o tamanho
        this->enemy.setFillColor(sf::Color::Cyan);// a cor que enemy tera
        break;    
    case 3:
        this->enemy.setSize(sf::Vector2f(70.f,70.f)); //definir o tamanho
        this->enemy.setFillColor(sf::Color::Red);// a cor que enemy tera
        break;
    case 4:
        this->enemy.setSize(sf::Vector2f(100.f,100.f)); //definir o tamanho
        this->enemy.setFillColor(sf::Color::Green);// a cor que enemy tera
        break;
    default:
        this->enemy.setSize(sf::Vector2f(100.f,100.f)); //definir o tamanho
        this->enemy.setFillColor(sf::Color::Yellow);// a cor que enemy tera
        break;
    }


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
void Game::updateText()// atualizacoes de textos
{   
    std::stringstream ss;// fluxo de string 

    ss << "Points: " << this->points << "\n" 
        << "Health: "<< this->health << "\n";

    this->uiText.setString(ss.str());
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

         //se o enemies está além da parte inferior da tela
        if(this->enemies[i].getPosition().y > this->window->getSize().y ) // se a posicao do enemies for maior que o tamanho da janela(window)
            { 
             this->enemies.erase(this->enemies.begin() +i); // Se os enemies foram apagados -- e se recomeçaram  
             this->health -= 1;   // saude menos ou igual 1
              std::cout << " Health: " << this->health << "\n"; //
            }   
    }  
     //verificar se foi clicado
    
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))// Se preciona o botao esquerdo do mause.
    {   
        if(this->mouseHeld == false) // mause segure 
        {   
            this->mouseHeld = true;
            bool deleted = false;
            for(size_t i=0;i<this->enemies.size() && deleted == false;i++)// se incidce por menor que tamanho de enemies e apagar seja falso.
            {
                if(this->enemies[i].getGlobalBounds().contains(this->mousePosview)) // Se este enemies obtem limites global, contem a vizualicao da posicao do mause.
                {   
                    //Ganha pontos
                    if(this->enemies[i].getFillColor() == sf::Color::Magenta)
                        this->points += 10;
                    else if(this->enemies[i].getFillColor() == sf::Color::Blue)    
                        this->points += 7;
                    else if(this->enemies[i].getFillColor() == sf::Color::Cyan)    
                        this->points += 5;
                    else if(this->enemies[i].getFillColor() == sf::Color::Green)    
                        this->points += 1;

                    std::cout << "Points: " << this->points << "\n"; //

                     // enemies excluido
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() +i); // Se os enemies foram apagados -- e se recomeçaram 
                }
            }    
        }    
    }
    else
    {
        this->mouseHeld = false;
    }

      

}
void Game::update()//atualização
{
    this->pollEvents();
    if(this->endGame == false )//fim de jogo
    {
    this->updateMausePositions();
    
    this->updateText();
    
    this->updateEnemies();
    }

    // condição de fim de jogo
    if(this->health <= 0) // se saude for menor ou igual que 0.
        this->endGame = true;// fim de jogo

}
void Game::renderText(sf::RenderTarget& target) // Renderização e (alvo) de texto
{
    target.draw(this->uiText); // (alvo) desenho de texto
}
void Game::renderEnemies(sf::RenderTarget& target) // renderização de enemies 
{
    //renderizando todos os inimigos
    for(auto &e : this->enemies)
    {
        target.draw(e); // alvo do desenho
    }    
}
void Game::render()
{
    this->window->clear();
    // desenha objeto do game.
    this->renderEnemies(*this->window);

    this->renderText(*this->window);

    this->window->display();
}