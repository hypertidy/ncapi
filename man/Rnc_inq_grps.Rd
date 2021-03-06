% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/RcppExports.R
\name{Rnc_inq_grps}
\alias{Rnc_inq_grps}
\title{Inquire group IDs}
\usage{
Rnc_inq_grps(ncid)
}
\arguments{
\item{ncid}{file connection provided by `Rnc_open`}
}
\description{
Inquire group IDs
}
\examples{
f_l3b <- system.file("extdata", "oceandata", "S2008001.L3b_DAY_CHL.nc", package = "ncapi")
 con <- Rnc_open(f_l3b)
 Rnc_inq_grps(con)
 Rnc_close(con)
}
