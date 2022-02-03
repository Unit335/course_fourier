#pragma once
#include "framework.h"
#include "afxdialogex.h"


typedef struct
{
public:
	double N=100., f=1000000., Fm=100000., m=0., scaleX=1., scaleY=1., n=0., dx=0., t=0.;
	bool log=0;
} m_par;

class Graphics : public CWinThread //Объявление класса расчёта Graphics
{
public:
	Graphics(); //Конструктор класса
	~Graphics();
	const double Fd = 10000000., a = 1., GR_END = 2 * M_PI * 120;
	POINT cs_p; //координата начала отсчёта
	m_par par;
	bool GetSignalF(double& Xx, double& fy);
	vector<double> GetFY(size_t k);
	vector<double> GetFX(size_t k);
	bool GetSpectreF(vector<double>& vec_fy, double& sy, double& t);
	bool ScaleSignal(double& ScaleX, double& ScaleY, double& Xx, double& fy);
	bool ScaleSpectre(double& ScaleX, double& ScaleY, vector<double>& vec_fy, double& Xx, double& sy, double& t);
	bool GetSignal(POINT& p, double ScaleX, double ScaleY, double& Xx, double& fy);
	bool GetSpectre(POINT& p, double ScaleX, double ScaleY, vector<double>& vec_fy, double& Xx, double& sy, double& t);
	bool Calc();
	bool CalcTimer();
	vector<POINT> GetPointsF();
	vector<POINT> GetPointsS();
	int GetNpt();
	bool Transfer(m_par &inpar);
	//Деструктор класса
	vector <POINT> m_vec_f, m_vec_s;
};