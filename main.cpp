#include<SFML/Graphics.hpp>
#include<time.h>
using namespace sf;

const int Altura = 20;
const int largura = 10;

int campo [Altura][largura] = {0};

struct ponto 
{int lugarX,lugarY;} blocoA[4],blocoB[4];


int figuras[7][4] = 
{  
    1,3,5,7, // I
    2,4,5,7, // Z
    3,5,4,6,  // S
    3,5,4,7,  // T
    2,3,5,7,  // L
    3,5,7,6,  // J
    2,3,4,5,  // O
};
bool verificar()
{
    for(int i=0;i<4;i++)
        if (blocoA[i].lugarX<0 || blocoA[i].lugarX>=largura || blocoA[i].lugarY>=Altura) return 0;
        else if (campo[blocoA[i].lugarY][blocoA[i].lugarX]) return 0;

        return 1;
}; 

int main()
{   
    srand(time(0));

    RenderWindow window(VideoMode(320,480),"O jogo!");

    Texture t1,t2,t3;
    t1.loadFromFile("images//tiles.png");
    t2.loadFromFile("images/background.png");
    t3.loadFromFile("images/frame.png");

    Sprite s(t1), background(t2), frame(t3);
    

    int move = 0; int giro = false; int ColorNum = 1;
    float tempor = 0, atraso =0.3;

    Clock clock;   

    while(window.isOpen())
    {   
        float tempo = clock.getElapsedTime().asSeconds();
        clock.restart();
        tempor+=tempo;

        Event e;
        while(window.pollEvent(e))
        { 
            if(e.type == Event::Closed)
                window.close();

            if(e.type == Event::KeyPressed)
                if(e.key.code == Keyboard::Up) giro = true;
                else if(e.key.code == Keyboard::Left)  move =-1;
                else if(e.key.code == Keyboard::Right) move = 1;   
        }
    if(Keyboard::isKeyPressed(Keyboard::Down)) atraso= 0.05;    
    /////// <-move -> ///////////
    for(int i=0;i<4;i++) {blocoB[i] = blocoA[i]; blocoA[i].lugarX+=move;}
    if(!verificar()) for (int i=0;i<4;i++) blocoA[i]=blocoB[i];
    ////// giro //////////
    if(giro)
    {
        ponto centro = blocoA[1];
        for(int i=0;i<4;i++)
        {
            int direita = blocoA[i].lugarY-centro.lugarY;
            int esquerda = blocoA[i].lugarX-centro.lugarX;
            blocoA[i].lugarX = centro.lugarX-direita;
            blocoA[i].lugarY = centro.lugarY+esquerda;

        }
        if(!verificar()) for(int i=0;i<4;i++) blocoA[i]=blocoB[i]; 
    }
    /////// marcação //////////////
    if(tempor>atraso)
    {
        for(int i=0;i<4;i++)   {blocoB[i]=blocoA[i]; blocoA[i].lugarY+=1;}

        if(!verificar()) 
        {
            for(int i=0;i<4;i++) campo[blocoB[i].lugarY][blocoB[i].lugarX]= ColorNum;

            ColorNum=1+rand()%7;
            int Num=rand()%7;
            for(int i=0;i<4;i++)
            {
                blocoA[i].lugarX = figuras[Num][i]%2;
                blocoA[i].lugarY = figuras[Num][i]/2;
            } 
        }
        tempor=0;
       
    }
    ////// verificar linhas ///////
    int Linhas = Altura-1;
    for(int i=Altura-1;i>0;i--)
    {
        int contar = 0;
        for(int j=0;j<largura;j++)
        {
            if(campo[i][j]) contar++;
                campo[Linhas][j]=campo[i][j];
        }
        if(contar<largura) Linhas --;
    }


    move=0; giro=0; atraso = 0.3;
    /////// desenha /////////
    window.clear(Color::White);
    window.draw(background);
    
    for (int i=0;i<Altura;i++)
        for(int j=0;j<largura;j++)
        {
            if(campo[i][j]==0) continue;
            s.setTextureRect(IntRect(campo[i][j]*18,0,18,18));
            s.setPosition(j*18,i*18);
            s.move(28,31);
            window.draw(s);
        }
    for(int i=0;i<4;i++)
    {   
        s.setTextureRect(IntRect(ColorNum*18,0,18,18));
        s.setPosition(blocoA[i].lugarX*18,blocoA[i].lugarY*18);
        s.move(28,31);
        window.draw(s);
    }
    window.draw(frame);
    window.display();    
    }
    return 0;
}