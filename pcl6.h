/* ================================================================
 * PCL6 Raster Output Interface for OpenRasterDriver
 * This header defines the minimal PCL XL constants and functions
 * for emitting raster data from a CUPS raster stream.
 * ================================================================ */

#ifndef PCL6_H
#define PCL6_H

#include <stdio.h>
#include <cups/raster.h>

/* ============================= */
/* Stream Header Identifiers     */
/* ============================= */
#define PCL_HEADER "( HP-PCL XL;2;0\r\n"

/* ============================= */
/* Operator Tags (1 byte each)   */
/* ============================= */
#define PCL_OP_BEGIN_SESSION       0x41
#define PCL_OP_END_SESSION         0x42
#define PCL_OP_BEGIN_PAGE          0x43
#define PCL_OP_END_PAGE            0x44

/* Raster Imaging */
#define PCL_OP_BEGIN_IMAGE         0xB0
#define PCL_OP_READ_IMAGE          0xB1
#define PCL_OP_END_IMAGE           0xB2

#define PCL_OP_BEGIN_SCAN          0xB6
#define PCL_OP_SCANLINE_REL        0xB9
#define PCL_OP_END_SCAN            0xB8

/* ============================= */
/* Attribute-ID Tag Prefixes     */
/* (indicate type of ID field)   */
/* ============================= */
#define PCL_ATTR_TAG_UBYTE		0xF8
#define PCL_ATTR_TAG_UINT16		0xF9
#define PCL_ATTR_TAG_UINT32		0xFA

/* ============================= */
/* Attribute IDs				 */
/* ============================= */
#define PCL_ATTR_MEASURE			0x86
#define PCL_ATTR_UNITS_PER_MEASURE	0x89
#define PCL_ATTR_MEDIA_SIZE			0x25
#define PCL_ATTR_ORIENTATION		0x28
#define PCL_ATTR_SOURCE_WIDTH		0x6C
#define PCL_ATTR_SOURCE_HEIGHT		0x6B
#define PCL_ATTR_COLOR_SPACE		0x03
#define PCL_ATTR_BITS_PER_PIXEL		0x62
#define PCL_ATTR_COMPRESSION		0x65
#define PCL_ATTR_ROP3				0x2C


/* ============================= */
/* Data-Type Tags				 */
/* ============================= */
#define PCL_DT_UBYTE			0x41
#define PCL_DT_UINT16			0x42
#define PCL_DT_UINT32			0x43
#define PCL_DT_SINT16			0x44
#define PCL_DT_SINT32			0x45
#define PCL_DT_REAL32			0x46
#define PCL_DT_UBYTE_XY			0x48
#define PCL_DT_UINT16_XY		0x49
#define PCL_DT_UINT32_XY		0x4A
#define PCL_DT_UBYTE_BOX		0x4B
#define PCL_DT_UINT16_BOX		0x4C
#define PCL_DT_UINT32_BOX		0x4D
#define PCL_DT_EMBEDDED_DATA	0xF8

/* ============================= */
/* Enumerations				     */
/* ============================= */

#define PCL_E_MEASURE_INCH		0x00
#define PCL_E_MEASURE_MM		0x01

#define PCL_E_ORIENT_PORTRAIT	0x00
#define PCL_E_ORIENT_LANDSCAPE	0x01

#define PCL_E_MEDIA_LETTER		0x01
#define PCL_E_MEDIA_A4			0x02

#define PCL_E_COLORSPACE_GRAY	0x03
#define PCL_E_COLORSPACE_RGB	0x04
#define PCL_E_COLORSPACE_CMYK   0x06

#define PCL_E_COMP_NONE			0x00
#define PCL_E_COMP_RLE			0x01
#define PCL_E_COMP_JPEG         0x02

#define PCL_ROP3_SRC			0xCC	/* Copy Source to Dest */
#define PCL_ROP3_BLACK			0x00
#define PCL_ROP3_WHITE			0xFF

#define PCL_LSB_FIRST			0x29	/* ')' - little-endian */
#define PCL_MSB_FIRST			0x28	/* '(' - big-endian */

void pcl6_start_job(FILE *out, cups_page_header2_t *header);
void pcl6_write_raster_line(FILE *out, const unsigned char *data, int bytes_per_line);
void pcl6_end_job(FILE *out);

#endif // PCL6_H


