#include <Rcpp.h>
#include <netcdf.h>

using namespace Rcpp;

void ERR(int status) {
  if (status < NC_NOERR) {
    fprintf(stderr, "%s\n", nc_strerror(status));
    exit(-1);
  }
}

//' Open a connection.
//'
//' Pass  a character data source name to the internal nc_open library function.
//' @param dsn data source name, i.e. file path or server path
//' @export
//' @examples
//' f_l3b <- system.file("inst", "oceandata", "S2008001.L3b_DAY_CHL.nc", package = "ncapi")
//'  Rnc_open(f_l3b)
//' f_l3m <- system.file("inst", "oceandata", "S2008001.L3m_DAY_CHL_chlor_a_9km.nc", package = "ncapi")
//'  Rnc_open(f_l3m)
//' u_cst <- "http://coastwatch.pfeg.noaa.gov/erddap/griddap/erdQSwind3da"
//'  Rnc_open(u_cst)
// [[Rcpp::export]]
int Rnc_open(CharacterVector dsn) {
  int ncid;
  int status;
  std::string fname0 = Rcpp::as<std::string>(dsn);
  status = nc_open(fname0.c_str(), NC_NOWRITE, &ncid);
  return ncid;
}
