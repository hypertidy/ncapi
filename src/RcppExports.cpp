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
// Rnc_inq_natts
IntegerVector Rnc_inq_natts(int grpid, int varid);
RcppExport SEXP _ncapi_Rnc_inq_natts(SEXP grpidSEXP, SEXP varidSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type grpid(grpidSEXP);
    Rcpp::traits::input_parameter< int >::type varid(varidSEXP);
    rcpp_result_gen = Rcpp::wrap(Rnc_inq_natts(grpid, varid));
    return rcpp_result_gen;
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
// Rnc_inq_dimension
List Rnc_inq_dimension(int grpid);
RcppExport SEXP _ncapi_Rnc_inq_dimension(SEXP grpidSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type grpid(grpidSEXP);
    rcpp_result_gen = Rcpp::wrap(Rnc_inq_dimension(grpid));
    return rcpp_result_gen;
END_RCPP
}
// Rnc_inq_variable
List Rnc_inq_variable(int grpid);
RcppExport SEXP _ncapi_Rnc_inq_variable(SEXP grpidSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type grpid(grpidSEXP);
    rcpp_result_gen = Rcpp::wrap(Rnc_inq_variable(grpid));
    return rcpp_result_gen;
END_RCPP
}
// Rnc_inq_vardims
IntegerVector Rnc_inq_vardims(int grpid, int ivar);
RcppExport SEXP _ncapi_Rnc_inq_vardims(SEXP grpidSEXP, SEXP ivarSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type grpid(grpidSEXP);
    Rcpp::traits::input_parameter< int >::type ivar(ivarSEXP);
    rcpp_result_gen = Rcpp::wrap(Rnc_inq_vardims(grpid, ivar));
    return rcpp_result_gen;
END_RCPP
}
// Rnc_inq
List Rnc_inq(int grpid);
RcppExport SEXP _ncapi_Rnc_inq(SEXP grpidSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type grpid(grpidSEXP);
    rcpp_result_gen = Rcpp::wrap(Rnc_inq(grpid));
    return rcpp_result_gen;
END_RCPP
}
// Rnc_inq_dims
int Rnc_inq_dims(int grpid);
RcppExport SEXP _ncapi_Rnc_inq_dims(SEXP grpidSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type grpid(grpidSEXP);
    rcpp_result_gen = Rcpp::wrap(Rnc_inq_dims(grpid));
    return rcpp_result_gen;
END_RCPP
}
