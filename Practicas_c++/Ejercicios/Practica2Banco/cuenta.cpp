#include "cuenta.hpp"



Cuenta::Cuenta():nombre(""),cuenta(0),saldo(0){};  //constructor por defecto asignando todo a 0

Cuenta::Cuenta(std::string nombrec,unsigned numeroc,float saldoc){

nombre=nombrec;
cuenta=numeroc;
saldo=saldoc;

};

Cuenta::~Cuenta(){};

Cuenta::Cuenta(const Cuenta &cuentaoriginal){

nombre=cuentaoriginal.nombre;
cuenta=cuentaoriginal.cuenta;       
saldo=cuentaoriginal.saldo;

};

std::string Cuenta::consultarNombre(){

std::string nombr;

return nombr=nombre;

};

unsigned Cuenta::consultarCuenta(){

unsigned ncuenta;

return ncuenta=cuenta;

};

float Cuenta::consultarSaldo(){

    float saldoc;

    return saldoc=saldo;
};

void Cuenta::asignarNombre(std::string nuevonombre){

    nombre=nuevonombre;
};

void Cuenta::asignarNumero(unsigned nuevonumero){

    cuenta=nuevonumero;
};

void Cuenta::asignarSaldo(float saldos){
    saldo=saldos;
};


float Cuenta::realizarIngreso(float ingreso){

    if(ingreso >0.0){
        saldo+=ingreso;
    }else{
        std::cout<<"introduzca un ingreso positivo"<<std::endl;
    }

    double s=saldo;

    return s;
    
};

float Cuenta::sacarDinero(float retiro){

    if(retiro>0.0  && retiro<=saldo){
        saldo-=retiro;
    }else{
        std::cout<<"introduce un retiro correcto"<<std::endl;
    }

    float r=saldo;
    return r;
};

float Cuenta::anyadeInteres(float interes){

    if(interes >0.0 && interes <=1.0){
        saldo+=saldo*interes;
    }else{
        std::cout<<"introduce un saldo valido"<<std::endl;
    }

    float s=consultarSaldo();

    return s;
};

void Cuenta::muestraEstadistica(){

    std::cout<<nombre<<std::endl;
    std::cout<<cuenta<<std::endl;
    std::cout<<saldo<<std::endl;
}

