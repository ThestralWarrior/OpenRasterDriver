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
#define PCL_HEADER ") HP-PCL XL;2;0\r\n"

/* ============================= */
/* Operator Tags (1 byte each)   */
/* ============================= */
#define PCL_OP_BEGIN_SESSION       0x41
#define PCL_OP_END_SESSION         0x42
#define PCL_OP_BEGIN_PAGE          0x43
#define PCL_OP_END_PAGE            0x44

#define PCL_OP_BEGIN_IMAGE         0xB0
#define PCL_OP_READ_IMAGE          0xB1
#define PCL_OP_END_IMAGE           0xB2

#define PCL_OP_BEGIN_SCAN          0xB6
#define PCL_OP_SCANLINE_REL        0xB9
#define PCL_OP_END_SCAN            0xB8

#define PCL_OP_OPEN_DATA_SRC	   0x48
#define PCL_OP_CLOSE_DATA_SRC	   0x49

#define PCL_OP_SET_CURSOR		   0x6B

/* ============================= */
/* Attribute-ID Tag Prefixes     */
/* (indicate type of ID field)   */
/* ============================= */
#define PCL_ATTR_TAG_UBYTE		0xF8
#define PCL_ATTR_TAG_UINT16		0xF9

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
#define PCL_ATTR_COMPRESSION		0x65
#define PCL_ATTR_ROP3				0x2C
#define PCL_ATTR_COLOR_MAPPING		0x64
#define PCL_ATTR_COLOR_DEPTH		0x62
#define PCL_ATTR_DESTINATION_SIZE	0x67
#define PCL_ATTR_START_LINE			0x6D
#define PCL_ATTR_BLOCK_HEIGHT		0x63
#define PCL_ATTR_ERROR_REPORT		0x8F
#define PCL_ATTR_PAD_BYTES_MULTIPLE	0x6E
#define PCL_ATTR_SOURCE_TYPE		0x88
#define PCL_ATTR_DATAORG			0x82
#define PCL_ATTR_POINT				0x4C

/* ============================= */
/* Data-Type Tags				 */
/* ============================= */
#define PCL_DT_UBYTE				0xC0
#define PCL_DT_UINT16				0xC1
#define PCL_DT_UINT32				0xC2
#define PCL_DT_SINT16				0xC3
#define PCL_DT_SINT32				0xC4
#define PCL_DT_REAL32				0xC5
#define PCL_DT_UBYTE_XY				0xD0
#define PCL_DT_UINT16_XY			0xD1
#define PCL_DT_UINT32_XY			0xD2
#define PCL_DT_EMBEDDED_DATA		0xFA
#define PCL_DT_EMBEDDED_DATA_BYTE	0xFB

/* ============================= */
/* Enumerations				     */
/* ============================= */

#define PCL_E_MEASURE_INCH		0x00
#define PCL_E_MEASURE_MM		0x01

#define PCL_E_ORIENT_PORTRAIT	0x00
#define PCL_E_ORIENT_LANDSCAPE	0x01

#define PCL_E_MEDIA_LEGAL		0x01
#define PCL_E_MEDIA_A4			0x02

#define PCL_E_COLORSPACE_GRAY	0x01
#define PCL_E_COLORSPACE_RGB	0x02

#define PCL_E_COMP_NONE			0x00
#define PCL_E_COMP_RLE			0x01
#define PCL_E_COMP_JPEG         0x02

#define PCL_E_DIRECT_PIXEL		0x00
#define PCL_E_INDEXED_PIXEL		0x01

#define PCL_E_1BIT				0x00
#define PCL_E_4BIT				0x01
#define PCL_E_8BIT				0x02

#define PCL_E_NO_REPORTING			0x00
#define PCL_E_BACK_CH				0x01
#define PCL_E_ERR_PAGE				0x02
#define PCL_E_BACK_CH_ERR_PAGE		0x03
#define PCL_E_NW_BACK_CH			0x04
#define PCL_E_NW_ERR_PAGE			0x05
#define PCL_E_NW_BACK_CH_ERR_PAGE	0x06

#define PCL_E_DEFAULT_SOURCE		0x00

#define PCL_E_BINARY_HIGH_BYTE_FIRST	0x00
#define PCL_E_BINARY_LOW_BYTE_FIRST		0x01

#define PCL_ROP3_SRC			0xCC	/* Copy Source to Dest */
#define PCL_ROP3_BLACK			0x00
#define PCL_ROP3_WHITE			0xFF

#define PCL_LSB_FIRST			0x29	/* ')' - little-endian */
#define PCL_MSB_FIRST			0x28	/* '(' - big-endian */

void pcl6_start_session(FILE *out, cups_page_header2_t *header);
void pcl6_start_job(FILE *out, cups_page_header2_t *header);
void pcl6_write_raster_line(FILE *out, const unsigned char *data, int bytes_per_line, unsigned int y);
void pcl6_end_job(FILE *out);
void pcl6_end_session(FILE *out);

#endif // PCL6_H


