/*#include <iostream>
#include "ScoreboardFile.h"



Archirank::Archirank(){}

	int Archirank::contarRegistro(){
	FILE* Archi1;

    Archi1 = fopen("ranking.dat", "rb");
    if (Archi1 == NULL) {
        return -1;
    }
    fseek(Archi1, 0, SEEK_END);
    int tam = ftell(Archi1);
    fclose(Archi1);

    return tam / sizeof(PlayerScore);
    }

	void Archirank::ordenarRanking(){
	FILE* Archi1;
	Archi1 = fopen("ranking.dat", "rb+");
	if (Archi1 == NULL) {
		std::cout << "error al ordenar" << std::endl;
		return;
	}

	PlayerScore obj1, obj2;
	int cant = contarRegistros();

    if (cant > 1) {
        for (int i = 0; i < cant - 1; i++) {
            for (int j = 0; j < cant - i - 1; j++) {
                obj1 = leerPlayer(j);
                obj2 = leerPlayer(j + 1);
                // Comprobar si el primer objeto tiene menos puntos que el segundo,
                // o si tienen los mismos puntos pero el primer nombre es mayor alfabéticamente
                if (obj1.getPoints() < obj2.getPoints() || (obj1.getPoints() == obj2.getPoints() && obj1.getPlayerName() > obj2.getPlayerName())) {
                    fseek(Archi1, j * sizeof obj1, SEEK_SET);
                    fwrite(&obj2, sizeof obj2, 1, Archi1);
                    fseek(Archi1, (j + 1) * sizeof obj1, SEEK_SET);
                    fwrite(&obj1, sizeof obj1, 1, Archi1);
                }
            }
        }
    }
	fclose(Archi1);

	// Si hay más de 10 registros, eliminar el último
    if (cant > 10) {
        FILE* pTemp;
        FILE* pOriginal;
        pOriginal = fopen("ranking.dat", "rb");
        pTemp = fopen("temp.dat", "wb");

        if (pOriginal == NULL || pTemp == NULL) {
            std::cout << "ERROR AL ABRIR ARCHIVOS original/temp" << std::endl;
            return;
        }

        for (int i = 0; i < 10; i++) {
            fread(&obj1, sizeof(PlayerScore), 1, pOriginal);
            fwrite(&obj1, sizeof(PlayerScore), 1, pTemp);
        }

        fclose(pOriginal);
        fclose(pTemp);

        // Reemplazar el archivo original con el temporal
        if (remove("ranking.dat") == 0) {
            if (rename("temp.dat", "ranking.dat") != 0) {
                std::cerr << "Error al renombrar el archivo temporal." << std::endl;
                // Manejar el error según sea necesario
            }
        }
        else {
            std::cerr << "Error al eliminar el archivo original." << std::endl;
            // Manejar el error según sea necesario
        }
    }
	}

	bool Archirank::savePlayer(const PlayerScore &score){
	FILE *Archi1;
	Archi1=fopen("Ranking.dat","ab");
	if(Archi1==NULL){
        std::cout << "ERROR AL ESCRIBIR/CREAR RANKING.DAT" << std::endl;
        return false;
	}
bool escritura=fwrite(&score, sizeof(PlayerScore), 1, Archi1);
fclose(Archi1);

return escritura;
	}

	PlayerScore Archirank::readPlayer(int pos){
	PlayerScore obj;
    FILE* Archi1;

    Archi1 = fopen("ranking.dat", "rb");
    if (Archi1 == NULL) {
        std::cout << "NO SE PUDO LEER en read player" << std::endl;
        return obj;
    }
    fseek(Archi1, pos * sizeof obj, SEEK_SET);
    fread(&obj, sizeof obj, 1, Archi1);
    fclose(Archi1);

    return obj;
	}

	void Archirank::showTopTen(sf::RenderWindow& window){
	PlayerScore obj;
    sf::Font font;
    if (!font.loadFromFile("fonts/pixelOperator8.ttf")) {
        return;
    }

    sf::View currentView = window.getView();
    sf::Vector2f centerPosition = currentView.getCenter();

    int cant = contarRegistros();

    for (int i = 0; i < 10; i++) {
        if (i <= cant) {
            obj = leerPlayer(i);
        }
        else {
            obj.setPlayerName("AAAAA");
            obj.setPoints(0);

        }

        std::string playerName = obj.getPlayerName();
        int points = obj.getPoints();

        // Texto para el número de clasificación
        sf::Text textRank;
        textRank.setFont(font);
        textRank.setString(std::to_string(i + 1));
        textRank.setCharacterSize(24); // en pixels
        textRank.setFillColor(sf::Color::White);
        textRank.setOutlineThickness(2);
        textRank.setOutlineColor(sf::Color::Black);

        // Texto para el nombre del jugador
        sf::Text textName;
        textName.setFont(font);
        textName.setString(playerName);
        textName.setCharacterSize(24); // en pixels
        textName.setFillColor(sf::Color::White);
        textName.setOutlineThickness(2);
        textName.setOutlineColor(sf::Color::Black);

        // Texto para los puntos
        sf::Text textPoints;
        textPoints.setFont(font);
        textPoints.setString(std::to_string(points));
        textPoints.setCharacterSize(24); // en pixels
        textPoints.setFillColor(sf::Color::White);
        textPoints.setOutlineThickness(2);
        textPoints.setOutlineColor(sf::Color::Black);

        // Calcular posición para centrar el número de clasificación
        sf::FloatRect rankRect = textRank.getLocalBounds();
        textRank.setOrigin(rankRect.left + rankRect.width / 2.0f, rankRect.top + rankRect.height / 2.0f);
        textRank.setPosition(centerPosition.x - 140, (window.getSize().y / 2.0f) + (30 * i) - (13 * 10));

        // Calcular posición para centrar el nombre del jugador
        sf::FloatRect nameRect = textName.getLocalBounds();
        textName.setOrigin(nameRect.left + nameRect.width / 2.0f, nameRect.top + nameRect.height / 2.0f);
        textName.setPosition(centerPosition.x - 10, (window.getSize().y / 2.0f) + (30 * i) - (13 * 10));

        // Calcular posición para centrar los puntos
        sf::FloatRect pointsRect = textPoints.getLocalBounds();
        textPoints.setOrigin(pointsRect.left + pointsRect.width / 2.0f, pointsRect.top + pointsRect.height / 2.0f);
        textPoints.setPosition(centerPosition.x + 120, (window.getSize().y / 2.0f) + (30 * i) - (13 * 10));

        window.draw(textRank);
        window.draw(textName);
        window.draw(textPoints);
    }
	}

*/
