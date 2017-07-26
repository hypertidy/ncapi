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


//' Source inquiry
//'
//' once we have a given ID (group-less file, or specific group)
//' find its contents
//' @inheritParams Rnc_inq_grpname
//' @export
//' @examples
//' f_l3b <- system.file("extdata", "oceandata", "S2008001.L3b_DAY_CHL.nc", package = "ncapi")
//'  con <- Rnc_open(f_l3b)
//'  groupids <- Rnc_inq_grps(con)
//'  l3b <- Rnc_inq(groupids[1])
//'  Rnc_close(con)
//'  print(basename(f_l3b))
//'  print(l3b)
// [[Rcpp::export]]
List Rnc_inq(int grpid) {
  int status;
  int ndims, nvars, ngatts, unlimdimid;
  status = nc_inq(grpid, &ndims, &nvars, &ngatts, &unlimdimid);

  if (ndims < 1) return List::create();
  size_t ilen;
  char recname[NC_MAX_NAME+1];

  // int nc_inq_dim     (int ncid, int dimid, char* name, size_t* lengthp);
  IntegerVector dimlens(ndims);
  CharacterVector dnames(ndims);
  //printf("%i\n", ndims);
  for (int idim = 0; idim < ndims; idim++) {
    status = nc_inq_dim(grpid, idim, recname, &ilen);
    dimlens[idim] = ilen;
    dnames[idim] = recname;
  }


  //   int nc_inq_var(int ncid, int varid, char *name, nc_type *xtypep, int *ndimsp, int dimids[], int *nattsp);
  // var dims somehow IntegerVector lens(nvars);
  CharacterVector vnames(nvars);

  //?? vtypes? CharacterVector vtypes(nvars);
  int  var_dimids[NC_MAX_VAR_DIMS];

  int var_natts;
  int var_ndim;
  nc_type var_type;
  for (int ivar = 0; ivar < nvars; ivar++) {
    status = nc_inq_var(grpid, ivar, recname, &var_type, &var_ndim, var_dimids, &var_natts);
    vnames[ivar] = recname;

    // printf("%s %i\n", recname, var_type);
  }



  IntegerVector R_dimids(var_ndim);
  for (int ii = 0; ii < var_ndim; ii++) R_dimids[ii] = var_dimids[ii];
  List out = List::create();
  out["dims"] = List::create(Named("length") = dimlens, Named("name") = dnames);
  out["vars"] = List::create(Named("varnames") = vnames,
                         Named("natts") = var_natts,
                         Named("dimIDs") = R_dimids);
  out["ngatts"] = ngatts;
  out["unlimdimid"] = unlimdimid;
  return out;

}
