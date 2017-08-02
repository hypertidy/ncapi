#' ncapi.
#' @useDynLib ncapi, .registration = TRUE
#' @importFrom Rcpp evalCpp
#' @name ncapi
#' @docType package
NULL

#' NetCDF types
#'
#' A data frame of the names of the NetCDF data types. Column `name` is the
#' descriptive name, and `id` is the 0-based index, corresponding to the value returned by
#' nc_inq_var.
#'
#' See code in data-raw/ for the creation.
#'
#' http://www.unidata.ucar.edu/software/netcdf/docs/data_type.html
#' @name nc_data_types
#' @docType data
NULL
