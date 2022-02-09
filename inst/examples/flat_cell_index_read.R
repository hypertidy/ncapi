#f_l3m <- raadtools::sstfiles()$fullname[1000]
f_l3m <- "/rdsi/PUBLIC/raad/data/www.ncei.noaa.gov/data/sea-surface-temperature-optimum-interpolation/v2.1/access/avhrr/198405/oisst-avhrr-v02r01.19840527.nc"

#a <- raster::raster(f_l3m)
#library(raster)
#extent(a) <- extent(0, ncol(a), 0, nrow(a))
con <- Rnc_open(f_l3m)
a <- numeric(720 * 720)
cnt <- 1
for (i in 0:719) {
  for (j in 0:719) {
    start <- c(i, j, 0, 0)

    a[cnt] = ncapi:::Rnc_var_get1(con, 5L, start = rev(as.integer(start)))
cnt <- cnt + 1
  }
}



