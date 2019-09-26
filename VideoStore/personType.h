#ifndef PERSONTYPE_H
#define PERSONTYPE_H

//************************************************************
// Author: D.S. Malik
//
// class personType
// This class specifies the members to implement a name.
//************************************************************

#include <iostream>
#include <string>

using namespace std;

class personType {
    
    public:

        // Funcion para imprimir el nombre y apellido de la persona
        void print() const;

        // Funcion para establecer los nombre y apellidos de la persona
        void setName( string first, string last );

        // Funcion para retornar el nombre de la persona
        string getFirstName() const;

        // Funcion para retornar el apellido de la persona
        string getLastName() const;

        // Constructor por defecto
        personType();

        // Constructor con parametros
        personType( string first, string last );

    private:

        string firstName;
        string lastName;
};

// IMPLEMENTACION DE LA CLASE PERSONTYPE

void personType::print() const {
    cout << firstName << " " << lastName << endl;
}

void personType::setName( string first, string last ) {
    firstName = first;
    lastName = last;
}

string personType::getFirstName() const {
    return firstName;
}

string personType::getLastName() const {
    return lastName;
}

personType::personType() {
    firstName = "";
    lastName = "";
}

personType::personType( string first, string last ) {
    firstName = first;
    lastName = last;
}

#endif