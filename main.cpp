#include <iostream>
#include <string>
#include <vector>
#include <xlsxio_read.h>
#include <mpi.h>

#include "funciones.h"
#include "DocenteCurso.h"
#include "DisponibilidadHoraria.h"
#include "HorarioSala.h"

using namespace std;

int main(){

    MPI_Init(NULL, NULL);

    int procesos;
    int proceso;

    MPI_Comm_rank(MPI_COMM_WORLD, &proceso);
    MPI_Comm_size(MPI_COMM_WORLD, &procesos);

    vector<DocenteCurso> vectorDocenteCurso = llenarVectorDocenteCurso();
    // vector<DisponibilidadHoraria> vectorDisponibilidad = llenarVectorDisponibilidadHoraria();
    vector<HorarioSala> vectorHorarioSala = llenarVectorHorarioSala();

    if(proceso == 0){
        //Se recorre una vez por cada objeto DocenteCurso
        for(int docente = 0; docente < vectorDocenteCurso.size(); docente++){
            int labFinal;
            int salaFinal;
            int bloqueFinal;
            int diaFinal;

            while(vectorDocenteCurso[docente].retornaBloquesDisponibles() > 0){
                cout << "Soy el docente: " << docente+2 << endl;
                int bloquesDisponiblesOriginal = vectorDocenteCurso[docente].retornaBloquesDisponibles();
                
                if(vectorDocenteCurso[docente].esINF()){
                    int primerLab = 35;
                    int ultimoLab = 40;
                    
                    //Se recorren todos los labs por cada DocenteCurso de INF    
                    for(int lab = primerLab; lab <= ultimoLab; lab++){
                        
                        //Se recorren los días de la semana
                        for(int dia = 0; dia < 6; dia++){
                            //Si es un día de lunes a viernes
                            if(dia != 5){
                                for(int bloque = 0; bloque < 7; bloque++){
                                    if(vectorHorarioSala[lab].retornaMatrizHorario()[bloque][dia] == "Disponible"){
                                        // cout << "Me quedan " << vectorDocenteCurso[docente].retornaBloquesDisponibles() << endl;
                                        // cout << "Se añade el bloque" << endl;
                                        // vectorDocenteCurso[docente].restaBloquesDisponibles();
                                        // cout << "Ahora me quedan " << vectorDocenteCurso[docente].retornaBloquesDisponibles() << endl;            
                                    }                                   
                                }
                            }
                            //Si es sábado
                            else{
                                for(int bloque = 0; bloque < 4; bloque++){
                                    if(vectorHorarioSala[lab].retornaMatrizHorario()[bloque][dia] == "Disponible"){
                                        // cout << "Me quedan " << vectorDocenteCurso[docente].retornaBloquesDisponibles() << endl;
                                        // cout << "Se añade el bloque" << endl;
                                        // vectorDocenteCurso[docente].restaBloquesDisponibles();
                                        // cout << "Ahora me quedan " << vectorDocenteCurso[docente].retornaBloquesDisponibles() << endl;                                           
                                    }
                                    bloqueFinal = bloque;                                                                      
                                }

                            }
                            if(bloquesDisponiblesOriginal > vectorDocenteCurso[docente].retornaBloquesDisponibles())
                                break; //Si ha cambiado la cantidad de bloques disponibles deja de recorrer
                        
                            diaFinal = dia;
                        }
                        if(bloquesDisponiblesOriginal > vectorDocenteCurso[docente].retornaBloquesDisponibles())
                                break; //Si ha cambiado la cantidad de bloques disponibles deja de recorrer

                        labFinal = lab;
                    }
                }                

                //Se verifica que el DocenteCurso no sea de INF
                else{
                    int primeraSala = 0;
                    int ultimaSala = 34;
                    
                    //Se recorren todos los labs por cada DocenteCurso de INF    
                    for(int sala = primeraSala; sala <= ultimaSala; sala++){
                        
                        //Se recorren los días de la semana
                        for(int dia = 0; dia < 6; dia++){
                            //Si es un día de lunes a viernes
                            if(dia != 5){
                                for(int bloque = 0; bloque < 7; bloque++){
                                    if(vectorHorarioSala[sala].retornaMatrizHorario()[bloque][dia] == "Disponible"){
                                        cout << "Me quedan " << vectorDocenteCurso[docente].retornaBloquesDisponibles() << endl;
                                        cout << "Se añade el bloque" << endl;
                                        vectorDocenteCurso[docente].restaBloquesDisponibles();
                                        cout << "Ahora me quedan " << vectorDocenteCurso[docente].retornaBloquesDisponibles() << endl;               
                                    }                                   
                                }
                            }
                            //Si es sábado
                            else{
                                for(int bloque = 0; bloque < 4; bloque++){
                                    if(vectorHorarioSala[sala].retornaMatrizHorario()[bloque][dia] == "Disponible"){
                                        cout << "Me quedan " << vectorDocenteCurso[docente].retornaBloquesDisponibles() << endl;
                                        cout << "Se añade el bloque" << endl;
                                        vectorDocenteCurso[docente].restaBloquesDisponibles();
                                        cout << "Ahora me quedan " << vectorDocenteCurso[docente].retornaBloquesDisponibles() << endl;                                           
                                    }
                                    bloqueFinal = bloque;                                                                      
                                }

                            }
                            if(bloquesDisponiblesOriginal > vectorDocenteCurso[docente].retornaBloquesDisponibles())
                                break; //Si ha cambiado la cantidad de bloques disponibles deja de recorrer
                        
                            diaFinal = dia;
                        }
                        if(bloquesDisponiblesOriginal > vectorDocenteCurso[docente].retornaBloquesDisponibles())
                                break; //Si ha cambiado la cantidad de bloques disponibles deja de recorrer

                        salaFinal = sala;
                    }
                }

                //Se realiza la salida del bucle en el caso de que no sea posible seguir llenando el horario con este DocenteCurso
                if(vectorDocenteCurso[docente].esINF()){
                    if(bloqueFinal == 3 && diaFinal == 5 && labFinal == 40){
                        cout << "Bloque Final: " << bloqueFinal << endl;
                        cout << "Dia Final: " << diaFinal << endl;
                        cout << "Lab Final: " << labFinal << endl;
                        break;
                    }
                }

                else{
                    if(bloqueFinal == 3 && diaFinal == 5 && salaFinal == 34){
                        cout << "Bloque Final: " << bloqueFinal << endl;
                        cout << "Dia Final: " << diaFinal << endl;
                        cout << "Sala Final: " << salaFinal << endl;
                        break;
                    }
                }

                    
            }//Mientras los bloques disponibles sean mayor a 0
            

        }
    }

    //Verifica que no hayan cuatro bloques del mismo curso/profe asignados
    if(proceso == 1){
        
    }

    //Verifica que el profe tenga disponibilidad, recibe indices retorna un bool
    if(proceso == 2){
        
    }

    MPI_Finalize();
    return 0;
}