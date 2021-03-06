/**********************************************************************
*   This file is part of Search and Rescue II (SaR2).                 *
*                                                                     *
*   SaR2 is free software: you can redistribute it and/or modify      *
*   it under the terms of the GNU General Public License v.2 as       *
*   published by the Free Software Foundation.                        *
*                                                                     *
*   SaR2 is distributed in the hope that it will be useful, but       *
*   WITHOUT ANY WARRANTY; without even the implied warranty of        *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See          *
*   the GNU General Public License for more details.                  *
*                                                                     *
*   You should have received a copy of the GNU General Public License *
*   along with SaR2.  If not, see <http://www.gnu.org/licenses/>.     *
***********************************************************************/

#include <stdlib.h>
#include <sys/types.h>

#include "v3dtex.h"
#include "obj.h"
#include "horizon.h"


v3d_texture_ref_struct *SARCreateHorizonTexture(
	const char *name,
	const sar_color_struct *start_color,	/* Top color */
	const sar_color_struct *end_color,	/* Bottom color */
	int height,				/* Width in pixels */
	float midpoint
);


#define ATOI(s)		(((s) != NULL) ? atoi(s) : 0)
#define ATOL(s)		(((s) != NULL) ? atol(s) : 0)
#define ATOF(s)		(((s) != NULL) ? atof(s) : 0.0f)
#define STRDUP(s)	(((s) != NULL) ? strdup(s) : NULL)

#define MAX(a,b)	(((a) > (b)) ? (a) : (b))
#define MIN(a,b)	(((a) < (b)) ? (a) : (b))
#define CLIP(a,l,h)	(MIN(MAX((a),(l)),(h)))
#define STRLEN(s)	(((s) != NULL) ? strlen(s) : 0)
#define STRISEMPTY(s)	(((s) != NULL) ? (*(s) == '\0') : 1)

#define RADTODEG(r)	((r) * 180.0 / PI)
#define DEGTORAD(d)	((d) * PI / 180.0)


/*
 *	Returns a 1D gradient horizon texture generated by the
 *	given colors.
 */
v3d_texture_ref_struct *SARCreateHorizonTexture(
	const char *name,
	const sar_color_struct *start_color,	/* Top color */
	const sar_color_struct *end_color,	/* Bottom color */
	int height,				/* Width in pixels */
	float midpoint
)
{
	int y, y_midpoint;
	float dr, dg, db;
	int bits_per_pixel = 32;
	u_int8_t *data;
	v3d_texture_ref_struct *t;
	u_int8_t r, g, b;
	u_int8_t *ptr8;


	if((start_color == NULL) || (end_color == NULL) ||
           (height <= 0)
	)
	    return(NULL);

	/* Allocate tempory image data that will be rendered and used
	 * to create the texture
	 *
	 * Note that we are allocating more bytes since the data passed
	 * for creation is only 24 bits (3 bytes)
	 */
	data = (u_int8_t *)malloc(
            height * (bits_per_pixel >> 3)
        );


	/* Render the image */
	y_midpoint = (int)MIN(midpoint * height, height - 1);
	dr = end_color->r - start_color->r;	/* Color delta coeffs */
        dg = end_color->g - start_color->g;
        db = end_color->b - start_color->b;
	switch(bits_per_pixel)
	{
	  case 32:
	    ptr8 = (u_int8_t *)(&data[0]);
	    for(y = 0; y < height; y++)
	    {
		if(y < y_midpoint)
		{
		    float coeff = (float)((y_midpoint > 0) ?
			(float)y / (float)y_midpoint : 0.0
		    );

		    r = (u_int8_t)CLIP(
			(start_color->r + (dr / 2 * coeff)) *
			0xff, 0x00, 0xff
		    );
                    g = (u_int8_t)CLIP(
                        (start_color->g + (dg / 2 * coeff)) *
                        0xff, 0x00, 0xff
                    );
                    b = (u_int8_t)CLIP(
                        (start_color->b + (db / 2 * coeff)) *
                        0xff, 0x00, 0xff
                    );
		}
		else
		{
                    float coeff = (float)(((height - y_midpoint) > 0) ?
                        (float)(y - y_midpoint) / 
			(float)(height - y_midpoint) :
			1.0
                    );

                    r = (u_int8_t)CLIP(
			(start_color->r + (dr / 2) + (dr / 2 * coeff)) *
			0xff, 0x00, 0xff
		    );
                    g = (u_int8_t)CLIP(
			(start_color->g + (dg / 2) + (dg / 2 * coeff)) *
			0xff, 0x00, 0xff
                    );
                    b = (u_int8_t)CLIP(
			(start_color->b + (db / 2) + (db / 2 * coeff)) *
			0xff, 0x00, 0xff
                    );
		}

		*ptr8++ = r;
		*ptr8++ = g;
                *ptr8++ = b;
	    }
	    break;
	}

	/* Create texture from image data */
	t = V3DTextureLoadFromData1D(
	    data, name,
	    height,
	    bits_per_pixel,
	    V3D_TEX_FORMAT_RGB,
	    NULL, NULL
	);
	V3DTexturePriority(t, 0.98f);

	/* Delete the tempory image data */
	free(data);

	return(t);
}
