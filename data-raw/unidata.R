u <- "https://www.unidata.ucar.edu/software/netcdf/examples/madis-hydro.nc"
curl::curl_download(u, file.path("extdata/inst/unidata", basename(u)), mode = "wb")

u1 <- "https://www.unidata.ucar.edu/software/netcdf/examples/test_hgroups.nc"
curl::curl_download(u1, file.path("extdata/inst/unidata", basename(u1)), mode = "wb")

u2 <- "https://oceandata.sci.gsfc.nasa.gov/cgi/getfile/S2008001.L3m_DAY_CHL_chlor_a_9km.nc"
u3 <- "https://oceandata.sci.gsfc.nasa.gov/cgi/getfile/S2008001.L3b_DAY_CHL.nc"
curl::curl_download(u2, file.path("extdata/inst/oceandata", basename(u2)), mode = "wb")
curl::curl_download(u3, file.path("extdata/inst/oceandata", basename(u3)), mode = "wb")



