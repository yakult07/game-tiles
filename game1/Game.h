#pragma once 

#include<iostream>
#include<Vector>
#include<ctime>
#include<sstream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>


class Game 
{
    private:
    //variables
    //window
    sf::RenderWindow* window; 
    sf::VideoMode videoMode;
    sf::Event ev;
    //mause posição
    sf::Vector2i mousePosWindow;// posiçao do mause na janela(window)
    sf::Vector2f mousePosview; // visualização da posição do mouse

    //Recursos
    sf::Font font;

    //Texto
    sf::Text uiText;

    //game logica
    bool endGame;
    unsigned points; //pontos
    int health; // saude
    float enemySpawnTimer; //tempo de desova do inimigo
    float enemySpawnTImerMax; //tempo máximo de desova do inimigo
    int maxEnemies; // maximo de inimigo
    bool mouseHeld; //  mause segurado

    //objeto de game
    std::vector<sf::RectangleShape> enemies; // inimigos 
    sf::RectangleShape enemy; // formato do inimigo(retangolo)


   
    //funcoes
    void initVariables(); // variaveis  
    void initWindow();  // janela
    void initFonts();  // 
    void initText(); //
    void initEnemies(); // inimigo

    public:
    Game();
    virtual ~Game();


    const bool running() const; // inica loop da janela
    const bool getEndGame() const; // fim de jogo

    //funçoes
    void spawnEnemy();// desova de enemy

    void pollEvents();// loop da janela
    void updateMausePositions();// mause
    void updateText();//
    void updateEnemies(); // atualizar inimigos
    void update();// atualização

    void renderText(sf::RenderTarget& target);// renderização de texto e (alvo)
    void renderEnemies(sf::RenderTarget& target);// renderização de enemies(alvo)
    void render();// renderiza e desenha.

    
};