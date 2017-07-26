#include <Rcpp.h>
#include <netcdf.h>

using namespace Rcpp;

//' Open a connection.
//'
//' Pass  a character data source name to the internal nc_open library function.
//' @param dsn data source name, i.e. file path or server path
//' @export
//' @examples
//' f_l3b <- system.file("extdata", "oceandata", "S2008001.L3b_DAY_CHL.nc", package = "ncapi")
//'  Rnc_open(f_l3b)
//' f_l3m <- system.file("extdata", "oceandata", "S2008001.L3m_DAY_CHL_chlor_a_9km.nc", package = "ncapi")
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

//' Close a connection.
//'
//' @param ncid file connection provided by `Rnc_open`
//' @export
//' @examples
//' f_l3b <- system.file("extdata", "oceandata", "S2008001.L3b_DAY_CHL.nc", package = "ncapi")
//'  con <- Rnc_open(f_l3b)
//'  Rnc_close(con)
// [[Rcpp::export]]
void Rnc_close(int ncid) {
  int status = nc_close(ncid);
}

//' Inquire group IDs
//'
//' @inheritParams Rnc_close
//' @export
//' @examples
//' f_l3b <- system.file("extdata", "oceandata", "S2008001.L3b_DAY_CHL.nc", package = "ncapi")
//'  con <- Rnc_open(f_l3b)
//'  Rnc_inq_grps(con)
//'  Rnc_close(con)
// [[Rcpp::export]]
IntegerVector Rnc_inq_grps(int ncid) {
  int numgrps;
  int status;
  //int *ncids;

  status = nc_inq_grps(ncid, &numgrps, NULL);
  int *ncids = new int[numgrps];
  status = nc_inq_grps(ncid, NULL, ncids);
  IntegerVector grpids(numgrps);
  for (int i = 0; i < numgrps; i++) grpids[i] = ncids[i];
  return grpids;
}


//' Inquire group name by ID
//'
//' @param grpid group ID provided by `Rnc_inq_grps`
//' @export
//' @examples
//' f_l3b <- system.file("extdata", "oceandata", "S2008001.L3b_DAY_CHL.nc", package = "ncapi")
//'  con <- Rnc_open(f_l3b)
//'  groupids <- Rnc_inq_grps(con)
//'  Rnc_inq_grpname(groupids[1])
//'  lapply(Rnc_inq_grps(con), Rnc_inq_grpname)
//'  Rnc_close(con)
// [[Rcpp::export]]
CharacterVector Rnc_inq_grpname(int grpid) {
//char name_in[1];
  char name_in[NC_MAX_NAME + 1];
  int status;
  status = nc_inq_grpname(grpid, name_in);
  CharacterVector cnames = name_in;
  return cnames;
}
