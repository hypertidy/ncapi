<!-- README.md is generated from README.Rmd. Please edit that file -->
set up notes
============

-   General system requirements:

<https://github.com/mdsumner/nectar/blob/master/r-spatial.sh>

-   package specific details See DESCRIPTION, ncapi-package.r, src/init.c, src/Makevars

-   Register routines, new in R 2017: <https://ironholds.org/registering-routines/>

<http://dirk.eddelbuettel.com/blog/2017/04/30/#006_easiest_package_registration>

-   update registration with `tools::package_native_routine_registration_skeleton(".", "src/init.c",,character_only = FALSE)`

-   Configure Rcpp 1) must import something <'@importFrom> Rcpp evalCpp' 2) useDynLib in roxygen
