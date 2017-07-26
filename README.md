<!-- README.md is generated from README.Rmd. Please edit that file -->
ncapi
=====

The goal of ncapi is to provide a foundation interface to the NetCDF API that transcends the three overlapping and patchily supported independent packages `ncdf4`, `RNetCDF` and `rhdf5`.

The need for this is discussed here:

<http://rpubs.com/cyclemumner/293536>

The first useable version of this package would replace the use of `RNetCDF` in <https://github.com/hypertidy/ncmeta>. A key need is to have consistent cross-platform support for NetCDF-4 and -3, Thredds servers, compression options and MPI options.

Later versions might be used by `RNetCDF` or `ncdf4`,

Interested? Great!!
===================

I have no idea what I'm doing so any assistance, ideas, testing, encouragement is welcome.

In particular I need help with:

-   basic C++, dealing with numbers and characters passed with the NetCDF API
-   higher level design and C++ implementations to reduce the maintenance footprint
-   interested uses able to test different sources

Relevant sources and sources of interest include:

-   classic NetCDF 3 files
-   NetCDF 4 files (the ones that can have *groups* and/or *compound-types*)
-   HDF5 files
-   Thredds, DODS, OpenDAP servers
-   files with pathologies, e.g. character string coordinate values, unused dimensions, broken entities
-   complex multi-dimensional models
-   NetCDF sources that use compound types for examples different to L3BIN NASA ocean colour or KEA

set up notes
============

-   General system requirements:

<https://github.com/mdsumner/nectar/blob/master/r-spatial.sh>

-   package specific details See DESCRIPTION, ncapi-package.r, src/init.c, src/Makevars

-   Register routines, new in R 2017: <https://ironholds.org/registering-routines/>

<http://dirk.eddelbuettel.com/blog/2017/04/30/#006_easiest_package_registration>

-   update registration with `tools::package_native_routine_registration_skeleton("../ncapi", "src/init.c",character_only = FALSE)`

-   Configure Rcpp 1) must import something <'@importFrom> Rcpp evalCpp' 2) useDynLib in roxygen

raw examples
============

``` r
library(ncapi)
f_l3b <- system.file("extdata", "oceandata", "S2008001.L3b_DAY_CHL.nc", package = "ncapi")
con <- Rnc_open(f_l3b)
groupids <- Rnc_inq_grps(con)
Rnc_inq_grpname(groupids[1])
#> [1] "level-3_binned_data"
lapply(Rnc_inq_grps(con), Rnc_inq_grpname)
#> [[1]]
#> [1] "level-3_binned_data"
#> 
#> [[2]]
#> [1] "processing_control"
Rnc_close(con)
```

``` r
get_groups <- function(x, check_exists = TRUE) {
  if (check_exists) stopifnot(file.exists(x))
  con <- Rnc_open(x)
  on.exit(Rnc_close(con), add = TRUE)
  groupids <- Rnc_inq_grps(con)
  cat(sprintf("returning %i group names\n", length(groupids)))
  names <- unlist(lapply(groupids, Rnc_inq_grpname))
  
  if (length(names) < 1) {
    names <- "<no groups found>"
    groupids <- NA_integer_
  }
   tibble::tibble(group_id = groupids, group_name = names, source = basename(x), access = Sys.time())
}
files <- list.files(system.file("extdata", package = "ncapi"), recursive = TRUE, pattern = "nc$", full.names = TRUE)
d <- dplyr::bind_rows(lapply(files, get_groups), .id = "source")
#> returning 2 group names
#> returning 1 group names
#> returning 0 group names
#> returning 7 group names
print(d)
#> # A tibble: 11 x 5
#>    source group_id                             group_name
#>     <chr>    <int>                                  <chr>
#>  1      1    65537                    level-3_binned_data
#>  2      1    65538                     processing_control
#>  3      2    65537                     processing_control
#>  4      3       NA                      <no groups found>
#>  5      4    65537  mozaic_flight_2012030403540535_ascent
#>  6      4    65538 mozaic_flight_2012030321335035_descent
#>  7      4    65539 mozaic_flight_2012030403540535_descent
#>  8      4    65540  mozaic_flight_2012030412545335_ascent
#>  9      4    65541  mozaic_flight_2012030419144751_ascent
#> 10      4    65542 mozaic_flight_2012030319051051_descent
#> 11      4    65543  mozaic_flight_2012030421382353_ascent
#> # ... with 2 more variables: source <chr>, access <dttm>
```

Thredds
=======

``` r
u <- "http://tds.hycom.org/thredds/dodsC/GLBa0.08/latest/2d"
get_groups(u, check_exists = FALSE)
#> returning 0 group names
#> # A tibble: 1 x 4
#>   group_id        group_name source              access
#>      <int>             <chr>  <chr>              <dttm>
#> 1       NA <no groups found>     2d 2017-07-26 16:24:03
```
