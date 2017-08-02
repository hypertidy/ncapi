library(dplyr)

nc_data_types <- tibble::tibble(name = c("NC_BYTE", "NC_UBYTE", "NC_CHAR", "NC_SHORT", "NC_USHORT",
  "NC_INT", "NC_UINT", "NC_INT64", "NC_UINT64", "NC_FLOAT", "NC_DOUBLE", "NC_STRING")) %>%
  dplyr::mutate(id = row_number()  - 1)

devtools::use_data(nc_data_types)
