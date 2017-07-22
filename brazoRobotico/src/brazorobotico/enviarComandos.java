/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package brazorobotico;

import com.panamahitek.ArduinoException;
import com.panamahitek.PanamaHitek_Arduino;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import jssc.SerialPortEvent;
import jssc.SerialPortEventListener;
import jssc.SerialPortException;

/**
 *
 * @author angel
 */
public class enviarComandos{
    window ventana = new window();
    
    PanamaHitek_Arduino ino = new PanamaHitek_Arduino();
    private final SerialPortEventListener listener = new SerialPortEventListener() {
        @Override
        public void serialEvent(SerialPortEvent spe) {
            try
            {
                if (ino.isMessageAvailable()){
                    ventana.consola.append(ino.printMessage() + "\n");
                    ventana.consola.setCaretPosition(ventana.consola.getDocument().getLength());
                    System.out.println(ino.printMessage() + "\n");
                }
            }catch(SerialPortException | ArduinoException ex){
                
                Logger.getLogger(window.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    };
    
    public enviarComandos(){
        
    }
    
    public List<String> getPorts(){
        return ino.getSerialPorts();
    }
    
    public void conectar(String puerto){
        try {
            ino.arduinoRXTX(puerto, 9600, listener);
        } catch (ArduinoException ex) {
            ventana.consola.setText("No se pudo conectar al arduino");
            Logger.getLogger(enviarComandos.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public void killconection(){
        try {
            ino.killArduinoConnection();
        } catch (ArduinoException ex) {
            Logger.getLogger(enviarComandos.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    //envia los datos//////////////////////////////////////////////////////////////////
    public void send(String comando){
        try {
            ino.sendData(comando);
        } catch (ArduinoException | SerialPortException ex) {
            ventana.consola.setText("No se pudo enviar los datos");
            Logger.getLogger(enviarComandos.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    ///////////////////////////////////////////////////////////////////////////////////
    
    //envia la lista de comandos///////////////////////////////////////////////////////
    public void sendComandos(String[] lineas){
        try {
            /*for(int i=0; i<lineas.length;i++){
            System.out.print("Comando "+i+": "+lineas[i].replace("\n", "")+"\n");
            try {
            ino.sendData(lineas[i].replace("\n", "")+"\n");
            System.out.println("Datos enviados");
            } catch (ArduinoException | SerialPortException ex) {
            System.out.println("Error al enviar los datos");
            Logger.getLogger(enviarComandos.class.getName()).log(Level.SEVERE, null, ex);
            }
            }*/
            ventana.ino.sendData("rotor 90");
            System.out.println("datos enviados");
        } catch (ArduinoException | SerialPortException ex) {
            ventana.consola.append("imposible enviar los datos");
            Logger.getLogger(enviarComandos.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
