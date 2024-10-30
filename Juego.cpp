#include <iostream>
#include "Juego.h"
using namespace std;



Juego::Juego(int X, int Y, sf::Font &font, sf::Texture &imagen){
texto.setFont(font);
texto.setString(to_string(Puntaje));
texto.setCharacterSize(24); ///tamanio de los caracteres de texto
texto.setPosition(float(x+75.f/2.f),float(y+75.f/2.f)-5); /// ubica el texto acomodado al tamanio de ventana
texto.setfillColor(sf::Color(255,255,255)); /// color blanco

/// COLORES
colors={sf::Color(102,102,102),sf::Color(255,166,0),sf::Color(245,151,245),sf::Color(51,204,153),sf::Color(255,110,110),sf::Color(255,204,77),sf::Color(166,166,255),sf::Color(137,194,247),sf::Color(0,255,255),sf::Color(0,128,0),sf::Color(255,0,255),sf::Color(128,128,0)};

/// setters
mostrarImagen.setPosition(x,y);
mostrarImagen.setColor(colors[0]); /// define color gris
mostrarImagen.setTexture(imagen);

}



void Juego::setPuntaje(int Puntaje){
Pun=Puntaje;

texto.setString(to_string(Pun)); ///actualiza el texto
texto.setOrigin(texto.getGlobalBounds().width/2,texto.getBlobalBounds().height/2); /// centra el texto correctamente en la ventana

if(Pun==0) mostrarImagen.setColor(colors[0]); /// color principal
else{
    for(int i=1;i<15;i++){
            ///mueve a la izquierda el uno para encontrar color correspondiente
        if(Pun&(1<<i)){
            mostrarImagen.setColor(colors[i]);
        }
    }
    Pun=0;
    mostrarImagen.setColor(colors[0]);
}

}


int Juego::getPuntaje(){
return Pun;
}

int actualizarPuntos();


void Juego::procesarEntrada(std::pair<int,int> dir){
mostrarImagen.Mov(dir.first,dir.second);
texto.Mov(dir.first,dir.second);
}



void Juego::setPos(sf::Vector2f pos){
mostrarImagen.setPosition(pos.x,pos.y);
texto.setPosition(float(pos.x+75.f/2.f),float(pos.y+75.f/2.f)-5);
}


sf::Vector2f Juego::getPos(){
return mostrarImagen.getPosition();
}

bool Juego::terminarjuego(){

bool endGame=true;

pair <int,int> Ubi={0,0};

for(int N=0;N<4;N++){
    if (N==0) Ubi{0,-1};
    if (N==1) Ubi{0,1};
    if (N==2) Ubi{-1,0};
    if (N==3) Ubi{1,0};


int iniI=0;
int UbiI=1;
int iniJ=0;
int UbiJ=1;

if(Ubi.first==1) iniI=3,UbiI=-1;
if(Ubi.second==1) iniJ=3,UbiJ=-1;

for(int i=iniI;i>=0&&i<4;i+=UbiI){
    for(int j=iniJ;j>=0&&j<4;i+=UbiJ){
        if(piece[i][j].getPuntaje()!=0){
          if(i+Ubi.first<0||i+Ubi.first>3||j+Ubi.second<0||j+Ubi.second>3) continue;

            if(piece[i+Ubi.first][j+Ubi.second].getPuntaje()==piece[i][j].getPuntaje()||piece[i+Ubi.first][j+Ubi.second].getPuntaje()==0||dest[i+Ubi.first][j+Ubi.second]!=sf::Vector2f(i+Ubi.first,j+Ubi.second) ){
                endGame=false;
            }
        }

    }

}

}
return endGame;
}

bool Ganaste();

void Juego::draw(sf::RenderTarget &rt,sf::RenderStates rs){
rt.draw(mostrarImagen,rs);
if(Pun!=0) rt.draw(texto,rs);
}
















int main(){


return 0;
}
