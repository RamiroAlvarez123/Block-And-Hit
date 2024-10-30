#pragma once
#include "usuario.h"
#include <string>
class ArchivoUsuario{

private:
    std::string _nombreArchivo;

public:
    ArchivoUsuario(std::string nombreArchivo);
    bool Guardar(std::string nombre);
    Usuario Leer(std::string nombre);
    bool Buscar(std::string nombre);
};



