#ifndef PERSONA_H
#define PERSONA_H

#include <QString>

class Persona {
    public:
        Persona();
        Persona( QString nombre, QString apellido, QString correo, char sexo, int edad, int dni );

    private:
        QString nombre;
        QString apellido;
        QString correo;
        char sexo;
        int edad;
        int dni;
};

#endif // PERSONA_H
