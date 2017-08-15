<!-- README.md is generated from README.Rmd. Please edit that file -->
ncapi
=====

The goal of ncapi is to provide a foundation interface to the NetCDF API that transcends the three overlapping and patchily supported independent packages `ncdf4`, `RNetCDF`, `rhdf5`, and `rgdal`.

The need for this is discussed here:

<http://rpubs.com/cyclemumner/293536>

The crux is cross-platform support for NetCDF class, NetCDF-4 and HDF5-compatibles, Thredds servers, and sources with groups and compound types.

The first useable version of this package would replace the use of `RNetCDF` in <https://github.com/hypertidy/ncmeta>. A key need is to have consistent cross-platform support for NetCDF-4 and -3, Thredds servers, compression options and MPI options.

Interested?
===========

Great!!

I have no idea what I'm doing so any assistance, ideas, testing, encouragement is welcome.

In particular I need help with:

-   basic C++, dealing with numbers and characters passed with the NetCDF API
-   higher level design and C++ implementations to reduce the maintenance footprint
-   specific workflows and sources to test
-   cross-platform support, ensuring this builds on unix, MacOS, with rwinlib, and with standard downloads from Unidata for DIY semi-hackers

ROpenSci show how to build RNetCDF via rwinlib, so NetCDF post 1.9.0 looks in good shape to hit CRAN and require being built against version 4. Ideally, we weould have CRAN prepared to do the same for rgdal, and even to include OpenDAP but it seems unlikely there's any communications channel for doing so. I have no idea if a successor to Win/Mac binary support is planned for CRAN, but it's a really obvious hole in the support for the general R community.

I thought I had figured out using `nc_get_vara_type` and `nc_get_var_type` but I hit problems via OpenDAP when getting over ~1000x1000 floating point values, that RNetCDF has no problem with. I might just be building the count array incorrectly.

Source of interest include:

-   classic NetCDF 3 files
-   NetCDF 4 files (the ones that can have *groups* and/or *compound-types*)
-   HDF5 files
-   Thredds, DODS, OpenDAP servers
-   files with pathologies, e.g. character string coordinate values, unused dimensions, broken entities
-   complex multi-dimensional models
-   NetCDF sources that use compound types for examples different to L3BIN NASA ocean colour or KEA
-   anything I haven't thought of that you know about ...

set up notes
============

-   General system requirements (WIP): <https://gist.github.com/mdsumner/3a19a0e4342b4067decfc049b4f4ecf5>
-   package specific details are set in 'DESCRIPTION', 'ncapi-package.r', 'src/init.c', 'src/Makevars'
-   Register routines, new in R 2017: <https://ironholds.org/registering-routines/>, <http://dirk.eddelbuettel.com/blog/2017/04/30/#006_easiest_package_registration>
-   Configure Rcpp - (must import something, and useDynLib in roxygen comments)

When additions/changes made we must update registration with

``` r
## Presumably this could be makefiled (TODO). 
tools::package_native_routine_registration_skeleton("../ncapi", "src/init.c",character_only = FALSE)
```

Examples
========

