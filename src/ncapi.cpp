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

// https://www.unidata.ucar.edu/software/netcdf/netcdf-4/newdocs/netcdf-c/nc_005finq-Family.html
// int nc_inq_ndims    (int ncid, int *ndimsp);
// int nc_inq_nvars    (int ncid, int *nvarsp);
// int nc_inq_natts    (int ncid, int *ngattsp);
// int nc_inq_unlimdim (int ncid, int *unlimdimidp);
// int nc_inq_format   (int ncid, int *formatp);


//' Dimension inquiry
//'
//' @inheritParams Rnc_inq_grpname
//' @export
//' @examples
//' f_l3b <- system.file("extdata", "oceandata", "S2008001.L3b_DAY_CHL.nc", package = "ncapi")
//' con <- Rnc_open(f_l3b)
//' groupids <- Rnc_inq_grps(con)
//' Rnc_inq_dimension(groupids[1])
//' Rnc_close(con)
//' f_l3m <- system.file("extdata", "oceandata", "S2008001.L3m_DAY_CHL_chlor_a_9km.nc", package = "ncapi")
//' con <- Rnc_open(f_l3m)
//' ## watch out because if only one, the file con is the one
//' ##groupids <- Rnc_inq_grps(con)
//' tibble::as_tibble(Rnc_inq_dimension(con))
//' Rnc_close(con)
//' ## that should be the same as
//' #ncmeta::nc_dims(f_l3m)
// [[Rcpp::export]]
List Rnc_inq_dimension(int grpid) {
  int status;
  int ndims, nvars, ngatts, unlimdimid;
  //status = nc_inq_ndims(grpid, &ndims);
  status = nc_inq(grpid, &ndims, &nvars, &ngatts, &unlimdimid);

  // int nc_inq_dim     (int ncid, int dimid, char* name, size_t* lengthp);
  IntegerVector dimlens(ndims);
  IntegerVector dimids(ndims);
  LogicalVector unlim(ndims);
  CharacterVector dimnames(ndims);
  char recname[NC_MAX_NAME+1];
  size_t ilen;
  for (int idim = 0; idim < ndims; idim++) {
    status = nc_inq_dim(grpid, idim, recname, &ilen);
    dimlens[idim] = ilen;
    dimnames[idim] = recname;
    dimids[idim] = idim;
    if (idim == unlimdimid) unlim[idim] = TRUE;
  }
  List out = List::create(Named("id") = dimids,
                          Named("name") = dimnames,
                          Named("length") = dimlens,
                          Named("unlim") = unlim);
  return(out);
}

//' Variable inquiry
//'
//' @inheritParams Rnc_inq_grpname
//' @export
//' @examples
//' f_l3m <- system.file("extdata", "oceandata", "S2008001.L3m_DAY_CHL_chlor_a_9km.nc", package = "ncapi")
//' con <- Rnc_open(f_l3m)
//' tibble::as_tibble(Rnc_inq_variable(con))
//' Rnc_close(con)
//' ## that should be the same as
//' # ncmeta::nc_vars(f_l3m)
//' # # A tibble: 4 x 5
//' #   id    name  type ndims natts
//' #   <int>   <chr> <chr> <int> <int>
//' #   0     chlor_a float     2    12
//' #   1     lat float     1     5
//' #   2     lon float     1     5
//' #   3     palette ubyte     2     0
// [[Rcpp::export]]
List Rnc_inq_variable(int grpid) {
  int status;
  int ndims, nvars, ngatts, unlimdimid;
  status = nc_inq(grpid, &ndims, &nvars, &ngatts, &unlimdimid);
  CharacterVector vnames(nvars);
  int  var_dimids[NC_MAX_VAR_DIMS];
  char recname[NC_MAX_NAME+1];
  int var_natts;
  int var_ndim;
  nc_type var_type;
  IntegerVector varids(ndims);
  CharacterVector varnames(nvars);
  CharacterVector vartypes(nvars);
  CharacterVector varndims(nvars);
  CharacterVector varnatts(nvars);
  // TODO: consider if this belongs in here or outside
  //List vardimids(nvars);
//  Rcpp::List tmp(n + 2);
//  tmp[0] = Rcpp::IntegerVector(3);
//  tmp[1] = Rcpp::IntegerVector(3);


  // https://www.unidata.ucar.edu/software/netcdf/netcdf-4/newdocs/netcdf-c/nc_005finq_005fvar.html
  // TODO: we need to map the nc_type, ncmeta used names "float" etc.

  for (int ivar = 0; ivar < nvars; ivar++) {
    status = nc_inq_var(grpid, ivar, recname, &var_type, &var_ndim, var_dimids, &var_natts);
    varids[ivar] = ivar;
    varnames[ivar] = recname;
    vartypes[ivar] = char(var_type);
    varndims[ivar] = var_ndim;
    varnatts[ivar] = var_natts;
    // TODO: consider if this belongs in here or outside
    //IntegerVector ivar_dims(var_ndim);
  }
  List out = List::create(Named("id") = varids,
                          Named("name") = varnames,
                          Named("type") = vartypes,
                          Named("ndims") = varndims,
                          Named("natts") = varnatts);
  return(out);
}


