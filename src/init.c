#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* FIXME:
 Check these declarations against the C/Fortran source code.
 */

/* .Call calls */
extern SEXP _ncapi_Rnc_open(SEXP);
extern SEXP _ncapi_Rnc_close(SEXP);

static const R_CallMethodDef CallEntries[] = {
  {"_ncapi_Rnc_open", (DL_FUNC) &_ncapi_Rnc_open, 1},
  {"_ncapi_Rnc_close", (DL_FUNC) &_ncapi_Rnc_close, 1},
  {NULL, NULL, 0}
};

void R_init_ncapi(DllInfo *dll)
{
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
