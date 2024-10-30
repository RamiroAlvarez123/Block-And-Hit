#include "ArchivoLogin.h"
#include "usuario.h"

ArchivoUsuario::ArchivoUsuario(std::string nombreArchivo){
    _nombreArchivo = nombreArchivo;
}

bool ArchivoUsuario::Guardar(std::string nombre){
    FILE *pArchivo = fopen(_nombreArchivo.c_str(), "ab");
    if(pArchivo == NULL){
        return false;
    }
    Usuario usuario;
    usuario.setNombre(nombre);
    usuario.setPuntajeMax(0);
    bool response = fwrite(&usuario, sizeof(usuario), 1, pArchivo);
    fclose(pArchivo);
    return response;

}
