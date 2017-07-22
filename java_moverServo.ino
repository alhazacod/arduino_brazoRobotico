#include <Servo.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//VARIABLES PARA EL INTERPRETE DE COMANDOS                                                                 ////
//                                                                                                         ////
/**/    int numChar = 0; //Numero ASCII del caracter.                                                      ////
/**/    char incomingByte = 0;   // informacion entrante (RX)                                              ////
/**/    int cantPalabras = 1; //Cantidad de palabras que se ingresan (el espacio separa las palabras)      ////
/**/    String palabra1 = ""; //Palabra 1 que se ingresa                                                   ////
/**/    String palabra2 = ""; //Palabra 2 que se ingresa                                                   ////
/**/    String palabra3 = ""; //PUEDEN AGREGAR TODAS LAS PALABRAS QUE QUIERAN.                             ////
/**/                                                                                                       ////
/**/    boolean datosAnalizados = false; //Indica si se termino de recorrer la palabra entrante.           ////
/**/                                                                                                       ////
//VARIABLES PARA EL INTERPRETE DE COMANDOS                                                                 ////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
Servo rotor;
Servo brazo;
int angulo;

void analizar(){
  while (Serial.available()>0){
        numChar = Serial.read();//codigo numerico ASCII del caracter
        incomingByte = numChar; //transformo el numero en el caracter ASCII 

        //Uso el caracter 32 (espacio) como delimitador de palabras.
        if (numChar==32){
            cantPalabras++; //Cuando encuentro un espacio, indico que se analizara la próxima palabra.
        }

        /* El caracter 13 corresponde al retorno de carro o la tecla enter.
           El caracter 10 es el salto de línea o la tecla enter.
           El caracter 32 es el espacio.
           Por lo general se utilizan los caracteres 13 10 para marcar el fin de línea, y equivalen a la tecla ENTER de Windows.
           Por lo tanto, me fijo que el caracter analizado no sea ni 13, 10 o 32*/
        if (numChar!=13 && numChar!=10 && numChar!=32){
            
            /*Me fijo que palabra estoy analizando*/
            if(cantPalabras==1){
                palabra1 = palabra1+incomingByte; //Voy agregando los caracteres leidos a la palabra1 para formarla.
            }
            if(cantPalabras==2){
                palabra2 = palabra2+incomingByte; //Voy agregando los caracteres leidos a la palabra2 para formarla.
            }
        }
        if (numChar==10 || numChar==59){
            datosAnalizados = true; //Esto indica que se analizaron datos
        }
    }    
    
    /*Cuando detecto que ya no hay nada para analizar,
    pero hay datos analizados, procedo a transmitirlos.
    */
    if (Serial.available() <=0 && datosAnalizados==true) {
        datosAnalizados = false; //Indico que ya no hay datos analizados, ya que los analizé previamente.

        /*Convierto todas las palabras en mayúscula para facilitar la interpretación, pero esto es opcional.*/
        palabra1.toUpperCase();
        palabra2.toUpperCase();

        //Llamo a la función 'commandInterpreter' y le paso las palabras. Esta función se encargará de interpretar los comandos.
        commandInterpreter(palabra1,palabra2);

        //Reestablezco el valor de las variables para que puedan ser utilizadas nuevamente.
        palabra1 = "";
        palabra2 = "";
        cantPalabras = 1;
        //Serial.flush();//Vacío el buffer del puerto serie para evitar leer valores ya leidos.
    }
}

void setup() {
    Serial.begin(9600);
    Serial.println("Arduino conectado");

    rotor.attach(12);
    brazo.attach(11);

    brazo.write(0);
    rotor.write(0);
}

void loop(){    
    analizar();
}
//Función que analiza e interpreta los comandos


void commandInterpreter(String comando1, String comando2){
    //Me fijo que el comando 1 no esté vacío.
    if (comando1 != ""){
////////////ROTOR////////////////////////////////////////////////////////////
        if (comando1 == "ROTOR"){   
          rotor.write(comando2.toInt());
          Serial.println("El rotor se movio");
          delay(70);
        }
////////////BRAZO////////////////////////////////////////////////////////////
        if(comando1 == "BRAZO"){
          brazo.write(comando2.toInt());
          Serial.println("El brazo se movio");
          delay(70);
        }
////////////ESPERA//////////////////////////////////////////////////////////
        if(comando1 == "ESPERA"){
          esperar(comando2.toInt());
        }
        }else{
          Serial.println("COMANDO 1 INVALIDO");
        }
}
//*********************************************************************************************************************************************
void esperar(int tiempo){
  Serial.println("Se esta esperando ");
  delay(tiempo);
}










//analizar datos*******************************************************************************************************************************

