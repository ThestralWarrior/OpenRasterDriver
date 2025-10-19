#ifndef PCL6_H
#define PCL6_H

#include <stdio.h>
#include <cups/raster.h>

void pcl6_start_job(FILE *out, cups_page_header2_t *header);
void pcl6_write_raster_line(FILE *out, const unsigned char *data, int bytes_per_line);
void pcl6_end_job(FILE *out);

#endif // PCL6_H

