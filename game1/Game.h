#pragma once 

#include<iostream>
#include<Vector>
#include<ctime>

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

    //game logica
    unsigned points; //pontos
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
    void initEnemies(); // inimigo

    public:
    Game();
    virtual ~Game();


    const bool running() const; // inica loop da janela

    //funçoes
    void spawnEnemy();

    void pollEvents();// loop da janela
    void updateMausePositions();// mause
    void updateEnemies(); // atualizar inimigos
    void update();

    void renderEnemies();
    void render();// renderiza e desenha.

    
};