#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* FIXME: 
   Check these declarations against the C/Fortran source code.
*/

/* .Call calls */
extern SEXP _ncapi_Rnc_close(SEXP);
extern SEXP _ncapi_Rnc_inq(SEXP);
extern SEXP _ncapi_Rnc_inq_dimension(SEXP);
extern SEXP _ncapi_Rnc_inq_dims(SEXP);
extern SEXP _ncapi_Rnc_inq_grpname(SEXP);
extern SEXP _ncapi_Rnc_inq_grps(SEXP);
extern SEXP _ncapi_Rnc_inq_vardims(SEXP, SEXP);
extern SEXP _ncapi_Rnc_inq_variable(SEXP);
extern SEXP _ncapi_Rnc_open(SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"_ncapi_Rnc_close",         (DL_FUNC) &_ncapi_Rnc_close,         1},
    {"_ncapi_Rnc_inq",           (DL_FUNC) &_ncapi_Rnc_inq,           1},
    {"_ncapi_Rnc_inq_dimension", (DL_FUNC) &_ncapi_Rnc_inq_dimension, 1},
    {"_ncapi_Rnc_inq_dims",      (DL_FUNC) &_ncapi_Rnc_inq_dims,      1},
    {"_ncapi_Rnc_inq_grpname",   (DL_FUNC) &_ncapi_Rnc_inq_grpname,   1},
    {"_ncapi_Rnc_inq_grps",      (DL_FUNC) &_ncapi_Rnc_inq_grps,      1},
    {"_ncapi_Rnc_inq_vardims",   (DL_FUNC) &_ncapi_Rnc_inq_vardims,   2},
    {"_ncapi_Rnc_inq_variable",  (DL_FUNC) &_ncapi_Rnc_inq_variable,  1},
    {"_ncapi_Rnc_open",          (DL_FUNC) &_ncapi_Rnc_open,          1},
    {NULL, NULL, 0}
};

void R_init_ncapi(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
