using namespace std;

#include <stdio.h>
#include <string>
#include <iostream> //pour cout et cin
#include "image.h"
#include "chargesauve.h"
#include "outils.h"

int main()
{
    bool load;
    //pour l'outil de seuillage
    t_Image *lena = NULL;
    lena = new(t_Image);

    //pour l'outil de difference
    t_Image *plane = NULL;
    t_Image *paysage = NULL;
    t_Image *diff = NULL;
    plane = new(t_Image);
    paysage = new(t_Image);
    diff = new(t_Image);

    //Pour test érosion / dilatation
    t_Image *img_dil = NULL;
    img_dil = new(t_Image);
    t_Image *elem_struct = NULL;
    elem_struct = new(t_Image);
    t_Image *img_err = NULL;
    img_err = new(t_Image);

    //Pour test ouverture / fermeture d'une image
    t_Image *img_ouv = NULL;
    img_ouv = new(t_Image);
    t_Image *img_fer = NULL;
    img_fer = new(t_Image);
    t_Image *diff_ouv = NULL;
    diff_ouv = new(t_Image);
    t_Image *diff_fer = NULL;
    diff_fer = new(t_Image);

    loadPgm("img/elemstruct3x3.pgm", elem_struct, load);
    if (!load)
        return -1;

    loadPgm("img/lena512x512.pgm", lena, load);
    if (!load)
        return -1;
    loadPgm("img/plane512x512.pgm", plane, load);
    if (!load)
        return -2;
    loadPgm("img/paysage.pgm", paysage, load);
    if (!load)
        return -3;

    //tests seuil
    outils_seuillage(127, lena);
    savePgm("img_out/lena_seuillee.png", lena);

    //tests différence
    outils_diference(plane, plane, diff);
    savePgm("img_out/plane_diff_plane.png", diff);
    outils_diference(plane, paysage, diff);
    savePgm("img_out/plane_diff_paysage.png", diff);
    outils_diference(paysage, plane, diff);
    savePgm("img_out/paysage_diff_plane.png", diff);

    //tests dilatation
    outils_dilatation(elem_struct, lena, img_dil);
    savePgm("img_out/lena_dil.png", img_dil);

    //tests erosion
    outils_erosion(elem_struct, lena, img_err);
    savePgm("img_out/lena_err.png", img_err);

    //tests ouverture /fermeture
    outils_ouverture(elem_struct, lena, img_ouv);
    savePgm("img_out/lena_ouv.png", img_ouv);
    outils_fermeture(elem_struct, lena, img_fer);
    savePgm("img_out/lena_fer.png", img_fer);
    outils_diference(lena, img_ouv, diff_ouv);
    savePgm("img_out/diff_ouv.png", diff_ouv);
    outils_diference(lena, img_fer, diff_fer);
    savePgm("img_out/diff_fer.png", diff_fer);

    delete lena;
    delete plane;
    delete paysage;
    delete diff;
    delete img_dil;
    delete elem_struct;
    delete img_err;
    delete img_ouv;
    delete img_fer;
    delete diff_ouv;
    delete diff_fer;

    return 0;
}