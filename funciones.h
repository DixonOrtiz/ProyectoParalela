#pragma once
#include <vector>
#include "DocenteCurso.h"
#include "DisponibilidadHoraria.h"
#include "HorarioSala.h"

using namespace std;

void mostrarMatrizDisponibilidad(vector<vector<bool>>);

void mostrarMatrizHorario(vector<vector<string>>);

vector<DocenteCurso> llenarVectorDocenteCurso();

vector<vector<bool>> retornaMatrizPorHoja(int);
vector<int> retornaVectorIdDocente();
vector<vector<bool>> cambiarColumnasPorFilas(vector<vector<bool>>&);
vector<DisponibilidadHoraria> llenarVectorDisponibilidadHoraria();

vector<vector<string>> llenarMatrizHorarioDisponible();
vector<HorarioSala> llenarVectorHorarioSala();

