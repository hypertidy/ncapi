ncmeta:::nc_meta.NetCDF
file <- raadfiles::oisst_daily_files()$fullname[1]
con <- Rnc_open(file)
## nc_dims
dims <- tibble::as_tibble(Rnc_inq_dimension(con))
## nc_varsdims
vars <- tibble::as_tibble(Rnc_inq_variable(con))
if (nrow(dims) > 0) dims$coord_dim <- dims$name %in% vars$name
if (nrow(vars) > 0) vars$dim_coord <- vars$ndims == 1L & vars$name %in% dims$name

## nc_atts

## nc_axes

## nc_grids


