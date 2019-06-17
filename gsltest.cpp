#include "gsltest.h"

#include <iostream>
#include <cmath>
#include <gsl/gsl_math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>

using namespace std;

int dfunc (double t, const double y[], double f[], void *params_ptr) {
    double *lparams = (double *) params_ptr;
    /* get parameter(s) from params_ptr */
    double alpha = lparams[0];
    double omega = lparams[1];
    /* evaluate the right-hand-side functions at t */
    f[0] = alpha * y[0] * (1+ sin (omega*t));
    return GSL_SUCCESS; /* GSL_SUCCESS defined in gsl/errno.h as 0 */
}



GSLTest::GSLTest()
{

}

void GSLTest::odeSolution()
{
    const int dimension = 1;   /* number of differential equations */
    int status;                /* status of driver function */
    const double eps_abs = 1.e-8;  /* absolute error requested  */
    const double eps_rel = 1.e-10; /* relative error requested  */
    double alpha = 0.015;	         /* parameter for the diff eq */
    double omega = 2.0*M_PI/365.0; /* parameter for the diff eq */
    double myparams[2];            /* array for parameters      */
    double y[dimension];	        /* current solution vector */
    double t, t_next;             /* current and next independent variable */
    double tmin, tmax, delta_t;   /* range of t and step size for output */
    double h = 1.0e-6;            /* starting step size for ode solver */
    gsl_odeiv2_system ode_system;	/* structure with the dfunc function, etc. */
    myparams[0] = alpha;          /* problem parameters */
    myparams[1] = omega;
    cout << "\nThis program solves a system with a single diff  equation\n\n";
    /* load values into the ode_system structure */
    ode_system.function = dfunc;       /* the right-hand-side of equation */
    ode_system.dimension = dimension;  /* number of diffeq's */
    ode_system.params = myparams;      /* parameters to pass to dfunc */
    tmin = 0.0;			/* starting t value */
    tmax = 365.0;			/* final t value */
    delta_t = 1.0;
    y[0] = 2.0;			/* initial value of x */
    gsl_odeiv2_driver * drv =
            gsl_odeiv2_driver_alloc_y_new (&ode_system, gsl_odeiv2_step_rkf45, h, eps_abs, eps_rel);
    cout << "Input data: \n";
    cout << " alpha = " <<  alpha << " omega = " << omega << "\n";
    cout << " Starting step size (h): " << h << endl;
    cout << " Time parameters: " <<  tmin << " " << tmax << " " << delta_t << endl;
    cout << " Absolute and relative error requested: " << eps_abs << " " <<  eps_rel << endl;
    cout << " Number of equations (dimension) " << dimension << endl;
    cout << "    Time         x          \n";
    t = tmin;             /* initialize t */
    cout <<  t << " " << y[0] << endl;	/* initial values */
    /* step from tmin to tmax */
    for (t_next = tmin + delta_t; t_next <= tmax; t_next += delta_t)
    {
        status = gsl_odeiv2_driver_apply (drv, &t, t_next, y);
        if (status != GSL_SUCCESS) {
            cout << "Error: status " <<  status << endl;
            break;
        }
        cout << t << " " << y[0] << endl; /* print at t=t_next */
    } // end for
    gsl_odeiv2_driver_free (drv);
}