``` r
f_l3b <- system.file("extdata", "oceandata", "S2008001.L3b_DAY_CHL.nc", package = "ncapi")
f_l3m <- system.file("extdata", "oceandata", "S2008001.L3m_DAY_CHL_chlor_a_9km.nc", package = "ncapi")
f_hydro <- system.file("extdata", "unidata", "madis-hydro.nc", package = "ncapi")
f_hgroups <- system.file("extdata", "unidata", "test_hgroups.nc", package = "ncapi")
u1 <- "http://tds.hycom.org/thredds/dodsC/GLBa0.08/latest/2d"
u2 <- "https://oceandata.sci.gsfc.nasa.gov:443/opendap/MODISA/L3SMI/2016/001/A20160012016032.L3m_R32_SST_sst_9km.nc"

library(tibble)
library(ncapi)
get_fun <- function(x) {
  con <- Rnc_open(x)
  on.exit(Rnc_close, add = TRUE)
  l <- list(as_tibble(Rnc_inq_dimension(con)), 
       as_tibble(Rnc_inq_variable(con)))
  list(l, lapply(l[[2]]$id, function(a) Rnc_inq_vardims(con, a)))
}
get_fun(f_l3m)
#> [[1]]
#> [[1]][[1]]
#> # A tibble: 4 x 4
#>      id          name length unlim
#>   <int>         <chr>  <int> <lgl>
#> 1     0           lat   2160 FALSE
#> 2     1           lon   4320 FALSE
#> 3     2           rgb      3 FALSE
#> 4     3 eightbitcolor    256 FALSE
#> 
#> [[1]][[2]]
#> # A tibble: 4 x 5
#>      id    name  type ndims natts
#>   <int>   <chr> <chr> <chr> <chr>
#> 1     0 chlor_a     5     2    12
#> 2     1     lat     5     1     5
#> 3     2     lon     5     1     5
#> 4     3 palette     7     2     0
#> 
#> 
#> [[2]]
#> [[2]][[1]]
#> [1] 0 1
#> 
#> [[2]][[2]]
#> [1] 0
#> 
#> [[2]][[3]]
#> [1] 1
#> 
#> [[2]][[4]]
#> [1] 2 3
get_fun(f_l3b)
#> [[1]]
#> [[1]][[1]]
#> # A tibble: 0 x 4
#> # ... with 4 variables: id <int>, name <chr>, length <int>, unlim <lgl>
#> 
#> [[1]][[2]]
#> # A tibble: 0 x 5
#> # ... with 5 variables: id <int>, name <chr>, type <chr>, ndims <chr>,
#> #   natts <chr>
#> 
#> 
#> [[2]]
#> list()
##get_fun(f_hydro)  ## doesn't work
get_fun(f_hgroups)
#> [[1]]
#> [[1]][[1]]
#> # A tibble: 1 x 4
#>      id   name length unlim
#>   <int>  <chr>  <int> <lgl>
#> 1     0 recNum     74 FALSE
#> 
#> [[1]][[2]]
#> # A tibble: 1 x 5
#>      id     name  type ndims natts
#>   <int>    <chr> <chr> <chr> <chr>
#> 1     0 UTC_time    12     1     2
#> 
#> 
#> [[2]]
#> [[2]][[1]]
#> [1] 0
#get_fun(u1)  ## doesn't work
#get_fun(u2)  ## doesn't work
```

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

Get a large-ish summary of what is in the file (very WIP).

``` r
example(Rnc_inq)
#> 
#> Rnc_nq> f_l3b <- system.file("extdata", "oceandata", "S2008001.L3b_DAY_CHL.nc", package = "ncapi")
#> 
#> Rnc_nq>  con <- Rnc_open(f_l3b)
#> 
#> Rnc_nq>  groupids <- Rnc_inq_grps(con)
#> 
#> Rnc_nq>  l3b <- Rnc_inq(groupids[1])
#> 
#> Rnc_nq>  Rnc_close(con)
#> 
#> Rnc_nq>  print(basename(f_l3b))
#> [1] "S2008001.L3b_DAY_CHL.nc"
#> 
#> Rnc_nq>  print(l3b)
#> $dims
#> $dims$length
#> [1]    2    2 2160
#> 
#> $dims$name
#> [1] "binListDim"  "binDataDim"  "binIndexDim"
#> 
#> 
#> $vars
#> $vars$varnames
#> [1] "BinList"  "chlor_a"  "chl_ocx"  "BinIndex"
#> 
#> $vars$natts
#> [1] 0
#> 
#> $vars$dimIDs
#> [1] 2
#> 
#> 
#> $ngatts
#> [1] 0
#> 
#> $unlimdimid
#> [1] 0
#> 
#> 
#> Rnc_nq>  f_l3m <- system.file("extdata", "oceandata", "S2008001.L3m_DAY_CHL_chlor_a_9km.nc", package = "ncapi")
```