//' Dimensions of variables
//'
//' @inheritParams Rnc_inq_grpname
//' @param ivar index of variable
//' @export
//' @examples
//' f_l3m <- system.file("extdata", "oceandata", "S2008001.L3m_DAY_CHL_chlor_a_9km.nc", package = "ncapi")
//' con <- Rnc_open(f_l3m)
//' variables <- tibble::as_tibble(Rnc_inq_variable(con))
//'  setNames(lapply(variables$id, function(x) Rnc_inq_vardims(con, x)), variables$name)
//' Rnc_close(con)
// [[Rcpp::export]]
IntegerVector Rnc_inq_vardims(int grpid, int ivar) {
  int status;
  int  var_dimids[NC_MAX_VAR_DIMS];
  char recname[NC_MAX_NAME+1];
  nc_type var_type;
  int var_ndim;
  int var_natts;
  // https://www.unidata.ucar.edu/software/netcdf/netcdf-4/newdocs/netcdf-c/nc_005finq_005fvar.html
 status = nc_inq_var(grpid, ivar, recname, &var_type, &var_ndim, var_dimids, &var_natts);
 IntegerVector vardims(var_ndim);
 for (int idim = 0; idim < var_ndim; idim++) {
   vardims[idim] = var_dimids[idim];
 }
 return(vardims);
}


// TODO cleanup
/// Stuff down here is probably not used ----------------------------------------------



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
//'  f_l3m <- system.file("extdata", "oceandata", "S2008001.L3m_DAY_CHL_chlor_a_9km.nc", package = "ncapi")
// [[Rcpp::export]]
List Rnc_inq(int grpid) {
  int status;
  int ndims, nvars, ngatts, unlimdimid;
  // Q: how do we know a dimension is unlimited from here?
  // A: it's the dimension id, or -1
  status = nc_inq(grpid, &ndims, &nvars, &ngatts, &unlimdimid);

  //TODO: no dimensions is possibly an ok state
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

//' Dimension inquiry
//'
//' @inheritParams Rnc_inq_grpname
//' @export
//' @examples
//' f_l3b <- system.file("extdata", "oceandata", "S2008001.L3b_DAY_CHL.nc", package = "ncapi")
//' con <- Rnc_open(f_l3b)
//' groupids <- Rnc_inq_grps(con)
//' Rnc_inq_dims(groupids[1])
//' Rnc_close(con)
//' f_l3m <- system.file("extdata", "oceandata", "S2008001.L3m_DAY_CHL_chlor_a_9km.nc", package = "ncapi")
//' # ncmeta::nc_dims(f_l3m)
//' # A tibble: 4 x 4
//'       id          name length unlim
//'  <int>         <chr>  <dbl> <lgl>
//'  1     0           lat   2160 FALSE
//'  2     1           lon   4320 FALSE
//'  3     2           rgb      3 FALSE
//'  4     3 eightbitcolor    256 FALSE
// [[Rcpp::export]]
int Rnc_inq_dims(int grpid) {
  int status;
  int ndims;
  status = nc_inq_ndims(grpid, &ndims);

  return(ndims);
}
