#include "pch.h"
#include "MFCApplication1Dlg.h"

Graphics::Graphics()
{
	cs_p.x = 4.;
	cs_p.y = 200.;
}					//описание конструктора, присвоение начальных значений

Graphics::~Graphics()
{
}

bool Graphics::GetSignalF(double& Xx, double& fy)
{
	fy = a * (1. + par.m * sin(2. * M_PI * par.Fm * Xx)) * sin(2. * M_PI * par.f * Xx);
	Xx *= Fd;
	return true;
}

vector<double> Graphics::GetFY(size_t k)
{
	vector<double> vec_fy;
	for (size_t i = 0; i <= k; i++)
	{
		double
			Xx = i * par.dx,
			fy = 0.;
		GetSignalF(Xx, fy);
		vec_fy.push_back(fy);
	}
	return vec_fy;
}

vector<double> Graphics::GetFX(size_t k)
{
	vector<double> vec_Xx;
	for (size_t i = 0; i <= k; i++)
	{
		double
			Xx = i * par.dx,
			fy = 0.;
		GetSignalF(Xx, fy);
		vec_Xx.push_back(Xx);
	}
	return vec_Xx;
}

bool Graphics::GetSpectreF(vector<double>& vec_fy, double& sy, double& t)
{
	double Re = 0., sRe = 0., Im = 0., sIm = 0.;
	for (int T = 0; T < vec_fy.size(); T++)
	{
		double fy = vec_fy[T];
		Re = fy * cos((2 * M_PI * t * T) / vec_fy.size());
		sRe += Re;
		Im = fy * sin((2 * M_PI * t * T) / vec_fy.size());
		sIm += Im;
	}
	sy = sqrt(pow(sRe, 2.) + pow(sIm, 2.));
	if (par.log)
	{
		sy = log10(sy);
	}
	else
	{
		sy *= 0.05;
	}
	return true;
}

bool Graphics::ScaleSignal(double& ScaleX, double& ScaleY, double& Xx, double& fy)
{
	if (GetSignalF(Xx, fy))
	{
		Xx *= ScaleX * GR_END / par.N;
		fy *= ScaleY;
		return true;
	}
	else
	{
		return 0;
	}
}

bool Graphics::ScaleSpectre(double& ScaleX, double& ScaleY, vector<double>& vec_fy, double& Xx, double& sy, double& t)
{
	if (GetSpectreF(vec_fy, sy, t))
	{
		Xx *= ScaleX *GR_END / par.N;
		sy *= ScaleY;
		return true;
	}
	else
	{
		return 0;
	}
}

bool Graphics::GetSignal(POINT& p, double ScaleX, double ScaleY, double& Xx, double& fy)
{
	if (ScaleSignal(ScaleX, ScaleY, Xx, fy))
	{
		p.x = cs_p.x + LONG(floor(Xx));
		p.y = LONG(cs_p.y * 0.5) - LONG(floor(fy));
	}
	else
	{
		return 0;
	}
}

bool Graphics::GetSpectre(POINT& p, double ScaleX, double ScaleY, vector<double>& vec_fy, double& Xx, double& sy, double& t)
{
	if (ScaleSpectre(ScaleX, ScaleY,vec_fy, Xx, sy, t))
	{
		p.x = cs_p.x + LONG(floor(Xx));
		if (par.log)
		{
			p.y = LONG(cs_p.y * 0.5) - LONG(floor(sy));
		}
		else
		{
			p.y = cs_p.y - LONG(floor(sy));
		}
		return true;
	}
	else
	{
		return 0;
	}
}

bool Graphics::Calc()
{
	m_vec_f.clear();
	m_vec_s.clear();
	bool b_n = par.n > 0.;
	if (b_n)
	{
		for (double t = 0; t <= par.n; t++)
		{
			double
				Xx = t * par.dx,
				fy = 0.;
			POINT p;
			if (GetSignal(p, par.scaleX, par.scaleY, Xx, fy))
			{
				m_vec_f.push_back(p);
			}
			else
			{
				return 0;
			}
		}
		vector<double> vec_fy=GetFY(par.n), vec_fx=GetFX(par.n);
		for (double t = 0; t <= par.n; t++)
		{
			double
				Xx = vec_fx[t],
				sy = 0.;
			POINT p;
			if (GetSpectre(p,1., 40., vec_fy, Xx, sy, t))
				m_vec_s.push_back(p);
			else
			{
				return 0;
			}
		}
		vec_fx.clear();
		vec_fy.clear();
		return (m_vec_s.size() > 0);
	}
	else
	{
		return 0;
	}
}

bool Graphics::CalcTimer()
{
	bool b_n = par.n > 0.;
	if (b_n)
	{
		vector<double> vec_fy=GetFY(par.n), vec_fx = GetFX(GetNpt());
		double
			Fx = par.t * par.dx,
			Sx = vec_fx[par.t],
			fy = 0.,
			sy = 0.;
		POINT p;
		if (GetSignal(p, par.scaleX, par.scaleY, Fx, fy))
		{
			m_vec_f.push_back(p);
			if (GetSpectre(p, 1., 40., vec_fy, Sx, sy, par.t))
				m_vec_s.push_back(p);
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
		vec_fx.clear();
		vec_fy.clear();
		return (m_vec_s.size() > 0);
	}
	else
	{
		return 0;
	}
}

vector<POINT> Graphics::GetPointsF()
{
	return m_vec_f;
}

vector<POINT> Graphics::GetPointsS()
{
	return m_vec_s;
}

int Graphics::GetNpt()
{
	return m_vec_f.size();
}

bool Graphics::Transfer(m_par &inpar)
{
	par = inpar;
	par.n = (GR_END * (par.N / 1000.));
	par.dx = 1. / Fd;
	if (par.t == -1)
	{
		par.t = 0;
		m_vec_f.clear();
		m_vec_s.clear();
	}
	else if (par.t == -2)
		Calc();
	else CalcTimer();
	return true;
}