#include <iostream>
#include "ScoreboardFile.h"
#include <vector>
#include <algorithm>


ScoreboardFile::ScoreboardFile(){}


    bool ScoreboardFile::guardarJugador(const ObjJugador& jugador){
	FILE *Archi1;
	Archi1=fopen("scoreboard.dat","ab");
	if(Archi1==NULL){
        std::cout << "ERROR AL ESCRIBIR/CREAR scoreboard.DAT" << std::endl;
        return false;
	}
bool escritura=fwrite(&jugador, sizeof(ObjJugador), 1, Archi1);
fclose(Archi1);

return escritura;
	}


	int ScoreboardFile::contarRegistros(){
	FILE* Archi1;

    Archi1 = fopen("scoreboard.dat", "rb");
    if (Archi1 == NULL) {
        return -1;
    }
    fseek(Archi1, 0, SEEK_END);
    int tam = ftell(Archi1);
    fclose(Archi1);

    return tam / sizeof(ObjJugador);
    }

    ObjJugador ScoreboardFile::leerJugador(int pos){
	ObjJugador obj;
    FILE* Archi1;

    Archi1 = fopen("scoreboard.dat", "rb");
    if (Archi1 == NULL) {
        std::cout << "NO SE PUDO LEER en read player" << std::endl;
        return obj;
    }
    fseek(Archi1, pos * sizeof obj, SEEK_SET);
    fread(&obj, sizeof obj, 1, Archi1);
    fclose(Archi1);

    return obj;
	}


	void ScoreboardFile::ordenarScoreboard() {
    FILE* archivo = fopen("scoreboard.dat", "rb");
    if (!archivo) {
        std::cerr << "Error al abrir el archivo para lectura" << std::endl;
        return;
    }

    std::vector<ObjJugador> jugadores;
    ObjJugador jugador;
    while (fread(&jugador, sizeof(ObjJugador), 1, archivo) == 1) {
        jugadores.push_back(jugador);
    }
    fclose(archivo);

    std::sort(jugadores.begin(), jugadores.end(), [](const ObjJugador& a, const ObjJugador& b) {
        return a.getPuntos() > b.getPuntos() ||
              (a.getPuntos() == b.getPuntos() && a.getNombreJugador() < b.getNombreJugador());
    });

    if (jugadores.size() > 10) {
        jugadores.resize(10);
    }

    archivo = fopen("scoreboard.dat", "wb");
    if (!archivo) {
        std::cerr << "Error al abrir el archivo para escritura" << std::endl;
        return;
    }
    fwrite(jugadores.data(), sizeof(ObjJugador), jugadores.size(), archivo);
    fclose(archivo);
}


	void ScoreboardFile::mostrarTop(sf::RenderWindow& window){
	ObjJugador obj;
    sf::Font font;
    if (!font.loadFromFile("fonts/pixelOperator8.ttf")) {
        return;
    }

    sf::View currentView = window.getView();
    sf::Vector2f centerPosition = currentView.getCenter();

    int cant = contarRegistros();

    for (int i = 0; i < 10; i++) {
        if (i <= cant) {
            obj = leerJugador(i);
        }

        std::string nombreJugador = obj.getNombreJugador();
        int puntos = obj.getPuntos();

        sf::Text textRank;
        textRank.setFont(font);
        textRank.setString(std::to_string(i + 1));
        textRank.setCharacterSize(20); // en pixels
        textRank.setFillColor(sf::Color::White);
        textRank.setOutlineThickness(2);
        textRank.setOutlineColor(sf::Color::Black);

        sf::Text textName;
        textName.setFont(font);
        textName.setString(nombreJugador);
        textName.setCharacterSize(20); // en pixels
        textName.setFillColor(sf::Color::White);
        textName.setOutlineThickness(2);
        textName.setOutlineColor(sf::Color::Black);

        sf::Text textPoints;
        textPoints.setFont(font);
        textPoints.setString(std::to_string(puntos));
        textPoints.setCharacterSize(20); // en pixels
        textPoints.setFillColor(sf::Color::White);
        textPoints.setOutlineThickness(2);
        textPoints.setOutlineColor(sf::Color::Black);

        if(i==0){textRank.setFillColor(sf::Color::Yellow);
                 textName.setFillColor(sf::Color::Yellow);
                 textPoints.setFillColor(sf::Color::Yellow);}

        sf::FloatRect rankRect = textRank.getLocalBounds();
        textRank.setOrigin(rankRect.left + rankRect.width / 2.0f, rankRect.top + rankRect.height / 2.0f);
        textRank.setPosition(centerPosition.x - 140, (window.getSize().y / 2.0f) + (30 * i) - (13 * 10));

        sf::FloatRect nameRect = textName.getLocalBounds();
        textName.setOrigin(nameRect.left + nameRect.width / 2.0f, nameRect.top + nameRect.height / 2.0f);
        textName.setPosition(centerPosition.x - 10, (window.getSize().y / 2.0f) + (30 * i) - (13 * 10));

        sf::FloatRect pointsRect = textPoints.getLocalBounds();
        textPoints.setOrigin(pointsRect.left + pointsRect.width / 2.0f, pointsRect.top + pointsRect.height / 2.0f);
        textPoints.setPosition(centerPosition.x + 120, (window.getSize().y / 2.0f) + (30 * i) - (13 * 10));

        window.draw(textRank);
        window.draw(textName);
        window.draw(textPoints);
    }
	}


