// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// Rnc_open
int Rnc_open(CharacterVector dsn);
RcppExport SEXP _ncapi_Rnc_open(SEXP dsnSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< CharacterVector >::type dsn(dsnSEXP);
    rcpp_result_gen = Rcpp::wrap(Rnc_open(dsn));
    return rcpp_result_gen;
END_RCPP
}
// Rnc_close
void Rnc_close(int ncid);
RcppExport SEXP _ncapi_Rnc_close(SEXP ncidSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type ncid(ncidSEXP);
    Rnc_close(ncid);
    return R_NilValue;
END_RCPP
}
// Rnc_inq_grps
IntegerVector Rnc_inq_grps(int ncid);
RcppExport SEXP _ncapi_Rnc_inq_grps(SEXP ncidSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type ncid(ncidSEXP);
    rcpp_result_gen = Rcpp::wrap(Rnc_inq_grps(ncid));
    return rcpp_result_gen;
END_RCPP
}
// Rnc_inq_grpname
CharacterVector Rnc_inq_grpname(int grpid);
RcppExport SEXP _ncapi_Rnc_inq_grpname(SEXP grpidSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type grpid(grpidSEXP);
    rcpp_result_gen = Rcpp::wrap(Rnc_inq_grpname(grpid));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_ncapi_Rnc_open", (DL_FUNC) &_ncapi_Rnc_open, 1},
    {"_ncapi_Rnc_close", (DL_FUNC) &_ncapi_Rnc_close, 1},
    {"_ncapi_Rnc_inq_grps", (DL_FUNC) &_ncapi_Rnc_inq_grps, 1},
    {"_ncapi_Rnc_inq_grpname", (DL_FUNC) &_ncapi_Rnc_inq_grpname, 1},
    {NULL, NULL, 0}
};

RcppExport void R_init_ncapi(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
