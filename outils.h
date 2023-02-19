#ifndef __OUTILS_H__
#define __OUTILS_H__

#include "image.h"

extern void outils_seuillage(unsigned int seuil, t_Image *img);
extern void outils_diference(t_Image *img1, t_Image *img2, t_Image *img3);
extern int outils_dilatation(t_Image *elem_struct, t_Image *img, t_Image *img_dil);
extern int outils_erosion(t_Image *elem_struct, t_Image *img, t_Image *img_err);
extern void outils_ouverture(t_Image *elem_struct, t_Image *img, t_Image *img_ouv);
extern void outils_fermeture(t_Image *elem_struct, t_Image *img, t_Image *img_fer);

#endif