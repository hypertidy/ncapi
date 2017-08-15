# NC_BYTE 8-bit signed integer
# NC_UBYTE 8-bit unsigned integer
# NC_CHAR 8-bit character byte
# NC_SHORT 16-bit signed integer
# NC_USHORT 16-bit unsigned integer *
# NC_INT (or NC_LONG) 32-bit signed integer
# NC_UINT 32-bit unsigned integer *
# NC_INT64 64-bit signed integer *
# NC_UINT64 64-bit unsigned integer *
# NC_FLOAT 32-bit floating point
# NC_DOUBLE 64-bit floating point
# NC_STRING variable length character string *

#' NetCDF types
#'
#' Return the descriptive name of the NetCDF data type from its ID number.
#' The ID is 0-based.
#' http://www.unidata.ucar.edu/software/netcdf/docs/data_type.html
#' @param x id integer, or character coercible to integer
#'
#' @return type names
#' @export
#'
#' @examples
nc_types <- function(x) {
 nc_data_types[["name"]][as.integer(x) + 1]
}