Simple get group names.

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
#>  1      1   262145                    level-3_binned_data
#>  2      1   262146                     processing_control
#>  3      2   262145                     processing_control
#>  4      3       NA                      <no groups found>
#>  5      4   262145  mozaic_flight_2012030403540535_ascent
#>  6      4   262146 mozaic_flight_2012030321335035_descent
#>  7      4   262147 mozaic_flight_2012030403540535_descent
#>  8      4   262148  mozaic_flight_2012030412545335_ascent
#>  9      4   262149  mozaic_flight_2012030419144751_ascent
#> 10      4   262150 mozaic_flight_2012030319051051_descent
#> 11      4   262151  mozaic_flight_2012030421382353_ascent
#> # ... with 2 more variables: source <chr>, access <dttm>
```

Thredds
=======

(These sources don't have groups so we need some more functionality to see anything happen).

``` r
u1 <- "http://tds.hycom.org/thredds/dodsC/GLBa0.08/latest/2d"
get_groups(u1, check_exists = FALSE)
#> returning 0 group names
#> # A tibble: 1 x 4
#>   group_id        group_name source              access
#>      <int>             <chr>  <chr>              <dttm>
#> 1       NA <no groups found>     2d 2017-08-15 21:42:14


u2 <- "https://oceandata.sci.gsfc.nasa.gov:443/opendap/MODISA/L3SMI/2016/001/A20160012016032.L3m_R32_SST_sst_9km.nc"
get_groups(u2, check_exists = FALSE)
#> returning 0 group names
#> # A tibble: 1 x 4
#>   group_id        group_name                                 source
#>      <int>             <chr>                                  <chr>
#> 1       NA <no groups found> A20160012016032.L3m_R32_SST_sst_9km.nc
#> # ... with 1 more variables: access <dttm>
```

Investigate them a little more deeply.

``` r
con <- Rnc_open(u1)
Rnc_inq_grps(con)
#> integer(0)

## notice how the connection is the group ID in the degenerate case
summ1 <- Rnc_inq(con)
Rnc_close(con)


con <- Rnc_open(u2)
summ2 <- Rnc_inq(con)
Rnc_close(con)
```

Content summary of hycom **GLBa0.08**.

``` r
print(summ1)
#> $dims
#> $dims$length
#> [1]   10 4500 3298
#> 
#> $dims$name
#> [1] "MT" "X"  "Y" 
#> 
#> 
#> $vars
#> $vars$varnames
#>  [1] "Y"                         "X"                        
#>  [3] "MT"                        "Date"                     
#>  [5] "Latitude"                  "Longitude"                
#>  [7] "qtot"                      "emp"                      
#>  [9] "surface_temperature_trend" "surface_salinity_trend"   
#> [11] "ssh"                      
#> 
#> $vars$natts
#> [1] 5
#> 
#> $vars$dimIDs
#> [1] 0 2 1
#> 
#> 
#> $ngatts
#> [1] 6
#> 
#> $unlimdimid
#> [1] -1
```

Content summary of **A20160012016032.L3m\_R32\_SST\_sst\_9km**.

``` r
print(summ2)
#> $dims
#> $dims$length
#> [1]  256 2160 4320    3
#> 
#> $dims$name
#> [1] "eightbitcolor" "lat"           "lon"           "rgb"          
#> 
#> 
#> $vars
#> $vars$varnames
#> [1] "lat"      "lon"      "palette"  "sst"      "qual_sst"
#> 
#> $vars$natts
#> [1] 4
#> 
#> $vars$dimIDs
#> [1] 1 2
#> 
#> 
#> $ngatts
#> [1] 65
#> 
#> $unlimdimid
#> [1] -1
```

Archaeology
===========

This project is a progression from past attempts to make sense of this space.

-   <https://github.com/mdsumner/anc>
-   <https://github.com/hypertidy/rancid>
-   <https://github.com/hypertidy/ncdump>
-   <http://lists.r-forge.r-project.org/pipermail/rcpp-devel/2016-December/009485.html>
-   <https://github.com/RConsortium/wishlist/issues/3>

Code of conduct
===============

Please note that this project is released with a [Contributor Code of Conduct](CONDUCT.md). By participating in this project you agree to abide by its terms.
